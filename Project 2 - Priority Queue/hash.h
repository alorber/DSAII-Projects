// Andrew Lorber
// DSA II Project 2 - Priority Queue
// Hash Table Class Header File

#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <string>

class hashTable {

public:
    // Constructor
    // Initializes Hash Table with specified size
    hashTable(int size = 0);

    // Inserts specified key & pointer into Hash Table
    // Returns:
    //      0 - Success
    //      1 - Key already exists
    //      2 - Rehash fails
    int insert(const std::string &key, void *pv = nullptr);

    // Checks if specified key is in Hash Table.
    bool contains(const std::string &key);

    // Gets pointer associated with the specified key
    // Writes:
    //      bool exists --> b
    // Returns:
    //      pointer - Key exists
    //      nullptr - Key doesn't exist
    void *getPointer(const std::string &key, bool *b = nullptr);

    // Sets pointer associated with the specified key
    // Returns:
    //      0 - Success
    //      1 - Key Doesn't exist
    int setPointer(const std::string &key, void *pv);

    // Deletes item with the specified key
    // Returns:
    //      true - Success
    //      false - Key does not exist
    bool remove(const std::string &key);

private:

    // Hash Item Class
    class hashItem {
    public:
        std::string key {""};   // Hash key
        bool isOccupied {false};
        bool isDeleted {false}; // Lazy deletion
        void *pv {nullptr};     // Pointer realted to key

        hashItem() = default;
    };

    int capacity; // Capacity of Hash Table
    int filled;   // Number of occupied items

    std::vector<hashItem> data; // Vector of hash items

    // The hash function
    int hash(const std::string &key);

    // Searches for an item with specified key
    // Returns: 
    //      Position - Key is found
    //      -1 - Not found
    int findPos(const std::string &key);

    // The rehash function; makes the hash table bigger
    // Returns:
    //      true - Success
    //      false - Memory allocation failed
    bool rehash();

    // Returns prime number at least as large as size
    static unsigned int getPrime(int size);
};

#endif //_HASH_H
