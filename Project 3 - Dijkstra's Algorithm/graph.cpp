// Andrew Lorber
// DSA II Project 3 - Dijkstra's Algorithm
// Graph Class

#include <fstream>
#include <string>
#include <list>
#include "graph.h"
#include "heap.h"

// Public Member Functions
// ------------------------

// Constructor
graph::graph() {
    // Creates Hash Table
    knownNodes = new hashTable(100000);
}

// Checks if graph contains node
bool graph::contains(std::string &node) {
    return knownNodes->contains(node);
}

// Builds graph from file
void graph::buildGraph(std::ifstream &infile) {
    // Gets line from file
    std::string srcNodeID, destNodeID;
    int cost;
    while(infile >> srcNodeID >> destNodeID >> cost) {
        node* srcNode;
        node* destNode;

        // Checks if source node exists
        if(knownNodes->contains(srcNodeID)) {
            srcNode = (node*)knownNodes->getPointer(srcNodeID);
        } else {
            srcNode = new node;
            srcNode->id = srcNodeID;
            
            // Adds node to list
            nodeList.push_back(srcNode);
            // Adds node to Hash Table
            knownNodes->insert(srcNodeID, srcNode);
        }

        // Checks if destination node exists
        if(knownNodes->contains(destNodeID)) {
            destNode = (node*)knownNodes->getPointer(destNodeID);
        } else {
            destNode = new node;
            destNode->id = destNodeID;

            // Adds node to list
            nodeList.push_back(destNode);
            // Adds node to Hash Table
            knownNodes->insert(destNodeID, destNode);
        }
    
        // Inserts new edge into adjacency list
        edge* e = new edge(cost, destNode);
        srcNode->adjacencyList.push_back(e);
    }
}

// Implements Dijkstra's Algorithm
void graph::dijkstra(std::string &startNodeID) {
    // Creates heap & adds nodes
    heap* nodes = new heap(nodeList.size());
    for(auto n : nodeList) {
        if((n->id).compare(startNodeID) == 0) {
            n->distance = 0;
        }
        nodes->insert(n->id, n->distance, n);
    }

    // Variables to hold node information
    int currDist;
    node* currNode;

    // Loops until heap is empty
    while(nodes->deleteMin(nullptr, &currDist, &currNode) == 0) {
        // Marks node as visited
        currNode->visited = true;

        // If node is unreachable, skip
        if(currDist == INT_MAX) { continue; }

        // Loops through adjacent nodes
        for(auto e : currNode->adjacencyList) {
            // Checks if shorter path is found
            if(!(e->destNode->visited)
                && currDist + e->cost < e->destNode->distance) {
                    // Updates distance
                    e->destNode->distance = currDist + e->cost;
                    e->destNode->prevNode = currNode;
                    nodes->setKey(e->destNode->id, e->destNode->distance);
            }
        }
    }
}

// Prints to the output file the shortest path to each node
void graph::printToFile(std::ofstream &outfile) {
    // Loops through nodes
    for(auto n : nodeList) {
        outfile << n->id << ": ";

        // Check for unreachable node
        if(n->distance == INT_MAX) {
            outfile << "NO PATH\n";
        } else {
            // Builds path
            std::string path = n->id;
            for(auto p = n->prevNode; p != nullptr; p = p->prevNode) {
                path = p->id + ", " + path;
            }

            // Outputs path to file
            outfile << n->distance << " [" << path << "]\n";
        }
    }
}