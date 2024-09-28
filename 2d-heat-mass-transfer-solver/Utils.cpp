#include "Utils.h"
#include <fstream>
#include <iomanip>
#include <string>

void Utils::initializeTemperature(ScalarField2D& temperature, double ambient, int hotspot_i, int hotspot_j, double hotspot_T) {
    for(auto& T : temperature.field) {
        T = ambient;
    }
    if(hotspot_i >=0 && hotspot_i < temperature.grid.nx && hotspot_j >=0 && hotspot_j < temperature.grid.ny) {
        temperature.at(hotspot_i, hotspot_j) = hotspot_T;
    }
}

void Utils::initializeConcentration(ScalarField2D& concentration, double initial_conc, int source_i, int source_j, double source_conc) {
    for(auto& C : concentration.field) {
        C = initial_conc;
    }
    if(source_i >=0 && source_i < concentration.grid.nx && source_j >=0 && source_j < concentration.grid.ny) {
        concentration.at(source_i, source_j) = source_conc;
    }
}

void Utils::exportData(const ScalarField2D& temperature, const ScalarField2D& concentration, int step) {
    std::string tempFilename = "temperature_step_" + std::to_string(step) + ".csv";
    std::ofstream tempFile(tempFilename);
    tempFile << std::fixed << std::setprecision(5);
    for(int i = 0; i < temperature.grid.nx; ++i) {
        for(int j = 0; j < temperature.grid.ny; ++j) {
            tempFile << temperature.at(i, j);
            if(j < temperature.grid.ny - 1) {
                tempFile << ",";
            }
        }
        tempFile << "\n";
    }
    tempFile.close();

    std::string concFilename = "concentration_step_" + std::to_string(step) + ".csv";
    std::ofstream concFile(concFilename);
    concFile << std::fixed << std::setprecision(5);
    for(int i = 0; i < concentration.grid.nx; ++i) {
        for(int j = 0; j < concentration.grid.ny; ++j) {
            concFile << concentration.at(i, j);
            if(j < concentration.grid.ny - 1) {
                concFile << ",";
            }
        }
        concFile << "\n";
    }
    concFile.close();
}

void Utils::visualizeResults() {
    // to implement after prof consult mostly using Python
}