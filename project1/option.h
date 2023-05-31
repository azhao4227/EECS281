// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79

#ifndef OPTION_H
#define OPTION_H

//Create an Option object that has two parameters, one for the scheme to be used,
//one for the output option to be used

#include "option.h"
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

    struct entry{
        char datum;
        char relativeLocation;
        bool discovered = false;
        char warpRoom;

    };

    struct location {
        uint32_t room;
        uint32_t row;
        uint32_t col;
    };


class Option {
public:


    void setScheme(char scheme_set);

    void setOutput(string output_set);

    void setFound(bool found_set);

    string getOption(int argc, char * argv[]);

    void input();

    void discover(entry &inputLocation);

    bool find();

    void output();

private:
    
    char schemeOpt;
    string outputOpt;

    uint32_t rooms;
    uint32_t size;

    bool schemeSet = false;
    bool pathFound;

    int tilesFound;

    vector<vector<vector<entry>>> input_map;
    location startLocation;
    location countessLocation;

};

#endif