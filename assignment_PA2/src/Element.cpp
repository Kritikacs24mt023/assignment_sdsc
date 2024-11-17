#include <cassert>
#include "Element.h"

/**
 * @brief Constructor initializing the element with specified vertices.
 * 
 * @param a_vertices Array of vertices for the element. 
 * This constructor initializes the element's vertices based on the provided input.
 */
Element::Element(int a_vertices[VERTICES])
{
  for (int ivert = 0; ivert < VERTICES; ivert++)
  {
    m_vertices[ivert] = a_vertices[ivert];
  }
};

/**
 * @brief Default constructor for the Element class.
 * 
 * This constructor initializes all the element's vertices to -1.
 */
Element::Element()
{
  for (int ivert = 0; ivert < VERTICES; ivert++)
  {
    m_vertices[ivert] = -1;
  }
};

/**
 * @brief Overloaded index operator to access local node vertices.
 * 
 * @param a_localNodeNumber The local node number (index) of the element.
 * @return The vertex at the specified local node.
 */
const int& Element::operator[](const int& a_localNodeNumber) const
{
  assert(a_localNodeNumber < VERTICES); // Ensure the node number is valid.
  return m_vertices[a_localNodeNumber];
};

/**
 * @brief Function to get the vertices of the element.
 * 
 * @param a_vertices Array where the vertices of the element will be stored.
 * This method copies the element's vertices into the provided array.
 */
void Element::vertices(int a_vertices[VERTICES]) const
{
  for (int i = 0; i < VERTICES; i++)
  {
    a_vertices[i] = m_vertices[i];
  }
}

