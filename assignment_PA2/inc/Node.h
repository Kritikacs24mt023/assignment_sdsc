#ifndef _NODE_H_
#define _NODE_H_
#define DIM 2
#include <cstdio>
#include <cmath>
#include <cassert>
#include <vector>
using namespace std;

/**
 * @class Node
 * @brief Class representing a node in the grid.
 *
 * The Node class stores the position of a node and whether it's an interior node or not.
 */
class Node
{
public:
  /**
   * @brief Default constructor.
   */
  Node();

  /**
   * @brief Constructor with position and ID for the node.
   * 
   * @param a_position Array representing the position of the node in 2D.
   * @param a_interiorNodeID The ID of the interior node.
   * @param a_isInterior A boolean indicating if the node is interior.
   */
  Node(double a_position[DIM], const int& a_interiorNodeID, const bool& a_isInterior);

  /**
   * @brief Get the position of the node.
   * 
   * @param a_position Array to store the position of the node.
   */
  void getPosition(double a_position[DIM]) const;

  /**
   * @brief Get the interior node ID.
   * 
   * @return The interior node ID.
   */
  const int& getInteriorNodeID() const;

  /**
   * @brief Check if the node is an interior node.
   * 
   * @return True if the node is interior, false otherwise.
   */
  const bool& isInterior() const;

private:
  double m_position[DIM]; /**< Position of the node in 2D space. */
  bool m_isInterior; /**< Flag indicating if the node is an interior node. */
  int m_interiorNodeID; /**< ID of the interior node. */
};

#endif

