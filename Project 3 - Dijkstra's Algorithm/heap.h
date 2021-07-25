// Andrew Lorber
// DSA II Project 3 - Dijkstra's Algorithm
// Heap Class Header File

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap {

public:

    // Constructor
    // Allocates space for nodes of heap and mapping based on specified capacity
    heap(int capacity);

    // Inserts a node with the specified id string, key, (pointer).
    // Returns:
    //      0 - Success
    //      1 - Heap already filled
    //      2 - ID already taken 
    int insert(const std::string &id, int key, void *pv = nullptr);

    // Sets the key of the specified node to the specified value
    // Returns:
    //      0 - Success
    //      1 - ID doesn't exist
    int setKey(const std::string &id, int key);

    // Returns data of smallest node & deletes it
    // Writes:
    //      Node ID --> pId
    //      Node key --> pKey
    //      Node void pointer --> ppData
    // Returns:
    //      0 - Success
    //      1 - Heap is empty
    int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);


    // Deletes node with specified ID
    // Writes:
    //      Node key --> pKey
    //      Node void pointer --> ppData
    // Returns:
    //      0 - Success
    //      1 - ID doesn't exist
    int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);


private:
    // Node Class
    class node {
        public:
        std::string id; // Node ID
        int key;        // Node key
        void *pData;    // Pointer to node data
    };

    std::vector<node> data; // Binary Heap
    hashTable *mapping;     // Hash Table to map IDs to pointers
    int capacity;
    int current_size;


    // Implements percolate up & down for Binary Heap
    void percolateUp(int posCur);
    void percolateDown(int posCur);
    // Gets position of node
    int getPos(node *pn);
};

#endif //_HEAP_H