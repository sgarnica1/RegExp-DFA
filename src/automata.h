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

  // Automata methods
  void readExpression(std::string expression);
  std::string mapExpression(std::string expression);

private:
  std::stack<Graph> automatas;
  std::stack<std::string> operators;

  // Push methods
  void pushOperator(std::string op);
  void pushAutomata(Graph automata);

  // Pop methods
  Graph popAutomata();
  std::string popOperator();

  // Getters
  Graph getAutomata();
  std::string getOperator();

  // Automata methods
  void print();
  void applyOperator(std::string op);
  int presedence(std::string op);

  // Printers
  void printAutomatas();
  void printOperators();

  // Operators
  Graph oneOrMore(Graph automata);
  Graph zeroOrMore(Graph automata);
  Graph concat(Graph automata1, Graph automata2);
  Graph orOperator(Graph automata1, Graph automata2);


};

#endif // AUTOMATA_H
