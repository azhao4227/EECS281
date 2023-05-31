// Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "round.h"
#include "P2random.h"
#include <getopt.h>
#include <array>
#include <vector>
#include <string>
#include <deque>
#include <stack>
#include <iostream>
#include <cstring>


using namespace std;

void Round::inputHeader(){
    string junk;
    string comment;

    getline(cin,comment);
    cin >> junk >> quiverCapacity;
    cin >> junk >> seed;
    cin >> junk >> randDist;
    cin >> junk >> randSpeed;
    cin >> junk >> randHealth;

    P2random::initialize(seed,randDist,randSpeed,randHealth);

}

void Round::unnamedRound(){

    updateZombies();

    if(alive){
        shoot();
    }

    
    if(median && alive){
        cout << "At the end of round " << currRound << ", the median zombie lifetime is " << currMedian << endl;
    }
    

}

void Round::updateZombies(){
    if(!zombies.empty()){
        
    string killerName;
    for(zombie &z: zombies ){


        if(z.aliveZombie){
            if(z.distance <= z.speed){

                // ur dead

                z.distance = 0;
                z.ETA = 0;

                if(alive){
                    finalRound = currRound;
                    killerName = z.name;
                }
                alive = false;

                

            } else {
                z.distance -= z.speed;
                z.ETA = z.distance / z.speed;

            }

            if(verbose){
                cout << "Moved: " << z.name << " (distance: " << z.distance << ", speed: ";
                cout << z.speed << ", health: " << z.health << ")" << endl;
            }

            z.roundsActive++;
        }

    }

    if(!alive){
        cout << "DEFEAT IN ROUND " << finalRound << "! " << killerName << " ate your brains!" << endl;
    }

    }
}

void Round::namedCreate(uint32_t num){

    string junk;
    string name;
    uint32_t speed;
    uint32_t distance;
    uint32_t health;
    zombie add;


    for(uint32_t i = 0; i < num; i++){
        cin >> name >> junk >> distance >> junk >> speed >> junk >> health;
        add.name = name;
        add.distance = distance;
        add.speed = speed;
        add.health = health;
        add.ETA = distance / speed;
        add.roundsActive = 1;

        zombies.push_back(add);

        zombie* ptr = &zombies.back();
        shooting.push(ptr);
        zombiePointers.push_back(ptr);

        if(verbose){
            cout << "Created: " << add.name << " (distance: " << add.distance << ", speed: ";
            cout << add.speed << ", health: " << add.health << ")" << endl;           
        }
        
        created++;

    }

}

void Round::randomCreate(uint32_t num){
    zombie add;

    for(uint32_t i = 0; i < num; i++){
        add.name = P2random::getNextZombieName();
        add.distance = P2random::getNextZombieDistance();
        add.speed = P2random::getNextZombieSpeed();
        add.health = P2random::getNextZombieHealth();
        add.ETA = add.distance / add.speed;
        add.roundsActive = 1;

        zombies.push_back(add);
        shooting.push(&zombies.back());
        zombiePointers.push_back(&zombies.back());

        

        if(verbose){
            cout << "Created: " << add.name << " (distance: " << add.distance << ", speed: ";
            cout << add.speed << ", health: " << add.health << ")" << endl;           
        }

        created++;


    }
}

void Round::shoot(){

    priority_queue<zombie*, vector<zombie*>, CompareETA> temp = shooting;
    uint32_t arrowsUsed = 0;

    while (arrowsUsed < quiverCapacity && !shooting.empty()) {

        zombie* target = shooting.top();

        while(target -> health != 0 && arrowsUsed < quiverCapacity){
            shooting.top() -> health -= 1;
            arrowsUsed++;
        }

        if(target -> health == 0){
            
            //push to median data container if median
            
            if(median){


                int insert = static_cast<int>(target -> roundsActive);

                if(insert > currMedian){
                    largerMedian.push(insert);
                } else {
                    smallerMedian.push(insert);
                }

                calculateMedian();
            }
            


            if(verbose){
                cout << "Destroyed: " << target -> name << " (distance: " << target -> distance << ", speed: ";
                cout << target -> speed << ", health: " << target -> health << ")" << endl;           
            }

            target -> aliveZombie = false;
            finalName = target -> name;

            killedZombies.push_back(target);
            destroyed++;

            shooting.pop();

        }

    }
}

void Round::gameRound(){

    string junk;
    uint32_t randomZombies;
    uint32_t namedZombies;

    updateZombies();

    if(alive){
        cin >> junk >> randomZombies;
        cin >> junk >> namedZombies;

        if(randomZombies != 0){
            randomCreate(randomZombies);
        }

        if(namedZombies != 0){
            namedCreate(namedZombies);
        }

        shoot();

        
        if(median && alive){
            cout << "At the end of round " << currRound << ", the median zombie lifetime is " << currMedian << endl;
        }
        
    }
  
}

void Round::game(){

    inputHeader();

    string delimiter;
    string junk;
    uint32_t roundNumber;
    currRound = 1;
    currMedian = 0;
    created = 0;
    destroyed = 0;
    alive = true;

    //input


    while(cin >> delimiter && alive){
        cin >> junk >> roundNumber;

        int numRounds = 10;

        if(currRound != roundNumber){

            int numRounds = 10;
            
            //play numRounds rounds
            for(int i = 0; i < numRounds; i++){

                //function call to play round
                playRound();

            }

            for(initialize; condition; update){
                //code block to be repeated
            }


            bool gameWon = false;

            while(!gameWon){

                //play round, return a bool
                gameWon = playRound();

            }

            while(condition){
                //code block to be repeated
            }

            for(int i = currRound; currRound < roundNumber; i++){
                if(alive){
                    if(verbose){
                        cout << "Round: " << currRound << endl; 
                    }
                    unnamedRound();
                    currRound++;
                } else {
                    break;
                }

            }
        }

        if(alive){
            if(verbose){
                cout << "Round: " << currRound << endl;
            }
            gameRound();
            currRound++;
        }


    }

    //no more input

    while(!shooting.empty() && alive){
        if(verbose){
            cout << "Round: " << currRound << endl;
        }
        unnamedRound();
        currRound++;
    }

    if(alive){
        cout << "VICTORY IN ROUND " << currRound - 1 << "! " << finalName << " was the last zombie." << endl;
    }

    
    if(statistics){
        cout << "Zombies still active: " << created - destroyed << endl;

        getStatistics();
    }
    


}


void Round::calculateMedian(){

    int smaller = static_cast<int>(smallerMedian.size());
    int larger = static_cast<int>(largerMedian.size());
    
    int diff = abs(larger-smaller);

    if(diff > 1){
        if(smallerMedian.size() > largerMedian.size()){
            largerMedian.push(smallerMedian.top());
            smallerMedian.pop();
        } else {
            smallerMedian.push(largerMedian.top());
            largerMedian.pop();    
        }
    }


    if(smallerMedian.size() == largerMedian.size()){
        currMedian = (smallerMedian.top() + largerMedian.top())/2;

    } else if(smallerMedian.size() > largerMedian.size()){
        currMedian = smallerMedian.top();

    } else {
        currMedian = largerMedian.top();
    }




}


void Round::getStatistics(){

    priority_queue<zombie*, vector<zombie*>, lessActive> mostActive(zombiePointers.begin(), zombiePointers.end());
    priority_queue<zombie*, vector<zombie*>, moreActive> leastActive(zombiePointers.begin(), zombiePointers.end());


    int size = static_cast<int>(killedZombies.size());

    int orig = numStats;
    if(numStats > size){
        numStats = size;
    }

    cout << "First zombies killed:" << endl;
    for(int i = 0; i < numStats; i++){
        cout << killedZombies.at(i) -> name << " " << i + 1 << endl;
    }
    
    cout << "Last zombies killed:" << endl;
    for(int i = 0; i < numStats; i++){
        cout << killedZombies.at(size - 1 - i) -> name << " " << numStats - i << endl;
    }

    numStats = orig;
    size = static_cast<int>(mostActive.size());
    if(numStats > size){
        numStats = size;
    }

    cout << "Most active zombies:" << endl;
    for(int i = 0; i < numStats; i++){
        cout << mostActive.top() -> name << " " << mostActive.top() -> roundsActive << endl;
        mostActive.pop();
    }

    cout << "Least active zombies:" << endl;
    for(int i = 0; i < numStats; i++){
        cout << leastActive.top() -> name << " " << leastActive.top() -> roundsActive << endl;
        leastActive.pop();
    }


}






void Round::getOption(int argc, char * argv[]) {

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        { "verbose",    no_argument,        nullptr, 'v' },
        { "statistics", required_argument,  nullptr, 's' },
        { "median",     no_argument,        nullptr, 'm' },
        { "help",       no_argument,        nullptr, 'h' },
        { nullptr,      0,                  nullptr, '\0'}
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "vs:mh", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'v':
            
            verbose = true;
            break;

        case 's':
            
            statistics = true;
            numStats = atoi(optarg);
            break;

        case 'm':

            median = true;
            break;

        case 'h':

            exit(0);

        default:
            cerr << "Unknown command line option" << endl;
            exit(1);
        } 
    } 
} 

int main(int argc, char *argv[]) {
    // This should be in all of your projects, speeds up I/O
    ios_base::sync_with_stdio(false);

    Round input;
    input.getOption(argc,argv);

    input.game();

    return 0;
} // main()


