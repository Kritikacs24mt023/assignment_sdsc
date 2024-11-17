#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#define VERTICES 3

/**
 * @class Element
 * @brief Class representing a finite element with vertices.
 *
 * The Element class defines a simple finite element with a fixed number of vertices
 * and provides methods to access the vertices.
 */
class Element
{
public:
  /**
   * @brief Default constructor.
   *
   * Initializes the element with default vertex values.
   */
  Element();

  /**
   * @brief Constructor with specified vertices.
   * 
   * @param a_vertices Array containing the vertices of the element.
   */
  Element(int a_vertices[VERTICES]);

  /**
   * @brief Accessor for the vertex at the given local node number.
   * 
   * @param a_localNodeNumber The local node number (index) for the element.
   * @return Reference to the vertex at the specified local node.
   */
  const int& operator[](const int& a_localNodeNumber) const;

  /**
   * @brief Get the vertices of the element.
   * 
   * @param a_vertices Array to store the vertices of the element.
   */
  void vertices(int a_vertices[VERTICES]) const;

private:
  int m_vertices[VERTICES]; /**< Array storing the vertices of the element. */
};

#endif

