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

  // Destructor
  ~Graph() = default;

  // Getters
  std::string getHead();
  std::string getTail();
  int size();
  std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> getAdjList();

  // Setters
  void setHead(std::string head);
  void setTail(std::string tail);

  // Methods
  int createNode();
  void addEdge(std::string origin, std::string destiny, std::string weight);
  void modifyDestiny(std::string origin, std::string destiny, std::string weight, std::string newDestiny);

  // Print methods
  void printAdjList();

private:
  std::string head;
  std::string tail;
  std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> adjList;
  std::set<int> nodes;
  std::set<std::string> edges;

  // Methods
};

#endif // GRAPH_H