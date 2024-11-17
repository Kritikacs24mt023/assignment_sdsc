#ifndef SOLUTION_H
#define SOLUTION_H

#include "GridFn.h"

class Solution {
public:
    Solution(GridFn* gridFn);
    void applyBoundaryConditions();
    void iterate();
    void printResults();

private:
    GridFn* gridFunction;
    double tolerance = 1e-6;
    int numSteps = 1000;
};

#endif

