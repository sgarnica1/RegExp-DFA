#include "utils.h"
#include "graph.h"
#include <algorithm>

// Constructor

/**
 * @brief
 * Graph class
 * @class Graph
 * @param weight
 * The weight of the graph
 * @details
 * This class is in charge of keeping the graph data structure.
 */

Graph::Graph(std::string weight)
{
  this->head = createNode();
  this->tail = createNode();
  this->addEdge(this->head, this->tail, weight);
}

/**
 * @brief
 * Graph class
 * @class Graph
 * @param head
 * The head of the graph
 * @param tail
 * The tail of the graph
 * @param weight
 * The weight of the graph
 * @details
 * This class is in charge of keeping the graph data structure.
 */

Graph::Graph(std::string head, std::string tail, std::string weight)
{
  this->head = head;
  this->tail = tail;
  this->addNode(head);
  this->addNode(tail);
  this->addEdge(head, tail, weight);
}

// Getters
/**
 * @brief
 * Get the head of the graph
 * @return std::string
 * The head of the graph
 */
std::string Graph::getHead()
{
  return this->head;
}

/**
 * @brief
 * Get the tail of the graph
 * @return std::string
 * The tail of the graph
 */
std::string Graph::getTail()
{
  return this->tail;
}

// Setters
/**
 * @brief
 * Set the head of the graph
 * @param head
 * The head of the graph
 */

void Graph::setHead(std::string head)
{
  this->head = head;
}

/**
 * @brief
 * Set the tail of the graph
 * @param tail
 * The tail of the graph
 */
void Graph::setTail(std::string tail)
{
  this->tail = tail;
}

// Printers
/**
 * @brief
 * Print the adjacency list of the graph
 */
void Graph::print()
{
  std::vector<std::string> lines;
  std::string aux;

  std::cout << "\nAdjacency list:\n"
            << std::endl;

  for (auto &i : this->adjList)
  {
    if (i.first == this->head)
      aux += "[Head] " + i.first + " -> ";
    else
      aux += "       " + i.first + " -> ";

    for (auto &j : i.second)
      aux += "(" + j.first + ", " + j.second + ") ";

    // Add the line to the vector
    lines.insert(lines.begin(), aux);

    // Clear the aux string
    aux = "";
  }

  utils::printVector(lines);

  // Print the tail
  std::cout << "\n[Tail] " << this->tail << std::endl;
}

// Graph methods
/**
 * @brief
 * Add a node to the graph
 * @param node
 * The node to be added
 */
void Graph::addNode(std::string node)
{
  this->nodes.insert(node);
}

/**
 * @brief
 * Create a node
 * @return std::string
 * The node created
 */
std::string Graph::createNode()
{
  int node = 0;

  if (nodes.size() > 0)
    node = std::stoi(*std::max_element(nodes.begin(), nodes.end())) + 1;

  // Add the node to the set
  addNode(std::to_string(node));
  return std::to_string(node);
}

/**
 * @brief
 * Add a node to the graph as the head and tail
 * @return void
 * @details
 * This method is used to extend the graph, by adding a new head and tail.
 */

void Graph::addLimitNodes()
{
  std::string newHead = createNode();
  std::string newTail = createNode();

  // Add the new head and tail
  addEdge(newHead, this->head, "ε");
  addEdge(this->tail, newTail, "ε");

  // Update the head and tail
  this->head = newHead;
  this->tail = newTail;
}

/**
 * @brief
 * Add an edge to the graph
 * @param origin
 * The origin of the edge
 * @param destination
 * The destination of the edge
 * @param weight
 * The weight of the edge
 */
void Graph::addEdge(std::string origin, std::string destination, std::string weight)
{
  this->adjList[origin].push_back(std::make_pair(destination, weight));

  if (head == "")
    this->head = origin;

  if (origin == this->tail)
    this->tail = destination;
}

/**
 * @brief
 * Join two graphs
 * @param automata
 * The graph to be joined
 */
void Graph::join(Graph automata)
{
  std::vector<std::vector<std::string>> lines;

  int size = nodes.size();
  std::string newHead = std::to_string(size + std::stoi(automata.getHead())); // current size + head of the automata
  this->addEdge(this->tail, newHead, "ε");

  // Add the edges
  for (auto &i : automata.adjList)
    for (auto &j : i.second)
    {
      int node1 = size + std::stoi(i.first);
      int node2 = size + std::stoi(j.first);

      // Add nodes
      this->addNode(std::to_string(node1));
      this->addNode(std::to_string(node2));

      lines.push_back({std::to_string(node1), std::to_string(node2), j.second});
    }

  // Add the edges to the graph in reverse order
  for (int i = lines.size() - 1; i >= 0; i--)
    this->addEdge(lines[i][0], lines[i][1], lines[i][2]);

  // Update the tail
  this->tail = std::to_string(size + std::stoi(automata.tail));
}
