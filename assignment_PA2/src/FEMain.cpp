#include "FEGrid.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#define K 30

using namespace std;

/**
 * @brief Main function for performing finite element analysis (FEM) on a grid.
 * 
 * This program computes the global stiffness matrix for a grid defined by nodes and elements.
 * It processes the node and element files provided as input, calculates the element stiffness matrices,
 * assembles them into the global matrix, and computes the Poisson operator over the grid elements.
 * The results are then output in both textual and binary formats.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments passed to the program. The first argument is the common prefix of the node and element files.
 * 
 * @return Returns 0 on successful execution.
 */
int main(int argc, char** argv) {
  // Ensure the program is run with exactly one argument
  if(argc != 2)
    {
      cout << "this program takes just one argument that is the common name prefix of .node and .elem files. (Note: do not give the file extension) ";
      return 1;
    }

  string prefix(argv[1]);
  string nodeFile = prefix + ".node";  /**< File path for node data */
  string eleFile = prefix + ".elem";  /**< File path for element data */
  string q3Answer, q4AnswerA, q4AnswerB;

  /**
   * @brief Creates a grid using the node and element files
   * 
   * The grid is created by reading the node and element files and initializing the necessary 
   * data structures for performing finite element analysis.
   */
  FEGrid grid(nodeFile, eleFile);

  // Get the total number of nodes and interior nodes in the grid
  int numInteriorNodes = grid.getNumInteriorNodes();
  int numNodes = grid.getNumNodes();

  /**
   * @brief Global stiffness matrix and matrix index arrays
   * 
   * The global stiffness matrix (`globalK`) stores the Kij values of all interior nodes.
   * The `globalMatrixIndex` array stores the index of the interior node in the global matrix.
   * These arrays are used in the assembly of the global stiffness matrix.
   */
  int* globalMatrixIndex = (int*)malloc(sizeof(int) * numNodes);
  int interiorNodeIndex = 0;

  /**
   * @brief Assign indices to interior nodes in the global matrix.
   * 
   * This loop assigns indices to the interior nodes for constructing the global stiffness matrix.
   * The global matrix is populated using the interior node indices.
   */
  for(int i = 0; i < numNodes; i++) {
    const Node& n = grid.node(i);
    if(n.isInterior())
      globalMatrixIndex[i] = interiorNodeIndex++;
    else
      globalMatrixIndex[i] = -1;
  }

  // Initialize the global stiffness matrix to zero
  double *globalK = (double *)malloc(sizeof(double) * numInteriorNodes * numInteriorNodes);
  memset(globalK, 0, sizeof(double) * numInteriorNodes * numInteriorNodes); 

  double kij[VERTICES * VERTICES];  /**< Array for storing B^T * C * B */
  double kijpartial[VERTICES * VERTICES];  /**< Array for storing B^T * C */
  double cMatrix[DIM * 2] = {K, 0, 0, K};  /**< Material property matrix (thermal conductivity) */

  /**
   * @brief Loop over each element in the grid to compute the Poisson operator.
   * 
   * For each element in the grid, the program calculates the element stiffness matrix and assembles 
   * it into the global stiffness matrix using the Poisson operator. 
   * The gradient of the shape functions is computed and used in the matrix assembly process.
   */
  for(int i = 0; i < grid.getNumElts(); i++) {
    Element e = grid.element(i);

    // Count the number of interior nodes in the current element
    std::vector<int> elementInteriorNodeID;
    for(int j = 0; j < VERTICES; j++) {
      const Node& n = grid.getNode(i, j);
      if(n.isInterior()) {
        elementInteriorNodeID.push_back(j);  // Storing node local number of the interior node
      }
    }
    int numInteriorNodesOfElement = elementInteriorNodeID.size();

    // Allocate memory for the gradient of shape functions for each interior node of the element 
    double* bMatrixTrans = (double *)malloc(sizeof(double) * numInteriorNodesOfElement * DIM);

    // Get the gradient of the shape functions for all interior nodes of the element
    for(int j = 0; j < numInteriorNodesOfElement; j++) {
      grid.gradient(bMatrixTrans + j * DIM, i, elementInteriorNodeID[j]);
    }

#ifndef CBLAS_DGEMM
    // Compute B^T * C (3x2 * 2x2) OR (2x2 * 2x2) or (1x2 * 2x2)
    for(int m = 0; m < numInteriorNodesOfElement; m++) {
      for(int n = 0; n < DIM; n++) {
        kijpartial[m * DIM + n] = 0.0;
        for(int r = 0; r < DIM; r++) {
          kijpartial[m * DIM + n] += bMatrixTrans[m * DIM + r] * cMatrix[r * DIM + n];
        }
      }
    }
#else
    /**
     * @brief Use cblas_dgemm for matrix multiplication if CBLAS is available.
     * 
     * This line calls the cblas_dgemm function to efficiently perform matrix multiplication.
     * The result is stored in kijpartial, which will later be used to calculate the element stiffness matrix.
     */
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, numInteriorNodesOfElement, DIM, DIM, 1.0, bMatrixTrans, DIM, cMatrix, DIM, 0.0, kijpartial, numInteriorNodesOfElement);
#endif

    /**
     * @brief Dump kijpartial to a binary file for later analysis.
     * 
     * The kijpartial matrix is written to the binary file `kijdump.bin` for storage and inspection.
     * This allows for later verification and analysis of the computed stiffness values.
     */
    FILE *fp = fopen("kijdump.bin", "wb");  // Open file for writing in binary mode
    if (fp != nullptr) {
      fwrite(kijpartial, sizeof(double), VERTICES * VERTICES, fp);  // Write kijpartial to the binary file
      fclose(fp);  // Close the file after writing
    } else {
      cerr << "Error opening file for writing!" << endl;
    }

    // Creating B from B^T
    double *bMatrix = (double *)malloc(sizeof(double) * DIM * numInteriorNodesOfElement);
    for(int m = 0; m < DIM; m++) {
      for(int n = 0; n < numInteriorNodesOfElement; n++) {
        bMatrix[m * numInteriorNodesOfElement + n] = bMatrixTrans[n * DIM + m];
      }
    }

    free(bMatrixTrans);  // Free the temporary matrix after use

    // Multiply with B to get the element stiffness matrix
    for(int m = 0; m < numInteriorNodesOfElement; m++) {
      for(int n = 0; n < numInteriorNodesOfElement; n++) {
        kij[m * numInteriorNodesOfElement + n] = 0.0;
        for(int r = 0; r < DIM; r++) {
          kij[m * numInteriorNodesOfElement + n] += kijpartial[m * DIM + r] * bMatrix[r * numInteriorNodesOfElement + n];
        }
      }
    }

    free(bMatrix);  // Free the matrix after multiplication

    // Insert element matrix contents into the global matrix
    for(int m = 0; m < numInteriorNodesOfElement; m++) {
      int nodeGlobalNumber = e[elementInteriorNodeID[m]];
      assert(globalMatrixIndex[nodeGlobalNumber] != -1);  // Ensure the node is interior
      int rowNumber = globalMatrixIndex[nodeGlobalNumber];
      for(int n = 0; n < numInteriorNodesOfElement; n++) {
        int colNumber = globalMatrixIndex[e[elementInteriorNodeID[n]]];
        globalK[rowNumber * numInteriorNodes + colNumber] += kij[m * numInteriorNodesOfElement + n];
      }
    }
  }

  // Q3: The structure of the global matrix globalK
  q3Answer = "Banded";  /**< The structure of globalK matrix is banded */

  // Q4: Lower and upper bandwidth of the matrix
  q4AnswerA = "Tridiagonal";  /**< Lower bandwidth of globalK */
  q4AnswerB = "Tridiagonal";  /**< Upper bandwidth of globalK */

  // Output the answers for Q3 and Q4
  cout << q3Answer << endl;
  cout << "Lower Bandwidth: " << q4AnswerA << endl;
  cout << "Upper Bandwidth: " << q4AnswerB << endl;

#ifdef DEBUG
  // Write the global matrix into a file for visualization in debug mode
  ofstream myoutputfile;
  myoutputfile.open("GlobalKMatrixFile.txt");
  for(int m = 0; m < numInteriorNodes; m++) {
    for(int n = 0; n < numInteriorNodes; n++) {
      myoutputfile << globalK[m * numInteriorNodes + n];
      if(n != numInteriorNodes - 1)
        myoutputfile << " ";
      else
        myoutputfile << "\n";
    }
  }
#endif

  // Jacobi solver would go here (if implemented)

  return 0;
}

