#include "GridFn.h"
#include <iostream>
#include <cmath>

GridFn::GridFn(int m, int n) : m(m), n(n) {
    gridValues.resize(m, std::vector<double>(n, 0));  // Initialize grid values to zero
}

void GridFn::initialize() {
    // Initialize grid values with given initial conditions (f(x) = x * sqrt((l - x)^3))
    for (int i = 0; i < m; i++) {
        double x = i * dx;
        for (int j = 0; j < n; j++) {
            gridValues[i][j] = x * sqrt((l - x) * (l - x) * (l - x));  // f(x) = x * sqrt((l - x)^3)
            printf("Initial Temperature at x=%f: %f\n", x, gridValues[i][j]);  // Print initial condition for debugging
        }
    }
}

void GridFn::solve() {
    // Implement the 1D heat diffusion equation solution using the three-point stencil method
    for (int i = 1; i < m - 1; i++) {
        double newTemperature = gridValues[i][0] + alpha * dt / (dx * dx) * (gridValues[i - 1][0] - 2 * gridValues[i][0] + gridValues[i + 1][0]);
        printf("T[%d] updated from %f to %f\n", i, gridValues[i][0], newTemperature);  // Print updated temperature values
        gridValues[i][0] = newTemperature;
    }
}

void GridFn::printGrid() {
    printf("Current Grid Values:\n");
    for (int i = 0; i < m; i++) {
        printf("x = %f, T(x) = %f\n", i * dx, gridValues[i][0]);
    }
}

