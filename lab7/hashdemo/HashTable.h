// EECS 281, Dr. David Paoletti

// A generic hash table, meant to mimic some of the behavior of the STL
// map container, but backed by a hash table using chained collision resolution.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedHashList.h"


// The HashTable template needs three types:
//  1) The key type used as the 'index' into the map
//  2) The value type associated with the key
//  3) A functor providing a mapping from the key type onto unsigned int
//     (the hash function)
template <class KEYTYPE, class VALUETYPE, class HASHTYPE>
class HashTable {
private:
    static const unsigned int TABLE_SIZE = 251;
    LinkedHashList<KEYTYPE, VALUETYPE> table[TABLE_SIZE];
    HASHTYPE hasher;

public:
    // Note that there is no destructor here.  In C++ when you have an array of
    // some type, each element of the array is destroyed when the array itself
    // is destroyed, calling the linked list destructor for each linked list in
    // the array.

    // Add the key/value pair to the container
    void add(const KEYTYPE &key, const VALUETYPE &value) {
        unsigned int addr = hasher(key) % TABLE_SIZE;

        table[addr].add(key, value);
    } // add()


    // Remove the selected key from the container
    void remove(const KEYTYPE &key) {
        unsigned int addr = hasher(key) % TABLE_SIZE;

        table[addr].remove(key);
    } // remove()


    // Get the value associated with the given key.  Note that the underlying
    // linked list will automatically add it with a default constructed element
    // if it does not already exist.
    VALUETYPE &get(const KEYTYPE &key) {
        unsigned int addr = hasher(key) % TABLE_SIZE;

        return table[addr].get(key);
    } // get()


    // Get the value associated with the given key.  Note that the underlying
    // linked list will automatically add it with a default constructed element
    // if it does not already exist.
    VALUETYPE &operator[](const KEYTYPE &key) {
        unsigned int addr = hasher(key) % TABLE_SIZE;

        return table[addr].get(key);
    } // operator[]()


    // Clear out the hash table, by clearing each linked list.
    void clear() {
        for (unsigned int i = 0; i < TABLE_SIZE; ++i)
            table[i].clear();
    } // clear()

}; // HashTable

#endif // HASHTABLE_H