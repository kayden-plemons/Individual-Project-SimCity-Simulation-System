#include <iostream>
#include "SharedVectors.h"
#include "commercial.h"
#include <vector>
using namespace std;

int ComPopulationCount = 0;

Commercial::Commercial() //constructor
{
}

void Commercial::InitializeCommercial() // Traverse the StoredRegion and save all 'C' locations
{
    int rows = StoredRegion.size();
    int cols = StoredRegion[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (StoredRegion[i][j] == 'C') {
                commercialZones.push_back({i, j});
            }
        }
    }
}

// Update population for all Commercial zones ('C') and Iterate over all stored Commercial zones and update population
void Commercial::UpdateCommercial() {
    for (const auto& coord : commercialZones) {
        int x = coord.first;
        int y = coord.second;
        UpdateComPopulation(x, y);  // this passes the coords
    }
}

// Check if a Commercial zone is adjacent to a powerline (T, P, or #)
bool Commercial::AdjacentToPowerLine(int x, int y) {
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1,  0,  1, 1, 1, 0, -1, -1}; //helps check all locations

    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < StoredRegion.size() && newY >= 0 && newY < StoredRegion[0].size()) {
            char adjacentCell = StoredRegion[newX][newY];
            if (adjacentCell == 'T' || adjacentCell == 'P' || adjacentCell == '#') {
                return true;
            }
        }
    }

    return false;
}

// Count adjacent cells with population >= minPopulation
int Commercial::CountAdjacentPop(int x, int y, int minPopulation) {
    int count = 0;

    // Check all 8 directions
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1,  0,  1, 1, 1, 0, -1, -1};

    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        // Ensure the new coords are in bounds
        if (newX >= 0 && newX < UpdatedRegion.size() && newY >= 0 && newY < UpdatedRegion[0].size()) {
            if (UpdatedRegion[newX][newY] >= minPopulation) {
                count++;
            }
        }
    }
    return count;
}

// this function apply's population growth rules to a specific Commercial zone at (x, y)
void Commercial::UpdateComPopulation(int x, int y) {
    int currentPopulation = UpdatedRegion[x][y];

    // Ensure there is at least 1 available worker and 1 available good before any growth
    if (Workers < 1 || Goods < 1) {
        return;  
    }

    // Population = 0, adjacent to a powerline, at least 1 worker and 1 good available
    else if (currentPopulation == 0 && AdjacentToPowerLine(x, y)) {
        UpdatedRegion[x][y]++;
        Workers--; 
        Goods--;    
        ComPopulationCount++;
        return;
    }

    // Population = 0, adjacent to at least 1 populated cell, at least 1 worker and 1 good available
    else if (currentPopulation == 0 && CountAdjacentPop(x, y, 1) >= 1) {
        UpdatedRegion[x][y]++;
        Workers--;  
        Goods--;    
        ComPopulationCount++;
        return;
    }

    // Population = 1, adjacent to at least 2 populated cells, at least 1 worker and 1 good available
    else if (currentPopulation == 1 && CountAdjacentPop(x, y, 1) >= 2) {
        UpdatedRegion[x][y]++;
        Workers--;  
        Goods--;  
        ComPopulationCount++;  
        return;
    }

}