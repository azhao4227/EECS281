// Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef OPTION_H
#define OPTION_H

//Create an Option object that has two parameters, one for the scheme to be used,
//one for the output option to be used

#include "round.h"
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

    struct zombie{
        string name;
        uint32_t distance;
        uint32_t speed;
        uint32_t health;
        uint32_t ETA;
        int roundsActive = 1;

        bool aliveZombie = true;
    };

    class CompareETA {
        public:
        bool operator()(zombie* z1, zombie* z2){
            if(z1 -> ETA == z2 -> ETA){
                if(z1 -> health != z2 -> health){
                    return z1 -> health > z2 -> health;
                } else {
                    return z1 -> name > z2 -> name;
                }
            }
            return z1 -> ETA > z2 -> ETA;
        }
    };

    class lessActive {
        public:
        bool operator()(zombie* z1, zombie* z2){
            if(z1 -> roundsActive != z2 -> roundsActive){
                return z1 -> roundsActive < z2 -> roundsActive;
            }
            return z1 -> name > z2 -> name;
        }
    };

    class moreActive {
        public:
        bool operator()(zombie* z1, zombie* z2){
            if(z1 -> roundsActive != z2 -> roundsActive){
                return z1 -> roundsActive > z2 -> roundsActive;
            }
            return z1 -> name > z2 -> name;
        }
    };



class Round {
public:

    void getOption(int argc, char * argv[]);

    void inputHeader();

    void unnamedRound();

    void updateZombies();

    void namedCreate(uint32_t num);

    void randomCreate(uint32_t num);

    void shoot();

    void gameRound();

    void game();

    void calculateMedian();

    void getStatistics();


private:

    uint32_t quiverCapacity;

    bool verbose;
    bool statistics;
    bool median;
    bool help;
    bool nextInput;

    int numStats;
    uint32_t seed;
    uint32_t randDist;
    uint32_t randSpeed;
    uint32_t randHealth; 

    uint32_t quivers;
    uint32_t currRound;

    deque<zombie> zombies;
    deque<zombie *> zombiePointers;
    priority_queue<zombie*, vector<zombie*>, CompareETA> shooting;

    deque<zombie*> killedZombies;

    int currMedian;
    priority_queue<int, vector<int>, greater<int>> largerMedian;
    priority_queue<int> smallerMedian;

    bool alive;
    uint32_t finalRound;
    string finalName;

    int created;
    int destroyed;

    
    
};

#endif