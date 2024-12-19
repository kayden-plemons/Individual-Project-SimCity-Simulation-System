#include <iostream>
#include <vector>
#include <fstream>
#include "SharedVectors.h"
#include "residential.h"
#include "industrial.h"
#include "commercial.h"
#include "traffic.h"
using namespace std;

//Function to display comp sci info
void DisplayHeader() {
    cout << endl;
    cout << "\t\t\tSimCity Project" << endl;
    cout << "\t\tComputer Science and Engineering" << endl;
    cout << "\t\t  CSCE 2110 - Data Structures" << endl;
    cout << "\tKayden Plemons, krp0190, kaydenplemons@my.unt.edu" << endl;
    cout << endl;
}

//Function to handle initialization tasks
void InitializeProgram(string& ConfigFile, Residential& residential, Industrial& industrial, Commercial& commercial, Traffic& traffic) {
    cout << "Enter Config File: ";
    cin >> ConfigFile;
    PassConfigFile(ConfigFile);
    cout << endl;

    initializeUpdatedRegion();
    residential.InitializeResidential();
    industrial.InitializeIndustrial();
    commercial.InitializeCommercial();
    traffic.InitializeTraffic();
}

//Function to handle the simulation loop
void RunSimulation(Residential& residential, Industrial& industrial, Commercial& commercial, Traffic& traffic) {
    bool hasChanged = true;
    int NoChangeCount = 0;
    int exitCount = 0;

    for (int i = 0; i <= TimeLimit && NoChangeCount < 2; i++) {
        vector<vector<int>> previousUpdatedRegion = UpdatedRegion;

        if (i == 0) {
            cout << "Initial Region Layout:" << endl;
            PrintRegion();
            cout << endl;
        } else if (i % RefreshRate == 0) {
            cout << "Time Step #" << i << ":" << endl;

            // Call update functions
            residential.UpdateResidential();
            commercial.UpdateCommercial();
            industrial.UpdateIndustrial();
            SpreadPollution();

            //Check for changes
            hasChanged = !CheckIfChange(UpdatedRegion, previousUpdatedRegion);
            NoChangeCount = hasChanged ? 0 : NoChangeCount + 1;
            exitCount = i;

            //Print the updated region
            PrintRegion();
            cout << endl;
        }
    }

    if (NoChangeCount >= 2) {
        cout << "Simulation halted due to no changes in two consecutive steps " << exitCount - 1 << " & " << exitCount << "." << endl;
        cout << endl;
    }
}

//Function to print final results
void PrintFinal(Residential& residential, Industrial& industrial, Commercial& commercial, Traffic& traffic) {
    cout << "Final Regional Population:" << endl;
    PrintRegion();

    cout << "Final Residential Population: " << residential.ResPopulationCount << endl;
    cout << "Final Industrial Population: " << industrial.IndPopulationCount << endl;
    cout << "Final Commercial Population: " << commercial.ComPopulationCount << endl;
    cout << "Final Regional Population: " << residential.ResPopulationCount + industrial.IndPopulationCount + commercial.ComPopulationCount << endl;
    cout << endl;

    //Print traffic congestion and pollution
    traffic.SpreadTraffic();
    traffic.PrintTraffic();
    PrintPollutionRegion();

    //Analyze specific area
    AnalyzeUserArea();
}

int main() {
    DisplayHeader();

    // Declare variables and objects
    string ConfigFile;
    Residential residential;
    Industrial industrial;
    Commercial commercial;
    Traffic traffic;

    // Initialize
    InitializeProgram(ConfigFile, residential, industrial, commercial, traffic);

    //Run simulation
    RunSimulation(residential, industrial, commercial, traffic);

    //Print final results
    PrintFinal(residential, industrial, commercial, traffic);

    return 0;
}
