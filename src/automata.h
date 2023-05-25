#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <stack>
#include <utility>
#include <string>
#include <algorithm>
#include "graph.h"

/**
 * @brief
 * Automata class
 * @class Automata
 * @details
 * This class is in charge of keeping the automata data structure.
 */
class Automata
{
public:
  Automata() = default;
  ~Automata() = default;

  // Methods
  void readExpression(std::string expression);

private:
  Graph graph;
  std::string tempHeadNode;
  std::stack<std::string> operatorStack;
  std::stack<std::string> expressionStack;

  // Methods
  void addOperator(std::string operator_);
  void addExpression(std::string expression);

  // Print methods
  void printOperatorStack();
  void printExpressionStack();

  // Getters
  std::string getLastOperator();
  std::string getTempHeadNode();

  // Setters
  void setTempHeadNode(std::string tempHeadNode);

  // Modifier methods
  void popOperator();
  void popExpression();

  // Operator Helpers
  void setFirstEdge(std::string character);
  void concat(std::string character);
  void oneOrMore();
  void zeroOrMore();
  void or_(std::string weight);
};

#endif // AUTOMATA_H
