#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
#include "automata.h"
#include "graph.cpp"

std::string OPERATORS = "[\\+\\|\\*\\-]";
std::string OPERANDS = "[a-zA-Z0-9]";
std::string CONCAT_OP = "-";

std::regex operatorsPattern(OPERATORS);
std::regex operandsPattern(OPERANDS);

// Automata methods

/**
 * @brief
 * Read the expression
 * @param expression
 * The expression to read
 */
void Automata::readExpression(std::string expression)
{
  expression = mapExpression(expression);

  for (char char_ : expression)
  {
    std::string character(1, char_);

    // Match operands
    if (std::regex_match(character, operandsPattern))
      pushAutomata(Graph(character));

    // Match opening parenthesis
    if (character == "(")
      pushOperator(character);

    // Match operators
    if (std::regex_match(character, operatorsPattern))
    {
      // If operators stack is empty, add the operator
      if (operators.size() == 0)
      {
        pushOperator(character);

        if (character == "*" || character == "+")
        {
          std::string lastOp = getOperator();
          popOperator();
          applyOperator(lastOp);
        }
        continue;
      }

      // If it is not empty, compare current op presedence with last op in stack
      if (presedence(character) > presedence(getOperator()))
        pushOperator(character);
      else
      {
        std::string lastOp = getOperator();
        popOperator();
        applyOperator(lastOp);
        pushOperator(character);
      }
    }

    if (character == ")")
    {
      while (operators.top() != "(")
      {
        std::string lastOp = getOperator();
        popOperator();
        applyOperator(lastOp);
      }
    }
  }

  while (!operators.empty())
  {
    std::string lastOp = getOperator();
    popOperator();
    applyOperator(lastOp);
  }

  std::cout << "\n--- NDFA --- ";
  printAutomatas();
}

/**
 * @brief
 * Modify the expression to add the concatenation operator
 * @param expression
 * The expression to modify
 * @return std::string
 */

std::string Automata::mapExpression(std::string expression)
{
  std::string mappedExpression = "";

  for (int i = 0; i < expression.length(); i++)
  {
    std::string character(1, expression[i]);

    if (i + 1 < expression.length())
    {
      std::string nextCharacter(1, expression[i + 1]);

      mappedExpression += character;

      if (std::regex_match(character, operandsPattern) && (std::regex_match(nextCharacter, operandsPattern) || nextCharacter == "("))
        mappedExpression += CONCAT_OP;

      if (character == "*" || character == "+")
        mappedExpression += CONCAT_OP;
    }
  }

  mappedExpression += expression[expression.length() - 1];

  return mappedExpression;
}

// Private methods

// Push methods
/**
 * @brief
 * Push an operator to the stack
 * @param op
 * The operator to push
 */
void Automata::pushOperator(std::string op)
{
  this->operators.push(op);
}

/**
 * @brief
 * Push an automata to the stack
 * @param automata
 * The automata to push
 */

void Automata::pushAutomata(Graph automata)
{
  this->automatas.push(automata);
}

// Pop methods
/**
 * @brief
 * Pop an automata from the stack
 * @return Graph
 * The automata popped
 */
Graph Automata::popAutomata()
{
  Graph automata = this->automatas.top();
  this->automatas.pop();
  return automata;
}

/**
 * @brief
 * Pop an operator from the stack
 * @return std::string
 * The operator popped
 */
std::string Automata::popOperator()
{
  std::string op = this->operators.top();
  this->operators.pop();
  return op;
}

// Getters
/**
 * @brief
 * Get the automata from the stack
 * @return Graph
 * The automata
 */

Graph Automata::getAutomata()
{
  return this->automatas.top();
}

/**
 * @brief
 * Get the operator from the stack
 * @return std::string
 * The operator
 */

std::string Automata::getOperator()
{
  return this->operators.top();
}

// Automata methods
/**
 * @brief
 * Apply the operator
 */
void Automata::applyOperator(std::string op)
{
  Graph automata;

  if (op == "*")
    automata = zeroOrMore(popAutomata());
  else if (op == "+")
    automata = oneOrMore(popAutomata());
  else if (op == CONCAT_OP)
    automata = concat(popAutomata(), popAutomata());
  else if (op == "|")
    automata = orOperator(popAutomata(), popAutomata());
  else
    return;

  pushAutomata(automata);
}

/**
 * @brief
 * Verify operator precedence weight
 * @param op Operator
 * @return int Weight
 */
int Automata::presedence(std::string op)
{
  if (op == "*")
    return 5;
  else if (op == "+")
    return 4;
  else if (op == ".")
    return 3;
  else if (op == "|")
    return 2;
  else if (op == "(" | op == ")")
    return 1;
  else
    return -1;
}

// Printers

/**
 * @brief
 * Print the automata
 */
void Automata::print()
{
  std::cout << "Automata: " << std::endl;
}

/**
 * @brief
 * Print the automatas
 */
void Automata::printAutomatas()
{
  std::stack<Graph> tempStack = automatas;

  while (!tempStack.empty())
  {
    Graph element = tempStack.top();
    tempStack.pop();
    element.print();
  }
}

/**
 * @brief
 * Print the operators
 */
void Automata::printOperators()
{
  std::stack<std::string> tempStack = operators; // Create a temporary stack

  while (!tempStack.empty())
  {
    std::string element = tempStack.top(); // Get the top element
    tempStack.pop();                       // Remove the top element
    std::cout << element << " ";           // Print the element
  }
}

// Operators

/**
 * @brief
 * Concatenate two automatas
 * @param automata1
 * The first automata
 * @param automata2
 * The second automata
 * @return Graph
 * The concatenated automata
 */

Graph Automata::concat(Graph graph1, Graph graph2)
{
  graph1.join(graph2);
  return graph1;
}

/**
 * @brief
 * Apply the one or more operator
 * @param automata
 * The automata to apply the operator
 * @return Graph
 * The automata with the operator applied
 */

Graph Automata::oneOrMore(Graph automata)
{
  std::string head = automata.getHead();
  std::string tail = automata.getTail();

  automata.addLimitNodes();
  automata.addEdge(tail, head, "ε");
  return automata;
}

/**
 * @brief
 * Apply the zero or more operator
 * @param automata
 * The automata to apply the operator
 * @return Graph
 * The automata with the operator applied
 */

Graph Automata::zeroOrMore(Graph automata)
{
  automata = oneOrMore(automata);
  automata.addEdge(automata.getHead(), automata.getTail(), "ε");
  return automata;
}

/**
 * @brief
 * Apply the or operator
 * @param automata1
 * The first automata
 * @param automata2
 * The second automata
 * @return Graph
 * The automata with the operator applied
 */

Graph Automata::orOperator(Graph automata1, Graph automata2)
{
  // Get the tail of the automata 1
  std::string tail = automata1.getTail();

  // Copy automata 2 in automata 1 and get the limits
  std::pair<int, int> limits = automata1.addGraph(automata2);

  // Get the head of the automata 2
  std::string head = std::to_string(limits.first);

  // Add the new head and tail to the automata 1
  automata1.addLimitNodes();

  // Add the new edges
  automata1.addEdge(automata1.getHead(), head, "ε");
  automata1.addEdge(tail, automata1.getTail(), "ε");

  return automata1;
}