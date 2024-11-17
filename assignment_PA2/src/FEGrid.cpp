#include <cstdio>   
#include <cmath>    
#include <cstring>  
#include <cassert>  
#include <vector>
#include <fstream>
#include<iostream>
#include<iomanip>
#include<limits>
#include "Node.h"   
#include "Element.h"
#include "FEGrid.h"

/**
 * @brief Default constructor for the FEGrid class.
 * 
 * Initializes the grid with default values, including setting the number of interior nodes to zero.
 */
FEGrid::FEGrid() : m_numInteriorNodes(0)
{
}

/**
 * @brief Constructor that initializes the FEGrid from files containing node and element data.
 * 
 * @param a_nodeFileName The file name containing node data.
 * @param a_elementFileName The file name containing element data.
 * This constructor reads the node and element files, creates nodes, and stores them in the grid.
 */
FEGrid::FEGrid(const std::string& a_nodeFileName, const std::string& a_elementFileName)
{
  // Reading node data from the specified file
  ifstream nodes(a_nodeFileName.c_str());
  int ncount;
  nodes >> ncount;

  m_nodes.resize(ncount);
  m_numInteriorNodes = 0;
  
  // Loop over all nodes and create Node objects
  for (int i = 0; i < ncount; i++)
  {
    int vertex;
    std::string tmp[DIM];
    double x[DIM];
    bool isInterior = true;

    nodes >> vertex >> tmp[0] >> tmp[1];
    x[0] = atof(tmp[0].c_str());
    x[1] = atof(tmp[1].c_str());

    // Determine if the node is on the boundary or an interior node
    if (((tmp[0].compare("0.60000")) == 0) || ((tmp[1].compare("0.40000")) == 0) || (x[0] == 0) || (x[1] == 0)) {
      isInterior = false;
    }
    else
    {
      m_numInteriorNodes++;
    }
    
    vertex--;
    m_nodes[vertex] = Node(x, vertex, isInterior);
  }

  // Reading element data from the specified file
  ifstream elements(a_elementFileName.c_str());
  int ncell;
  elements >> ncell;
  int vert[VERTICES];
  m_elements.resize(ncell);

  // Loop over all elements and create Element objects
  for (int i = 0; i < ncell; i++)
  {
    int cellID;
    elements >> cellID >> vert[0] >> vert[1] >> vert[2];
    vert[0]--; vert[1]--; vert[2]--;
    cellID--;
    m_elements[cellID] = Element(vert);
  }
}

/**
 * @brief Compute the gradient of shape functions N1, N2, and N3 for a specific element.
 * 
 * @param a_gradient Array to store the computed gradient.
 * @param a_eltNumber The element number.
 * @param a_nodeNumber The local node number within the element.
 * This method calculates the gradient of the shape functions for a triangle element.
 */
void FEGrid::gradient(double a_gradient[DIM], const int& a_eltNumber, const int& a_nodeNumber) const
{
  const Element& e = m_elements[a_eltNumber];
  const Node& n = m_nodes[e[a_nodeNumber]];
  double xbase[DIM];
  n.getPosition(xbase);
  double dx[VERTICES-1][DIM];
  
  // Calculate the differences between the node positions
  for (int ivert = 0; ivert < VERTICES-1; ivert++)
  {
    int otherNodeNumber = e[(a_nodeNumber + ivert + 1) % VERTICES];
    m_nodes[otherNodeNumber].getPosition(dx[ivert]);
    for (int idir = 0; idir < DIM; idir++)
    {
      dx[ivert][idir] -= xbase[idir];
    }
  }

  // Calculate the determinant and gradient for 2D triangles
  double det = dx[0][0] * dx[1][1] - dx[1][0] * dx[0][1];
  a_gradient[0] = (-(dx[1][1] - dx[0][1]) / det);
  a_gradient[1] = (-(dx[1][0] - dx[0][0]) / det);
}

/**
 * @brief Calculate the area of a specific element.
 * 
 * @param a_eltNumber The element number.
 * @return The area of the element.
 * This method calculates the area of a triangle element in 2D.
 */
double FEGrid::elementArea(const int& a_eltNumber) const
{
  const Element& e = m_elements[a_eltNumber];
  const Node& n = m_nodes[e[0]];
  double xbase[DIM];
  n.getPosition(xbase);
  double dx[VERTICES-1][DIM];

  // Calculate the differences between the node positions
  for (int ivert = 1; ivert < VERTICES; ivert++)
  {
    int otherNodeNumber = e[ivert];
    m_nodes[otherNodeNumber].getPosition(dx[ivert-1]);
    for (int idir = 0; idir < DIM; idir++)
    {
      dx[ivert-1][idir] -= xbase[idir];
    }
  }

  // Calculate and return the area of the triangle
  double area = fabs(dx[0][0] * dx[1][1] - dx[1][0] * dx[0][1]) / 2;
  return area;
}

/**
 * @brief Get the node associated with a specific element and local node number.
 * 
 * @param a_eltNumber The element number.
 * @param a_localNodeNumber The local node number within the element.
 * @return Reference to the Node object.
 */
const Node& FEGrid::getNode(const int& a_eltNumber, const int& a_localNodeNumber) const
{
  return m_nodes[m_elements[a_eltNumber][a_localNodeNumber]];
}

/**
 * @brief Get the number of elements in the grid.
 * 
 * @return The total number of elements in the grid.
 */
int FEGrid::getNumElts() const
{
  return m_elements.size();
}

/**
 * @brief Get the number of nodes in the grid.
 * 
 * @return The total number of nodes in the grid.
 */
int FEGrid::getNumNodes() const
{
  return m_nodes.size();
}

/**
 * @brief Get the number of interior nodes in the grid.
 * 
 * @return The total number of interior nodes.
 */
int FEGrid::getNumInteriorNodes() const
{
  return m_numInteriorNodes;
}

/**
 * @brief Access an element by index.
 * 
 * @param i The index of the element.
 * @return Reference to the Element object at the specified index.
 */
const Element& FEGrid::element(int i) const
{
  return m_elements[i];
}

/**
 * @brief Access a node by index.
 * 
 * @param i The index of the node.
 * @return Reference to the Node object at the specified index.
 */
const Node& FEGrid::node(int i) const
{
  return m_nodes[i];
}

