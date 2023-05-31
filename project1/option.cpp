// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79

#include "option.h"
#include <getopt.h>
#include <array>
#include <vector>
#include <string>
#include <deque>
#include <stack>
#include <iostream>


using namespace std;

void Option::setScheme(char scheme_set){
    Option::schemeOpt = scheme_set;
}

void Option::setOutput(string output_set){
    Option::outputOpt = output_set;
}

void Option::setFound(bool found_set){
    Option::pathFound = found_set;
}

void Option::input(){
    char inputMode;
    uint32_t inputRoom, inputSize;
    
    cin >> inputMode;

    cin >> inputRoom;
    rooms = inputRoom;

    cin >> inputSize;
    size = inputSize;

    input_map.resize(inputRoom, vector<vector<entry>>(inputSize, vector<entry>(inputSize)));

    //map input
    if(inputMode == 'M'){


        char start, datum, check;
        uint32_t room, row;

        room = 0;
        row = 0;

        string comment;

        getline(cin, comment);

        while(cin >> start){
            //SKIP LINE IF COMMENT, increment room
            if(start == '/'){
                getline(cin, comment);

            } else {
                //IF TRUE, NOW IN NEXT ROOM, RESET ROW AND COLUMN
                if(row == inputSize){
                    room++;
                    row = 0;
                }

                if(room == inputRoom){
                    break;
                }

                //GO ALONG ROW, FILLING COLUMNS
                for(uint32_t i = 0; i < inputSize; i++){
                    if(i == 0){
                        input_map[room][row][i].datum = start;
                    } else{
                        cin >> datum;
                        input_map[room][row][i].datum = datum;
                    }

                    check = input_map[room][row][i].datum;

                    if(check != '.' && check!= '#' && check != '!' && check != 'C' && check != 'S' && check != '0' &&
                    check != '1' && check != '2' && check != '3' && check != '4' && check != '5' && check != '6' &&
                    check != '7' && check != '8' && check != '9'){
                        cerr << "Unknown map character" << endl;
                        exit(1);
                    }


                    if(input_map[room][row][i].datum == 'S'){
                        startLocation.room = room;
                        startLocation.row = row;
                        startLocation.col = i;
                    }

                }

                //INCREMENT ROW NUMBER, REPEAT LOOP
                row++;

            }
        }

        
    //list input
    } else if (inputMode == 'L') {

        char start, last, comma, datum;
        uint32_t room, row, col;
        string comment;


        for(uint32_t i = 0; i < rooms; i++ ){       
            for(uint32_t x = 0; x < size; x++){
                for(uint32_t y = 0; y < size; y++){
                    input_map[i][x][y].datum = '.';
                }
            }     
        }


        //list input to change
        while(cin >> start){
            if(start == '/'){
                getline(cin,comment);

            } else {
                cin >> room >> comma >> row >> comma >> col >> comma >> datum >> last;

                if(room >= rooms){
                    cerr << "Invalid room number" << endl;
                    exit(1);
                }

                if(row >= size){
                    cerr << "Invalid row number" << endl;
                    exit(1);
                }

                if(col >= size){
                    cerr << "Invalid col number" << endl;
                    exit(1);
                }

                input_map[room][row][col].datum = datum;
                    
                if(input_map[room][row][col].datum == 'S'){
                    startLocation.room = room;
                    startLocation.row = row;
                    startLocation.col = col;
                }

                char check = input_map[room][row][col].datum;

                if(check != '.' && check!= '#' && check != '!' && check != 'C' && check != 'S' && check != '0' &&
                check != '1' && check != '2' && check != '3' && check != '4' && check != '5' && check != '6' &&
                check != '7' && check != '8' && check != '9'){
                    cerr << "Unknown map character" << endl;
                    exit(1);
                }

            }
        }

    } else {
        exit(1);
    }

}

void Option::discover(entry &looked){
    looked.discovered = true;
}

bool Option::find(){
    char scheme = Option::schemeOpt;

    location currLoc;
    currLoc = startLocation;
    deque<location> container;

    container.push_back(startLocation);
    tilesFound = 1;



    
    while(!container.empty()){

        
        if(scheme == 's'){

            currLoc = container.back();
            container.pop_back();

        }else{

            currLoc = container.front();
            container.pop_front();
        }

        
        uint32_t currRoom = currLoc.room;
        uint32_t currRow = currLoc.row;
        uint32_t currCol = currLoc.col; 


        discover(input_map[currRoom][currRow][currCol]);


        location northLoc, eastLoc, southLoc, westLoc;
        char check = input_map[currLoc.room][currLoc.row][currLoc.col].datum;

        //first check if warp pipe
        if(check >= '0' && check <= '9'){
            int oldRoom = currLoc.room;

            //check status of end of warp
            uint32_t newRoom = check - '0';
            char otherDatum = '.';
            bool validRoom = false;
            
            //verify valid room
            if(newRoom < rooms){
                otherDatum = input_map[newRoom][currLoc.row][currLoc.col].datum;
                validRoom = true;
                input_map[currLoc.room][currLoc.row][currLoc.col].warpRoom = check;
            }

            //if valid room, verify valid datum

            if(validRoom){
                if(otherDatum != '!' && otherDatum != '#' && input_map[newRoom][currLoc.row][currLoc.col].discovered == false){
                    
                    location newLoc = currLoc;
                    newLoc.room = newRoom;
                    container.push_back(newLoc);
                    tilesFound++;

                    char ch;
                    
                    ch = static_cast<char>(oldRoom + '0');

                    input_map[newRoom][currLoc.row][currLoc.col].discovered = true;
                    input_map[newRoom][currLoc.row][currLoc.col].relativeLocation = ch;

                    char followingDatum = input_map[newRoom][currLoc.row][currLoc.col].datum;

                    if(followingDatum == 'C'){
                        //countess found
                        countessLocation.room = newRoom;
                        countessLocation.row = currLoc.row;
                        countessLocation.col = currLoc.col;

                        return true;
                    }

                }
            }
                
        } else {

            //north
            if(currLoc.row != 0){
                char northDatum = input_map[currRoom][currRow-1][currCol].datum;
                if(northDatum != '!' && northDatum != '#' && !input_map[currRoom][currRow-1][currCol].discovered){

                    if(northDatum == 'C'){
                        discover(input_map[currRoom][currRow-1][currCol]);
                        input_map[currRoom][currRow-1][currCol].relativeLocation = 'n';

                        countessLocation.room = currRoom;
                        countessLocation.row = currRow-1;
                        countessLocation.col = currCol;
                        
                        return true;
                    }

                    northLoc.room = currRoom;
                    northLoc.col = currCol;
                    northLoc.row = currRow - 1;
                    container.push_back(northLoc);

                    discover(input_map[currRoom][currRow-1][currCol]);
                    tilesFound++;
                    input_map[currRoom][currRow-1][currCol].relativeLocation = 'n';



                }
            }

            //east

            if(currLoc.col < size-1){
                char eastDatum = input_map[currRoom][currRow][currCol+1].datum;
                if(eastDatum != '!' && eastDatum != '#' && !input_map[currRoom][currRow][currCol+1].discovered){

                    if(eastDatum == 'C'){
                        discover(input_map[currRoom][currRow][currCol+1]);
                        input_map[currRoom][currRow][currCol+1].relativeLocation = 'e';

                        countessLocation.room = currRoom;
                        countessLocation.row = currRow;
                        countessLocation.col = currCol+1;
                        
                        return true;
                }

                eastLoc.room = currRoom;
                eastLoc.col = currCol+1;
                eastLoc.row = currRow;
                container.push_back(eastLoc);

                discover(input_map[currRoom][currRow][currCol+1]);
                tilesFound++;
                input_map[currRoom][currRow][currCol+1].relativeLocation = 'e';

                }
            }

            //south
            if(currLoc.row < size-1){
                char southDatum = input_map[currRoom][currRow+1][currCol].datum;
                if(southDatum != '!' && southDatum != '#' && !input_map[currRoom][currRow+1][currCol].discovered){

                    if(southDatum == 'C'){
                        discover(input_map[currRoom][currRow+1][currCol]);
                        input_map[currRoom][currRow+1][currCol].relativeLocation = 's';

                        countessLocation.room = currRoom;
                        countessLocation.row = currRow+1;
                        countessLocation.col = currCol;
                        
                        return true;
                    }

                    southLoc.room = currRoom;
                    southLoc.col = currCol;
                    southLoc.row = currRow + 1;
                    container.push_back(southLoc);

                    discover(input_map[currRoom][currRow+1][currCol]);
                    tilesFound++;
                    input_map[currRoom][currRow+1][currCol].relativeLocation = 's';

                }
            }

            //west

            if(currLoc.col != 0){
                char westDatum = input_map[currRoom][currRow][currCol-1].datum;

                if(westDatum != '!' && westDatum != '#' && !input_map[currRoom][currRow][currCol-1].discovered){

                    if(westDatum == 'C'){
                        discover(input_map[currRoom][currRow][currCol-1]);
                        input_map[currRoom][currRow][currCol-1].relativeLocation = 'w';

                        countessLocation.room = currRoom;
                        countessLocation.row = currRow;
                        countessLocation.col = currCol-1;
                        
                        return true;
                    }

                    westLoc.room = currRoom;
                    westLoc.col = currCol-1;
                    westLoc.row = currRow;
                    container.push_back(westLoc);

                    discover(input_map[currRoom][currRow][currCol-1]);
                    tilesFound++;
                    input_map[currRoom][currRow][currCol-1].relativeLocation = 'w';

                }
            }
        }
          

    }

    return false;
    
}

void Option::output(){


    location pathPointer;
    pathPointer = countessLocation;


    if(!pathFound){
        cout << "No solution, " << tilesFound << " tiles discovered." << endl;
    }

    while(true && pathFound){

        if(pathPointer.room == startLocation.room && pathPointer.row == startLocation.row && pathPointer.col == startLocation.col){
            break;
        }
        
        //get next direction
        char next = input_map[pathPointer.room][pathPointer.row][pathPointer.col].relativeLocation;

        //modify the value
        if(next == 'n'){
            input_map[pathPointer.room][pathPointer.row+1][pathPointer.col].datum = 'n';
            pathPointer.row = pathPointer.row+1;


        }else if(next == 'e'){
            input_map[pathPointer.room][pathPointer.row][pathPointer.col-1].datum = 'e';
            pathPointer.col = pathPointer.col-1;

        }else if(next == 's'){
            input_map[pathPointer.room][pathPointer.row-1][pathPointer.col].datum = 's';
            pathPointer.row = pathPointer.row-1;


        } else if(next == 'w'){
            input_map[pathPointer.room][pathPointer.row][pathPointer.col+1].datum = 'w';
            pathPointer.col = pathPointer.col+1;

        

        } else {
            //new room
            uint32_t goRoom = next - '0';

            input_map[goRoom][pathPointer.row][pathPointer.col].datum = 'p';
            pathPointer.room = goRoom;
            
        }



    }

    //Map

    if(outputOpt == "M" && pathFound){

        cout << "Start in room " << startLocation.room << ", row " << startLocation.row << ", column " << startLocation.col << endl;
        for(uint32_t i = 0; i < rooms; i++ ){
            cout << "//castle room " << i << endl;
        
            for(uint32_t x = 0; x < size; x++){
                for(uint32_t y = 0; y < size; y++){
                    cout << input_map[i][x][y].datum;
                }
                cout << endl;
            }
        
        }
    }

    //List

    if(outputOpt == "L" && pathFound){

        cout << "Path taken:" << endl;

        location listPointer;
        listPointer = startLocation;

        while(true){

            uint32_t atRoom = listPointer.room;
            uint32_t atRow = listPointer.row;
            uint32_t atCol = listPointer.col;
        
        
            char currDatum = input_map[atRoom][atRow][atCol].datum;


            if(currDatum == 'C'){
                break;
            }

            cout << "(" << atRoom << "," << atRow << "," << atCol << "," << currDatum << ")" << endl;

            if(currDatum == 'n'){
                listPointer.row = listPointer.row-1;
            } else if(currDatum == 'e'){
                listPointer.col = listPointer.col+1;
            } else if(currDatum == 's'){
                listPointer.row = listPointer.row+1;
            } else if(currDatum == 'w'){
                listPointer.col = listPointer.col-1;
            } else {
                char goRoomChar = input_map[atRoom][atRow][atCol].warpRoom;
                uint32_t goRoom = goRoomChar - '0';
                listPointer.room = goRoom;
            }


        }

    }


}

string Option::getOption(int argc, char * argv[]) {
    bool optionSpecified = false;
    string chosen;

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        { "stack", no_argument, nullptr, 's' },
        { "queue", no_argument, nullptr, 'q' },
        { "output", required_argument, nullptr, 'o' },
        { nullptr, 0,                nullptr, '\0'}
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "sqo:", long_options, &option_index)) != -1) {
        switch (choice) {
        case 's':
            
            if(schemeSet){
                cerr << "Stack or queue can only be specified once" << endl;
                exit(1);
            }
            
            Option::setScheme('s');
            schemeSet = true;

            break;

        case 'q':
            
            if(schemeSet){
                cerr << "Stack or queue can only be specified once" << endl;
                exit(1);
            }
            
            Option::setScheme('q');
            schemeSet = true;

            break;


        case 'o':
            chosen = optarg;
            if (chosen != "M" && chosen != "L") {

                cerr << "Error: invalid mode" << endl;
                cerr << "  I don't know recognize: " << chosen << endl;
                exit(1);
            } 
            optionSpecified = true;
            break;

        default:
            cerr << "Unknown command line option" << endl;
            exit(1);
        } 
    } 

    if(!schemeSet){
        cerr << "Stack or queue must be specified" << endl;
        exit(1);
    }

    if (!optionSpecified) {
        chosen = "M";
    } 

    return chosen;
} 


