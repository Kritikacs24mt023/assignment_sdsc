#include "Solution.h"
#include <iostream>

Solution::Solution(GridFn* gridFn) : gridFunction(gridFn) {}

void Solution::applyBoundaryConditions() {
    // Apply boundary conditions: T(0) = 0, T(l) = 0
    gridFunction->initialize();
    printf("Boundary Conditions Applied: T(0) = 0.0, T(1.2) = 0.0\n");
}

void Solution::iterate() {
    for (int step = 0; step < numSteps; ++step) {
        printf("Time Step %d:\n", step);
        gridFunction->solve();  // Solve for the next time step
        gridFunction->printGrid();  // Print grid at this step
    }
}

void Solution::printResults() {
    printf("Final Temperature Distribution:\n");
    gridFunction->printGrid();  // Print final grid values after iteration
}

