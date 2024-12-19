#ifndef SHAREDVECTORS_H
#define SHAREDVECTORS_H
#include <iostream>
#include <vector>
using namespace std;

extern vector<vector<char>> StoredRegion;  
extern vector<vector<int>> UpdatedRegion;
extern vector<vector<int>> RegionPollution;  

extern int RefreshRate;
extern int TimeLimit;
extern int Population;
extern int Goods;
extern int Workers;
extern int Pollution;

// functions that need to be accessed by all files and share the data.
void PassConfigFile(const string& ConfigFile);
void LoadRegionLayout(const string& RegionLayout);
void initializeUpdatedRegion();
bool CheckIfChange(const vector<vector<int>>& UpdatedRegion, const vector<vector<int>>& previousUpdatedRegion);
void SpreadPollution(); 
void PrintPollutionRegion();
void PrintRegion(); 
void AnalyzeUserArea();

#endif