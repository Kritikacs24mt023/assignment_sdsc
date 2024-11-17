#include <cstdio>
#include <cmath>
#include <cassert>
#include <cfloat>
#include <vector>
#include "Node.h"
using namespace std;

/**
 * @brief Default constructor for the Node class.
 * 
 * Initializes the position of the node to FLT_MAX (indicating undefined or uninitialized) and sets the node as an interior node with ID -1.
 */
Node::Node()
{
  for (int idir = 0; idir < DIM; idir++) {
    m_position[idir] = FLT_MAX;
  }
  m_isInterior = true;
  m_interiorNodeID = -1;
};

/**
 * @brief Constructor for creating a Node with a specified position, ID, and interior status.
 * 
 * @param a_position The position of the node in the grid.
 * @param a_interiorNodeID The interior node ID.
 * @param a_isInterior Boolean indicating if the node is an interior node.
 */
Node::Node(double a_position[DIM], const int& a_interiorNodeID, const bool& a_isInterior)
{
  for (int idir = 0; idir < DIM; idir++) {
    m_position[idir] = a_position[idir];
  }
  m_isInterior = a_isInterior;
  m_interiorNodeID = a_interiorNodeID;
};

/**
 * @brief Get the position of the node.
 * 
 * @param a_x Array to store the position of the node.
 */
void Node::getPosition(double a_x[DIM]) const
{
  for (int idir = 0; idir < DIM; idir++) {
    a_x[idir] = m_position[idir];
  }
};

/**
 * @brief Get the interior node ID.
 * 
 * @return The interior node ID.
 */
const int& Node::getInteriorNodeID() const
{
  return m_interiorNodeID;
};

/**
 * @brief Check if the node is an interior node.
 * 
 * @return True if the node is interior, false otherwise.
 */
const bool& Node::isInterior() const
{
  return m_isInterior;
};

