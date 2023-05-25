#include "edge.h"
#include "graph.cpp"

Graph graph;

// Constructor
/**
 * @brief
 * Edge constructor
 * @param weight Weight of the edge
 * @return void
 * @details
 * This constructor is in charge of creating an edge with a weight.
 * It also creates the origin and destiny nodes.
 * @see Graph::createNode()
 *
 */
Edge::Edge(std::string weight)
{
  this->weight = weight;
  this->origin = std::to_string(graph.createNode());
  this->destiny = std::to_string(graph.createNode());
}

/**
 * @brief
 * Edge constructor
 * @param origin Origin node of the edge
 * @param destiny Destiny node of the edge
 * @return void
 * @details
 * This constructor is in charge of creating an edge with a weight.
 * It also creates the origin and destiny nodes.
 * @see Graph::createNode()
 *
 */
Edge::Edge(std::string origin, std::string destiny)
{
  this->origin = origin;
  this->destiny = destiny;
  this->weight = nullptr;
}

/**
 * @brief
 * Edge constructor
 * @param origin Origin node of the edge
 * @param destiny Destiny node of the edge
 * @param weight Weight of the edge
 * @return void
 * @details
 * This constructor is in charge of creating an edge with a weight.
 * It also creates the origin and destiny nodes.
 */

Edge::Edge(std::string origin, std::string destiny, std::string weight)
{
  this->origin = origin;
  this->destiny = destiny;
  this->weight = weight;
}

// Getters
/**
 * @brief
 * Gets the origin node of the edge
 * @return std::string
 */
std::string Edge::getOrigin()
{
  return this->origin;
}

/**
 * @brief
 * Gets the destiny node of the edge
 * @return std::string
 */
std::string Edge::getDestiny()
{
  return this->destiny;
}

/**
 * @brief
 * Gets the weight of the edge
 * @return std::string
 */

std::string Edge::getWeight()
{
  return this->weight;
}
