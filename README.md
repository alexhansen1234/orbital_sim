# Orbital Network Simulation

Dynamics modeled in C++

Wrapped with SWIG

Scripted in Python3

Network Analysis using networkx

To build:

    cd build
    cmake .. && make
    python3 orbital_sim_impl.py

Results can be viewed using MATLAB by running 'orbital_sim_plot.m'

(I'll write up a script to view results in Matplotlib, when I have more time.)

Dependencies:

    Python:
        pickle
        numpy
        networkx
        pygraphviz


