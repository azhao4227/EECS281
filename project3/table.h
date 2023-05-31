// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include "TableEntry.h"

using namespace std;

class Less{
    public:

        Less(TableEntry compareTo_in, size_t index_in) : compareTo(compareTo_in), index(index_in) { }

        bool operator()(vector<TableEntry> row) const{
            return row.at(index) < compareTo;
        }

    private:

        TableEntry compareTo;
        size_t index;

};

class Greater{
    public:

        Greater(TableEntry compareTo_in, size_t index_in) : compareTo(compareTo_in), index(index_in) {}

        bool operator()(vector<TableEntry> row) const{
            return row.at(index) > compareTo;
        }

    private:

        TableEntry compareTo;
        size_t index;

};

class Equal{
    public:

        Equal(TableEntry compareTo_in, size_t index_in) : compareTo(compareTo_in), index(index_in) {}

        bool operator()(vector<TableEntry> row) const{
            return row.at(index) == compareTo;
        }

    private:

        TableEntry compareTo;
        size_t index;

};


class Table {

public:

    void create(string name, bool quietMode);

    void insert(size_t rows);

    void print();

    void printWhere(vector<size_t> row);

    TableEntry getType(EntryType type);

    void wherePrinter(TableEntry compareTo, string op, size_t index, vector<size_t> columns);

    void DELETE();

    void generate();

    string name;
    vector<string> columnNames;
    vector<EntryType> columnTypes;
    vector<vector<TableEntry>> entries;
    bool quiet;

    string columnWithIndex;
    size_t colIndex;
    bool bstExists = false;
    bool hashExists = false;
    map<TableEntry, vector<size_t>> bst;
    unordered_map<TableEntry, vector<size_t>> hash;


 
    
};

