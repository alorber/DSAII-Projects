// Andrew Lorber
// DSA II Project 2 - Priority Queue
// Hash Table Class

#include "hash.h"
#include <algorithm>
#include <iostream>

// Public Member Functions
// ------------------------

// Constructor
hashTable::hashTable(int size) {
    capacity = hashTable::getPrime(size);
    filled = 0;
    data.resize(capacity);
}

// Inserts key into hash table
int hashTable::insert(const std::string &key, void *pv) {
    // Checks if key already exists
    if(findPos(key) != -1) {
        return 1;
    }

    // Checks if vector needs to be made bigger
    if(filled * 2 > capacity && !rehash()) {
        return 2;
    }

    // Gets hash value (using linear probing)
    int pos = hash(key);
    while(data.at(pos).isOccupied && !data.at(pos).isDeleted) {
        pos = (pos + 1) % capacity;
    }

    // Updates fillled count
    if(!data.at(pos).isOccupied) {
        filled++;
    }

    // Inserts new key and ptr
    data.at(pos).key = key;
    data.at(pos).isOccupied = true;
    data.at(pos).isDeleted = false;
    data.at(pos).pv = pv;

    return 0;
}

// Checks if key is in hash table
bool hashTable::contains(const std::string &key) {
    return (findPos(key) >= 0);
}

// Gets pointer associated with the specified key
void* hashTable::getPointer(const std::string &key, bool *b) {
    // Checks if key exists
    if(!contains(key)) {
        if(b) { *b = false; }
        return nullptr;
    } else {
        if(b) { *b = true; }
        return data.at(findPos(key)).pv;
    }
}

// Sets pointer associated with the specified key
int hashTable::setPointer(const std::string &key, void *pv) {
    // Checks if key exists
    if(!contains(key)) {
        return 1;
    } else {
        data.at(findPos(key)).pv = pv;
        return 0;
    }
}

// (Lazy) Deletes item with specified key (if in hash table)
bool hashTable::remove(const std::string &key) {
    int pos = findPos(key);

    if(pos == -1) {
        return false;
    } else {
        data.at(pos).isDeleted = true;
        return true;
    }
}

// Private Member Functions
// ------------------------

// Hash function (from textbook)
int hashTable::hash(const std::string &key) {
    int hash_value = 0;

    for(int i = 0; i < key.length(); i++) {
        hash_value = 37 * hash_value + key[i];
    }

    hash_value %= capacity;
    if(hash_value < 0) {
        hash_value += capacity;
    }

    return hash_value;
}

// Finds position of key in hash table
int hashTable::findPos(const std::string &key) {
    // Gets hash value for key
    int hash_value = hash(key);

    // Checks index in hash table and moves right until finds empty spot, key, or overlaps
    int pos = hash_value;
    while(data.at(pos).isOccupied) {
        if(data.at(pos).key == key && !data.at(pos).isDeleted) {
            return pos;
        } else {
            pos = (pos + 1) % capacity;
            if(pos == hash_value) {
                return -1;
            }
        }
    }
    return -1;
}

// Rehashes the hash table to a bigger size
bool hashTable::rehash() {
    // Creates new (temporary) hash table
    std::vector<hashItem> old_table = data;

    // Resets hash table
    for (int i = 0; i < capacity; i++) {
        data.at(i).key = "";
        data.at(i).isOccupied = false;
        data.at(i).isDeleted = false;
        data.at(i).pv = nullptr;
    }

    // Resizes hash table (catching errors)
    try {
        data.resize(getPrime(capacity));
    } catch(const std::bad_alloc){
        return false;
    }
    
    // Resets class variable
    capacity = data.size();
    filled = 0;

    // Copies data over
    for(hashItem item : old_table) {
        if(item.isOccupied && !item.isDeleted) {
            insert(item.key, item.pv);
        }
    }

    return true;
}

// Returns a prime number greater than size
unsigned int hashTable::getPrime(int size) {
    unsigned int primes[] = {41011, 83003, 166567, 333631, 668033, 1336729, 2673857, 5347729, 10696073};

    for(unsigned int n : primes) {
        if(n > size) {
            return n;
        }
    }

    return primes[8];
}

