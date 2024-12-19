#include "SharedVectors.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<vector<char>> StoredRegion;
vector<vector<int>> UpdatedRegion;
vector<vector<int>> RegionPollution;

int RefreshRate = 0;
int TimeLimit = 0;
int Goods = 0;
int Workers = 0;
int Pollution = 0;
ifstream fin;

//this function is called from the main and it makes an int vector the same size as the region vector.
void initializeUpdatedRegion() {
    if (!StoredRegion.empty()) {  
        UpdatedRegion.resize(StoredRegion.size(), vector<int>(StoredRegion[0].size(), 0)); // Resize to match StoredRegion and initialize with 0s
    }
}

//this function opens the config file and stores the configuration information.
void PassConfigFile(const string &ConfigFile)
{
    
    fin.open(ConfigFile); //opens the config file given to us.
    if (fin.fail()) 
	{
        cout << "Unable to open input file " << ConfigFile << endl;
        exit(EXIT_FAILURE);
    }
 
    string line; //temp string to help assign through iterations.
    string RegionLayout; //uses this string to store the next region file name.
    while (getline(fin, line)) {  //iterates through each line
        if (line.find("Region Layout:") != string::npos) {
            RegionLayout = line.substr(line.find(":") + 1);
        }
        else if (line.find("Time Limit:") != string::npos) {
            TimeLimit = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Refresh Rate:") != string::npos) {
            RefreshRate = stoi(line.substr(line.find(":") + 1));
        }
    }
    fin.close();

    /* Output the values to verify
    cout << "Region Layout: " << RegionLayout << endl;
    cout << "Time Limit: " << TimeLimit << endl;
    cout << "Refresh Rate: " << RefreshRate << "s"<< endl;
    */
    LoadRegionLayout(RegionLayout);
}

// After serveral testing I needed to put the region layout and soon to be updated region in seprerate files so that other files can access it.
void LoadRegionLayout(const string& RegionLayout) {
    ifstream fin(RegionLayout);
     
    if (fin.fail()) {
        cout << "Unable to open input file " << RegionLayout << endl;
        exit(EXIT_FAILURE);
    }

    string TempLine;
    while (getline(fin, TempLine)) {
        vector<char> row; 
        for (char ch : TempLine) {
            if (ch != ',') {
                row.push_back(ch);
            }
        }
        StoredRegion.push_back(row);  // Add the row to the 2D vector
    }
    fin.close();
}

//this function gets called from main to check for change between steps.
bool CheckIfChange(const vector<vector<int>>& UpdatedRegion, const vector<vector<int>>& previousUpdatedRegion)
{
    //checks for diff's
    for (size_t i = 0; i < UpdatedRegion.size(); ++i) {
        for (size_t j = 0; j < UpdatedRegion[i].size(); ++j) {
            if (UpdatedRegion[i][j] != previousUpdatedRegion[i][j]) {
                return false;  
            }
        }
    }
    //if no diff, return true to indicate regions are the same
    return true;
}

//this function implements pollution spreading, I couldnt figure out if it was working right after trying many things.
void SpreadPollution()
{
   vector<vector<int>> TempPollution(UpdatedRegion.size(), vector<int>(UpdatedRegion[0].size(), 0));
    for (size_t i = 0; i < UpdatedRegion.size(); ++i) {
        for (size_t j = 0; j < UpdatedRegion[0].size(); ++j) {
            int population = UpdatedRegion[i][j];
            
            if (StoredRegion[i][j] == 'I' && population > 0) {
                TempPollution[i][j] += population;
                Pollution++;

                // Spread pollution to adjacent cells
                for (int i2 = -1; i2 <= 1; ++i2) {
                    for (int j2 = -1; j2 <= 1; ++j2) {
                        if (i2 == 0 && j2 == 0) continue;
                        int i3 = i + i2;
                        int j3 = j + j2;
                        // Check bounds
                        if (i3 >= 0 && i3 < UpdatedRegion.size() && j3 >= 0 && j3 < UpdatedRegion[0].size()) {
                            // Spread pollution to adjacent cells, pollution decreases by 1
                            TempPollution[i3][j3] += max(0, population - 1);
                        }
                    }
                }
            }
        }
    }

    // Update the main vector
     RegionPollution = TempPollution;
}

//this function is just for printing the pollution region.
void PrintPollutionRegion() {
    cout << "Final Regional Pollution:" << endl;
    for (int i = 0; i < RegionPollution.size(); ++i) {
        for (int j = 0; j < RegionPollution[0].size(); ++j) {
            if (RegionPollution[i][j] == 0) {
                cout << StoredRegion[i][j] << " "; 
            } else {
                // Check if the current character is not 'I'
                if (StoredRegion[i][j] != 'I' && StoredRegion[i][j] != ' ' && StoredRegion[i][j] != '-') {
                    cout << StoredRegion[i][j] << "(" << RegionPollution[i][j] << ") ";  // Print char with pollution value
                } else {
                    cout << RegionPollution[i][j] << " ";  // Display pollution value for industrial zones
                }
            }
        }
        cout << endl;
    }
    cout<<"Poulltion Count: "<<Pollution<<endl;
    cout<<endl;
}

//this is the main updated region printing function.
void PrintRegion() {
    for (size_t row = 0; row < UpdatedRegion.size(); ++row) {
        for (size_t col = 0; col < UpdatedRegion[row].size(); ++col) {
            // If population remains 0, print the character from StoredRegion
            if (UpdatedRegion[row][col] == 0) {
                cout << StoredRegion[row][col];  // Print from StoredRegion if no population growth
            } else {
                cout << UpdatedRegion[row][col];  // Print population number if there's growth
            }

            if (col != UpdatedRegion[row].size() - 1) {
                cout << " "; 
            }
        }
        cout << endl; 
    }

    cout<<"Available Workers: "<<Workers<<endl;
    cout<<"Available Goods: "<<Goods<<endl;
}

//this function ask the user to enter coords for a part of the region and analyzes that part.
 void AnalyzeUserArea() {
    int x1, y1, x2, y2;
    bool BoundsInput = false;
    int regionHeight = StoredRegion.size();
    int regionWidth = StoredRegion[0].size();

    int TotalResPop = 0;
    int TotalIndPop = 0;
    int TotalComPop = 0;
    int TotalPoll = 0;

    // Prompt for coordinates 
    while (!BoundsInput) {
        cout<<"Please enter coordinates below to analze an area."<<endl;
        cout << "Enter the top-left coordinates x1 y1: ";
        cin >> x1 >> y1;
        cout << "Enter the bottom-right coordinates x2 y2: ";
        cin >> x2 >> y2;

        // bounds check
        if (x1 >= 0 && x1 < regionWidth &&
            y1 >= 0 && y1 < regionHeight &&
            x2 >= 0 && x2 < regionWidth &&
            y2 >= 0 && y2 < regionHeight &&
            x1 <= x2 && y1 <= y2) {
            BoundsInput = true;
        } else {
            cout << "Invalid coordinates. Please ensure they are within bounds."<<endl;
            cout<<endl;
        }
    }

    // Analyze the region specified by the user
    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            // Check the zone type
            if (StoredRegion[i][j] == 'R') {
                TotalResPop += UpdatedRegion[i][j];
            } else if (StoredRegion[i][j] == 'I') {
                TotalIndPop += UpdatedRegion[i][j];
            } else if (StoredRegion[i][j] == 'C') {
                TotalComPop += UpdatedRegion[i][j];
            }
            TotalPoll += RegionPollution[i][j];
        }
    }
    cout<<endl;
    cout << "Analysis of the specified region:"<<endl;
    cout << "Total Residential Population: " << TotalResPop << endl;
    cout << "Total Industrial Population: " << TotalIndPop << endl;
    cout << "Total Commercial Population: " << TotalComPop << endl;
    cout << "Total Pollution: " << TotalPoll << endl;
 }
