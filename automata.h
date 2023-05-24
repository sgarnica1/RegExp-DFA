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
  std::stack<std::string> operatorStack;
  std::stack<std::string> expressionStack;
  Graph graph;
  std::string tempHeadNode;

  // Methods
  void addOperator(std::string operator_);
  void addExpression(std::string expression);

  // Print methods
  void printOperatorStack();
  void printExpressionStack();

  // Getters
  std::string getLastOperator();
  std::string getLastExpression();
  std::string getTempHeadNode();

  // Setters
  void setTempHeadNode(std::string tempHeadNode);

  // Operator Helpers
  void setFirstNode(std::string character);
  void concat(std::string character);
  void oneOrMore();
  void zeroOrMore();
  void or_();
};

#endif // AUTOMATA_H
