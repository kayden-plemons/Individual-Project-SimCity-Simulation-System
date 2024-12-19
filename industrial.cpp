#include "industrial.h"
#include "residential.h"
#include <iostream>
#include "SharedVectors.h"
#include <vector>
using namespace std;

int IndPopulationCount = 0;

Industrial::Industrial() //constructor
{
}

void Industrial::InitializeIndustrial() // Traverse the StoredRegion and save all 'I' locations
{
    int rows = StoredRegion.size();
    int cols = StoredRegion[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (StoredRegion[i][j] == 'I') {
                industrialZones.push_back({i, j});
            }
        }
    }
}

// Update population for all Industrial zones ('I') and Iterate over all stored Industrial zones and update population
void Industrial::UpdateIndustrial() {
    for (const auto& coord : industrialZones) {
        int x = coord.first;
        int y = coord.second;
        UpdateIndPopulation(x, y);  // this passes the coords
    }
}

// Check if a Industrial zone is adjacent to a powerline (T, P, or #)
bool Industrial::AdjacentToPowerLine(int x, int y) {
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
int Industrial::CountAdjacentPop(int x, int y, int minPopulation) {
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

// this function apply's population growth rules
void Industrial::UpdateIndPopulation(int x, int y) {
    int currentPopulation = UpdatedRegion[x][y];

    // Ensure there are at least 2 available workers
    if (Workers < 2) {
        return; 
    }

    //Population is 0, adjacent to a powerline, and at least 2 workers available
    else if (currentPopulation == 0 && AdjacentToPowerLine(x, y)) {
        UpdatedRegion[x][y]++;
        Goods++;
        Workers -= 2;  // 2 workers assigned to this job
        IndPopulationCount++;
        Pollution++;
        return;
    }

    //Population is 0, adjacent to at least 1 populated cell, and at least 2 workers available
    else if (currentPopulation == 0 && CountAdjacentPop(x, y, 1) >= 1) {
        UpdatedRegion[x][y]++;
        Goods++;
        Workers -= 2; 
        IndPopulationCount++;
        Pollution++;
        return;
    }

    //Population is 1, adjacent to at least 2 populated cells, and at least 2 workers available
    else if (currentPopulation == 1 && CountAdjacentPop(x, y, 1) >= 2) {
        UpdatedRegion[x][y]++;
        Goods++;
        Workers -= 2; 
        IndPopulationCount++;
        Pollution++;
        return;
    }

    //Population is 2, adjacent to at least 4 populated cells, and at least 2 workers available
    else if (currentPopulation == 2 && CountAdjacentPop(x, y, 2) >= 4) {
        UpdatedRegion[x][y]++;
        Goods++;
        Workers -= 2; 
        IndPopulationCount++;
        Pollution++;
        return;
    }
}