// Andrew Lorber
// DSA II Project 3 - Dijkstra's Algorithm
// Main Driver Program

#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"


int main(int argc, char* argv[]) {
    // Opens input file
    std::string file;
    std::ifstream infile;

    do {
        std::cout << "Please enter the input file.\n";
        std::cin >> file;
        infile.open(file);
    } while(!infile.is_open());

    // Builds graph
    graph* g = new graph;
    g->buildGraph(infile);

    // Closes file
    infile.close();
    
    // Gets starting node
    std::string startNode;
    do {
        std::cout << "Please enter the ID of the starting node.\n";
        std::cin >> startNode;
    } while(!(g->contains(startNode)));

    // Runs Dijkstra's Algorithm
    clock_t start = clock();
    g->dijkstra(startNode);
    clock_t end = clock();
    
    // Calculates & prints running time
    std::cout << "Dijkstra's algorithm took " << ((double)(end - start)) / CLOCKS_PER_SEC << " seconds.\n";

    // Opens output file
    std::ofstream outfile;

    do {
        std::cout << "Please enter the output file.\n";
        std::cin >> file;
        outfile.open(file);
    } while(!outfile.is_open());

    // Prints paths to output file
    g->printToFile(outfile);

    // Closes file
    outfile.close();
}


