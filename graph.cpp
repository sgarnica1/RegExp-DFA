#include "graph.h"
#include "utils.h"

// Access methods

/**
 * @brief
 * Gets the head of the graph
 * @return std::string Head of the graph
 */
std::string Graph::getHead()
{
  return this->head;
}

/**
 * @brief
 * Gets the tail of the graph
 * @return std::string Tail of the graph
 */
std::string Graph::getTail()
{
  return this->tail;
}

/**
 * @brief
 * Gets the size of the nodes
 * @return int Size of the nodes
 */

int Graph::size()
{
  return this->nodes.size();
}

// Manipulation methods
/**
 * @brief
 * Sets the head of the graph
 * @param head Head of the graph
 * @return void
 */
void Graph::setHead(std::string head)
{
  this->head = head;
}

/**
 * @brief
 * Sets the tail of the graph
 * @param tail Tail of the graph
 * @return void
 */
void Graph::setTail(std::string tail)
{
  this->tail = tail;
}

/**
 * @brief
 * Adds an edge to the graph
 * @param origin Origin of the edge
 * @param destiny Destiny of the edge
 * @param weight Weight of the edge
 * @return void
 */
void Graph::addEdge(std::string origin, std::string destiny, std::string weight)
{
  this->adjList[origin].push_back(std::make_pair(destiny, weight));
  this->edges.insert(weight);
}

/**
 * @brief
 * Creates a node in the graph
 * @return void
 */
int Graph::createNode()
{
  int node = utils::random(0, 1000);

  // Check if the node already exists
  while (this->nodes.find(node) != this->nodes.end())
    node = utils::random(0, 1000);

  // Add the node to the set
  this->nodes.insert(node);
  return node;
}

// Print methods
/**
 * @brief
 * Prints the adjacency list of the graph
 * @return void
 */
void Graph::printAdjList()
{
  std::vector<std::string> lines;
  std::string aux;

  for (auto &i : this->adjList)
  {
    aux += i.first + " -> ";

    for (auto &j : i.second)
      aux += "(" + j.first + ", " + j.second + ") ";

    // Add the line to the vector
    lines.insert(lines.begin(), aux);

    // Clear the aux string
    aux = "";
  }

  // Print the vector
  utils::printVector(lines);
}