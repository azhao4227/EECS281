// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7

#include <utility>
#include <string>
#include <iosfwd>
#include <cassert>
#include <exception>
#include <vector>
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <getopt.h>
#include "amongus.h"

using namespace std;

//part A
void AmongUs::mstPrim(vector<Vertex> map){
    
    size_t size = map.size();

    k.clear();
    d.clear();
    p.clear();

    k.resize(size, false);
    d.resize(size, numeric_limits<double>::infinity());
    p.resize(size);

    d[0] = 0;
    for(size_t i = 0; i < size; i++){
        
        size_t newV = 0;
        double smallestUndiscovered = numeric_limits<double>::infinity();

        //select smallerst d of undiscovered
        for(size_t j = 0; j < size; j++){
            if(k[j] == false){
                if(d[j] < smallestUndiscovered){
                    newV = j;
                    smallestUndiscovered = d[j];
                }
            }
        }
        k[newV] = true;

        //check children of newV
        Vertex parent = map[newV];
        for(size_t j = 0; j < size; j++){
            Vertex child = map[j];
            if(checkAdj(parent, child, newV, j) && k[j] == false){
                double distance = calcDistance(parent, child);
                if(d[j] > distance){
                    d[j] = distance;
                    p[j] = newV;
                }
            }
        }
    }
}

void AmongUs::mstPrint(){
    double sum = 0;
    for(size_t i = 1; i < d.size(); i++){
        sum += d[i];
    }
    cout << sum << "\n";

    for(size_t i = 1; i < map.size(); i++){
        if(i > p[i]){
            cout << p[i] << " " << i << "\n";
        } else {
            cout << i << " " << p[i] << "\n";
        }
    }
}

void AmongUs::partA(){
    mapInput();
    mstPrim(map);
    mstPrint();
}

//part B
void AmongUs::fTSPgenerate(vector<Vertex> &map){

    vector<size_t> path;
    double totalDist = 0;
    k.resize(map.size(), false);
    path.reserve(map.size());

    //start with nearest insert
    double minNext = numeric_limits<double>::infinity();
    size_t minIndex = 0;
    k[0] = true;
    path.push_back(0);
    for(size_t j = 1; j < map.size(); j++){
        double distance = calcDistance(map[0], map[j]);
        if(distance < minNext){
            minIndex = j;
            minNext = distance;
        }
    }
    k[minIndex] = true;
    path.push_back(minIndex);
    path.push_back(0);
    totalDist += minNext * 2;

    //now arbitrarily insert rest of vertices
    for(size_t i = 0; i < map.size() - 2; i++){

        //select arbitrary value
        size_t newV = 0;
        for(size_t j = 0; j < map.size(); j++){
            if(!k[j]){
                newV = j;
                break;
            }
        }
        k[newV] = true;
        Vertex insert = map[newV];

        //check edge to insert
        double minInsert = numeric_limits<double>::infinity();
        size_t insertIndex = 0;

        for(size_t j = 0; j < path.size() - 1; j++){
            Vertex first = map[path[j]];
            Vertex second = map[path[j+1]];

            double firstInsert = calcDistance(first, insert);
            double insertSecond = calcDistance(insert, second);
            double original = calcDistance(first, second);

            double total = firstInsert + insertSecond - original;

            if(total < minInsert){
                insertIndex = j + 1;
                minInsert = total;
            }
        }
        totalDist += minInsert;
        path.insert(path.begin() + insertIndex, newV);

    }

    path.pop_back();
    bestDistance = totalDist;
    bestPath = path;
}

void AmongUs::partB(){
    mapInput();
    fTSPgenerate(map);
    printTSP();
}

//part C
void AmongUs::createDistMat(vector<Vertex> map){
    size_t size = map.size();
    distMat.resize(size, vector<double>(size));
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            distMat[i][j] = calcDistance(map[i], map[j]);
        }
    }
}

void AmongUs::genPerms(vector<size_t> &path, size_t permLength) {

    if (permLength == path.size()) {
        
        double finalEdge = distMat[0][path[permLength-1]];
        double finalDist = currDistance + finalEdge;

        if(finalDist < bestDistance){
            bestDistance = finalDist;
            bestPath = path;
        }
        return;
    }  // if ..complete path
    
    if (!promising(path, permLength)) {
        return;
    }  // if ..not promising
    
    for (size_t i = permLength; i < path.size(); ++i) {
        swap(path[permLength], path[i]);
        double addDist = distMat[path[permLength - 1]][path[permLength]];
        currDistance += addDist;
        genPerms(path, permLength + 1);
        currDistance -= addDist;
        swap(path[permLength], path[i]);
    }  // for ..unpermuted elements
}

void AmongUs::tspPrim(vector<Vertex> map){
    
    size_t size = map.size();

    k.clear();
    d.clear();

    k.resize(size, false);
    d.resize(size, numeric_limits<double>::infinity());

    d[0] = 0;
    for(size_t i = 0; i < size; i++){
        
        size_t newV = 0;
        double smallestUndiscovered = numeric_limits<double>::infinity();

        //select smallerst d of undiscovered
        for(size_t j = 0; j < size; j++){
            if(k[j] == false){
                if(d[j] < smallestUndiscovered){
                    newV = j;
                    smallestUndiscovered = d[j];
                }
            }
        }
        k[newV] = true;

        //check children of newV
        Vertex parent = map[newV];
        for(size_t j = 0; j < size; j++){
            Vertex child = map[j];
            if(k[j] == false){
                double distance = calcDistance(parent, child);
                if(d[j] > distance){
                    d[j] = distance;
                }
            }
        }
    }
}

bool AmongUs::promising(vector<size_t> &path, size_t permLength){

    //Create subpath and submap of unset vertices
    vector<size_t> subPath(path.begin() + permLength, path.end());
    vector<Vertex> subMap;
    subMap.reserve(subPath.size());
    for(size_t i = 0; i < subPath.size(); i++){
        subMap.push_back(map[subPath[i]]);
    }   

    //MST
    tspPrim(subMap);
    double sum = 0;
    for(size_t i = 1; i < d.size(); i++){
        sum += d[i];
    }

    //Connecting Arms
    double minFirst = numeric_limits<double>::infinity();
    double minSecond = numeric_limits<double>::infinity();
    for(size_t i = 0; i < subMap.size(); i++){
        double tempFirst = distMat[0][subPath[i]];
        double tempSecond = distMat[path[permLength - 1]][subPath[i]];
        if(tempFirst < minFirst){
            minFirst = tempFirst;
        }
        if(tempSecond < minSecond){
            minSecond = tempSecond;
        }
    }

    return currDistance + sum + minFirst + minSecond < bestDistance;
}

void AmongUs::partC(){
    mapInput();
    createDistMat(map);
    fTSPgenerate(map);
    currPath = bestPath;

    genPerms(currPath, 1);
    printTSP();
}

//helpers
void AmongUs::mapInput(){
    size_t size;
    int x;
    int y;

    cin >> size;
    vector<Vertex> input;
    input.reserve(size);

    for(size_t i = 0; i < size; i++){
        cin >> x;
        cin >> y;

        Vertex temp;
        temp.x = x;
        temp.y = y;

        //check in decon
        if(x < 0 && y == 0){
            temp.type = LocationType::Decon;
        } else if (x == 0 && y < 0){
            temp.type = LocationType::Decon;
        } else if (x == 0 && y == 0){
            temp.type = LocationType::Decon;
        } else if (x < 0 && y < 0){
            //check in lab
            temp.type = LocationType::Lab;
        } else {
            //else outside
            temp.type = LocationType::Outer;
        }

        input.push_back(temp);
    }

    map = input;
}

double AmongUs::calcDistance(Vertex first, Vertex second){
    double xDiff = first.x - second.x;
    double yDiff = first.y - second.y;

    double distance = sqrt(xDiff * xDiff + yDiff * yDiff);
    return distance;
}

bool AmongUs::checkAdj(Vertex parent, Vertex child, size_t newV, size_t j){
    bool adjacent = true;
    if(j == newV){
        adjacent = false;
                }
    if(parent.type == LocationType::Lab && child.type == LocationType::Outer){
        adjacent = false;
    }
    if(parent.type == LocationType::Outer && child.type == LocationType::Lab){
        adjacent = false;
    }

    return adjacent;
}

void AmongUs::printTSP(){
    cout << bestDistance << "\n";
    for(size_t i = 0; i < bestPath.size(); i++){
        cout << bestPath.at(i) << " ";
    }
}

//getOpt
string getOption(int argc, char * argv[]) {

    string modeChosen;
    bool chosen = false;

    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        { "mode",       required_argument,  nullptr, 'm' },
        { "help",       no_argument,        nullptr, 'h' },
        { nullptr,      0,                  nullptr, '\0'}
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "hm:", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            exit(0);
        case 'm':            
            modeChosen = optarg;
            if (modeChosen != "MST" && modeChosen != "FASTTSP" && modeChosen != "OPTTSP") {

                cerr << "Error: invalid mode" << endl;
                cerr << "  I don't know recognize: " << modeChosen << endl;
                exit(1);
            } 
            chosen = true;
            break;
        default:
            cerr << "Unknown command line option" << endl;
            exit(1);
        } 
    } 

    if(!chosen){
        cerr << "Mode must be specified" << endl;
        exit(1);
    }

    return modeChosen;
} 

void AmongUs::setMode(string modeInput){
    mode = modeInput;
}

//main
int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    cout << std::setprecision(2);
    cout << std::fixed;

    string mode = getOption(argc, argv);
    AmongUs game;
    game.setMode(mode);

    if(mode == "MST"){
        game.partA();
    }

    if(mode == "FASTTSP"){
        game.partB();
    }

    if(mode == "OPTTSP"){
        game.partC();
    }

    return 0;
}