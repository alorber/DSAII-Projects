## Project 3 - Dijkstra's Algorithm

The goal of this project was to use the the hash table and binary heap developed in projects 1 & 2 in order to implement Dijkstra's algorithm 
to solve the single-source shortest-path problem.

The program begins by asking the user to enter the name of a file specifying the graph.
Every row in the input file contains two string ids representing the source vertex and destination vertex of an edge in the graph followed by an
integer representing the cost (a.k.a. distance or weight) of that edge. Once the program is finished reading in the graph, the user is then 
prompted to enter the id of a starting vertex. The program then applies Dijkstra's algorithm to determine the shortest path to each node 
from the specified starting vertex. When the algorithm has finished determining the shortest path to each node, the program outputs the CPU 
time, in seconds, that was spent executing the algorithm. The program then asks the user for the name of an output file, which the results 
will be printed to.
