#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Industrial {
    public:
        Industrial(); //default constructor
        int IndPopulationCount = 0;
        void InitializeIndustrial();
        void UpdateIndustrial();
        bool AdjacentToPowerLine(int x, int y);  
        int CountAdjacentPop(int x, int y, int minPopulation);  
        void UpdateIndPopulation(int x, int y);  
       
    private:
        vector<pair<int, int>> industrialZones;
};

#endif