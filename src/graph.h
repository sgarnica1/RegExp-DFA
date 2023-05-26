#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <iomanip>
#include <utility>
#include <set>
#include <unordered_map>

/**
 * @brief
 * Graph class
 * @class Graph
 * @details
 * This class is in charge of keeping the graph data structure.
 */
class Graph
{
public:
  // Constructor
  Graph() = default;
  Graph(std::string weight);
  Graph(std::string head, std::string tail, std::string weight);

  // Destructor
  ~Graph() = default;

  // Getters
  std::string getHead();
  std::string getTail();

  // Setters
  void setHead(std::string head);
  void setTail(std::string tail);

  // Printers
  void print();

  // Graph methods
  std::string createNode();
  void addNode(std::string node);
  void addEdge(std::string origin, std::string destination, std::string weight);
  void join(Graph automata);

private:
  std::string head;
  std::string tail;
  std::set<std::string> nodes;
  std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> adjList;
};

#endif // GRAPH_H