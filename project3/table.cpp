// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D

#include <vector>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <algorithm>
#include "table.h"
#include "TableEntry.h"
#include <getopt.h>

using namespace std;

void Table::create(string tableName, bool quietMode){

    name = tableName;
    quiet = quietMode;

    size_t numCols;
    cin >> numCols;

    columnNames.reserve(numCols);
    columnTypes.reserve(numCols);

    cout << "New table " << tableName << " with column(s) ";

    for(size_t i = 0; i < numCols; i++){
        EntryType type;
        string inputType;
        cin >> inputType;

        if(inputType == "int"){
            type = EntryType::Int;
        } else if (inputType == "double"){
            type = EntryType::Double;
        } else if (inputType == "bool"){
            type = EntryType::Bool;
        } else {
            type = EntryType::String;
        } 

        columnTypes.push_back(type);
    }

    string colName;
    for(size_t i = 0; i < numCols; i++){
        cin >> colName;
        columnNames.push_back(colName);
        cout << colName << " ";
    }

    cout << "created" << "\n";

}

void Table::insert(size_t rows){

    size_t originalSize = entries.size();
    size_t finalSize = entries.size() + rows;
    size_t numCols = columnNames.size();

    entries.resize(finalSize);

    if(hashExists){

        for(size_t i = originalSize; i < finalSize; i++){

            entries.at(i).reserve(numCols);

            for(size_t y = 0; y < numCols; y++){
            //check for type, read in type

                switch(columnTypes.at(y)){
                    case EntryType::Bool:{
                        bool input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::Int:{
                        int input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::Double:{
                        double input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::String:{
                        string input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                }
            }
            hash[entries.at(i).at(colIndex)].push_back(i);
        }

    } else if (bstExists){

        for(size_t i = originalSize; i < finalSize; i++){

            entries.at(i).reserve(numCols);

            for(size_t y = 0; y < numCols; y++){
            //check for type, read in type

                switch(columnTypes.at(y)){
                    case EntryType::Bool:{
                        bool input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::Int:{
                        int input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::Double:{
                        double input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::String:{
                        string input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                }
            }   
            bst[entries.at(i).at(colIndex)].push_back(i);   
        }

    } else {

        for(size_t i = originalSize; i < finalSize; i++){

            entries.at(i).reserve(numCols);

            for(size_t y = 0; y < numCols; y++){
            //check for type, read in type

                switch(columnTypes.at(y)){
                    case EntryType::Bool:{
                        bool input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::Int:{
                        int input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::Double:{
                        double input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                    case EntryType::String:{
                        string input;
                        cin >> input;
                        TableEntry put(input);
                        entries.at(i).emplace_back(put);
                        break;
                    }
                }
            }
        }
    }

    cout << "Added " << rows << " rows to " << name << " from position " << originalSize << " to " << finalSize - 1 << "\n";

}

void Table::print(){
    size_t numCols;
    bool validCol = false;
    cin >> numCols;

    vector<size_t> columns;
    columns.reserve(numCols);

    //column check

    for(size_t i = 0; i < numCols; i++){
        string colName;
        validCol = false;
        cin >> colName;

        for(size_t i = 0; i < columnNames.size(); i++){
            if(columnNames.at(i) == colName){
                columns.push_back(i);
                validCol = true;
            }
        }

        if(!validCol){
            cout << "Error during PRINT: " << colName << " does not name a column in " << name << "\n";
            string next;
            getline(cin, next);
            break;
        }
    }

    //print if columns are valid

    if(validCol){

        string type;
        cin >> type;

        if(type == "ALL"){

            if(!quiet){
                for(size_t i = 0; i < numCols; i++){
                    cout << columnNames.at(columns.at(i)) << " ";
                }
                cout << "\n";

                for(size_t i = 0; i < entries.size(); i++){
                    for(size_t y = 0; y < numCols; y++){
                        cout << entries[i][columns[y]] << " ";
                    }
                    cout << "\n";
                }
            }

            cout << "Printed " << entries.size() << " matching rows from " << name << "\n";

        } else {
            // type is WHERE
            printWhere(columns);           
        }
    }
}

void Table::printWhere(vector<size_t> columns){

    string column;
    cin >> column;

    EntryType type;
    bool valid = false;
    size_t columnIndex;

    for(size_t i = 0; i < columnNames.size(); i++){
        if(columnNames.at(i) == column){
            valid = true;
            type = columnTypes.at(i);
            columnIndex = i;
            break;
        }
    }

    if(valid){
        
        string op;
        cin >> op;
        TableEntry compareTo = getType(type);
        wherePrinter(compareTo, op, columnIndex, columns);

    } else {
        cout << "Error during PRINT: " << column << " does not name a column in " << name << "\n";
        getline(cin, column);
    }
}

TableEntry Table::getType(EntryType type){
    switch(type){
        case EntryType::Bool:
        {
            bool input;
            cin >> input;
            TableEntry temp(input);
            return temp;
        }
        case EntryType::Int:
        {
            int input;
            cin >> input;
            TableEntry temp(input);
            return temp;
        }
        case EntryType::Double:
        {
            double input;
            cin >> input;
            TableEntry temp(input);
            return temp;
        }
        default:
        {
            string input;
            cin >> input;
            TableEntry temp(input);
            return temp;
        }
    }
}

void Table::wherePrinter(TableEntry compareTo, string op, size_t index, vector<size_t> columns){

    size_t numRows = 0;

    if(!quiet){
        for(size_t i = 0; i < columns.size(); i++){
            cout << columnNames.at(columns.at(i)) << " ";
        }
        cout << "\n";
    }

    //bst exists on column
    if(columnNames.at(index) == columnWithIndex && bstExists){

        vector<size_t> printnum;

        if(op == "<"){
            auto last = bst.lower_bound(compareTo);
            for(auto it = bst.begin(); it != last; it++){
                printnum = it->second;
                if(!quiet){
                    for(auto it2 = printnum.begin(); it2 != printnum.end(); it2++){
                        for(size_t y = 0; y < columns.size(); y++){
                            cout << entries[*it2][columns[y]] << " ";
                        }
                        cout << "\n";
                    }
                }
                numRows += it->second.size();
          
            }

        } else if (op == ">") {
            auto first = bst.upper_bound(compareTo);
            for(auto it = first; it != bst.end(); it++){
                printnum = it->second;
                if(!quiet){
                    for(auto it2 = printnum.begin(); it2 != printnum.end(); it2++){
                        for(size_t y = 0; y < columns.size(); y++){
                            cout << entries[*it2][columns[y]] << " ";
                        }
                        cout << "\n";
                    }
                }
                numRows += it->second.size();
            }
        } else {
            auto first = bst.lower_bound(compareTo);
            auto last = bst.upper_bound(compareTo);
            for(auto it = first; it != last; it++){
                printnum = it->second;
                if(!quiet){
                    for(auto it2 = printnum.begin(); it2 != printnum.end(); it2++){
                        for(size_t y = 0; y < columns.size(); y++){
                            cout << entries[*it2][columns[y]] << " ";
                        }
                        cout << "\n";
                    }
                }
                numRows += it->second.size();
            }
        }
        

    } else {

        if(op == "<"){
            Less l(compareTo, index);
            for(auto &e : entries){
                if(l(e)){
                    if(!quiet){
                        for(size_t y = 0; y < columns.size(); y++){
                            cout << e[columns[y]] << " ";
                        }
                        cout << "\n";
                    }
                    numRows++;
                }
            }
        
        } else if(op == ">") {
            Greater g(compareTo, index);
            for(auto &e : entries){
                if(g(e)){
                    if(!quiet){
                        for(size_t y = 0; y < columns.size(); y++){
                            cout << e[columns[y]] << " ";
                        }
                        cout << "\n";
                    }
                    numRows++;
                }
            }

        } else {
        
            Equal E(compareTo, index);
            for(auto &e : entries){
                if(E(e)){
                    if(!quiet){
                        for(size_t y = 0; y < columns.size(); y++){
                            cout << e[columns[y]] << " ";
                        }
                        cout << "\n";
                    }
                    numRows++;
                }
            }
        }

    }

    cout << "Printed " << numRows << " matching rows from " << name << "\n";
   
}


void Table::DELETE(){

    string junk;
    cin >> junk;

    string column;
    cin >> column;

    EntryType type;
    bool valid = false;
    size_t columnIndex;

    for(size_t i = 0; i < columnNames.size(); i++){
        if(columnNames.at(i) == column){
            valid = true;
            type = columnTypes.at(i);
            columnIndex = i;
            break;
        }
    }

    if(valid){

        size_t currSize = entries.size();

        string op;
        cin >> op;
        TableEntry compareTo = getType(type);
            
        if(op == "<"){
            Less l(compareTo, columnIndex);
            auto it = remove_if(entries.begin(), entries.end(), l);
            entries.erase(it, entries.end());
        } else if(op == ">") {
            Greater g(compareTo, columnIndex);
            auto it = remove_if(entries.begin(), entries.end(), g);
            entries.erase(it, entries.end());
        } else {
            Equal E(compareTo, columnIndex);
            auto it = remove_if(entries.begin(), entries.end(), E);
            entries.erase(it, entries.end());
        }

        size_t newSize = entries.size();
        cout << "Deleted " << currSize - newSize << " rows from " << name << "\n";

        if(bstExists){
            size_t row = 0;
            bst.clear();
            for(auto &e : entries){
                bst[e.at(colIndex)].push_back(row);
                row++;
            }

        } 
        if(hashExists){
            size_t row = 0;
            hash.clear();
            for(auto &e : entries){
                hash[e.at(colIndex)].push_back(row);
                row++;
            }
        }

    } else {
        cout << "Error during DELETE: " << column << " does not name a column in " << name << "\n";
        getline(cin, column);
    }
}

void Table::generate(){
    string type;
    string junk;
    string colName;
    colIndex = 0;
    bool validCol = false;

    cin >> type; //INDEX TYPE
    cin >> junk; //INDEX
    cin >> junk; //ON
    cin >> colName; //TABLENAME

    for(size_t i = 0; i < columnNames.size(); i++){
        if(columnNames.at(i) == colName){
            colIndex = i;
            validCol = true;
            break;
        }
    }

    if(validCol){

        columnWithIndex = colName;
    
        if(type == "bst"){
            size_t row = 0;
            bst.clear();
            for(auto &e : entries){
                bst[e.at(colIndex)].push_back(row);
                row++;
            }
            hashExists = false;
            bstExists = true;

        } else {
            size_t row = 0;
            hash.clear();
            for(auto &e : entries){
                hash[e.at(colIndex)].push_back(row);
                row++;
            }
            hashExists = true;
            bstExists = false;
        }

        cout << "Created " << type <<  " index for table " << name << " on column " << colName << "\n";

    } else {
        cout << "Error during GENERATE: " << colName << " does not name a column in " << name << "\n";
        getline(cin, colName);
    }

}

bool getOption(int argc, char * argv[]) {

    bool quiet = false;

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        { "quiet",      no_argument,    nullptr, 'q' },
        { "help",       no_argument,    nullptr, 'h' },
        { nullptr,      0,              nullptr, '\0'}
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "qh", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'q':            
            quiet = true;
            break;
        case 'h':
            exit(0);
        default:
            cerr << "Unknown command line option" << "\n";
            exit(1);
        } 
    } 

    return quiet;
} 



int main(int argc, char *argv[]) {
    // This should be in all of your projects, speeds up I/O
    ios_base::sync_with_stdio(false);
    cin >> std::boolalpha;  // add these two lines
    cout << std::boolalpha;

    
    bool quietMode = getOption(argc, argv);

    //full underlying database
    unordered_map<string, Table> tables;
    string command;

    do{

        cout << "% ";
        cin >> command;

        
        if (cin.fail()) {
            cerr << "Error: Reading from cin has failed" << "\n";
            exit(1);
        } 
        

        char c = command[0];

        switch(c){
        
        //database commands

        case 'C' : {

            string tableName;
            cin >> tableName;

            if(tables.find(tableName) != tables.end()){
                cout << "Error during CREATE: Cannot create already existing table " << tableName << "\n";
                getline(cin, tableName);
            } else {
                Table& new_table = tables[tableName];
                new_table.create(tableName, quietMode);
            }

            break;

        }

        case 'R' : {
            string tableName;
            cin >> tableName;

            if(tables.find(tableName) != tables.end()){
                tables.erase(tableName);
                cout << "Table " << tableName << " deleted" << "\n";
            } else {
                cout << "Error during REMOVE: " << tableName << " does not name a table in the database" << "\n";
                getline(cin, tableName);
            }

            break;

        }


        case '#' : {
            getline(cin, command);
            break;
        }

        //table commands

        case 'I' : {

            string junk;
            string tableName;
            size_t numRows;

            //INSERT INTO <tableName> <numRows> ROWS
            cin >> junk;
            cin >> tableName;
            cin >> numRows;
            cin >> junk;

            //insert table
            if(tables.find(tableName) != tables.end()){
                Table& edit_table = tables[tableName];
                edit_table.insert(numRows);
            } else {
                cout << "Error during INSERT: " << tableName << " does not name a table in the database" << "\n";
                getline(cin, tableName);
            }
            break;

        }

        case 'P' : {
            string junk;
            string tableName;

            cin >> junk;
            cin >> tableName;
            if(tables.find(tableName) != tables.end()){
                Table& edit_table = tables[tableName];
                edit_table.print();
            } else {
                cout << "Error during PRINT: " << tableName << " does not name a table in the database" << "\n";
                getline(cin, tableName);
            }
            break;
        }

        case 'D': {
            string junk;
            string tableName;

            cin >> junk;
            cin >> tableName;
            if(tables.find(tableName) != tables.end()){
                Table& edit_table = tables[tableName];
                edit_table.DELETE();
            } else {
                cout << "Error during DELETE: " << tableName << " does not name a table in the database" << "\n";
                getline(cin, tableName);
            }
            break;
        }

        
        case 'G': {
            string junk;
            string tableName;
            cin >> junk;
            cin >> tableName;

            if(tables.find(tableName) != tables.end()){
                Table& edit_table = tables[tableName];
                edit_table.generate();
            } else {
                cout << "Error during GENERATE: " << tableName << " does not name a table in the database" << "\n";
                getline(cin, tableName);
            }
            break;
        }

        case 'J': {
            string table1;
            string table2;
            string junk;

            cin >> table1;
            cin >> junk;
            cin >> table2;
            cin >> junk;


            if(tables.find(table1) != tables.end() && tables.find(table2) != tables.end()){

                Table& first = tables[table1];
                Table& second = tables[table2];
                string col1;
                string col2;
                size_t index1;
                size_t index2;
                size_t numCols;
                size_t numRows = 0;
                vector<size_t> whichTable;
                vector<size_t> column1Indices;
                vector<size_t> column2Indices;
                vector<size_t> print_rows;
                bool valid = false;

                cin >> col1; 
                cin >> junk; //equal
                cin >> col2;
                //equals error checking

                for(size_t i = 0; i < first.columnNames.size(); i++){
                    if(first.columnNames.at(i) == col1){
                        index1 = i;
                        valid = true;
                        break;
                    }
                }         
                if(!valid){
                    cout << "Error during JOIN: " << col1 << " does not name a column in " << first.name << "\n";
                    getline(cin, col1);
                    break;
                }     
                valid = false;      
                
                for(size_t i = 0; i < second.columnNames.size(); i++){
                    if(second.columnNames.at(i) == col2){
                        index2 = i;
                        valid = true;
                        break;
                    }
                }
                if(!valid){
                    cout << "Error during JOIN: " << col2 << " does not name a column in " << second.name << "\n";
                    getline(cin, col2);
                    break;
                }           
                
                //print error checking and reserving
                if(valid){
                    cin >> junk; //AND 
                    cin >> junk; //PRINT
                    cin >> numCols;

                    whichTable.reserve(numCols);
                    column1Indices.reserve(numCols);
                    column2Indices.reserve(numCols);

                    for(size_t i = 0; i < numCols; i++){
                        bool validCol = false;
                        size_t table;
                        string colName;
                        cin >> colName;
                        cin >> table;

                        //column is in table 
                        if(table == 1){
                            for(size_t i = 0; i < first.columnNames.size(); i++){
                                if(first.columnNames.at(i) == colName){
                                    column1Indices.push_back(i);
                                    whichTable.push_back(1);
                                    validCol = true;
                                    break;
                                }
                            }
                        //column is in table 2
                        } else {
                            for(size_t i = 0; i < second.columnNames.size(); i++){
                                if(second.columnNames.at(i) == colName){
                                    column2Indices.push_back(i);
                                    whichTable.push_back(2);
                                    validCol = true;
                                    break;
                                }
                            }
                        }

                        if(!validCol){
                            if(table == 1){
                                cout << "Error during JOIN: " << colName << " does not name a column in " << first.name << "\n";
                            } else {
                                cout << "Error during JOIN: " << colName << " does not name a column in " << second.name << "\n";
                            }
                            getline(cin, colName);
                            valid = false;
                            break;
                        }

                    }
                }
            
                //if all good, continue
                //create hash
                if(valid){
                    unordered_map<TableEntry, vector<size_t>> hash;
                    hash.clear();
                    if(second.hashExists && second.columnWithIndex == col2){
                        hash = second.hash;
                    } else {
                        size_t row = 0;
                        for(auto &e : second.entries){
                            hash[e.at(index2)].push_back(row);
                            row++;
                        }
                    }
                    //hash created, now loop through 1 and print

                    if(!quietMode){
                        size_t c1 = 0;
                        size_t c2 = 0;
                        for(size_t i = 0; i < numCols; i++){
                            if(whichTable.at(i) == 1){
                                cout << first.columnNames.at(column1Indices.at(c1)) << " ";
                                c1++;
                            } else {
                                cout << second.columnNames.at(column2Indices.at(c2)) << " ";
                                c2++; 
                            }
                        }
                        cout << "\n";
                    }

                    for(size_t ir = 0; ir < first.entries.size(); ir++){
                        print_rows = hash[first.entries.at(ir).at(index1)];
                        if(!print_rows.empty()){
                            if(!quietMode){
                                for(size_t i = 0; i < print_rows.size(); i++){
                                    size_t c1 = 0;
                                    size_t c2 = 0;
                                    for(size_t y = 0; y < numCols; y++){
                                        //PRINTING FROM TABLE 1 COLUMN
                                        if(whichTable.at(y) == 1){
                                            cout << first.entries.at(ir).at(column1Indices.at(c1)) << " ";
                                            c1++;
                                            //PRINTING FROM TABLE 2 COLUMN
                                        } else {
                                            cout << second.entries.at(print_rows.at(i)).at(column2Indices.at(c2)) << " ";
                                            c2++;
                                        }
                                    }
                                    cout << "\n";
                                }                                
                            }
                            numRows += print_rows.size();
                        }
                    }

                    cout << "Printed " << numRows << " rows from joining " << table1 << " to " << table2 << "\n";

                }

            } else if(tables.find(table1) == tables.end()){
                cout << "Error during JOIN: " << table1 << " does not name a table in the database" << "\n";
                getline(cin, table1);

            } else {
                cout << "Error during JOIN: " << table2 << " does not name a table in the database" << "\n";
                getline(cin, table2);

            }
            
            break;

        }

        case 'Q' : {
            cout << "Thanks for being silly!" << "\n";
            return 0;
        }

        default : {
            cout << "Error: unrecognized command" << "\n";
            getline(cin, command);
            break;
        }

        }

    } while (command != "QUIT");

    return 0;
} // main()