// EECS 281, Dr. David Paoletti

// Example of using a hash table template that hashes from
// string to double.

#include <iostream>
#include <string>
using namespace std;

#include "HashTable.h"


// A hash function structure is a functor, overloading operator()().
// All hash functions should return an integer.
// This hash function maps from strings onto int.
struct HashFunction {
    static const unsigned int D = 128;
    static const unsigned int Q = 2147483647;

    unsigned int operator()(const string &key) const {
        unsigned int sum = 0;

        for (size_t i = 0; i < key.length(); ++i)
            sum = (D * sum + key[i]) % Q;

        return sum;
    } // operator()()
}; // struct HashFunction


int main() {
    string str = "David Paoletti";
    HashTable<string, double, HashFunction> table;

    cout << "The value associated with " << str << " is " << table.get(str) << endl;
    cout << "Adding it to the table" << endl;
    table.add(str, 123.4);
    cout << "The value associated with " << str << " is " << table.get(str) << endl;

    cout << "Removing it from the table" << endl;
    table.remove(str);
    cout << "The value associated with " << str << " is " << table.get(str) << endl;

    cout << "Subscript 'Testing' is " << table["Testing"] << endl;
    table["Testing"] = 432.1;
    cout << "Subscript 'Testing' is " << table["Testing"] << endl;
    cout << "Removing it from the table" << endl;
    table.remove("Testing");
    ++table["Testing"];
    cout << "Subscript 'Testing' is " << table["Testing"] << endl;

    cout << "Clearing the table" << endl;
    table.clear();
    cout << "Subscript 'Testing' is " << table["Testing"] << endl;

    return 0;
} // main()
