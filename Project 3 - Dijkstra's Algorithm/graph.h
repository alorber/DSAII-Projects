// Andrew Lorber
// DSA II Project 3 - Dijkstra's Algorithm
// Graph Class Header File

#ifndef _GRAPH_H
#define _GRAPH_H

#include <list>
#include <fstream>
#include <string>
#include "hash.h"

class graph {

public:
    // Constructor
    graph();

    // Checks if graph contains node
    bool contains(std::string &node);

    // Builds graph from file 
    void buildGraph(std::ifstream &infile);

    // Implements Dijkstra's Algorithm
    void dijkstra(std::string &startNodeID);

    // Prints to the output file the shortest path to each node
    void printToFile(std::ofstream &outfile);

private:
    class edge;

    // Class for node / vertex
    class node {
    public:
        // Parameters
        std::string id;
        std::list<edge*> adjacencyList;
        // Parameters for Dijktra's Algorith,
        bool visited = false;
        int distance = INT_MAX;   // Distance from vertex
        node* prevNode = nullptr;
    };

    // Class for edge
    class edge {
    public:
        // Constructor
        edge(int cost, node* dest) : cost{cost}, destNode{dest} {}
        // Parameters
        int cost;
        node* destNode;
    };

    // List of nodes in graph
    std::list<node*> nodeList;
    // Hash Table for tracking vertices
    // nodeID <-> node*
    hashTable* knownNodes;


};

#endif //_GRAPH_H