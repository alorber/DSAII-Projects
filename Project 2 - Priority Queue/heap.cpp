// Andrew Lorber
// DSA II Project 2 - Priority Queue
// Heap Class

#include "heap.h"
#include <vector>

// Public Member Functions
// ------------------------

// Constructor
heap::heap(int capacity) {
    // Resizes vector for binary heap
    data.resize(capacity + 1);
    mapping = new hashTable(capacity * 2);
    this->capacity = capacity;
    current_size = 0;
}

// Inserts a node with the specified id string, key, (pointer).
int heap::insert(const std::string &id, int key, void *pv) {
    // Checks if Binary Heap is full
    if(current_size >= capacity) {
        return 1;
    }
    // Checks if ID is already taken
    else if(mapping->contains(id)) {
        return 2;
    }
    // Inserts into Binary Heap
    else {
        // Creates new node
        node newNode;
        newNode.id = id;
        newNode.key = key;
        newNode.pData = pv;

        // Adds node to Binary Heap & Hash Table and percolates up
        data.at(++current_size) = newNode;
        mapping->insert(id, &data[current_size]);
        percolateUp(current_size);
        return 0;
    }
}

// Sets the key of the specified node to the specified value
int heap::setKey(const std::string &id, int key) {
    // Checks if ID exists
    if(!(mapping->contains(id))) {
        return 1;
    }
    // Sets key
    else {
        // Gets old key & updates key
        node *n =  static_cast<node*>(mapping->getPointer(id));
        int old_key = n->key;
        n->key = key;

        // Percolates
        if(key < old_key) {
            percolateUp(getPos(n));
        } else if(key > old_key) {
            percolateDown(getPos(n));
        }
        return 0;
    }
}

// Returns data of smallest node & deletes it
int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    // Checks if heap is empty
    if(current_size == 0) {
        return 1;
    } else {
        // Sets pointers
        if(pId) { *pId = data.at(1).id; }
        if(pKey) { *pKey = data.at(1).key; }
        if(ppData) { *(static_cast<void **>(ppData)) = data[1].pData; }

        // Removes node from Hash Table
        mapping->remove(data.at(1).id);

        // Moves last node to root and percolates down 
        data.at(1) = data.at(current_size--);
        percolateDown(1);

        return 0;
    }
}

// Deletes node with specified ID
int heap::remove(const std::string &id, int *pKey, void *ppData) {
    // Checks if ID exists
    if(!(mapping->contains(id))) {
        return 1;
    } else {
        // Finds node with given ID
        node *n =  static_cast<node*>(mapping->getPointer(id));

        // Stores key
        if(pKey) { *pKey = n->key; }

        // Sets key to root - 1 & deletes min
        setKey(id, data.at(1).key - 1);
        deleteMin(nullptr, nullptr, ppData);

        return 0;
    }
}

// Private Member Functions
// ------------------------

// Percolate node at given position up until correct position
void heap::percolateUp(int posCur) {
    // Stores node
    data.at(0) = data.at(posCur);

    // Percolates the hole up
    for(int key = data.at(0).key; key < data.at(posCur / 2).key; posCur /= 2) {
        data.at(posCur) = data.at(posCur / 2);
        mapping->setPointer(data.at(posCur).id, &(data.at(posCur)));
    }
    // Fills hole with stored node
    data.at(posCur) = data.at(0);
    mapping->setPointer(data.at(posCur).id, &(data.at(posCur)));
}

// Percolate node at given position down until correct position
void heap::percolateDown(int posCur) {
    // Stores node
    data.at(0) = data.at(posCur);

    for(int key = data.at(0).key, smallest_child; posCur * 2 <= current_size; posCur = smallest_child) {
        // Finds smallest child node
        smallest_child = posCur * 2;
        if(smallest_child + 1 <= current_size && 
                data.at(smallest_child + 1).key < data.at(smallest_child).key) {
            smallest_child += 1;
        }

        // Checks if key is larger than child key
        if(key > data.at(smallest_child).key) {
            // Percolate hole down
            data.at(posCur) = data.at(smallest_child);
            mapping->setPointer(data.at(posCur).id, &(data.at(posCur)));
        } else {
            break;
        }
    }
    data.at(posCur) = data.at(0);
    mapping->setPointer(data.at(posCur).id, &(data.at(posCur)));
}

// Gets position of given node in vector
int heap::getPos(node *pn) {
    return (pn - &(data.at(0)));
}
