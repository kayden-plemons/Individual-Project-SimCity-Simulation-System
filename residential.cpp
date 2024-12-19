#include "residential.h"
#include <iostream>
#include "SharedVectors.h"
#include <vector>
using namespace std;

int ResPopulationCount = 0;

Residential::Residential() //constructor
{
}

void Residential::InitializeResidential() // Traverse the StoredRegion and save all 'R' locations
{
    int rows = StoredRegion.size();
    int cols = StoredRegion[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (StoredRegion[i][j] == 'R') {
                residentialZones.push_back({i, j});
            }
        }
    }
}

// Update population for all residential zones ('R') and Iterate over all stored residential zones and update population
void Residential::UpdateResidential() {
    for (const auto& coord : residentialZones) {
        int x = coord.first;
        int y = coord.second;
        UpdateResPopulation(x, y);  // this passes the coords
    }
}

// Check if a residential zone is adjacent to a powerline (T, P, or #)
bool Residential::AdjacentToPowerLine(int x, int y) {
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
int Residential::CountAdjacentPop(int x, int y, int minPopulation) {
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

// this function apply's population growth rules to a specific residential zone at (x, y)
void Residential::UpdateResPopulation(int x, int y) {
    int currentPopulation = UpdatedRegion[x][y];

    if (currentPopulation == 0 && AdjacentToPowerLine(x, y)) {
        UpdatedRegion[x][y]++;
        Workers++;
        ResPopulationCount++;
        return;
    }
    else if (currentPopulation == 0 && CountAdjacentPop(x, y, 1) >= 1) {
        UpdatedRegion[x][y]++;
        Workers++;
        ResPopulationCount++;
        return;
    }
    else if (currentPopulation == 1 && CountAdjacentPop(x, y, 1) >= 2) {
        UpdatedRegion[x][y]++;
        Workers++;
        ResPopulationCount++;
        return;
    }
    else if (currentPopulation == 2 && CountAdjacentPop(x, y, 2) >= 4) {
        UpdatedRegion[x][y]++;
        Workers++;
        ResPopulationCount++;
        return;
    }
    else if (currentPopulation == 3 && CountAdjacentPop(x, y, 3) >= 6) {
        UpdatedRegion[x][y]++;
        Workers++;
        ResPopulationCount++;
        return;
    }
    else if (currentPopulation == 4 && CountAdjacentPop(x, y, 4) >= 8) {
        UpdatedRegion[x][y]++;
        Workers++;
        ResPopulationCount++;
        return;
    }
}
