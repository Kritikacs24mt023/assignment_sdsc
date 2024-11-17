#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Domain {
public:
    virtual void PrintGrid(const std::string& outputFileName) const = 0;
    virtual ~Domain() = default;
};

#endif

