#ifndef EDGE_H
#define EDGE_H

#include <iostream>

/**
 * @brief
 * Edge class
 * @struct Edge
 * @details
 * This class is in charge of keeping the edge data structure.
 * It has the origin, destiny and weight of the edge.
 */

class Edge
{
private:
  std::string origin;
  std::string destiny;
  std::string weight;

public:
  // Constructor
  Edge(std::string weight);
  Edge(std::string origin, std::string destiny);
  Edge(std::string origin, std::string destiny, std::string weight);

  // Destructor
  ~Edge() = default;

  // Getters
  std::string getOrigin();
  std::string getDestiny();
  std::string getWeight();

  // Setters
  void setOrigin(std::string origin);
  void setDestiny(std::string destiny);
  void setWeight(std::string weight);
};

#endif // EDGE_H