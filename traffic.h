#ifndef TRAFFIC_H
#define TRAFFIC_H
#include <iostream>
#include <vector>
using namespace std;

class Traffic {
    public:
        Traffic(); //default constructor
        void InitializeTraffic();
        void InitializeTrafficCongestion();
        void SpreadTraffic();
        void PrintTraffic();
       
    private:
    
        //private vectors to help run through stored roads and stored traffic congestion.
        vector<pair<int, int>> StoredRoads;
        vector<vector<int>> TrafficCongestion;
        int TrafficPollution = 0;
};

#endif