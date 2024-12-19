#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Commercial {
    public:
        Commercial(); //default constructor
        int ComPopulationCount = 0;
        void InitializeCommercial();
        void UpdateCommercial();
        bool AdjacentToPowerLine(int x, int y);  
        int CountAdjacentPop(int x, int y, int minPopulation);  
        void UpdateComPopulation(int x, int y);  
       
    private:
        vector<pair<int, int>> commercialZones;
    
};

#endif