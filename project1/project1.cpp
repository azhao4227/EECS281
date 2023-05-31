// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79

// EECS 281, Project 1


#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "option.h"
using namespace std;


int main(int argc, char *argv[]) {
    // This should be in all of your projects, speeds up I/O
    ios_base::sync_with_stdio(false);




    //cout << argc << argv;

    Option input;
    input.setOutput(input.getOption(argc,argv));

    input.input();

    input.setFound(input.find());



    input.output();




    return 0;
} // main()
