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
  std::stack<std::string> positionStack;
  std::string prev;

  // Methods
  void addOperator(std::string operator_);
  void addExpression(std::string expression);
  void addPosition(std::string position);

  // Print methods
  void printOperatorStack();
  void printExpressionStack();
  void printPositionStack();

  // Getters
  std::string getLastOperator();
  std::string getTempHeadNode();
  std::string getLastPosition();
  std::string getPrev();

  // Setters
  void setTempHeadNode(std::string tempHeadNode);
  void setPrev(std::string prev);

  // Modifier methods
  void popOperator();
  void popExpression();
  void popPosition();

  // Operator Helpers
  void setFirstEdge(std::string character);
  void concat(std::string character);
  void oneOrMore();
  void zeroOrMore();
  void or_(std::string origin, std::string destiny);
};

#endif // AUTOMATA_H
