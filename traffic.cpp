#include "traffic.h"
#include <iostream>
#include "SharedVectors.h"
#include <vector>
using namespace std;

Traffic::Traffic() //constructor
{
}

void Traffic::InitializeTraffic() // Traverse the StoredRegion and save all '-' locations
{
    int rows = StoredRegion.size();
    int cols = StoredRegion[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (StoredRegion[i][j] == '-') {
                StoredRoads.push_back({i, j});
            }
        }
    }
    InitializeTrafficCongestion();
}

void Traffic::InitializeTrafficCongestion() {
    if (!StoredRegion.empty()) {  
        TrafficCongestion.resize(StoredRegion.size(), vector<int>(StoredRegion[0].size(), 0)); // Resize to match StoredRegion and initialize with 0s
    }
}

//need to anaylze and build this function to compare if the region grew and if road is next to zone cells.
void Traffic::SpreadTraffic() {
    for (const auto& road : StoredRoads) {
        int x = road.first;
        int y = road.second;
        int adjacentZones = 0;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {

                if (dx == 0 && dy == 0) continue;
                int nx = x + dx;
                int ny = y + dy;

                //check bounds
                if (nx >= 0 && nx < StoredRegion.size() && ny >= 0 && ny < StoredRegion[0].size()) {
                    //Check if adjacent
                    char cell = StoredRegion[nx][ny];
                    if (cell == 'C' || cell == 'I' || cell == 'R') {
                        adjacentZones++;
                    }
                }
            }
        }

        if (adjacentZones >= 3) {
            TrafficCongestion[x][y] = 2; //High congestion
        } else if (adjacentZones == 2) {
            TrafficCongestion[x][y] = 1; //Moderate congestion
        }

        if (TrafficCongestion[x][y] > 0) {
            RegionPollution[x][y] += TrafficCongestion[x][y]; //Add pollution
            Pollution++;
            TrafficPollution++;
        } 
    }
}

//this function prints the traffic and compares if growth otherwise output stored region char. 
void Traffic::PrintTraffic()
{
    cout << "Final Regional Traffic:" << endl;
    for (size_t row = 0; row < TrafficCongestion.size(); ++row) {
        for (size_t col = 0; col < TrafficCongestion[row].size(); ++col) {
            // If traffic congestion remains 0, print the character from StoredRegion
            if (TrafficCongestion[row][col] == 0) {
                cout << "0";  // Print from StoredRegion if no congestion.
            } else {
                cout << TrafficCongestion[row][col];  // Print traffic congestion number if there's growth
            }

            if (col != TrafficCongestion[row].size() - 1) {
                cout << " "; 
            }
        }
        cout << endl; 
    }
    cout << "Traffic Congestion Levels:" << endl;
    cout << "0 = No Congestion" << endl;
    cout << "1 = Moderate Congestion" << endl;
    cout << "2 = High Congestion" << endl;
    cout<<"Total Pollution From Traffic Congestion = "<<TrafficPollution<<endl;
    cout<<endl;
}
