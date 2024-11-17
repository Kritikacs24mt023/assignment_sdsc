#include "GridFn.h"
#include "Solution.h"
#include "RDomain.h"
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    // Read command-line arguments for l (length), dt (time step), and dx (space step)
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <length> <time-step> <space-step>" << std::endl;
        return 1;
    }

    double l = std::stod(argv[1]);
    double dt = std::stod(argv[2]);
    double dx = std::stod(argv[3]);

    int m = static_cast<int>(l / dx);  // Number of grid points
    int n = 1;  // Only one dimension (1D heat diffusion)

    GridFn gridFn(m, n);
    Solution solution(&gridFn);

    solution.applyBoundaryConditions();
    solution.iterate();
    solution.printResults();

    return 0;
}

