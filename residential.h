#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include <iostream>
#include <vector>
using namespace std;

class Residential {
    public:
        Residential(); //default constructor
        int ResPopulationCount = 0;
        void InitializeResidential();
        void UpdateResidential();
        bool AdjacentToPowerLine(int x, int y);  
        int CountAdjacentPop(int x, int y, int minPopulation);  
        void UpdateResPopulation(int x, int y);  
       
    private:
        vector<pair<int, int>> residentialZones;
    
};

#endif