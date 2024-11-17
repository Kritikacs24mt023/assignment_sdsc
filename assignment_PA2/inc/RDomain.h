// RDomain.h (Header File)

#ifndef RDOMAIN_H
#define RDOMAIN_H

#include "Domain.h"
#include <vector>

class RDomain : public Domain {
private:
    int m, n;  // Dimensions of the grid (number of points in x and y directions)
    double dx, dy;  // Step sizes in x and y directions
    std::vector<double> xCoords;  // Stores X-coordinates of the grid
    std::vector<double> yCoords;  // Stores Y-coordinates of the grid

public:
    // Constructor to initialize grid size and step sizes
    RDomain(int m, int n, double dx, double dy);

    // Method to generate the grid
    void generateGrid();

    // Print grid to binary file
    virtual void PrintGrid(const std::string& outputFileName) const override;

    // Getter methods for coordinates
    const std::vector<double>& getXCoords() const { return xCoords; }
    const std::vector<double>& getYCoords() const { return yCoords; }
};

#endif  // RDOMAIN_H

