#ifndef GRIDFN_H
#define GRIDFN_H

#include <vector>
#include <cmath>

class GridFn {
public:
    GridFn(int m, int n);  // Constructor to initialize grid size
    void initialize();  // Function to initialize grid values
    void solve();  // Function to solve the 1D heat diffusion equation
    void printGrid();  // Print the current grid for debugging

private:
    int m, n;  // Grid dimensions
    std::vector<std::vector<double>> gridValues;  // Grid to hold temperature values
    double alpha = 1.0;  // Thermal diffusivity constant
    double dx = 0.4;  // Space step
    double dt = 0.1;  // Time step
    double l = 1.2;  // Length of the rod
};

#endif

