#ifndef _FEGRID_H_
#define _FEGRID_H_

#include <cstdio>   
#include <cmath>    
#include <cassert>
#include <cstring> 
#include <vector> 
#include <string>
#include "Node.h"   
#include "Element.h"

using namespace std;

/**
 * @class FEGrid
 * @brief Class representing a finite element grid.
 *
 * The FEGrid class manages a grid of finite elements and nodes, providing methods
 * to calculate gradients, element areas, and access nodes and elements.
 */
class FEGrid
{
public:
  /**
   * @brief Default constructor.
   */
  FEGrid();

  /**
   * @brief Constructor initializing grid from node and element files.
   * 
   * @param nodeFile Path to the file containing node data.
   * @param a_elementFileName Path to the file containing element data.
   */
  FEGrid(const std::string& nodeFile, const std::string& a_elementFileName);

  /**
   * @brief Calculate the gradient at a specific element.
   * 
   * @param a_gradient Array to store the gradient.
   * @param a_eltNumber The element number.
   * @param a_localNodeNumber The local node number within the element.
   */
  void gradient(double a_gradient[DIM], const int& a_eltNumber, const int& a_localNodeNumber) const;

  /**
   * @brief Get the area of a specific element.
   * 
   * @param a_eltNumber The element number.
   * @return The area of the element.
   */
  double elementArea(const int& a_eltNumber) const;

  /**
   * @brief Get the node at a specific element and local node number.
   * 
   * @param a_eltNumber The element number.
   * @param a_localNodeNumber The local node number within the element.
   * @return Reference to the Node object.
   */
  const Node& getNode(const int& a_eltNumber, const int& a_localNodeNumber) const;

  /**
   * @brief Get the number of elements in the grid.
   * 
   * @return The total number of elements.
   */
  int getNumElts() const;

  /**
   * @brief Get the number of nodes in the grid.
   * 
   * @return The total number of nodes.
   */
  int getNumNodes() const;

  /**
   * @brief Get the number of interior nodes in the grid.
   * 
   * @return The number of interior nodes.
   */
  int getNumInteriorNodes() const;

  /**
   * @brief Accessor for an element by index.
   * 
   * @param i The index of the element.
   * @return Reference to the Element object.
   */
  const Element& element(int i) const;

  /**
   * @brief Accessor for a node by index.
   * 
   * @param i The index of the node.
   * @return Reference to the Node object.
   */
  const Node& node(int i) const;

private:
  vector<Node> m_nodes; /**< Vector of nodes in the grid. */
  vector<Element> m_elements; /**< Vector of elements in the grid. */
  int m_numInteriorNodes; /**< The number of interior nodes in the grid. */
};

#endif

