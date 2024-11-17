#!/bin/bash

# Ensure that the bin directory exists
mkdir -p bin

# Check if the correct number of arguments are provided
if [ $# -ne 3 ]; then
    echo "Usage: $0 <rod-length> <time-step> <space-step>"
    exit 1
fi

# Take user inputs for rod length, time-step, and space-step
LENGTH=$1
TIME_STEP=$2
SPACE_STEP=$3

# Build part2 using the Makefile
make part2

# Run the part2 program with the user inputs and store the binary file in the bin directory
./part2 $LENGTH $TIME_STEP $SPACE_STEP

# Check if the output binary file exists and is written to the bin directory
if [ -f "bin/grid_output.bin" ]; then
    echo "Grid output successfully written to bin/grid_output.bin"
else
    echo "Error: Failed to write grid output."
fi

