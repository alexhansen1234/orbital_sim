import orbital_sim as os
import os as filesys
import numpy.random as random
import math
import networkx as nx
import itertools
import pygraphviz
import pickle
from networkx.drawing.nx_agraph import graphviz_layout, to_agraph

def proj(u, v):
    """Returns the orthogonal projection of u onto v.
        u and v are both purely imaginary quaternions."""
    return v.vector() * (u.x * v.x + u.y * v.y + u.z * v.z) / (v.x * v.x + v.y * v.y + v.z * v.z)

def dist(u, v):
    return (u.get_position() - v.get_position()).mag()

if __name__ == '__main__':

    # Initialize system solver
    os.sys_init()

    # Generating route table takes some time, but
    # lists all paths from node x to y
    generate_route_table = False

    # Time per simulation iteration in seconds
    simulation_delta_t = 60

    # Total simulation time
    simulation_time = 60 * 60 * 24 * 2

    # Number of satellites per orbital plane
    sat_per_orbit = 20

    # Number of orbital planes per simulation
    orbit_per_sim = 2

    # Set radius of satellites from center of earth
    orbit_radius = 8000000

    # Set range of random values for generating random orbit axes (is a tuple)
    rand_range = (-1, 1)

    # Set time step for generating new routing table
    min_table_update_time = 3600

    # Set maximum distance for establishing a link
    # Because this simulation is highly symmetric in distribtion, calculate
    # lenght of chord of regular n-gon where n is number of satellites
    # per orbit and use this as a rough max + 1%
    link_distance_threshold = 1.01 * math.sqrt(2 * orbit_radius**2 * (1 - math.cos(math.radians(360/sat_per_orbit))))

    # Circular orbit
    orbital_velocity = math.sqrt(os.G * os.M / orbit_radius)

    # Radius of earth
    ground_station_radius = 6371000

    # Angular velocity of point rotating with earth
    ground_station_angular_velocity = 360 / 24 / 60 / 60

    ground_station_rotation_quat = os.quatd_rotation(ground_station_angular_velocity * simulation_delta_t, 0, 0, 1)

    groundstation_list = []

    # Place two ground stations, on opposite sides of the planet
    groundstation_list.append(os.Satellite( os.quatd(0, ground_station_radius, 0, 0), os.quatd()))
    groundstation_list.append(os.Satellite( os.quatd(0,-ground_station_radius, 0, 0), os.quatd()))

    satellite_list = []

    for i in range(0, orbit_per_sim):
        axis = os.quatd_rotation(360/sat_per_orbit, random.uniform(*rand_range), random.uniform(*rand_range), random.uniform(*rand_range));
        velocity_rotation = os.quatd_rotation(90, axis.x, axis.y, axis.z)
        rando = os.quatd(0, random.uniform(*rand_range), random.uniform(*rand_range), random.uniform(*rand_range))
        position = rando - proj(rando, axis)
        position = position / position.mag() * orbit_radius
        for j in range(0, sat_per_orbit):
            velocity = velocity_rotation * position * ~velocity_rotation
            velocity = velocity / velocity.mag() * orbital_velocity
            satellite_list.append(os.Satellite(position, velocity))
            position = axis * position * ~axis

    time_accumulator = 0

    t_epsilon = 1e-3

    graph_id_label_width = len(str(math.floor(simulation_time / min_table_update_time)))

    time_slice_counter = 0

    try:
        filesys.stat("results")
    except:
        filesys.mkdir("results")
    try:
        filesys.stat("results/graphs")
    except:
        filesys.mkdir("results/graphs")
    try:
        filesys.stat("results/routes")
    except:
        filesys.mkdir("results/routes")
    try:
        filesys.stat("results/trajectory")
    except:
        filesys.mkdir("results/trajectory")
    try:
        filesys.stat("results/random")
    except:
        filesys.mkdir("results/random")

    fp1 = open("results/trajectory/satellites.txt", "w")
    fp2 = open("results/trajectory/groundstation.txt", "w")

    if(generate_route_table):
        fp3 = open("results/routes/route_table.txt", "w")
        fp4 = open("results/routes/route_table_dump.txt", "wb")

    # Save PRNG state for reproducing a simulations results
    fp5 = open("results/random/rng_state.txt", "wb")
    prng = random.RandomState()
    saved = prng.get_state()
    pickle.dump(saved, fp5)

    if(generate_route_table):
        route_table = {}

    for k in range(0, simulation_time // simulation_delta_t):
        for i in satellite_list:
            i.time_step(simulation_delta_t)
            fp1.write("%f %f %f " % (i.get_position().x, i.get_position().y, i.get_position().z))
        fp1.write("\n")

        for i in groundstation_list:
            fp2.write("%f %f %f " % (i.get_position().x, i.get_position().y, i.get_position().z))
            i.set_position(ground_station_rotation_quat * i.get_position() * ~ground_station_rotation_quat)
        fp2.write("\n")

        if(time_accumulator < t_epsilon):
            G = nx.Graph()

            for x in groundstation_list:
                G.add_node(x.get_id(), color = "green")

            for x in satellite_list:
                G.add_node(x.get_id(), color = "red")

            for x in itertools.combinations(satellite_list + groundstation_list, 2):
                id0 = x[0].get_id()
                id1 = x[1].get_id()

                if(dist(*x) < link_distance_threshold):
                    G.add_edge(id0, id1)

            if(generate_route_table and ( not route_table.get((time_slice_counter,(id0, id1))) or not route_table.get((time_slice_counter,(id1, id0))))):
                route_table[(time_slice_counter, (id0, id1))] = list(nx.all_simple_paths(G, source=id0, target=id1))
                route_table[(time_slice_counter, (id1, id0))] = route_table[(time_slice_counter, (id0, id1))]
                fp3.write("%d (%d <-> %d) :" % (time_slice_counter, id0, id1))
                fp3.write(str(route_table[(time_slice_counter, (id0,id1))]))
                fp3.write("\n")

            A = to_agraph(G)
            A.layout("neato", args="-Goverlap=false -Gsplines=true")
            s = "results/graphs/graph_" + str(time_slice_counter).zfill(graph_id_label_width) + ".png"

            A.draw(s)
            time_slice_counter += 1



        time_accumulator += simulation_delta_t

        if(time_accumulator >= min_table_update_time):
            time_accumulator = 0

    if(generate_route_table):
        pickle.dump(route_table, fp4)
