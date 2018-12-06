import rk4
import time
import math

if __name__ == '__main__':
    # v^2/r = GM/r^2
    # Solve for v to get circular motion

    # rk4.sys_init() sets the dynamical equations defined in the rk4 library
    # modification of the model can be done in rk4.cpp
    rk4.sys_init()

    # Gravitational Constant
    G = 6.67408e-11

    # Mass of Earth
    M = 5.972e24

    # Radius from center of earth
    rad = 8000000

    # Calculate velocity for circular orbit
    vel = math.sqrt(G*M/rad)

    # Calculate time to complete a revolution
    orbital_period = 2 * math.pi * rad / vel

    # Set change in time between iterations of simulation
    time_step = 10

    # Generate a list of state vectors of the form:
    # (x, dx/dt, y, dy/dt, z, dz/dt)
    s = rk4.iterate_range(time_step, 0, orbital_period, rad, 0, 0, vel, 0, 0)

    # Save results to file for displaying in MATLAB, because I don't know
    # how to keep axes from auto-scaling in matplotlib
    fp = open("results.txt", "w")

    for r in s:
        fp.write("%f %f %f\n" % (r[0], r[2], r[4]))
