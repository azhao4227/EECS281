// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7

#include <utility>
#include <string>
#include <iosfwd>
#include <cassert>
#include <exception>
#include <vector>

using namespace std;

enum class LocationType : uint8_t {Decon, Outer, Lab};

struct Vertex {
    int x;
    int y;
    LocationType type;
};

class AmongUs{
    public:

        //part A
        void partA();
        void mstPrim(vector<Vertex> map);
        void mstPrint();

        //part B
        void partB();
        void fTSPgenerate(vector<Vertex> &map);
        void printfTSP(pair<double, vector<size_t>> pathPair);

        //part C
        void createDistMat(vector<Vertex> map);
        void genPerms(vector<size_t> &path, size_t permLength);
        void tspPrim(vector<Vertex> map);
        bool promising(vector<size_t> &path, size_t permLength);
        void partC();

        //helpers
        double calcDistance(Vertex first, Vertex second);
        bool checkAdj(Vertex parent, Vertex child, size_t newV, size_t j);
        void mapInput();
        void printTSP();
        void setMode(string modeInput);
        
    private:

        string mode;
        vector<Vertex> map;

        //part A member variables
        vector<bool> k;
        vector<double> d;
        vector<size_t> p;

        //part B+C member variables
        vector<size_t> bestPath;
        vector<size_t> currPath;
        vector<vector<double>> distMat;
        double bestDistance;
        double currDistance = 0;
};