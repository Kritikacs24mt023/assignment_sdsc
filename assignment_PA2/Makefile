# Compiler and flags
CFLAGS = -g -Wall
CXX = g++

# Directories for source files, include files, and object files
SRC = ./src
INC = ./inc
OBJ = ./obj

# Name of the executables
EXEC_PART1 = part1
EXEC_PART2 = part2

# Default target: Builds part1 and part2 executables and generates documentation
all: $(OBJ) part1 part2 doc

# Create the obj directory if it doesn't exist
$(OBJ):
	mkdir -p $(OBJ)

# Target for building part1 executable
part1: FEMain.o FEGrid.o Element.o Node.o 
	$(CXX) $(OBJ)/FEMain.o $(OBJ)/FEGrid.o $(OBJ)/Element.o $(OBJ)/Node.o -o $(EXEC_PART1)

# Target for building part2 executable
part2: RDomain.o GridFn.o Solution.o main.o
	$(CXX) $(OBJ)/RDomain.o $(OBJ)/GridFn.o $(OBJ)/Solution.o $(OBJ)/main.o -o $(EXEC_PART2)

# Compile FEMain.cpp into object file
FEMain.o: $(SRC)/FEMain.cpp $(INC)/FEGrid.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEMain.o $(SRC)/FEMain.cpp

# Compile Node.cpp into object file
Node.o: $(SRC)/Node.cpp $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Node.o $(SRC)/Node.cpp

# Compile Element.cpp into object file
Element.o: $(INC)/Element.h $(SRC)/Element.cpp 
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Element.o $(SRC)/Element.cpp

# Compile FEGrid.cpp into object file
FEGrid.o: $(INC)/FEGrid.h $(SRC)/FEGrid.cpp $(INC)/Element.h $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEGrid.o $(SRC)/FEGrid.cpp

# Compile RDomain.cpp into object file for Part 2
RDomain.o: $(SRC)/RDomain.cpp $(INC)/RDomain.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/RDomain.o $(SRC)/RDomain.cpp

# Compile GridFn.cpp into object file for Part 2
GridFn.o: $(SRC)/GridFn.cpp $(INC)/GridFn.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/GridFn.o $(SRC)/GridFn.cpp

# Compile Solution.cpp into object file for Part 2
Solution.o: $(SRC)/Solution.cpp $(INC)/Solution.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Solution.o $(SRC)/Solution.cpp

# Compile main.cpp into object file for Part 2
main.o: $(SRC)/main.cpp $(INC)/Solution.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/main.o $(SRC)/main.cpp

# Clean up the object files and executables
clean:
	rm -f $(OBJ)/* $(EXEC_PART1) $(EXEC_PART2)

# Documentation generation with Doxygen
doc:
	doxygen Doxyfile  # Ensure you have a Doxyfile in your project directory

# Display team information
team:
	@echo "\nTeam Members:"
	@echo "Member 1 :"
	@echo "Name : Kritika Mahajan"
	@echo "Roll No. : CS24MT023\n"
	@echo "Member 2 : "
	@echo "Name : Deepanshu"
	@echo "Roll No. : CS24MT024\n"
	@echo "Course: CS601 - Software Development for Scientific Computing"
	@echo "Instructor: Nikhil Hegde\n"

