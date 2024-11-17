// RDomain.cpp (Implementation File)

#include "RDomain.h"
#include <fstream>
#include <iostream>
#include <cstdio>  // for fopen, fwrite, fclose

// Constructor to initialize grid size and step sizes
RDomain::RDomain(int m, int n, double dx, double dy)
    : m(m), n(n), dx(dx), dy(dy) {
    generateGrid();  // Generate the grid upon object creation
}

// Generate grid coordinates
void RDomain::generateGrid() {
    // Generate X-coordinates
    for (int i = 0; i < m; ++i) {
        xCoords.push_back(i * dx);
    }

    // Generate Y-coordinates
    for (int j = 0; j < n; ++j) {
        yCoords.push_back(j * dy);
    }
}

// Print the grid to a binary file
void RDomain::PrintGrid(const std::string& outputFileName) const {
    // Open the file for writing in binary mode
    FILE* fp = fopen(outputFileName.c_str(), "wb");
    if (!fp) {
        std::cerr << "Error: Could not open file " << outputFileName << std::endl;
        return;
    }

    // Write X-coordinates first
    size_t xSize = xCoords.size();
    fwrite(xCoords.data(), sizeof(double), xSize, fp);

    // Write Y-coordinates second
    size_t ySize = yCoords.size();
    fwrite(yCoords.data(), sizeof(double), ySize, fp);

    // Close the file
    fclose(fp);
}

