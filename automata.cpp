#include <iostream>
#include <regex>
#include <string>
#include <algorithm>
#include "automata.h"
#include "graph.cpp"

// Regular expressions
std::string operators = "[\\+\\|\\*\\(\\)]";
std::string expressions = "[a-zA-Z0-9]";

// Regex patterns
std::regex operPattern(operators);
std::regex exprPattern(expressions);

// Read methods

/**
 * @brief
 * Reads an expression and adds it to the stack
 * @param expression expression to be read
 * @return void
 */
void Automata::readExpression(std::string expression)
{
  std::cout << "Expression: " << expression << std::endl;

  for (char character : expression)
  {

    std::string char_(1, character);

    // Check if the character is an expression
    if (graph.size() > 0 && std::regex_match(char_, exprPattern))
      concat(char_);

    // Check if the character is the first expression
    if (graph.size() == 0 && std::regex_match(char_, exprPattern))
      setFirstNode(char_);

    if (char_ == "+")
      oneOrMore();

    if (char_ == "*")
      zeroOrMore();

    // if (std::regex_match(std::string(1, character), std::regex("\\)")))
    // {
    //   std::cout << "Get elements from stacks" << std::endl;
    // }

    // Check if the character is an operator
    if (std::regex_match(char_, operPattern))
    {
      this->addOperator(char_);
    }
  }

  graph.printAdjList();
}

// Access methods
/**
 * @brief
 * Gets the last operator of the stack
 * @return std::string Last operator of the stack
 */
std::string Automata::getLastOperator()
{
  std::string lastOperator;

  lastOperator = this->operatorStack.top();
  this->operatorStack.pop();

  return lastOperator;
}

/**
 * @brief
 * Gets the last expression of the stack
 * @return std::string Last expression of the stack
 */
std::string Automata::getLastExpression()
{
  std::string lastExpression;

  lastExpression = this->expressionStack.top();
  this->expressionStack.pop();

  return lastExpression;
}

/**
 * @brief
 * Gets the temporary head node
 * @return std::string Temporary head node
 */
std::string Automata::getTempHeadNode()
{
  return this->tempHeadNode;
}

// Setters

/**
 * @brief
 * Sets the temporary head node
 * @param tempHeadNode Temporary head node
 * @return void
 */

void Automata::setTempHeadNode(std::string tempHeadNode)
{
  this->tempHeadNode = tempHeadNode;
}

// Manipulation methods

/**
 * @brief
 * Adds an operator to the stack
 * @param operator_ Operator to be added
 * @return void
 */
void Automata::addOperator(std::string operator_)
{
  this->operatorStack.push(operator_);
}

/**
 * @brief
 * Adds an expression to the stack
 * @param expression expression to be added
 * @return void
 */

void Automata::addExpression(std::string expression)
{
  this->expressionStack.push(expression);
}

// Print methods

/**
 * @brief
 * Prints the operator stack
 * @return void
 */
void Automata::printOperatorStack()
{
  std::stack<std::string> tempStack;
  tempStack = this->operatorStack;

  std::cout << "Operator stack: ";

  while (!tempStack.empty())
  {
    std::cout << tempStack.top() << " ";
    tempStack.pop();
  }
}

/**
 * @brief
 * Prints the expression stack
 * @return void
 */

void Automata::printExpressionStack()
{
  std::stack<std::string> tempStack;
  tempStack = this->expressionStack;

  std::cout << "Expression stack: ";

  while (!tempStack.empty())
  {
    std::cout << tempStack.top() << " ";
    tempStack.pop();
  }
}

// Operator helpers

/**
 * @brief
 * Sets the first node of the graph
 * @param character character to be added
 * @return void
 */
void Automata::setFirstNode(std::string character)
{
  // Create two nodes
  int Node1 = this->graph.createNode();
  int Node2 = this->graph.createNode();

  // Set node 1 as head
  this->graph.setHead(std::to_string(Node1));
  setTempHeadNode(std::to_string(Node1));

  // Set node 2 as tail
  this->graph.setTail(std::to_string(Node2));

  // Connect node 1 to node 2 through character
  this->graph.addEdge(std::to_string(Node1), std::to_string(Node2), character);

  // Add character to expression stack
  this->addExpression(character);
}

/**
 * @brief
 * Concatenates the last two expressions
 * @param character character to be concatenated
 * @return void
 */
void Automata::concat(std::string character)
{
  // Create a new node
  int Node = this->graph.createNode();

  // Connect new node to last node
  setTempHeadNode(this->graph.getTail());
  this->graph.addEdge(this->graph.getTail(), std::to_string(Node), character);

  // Set new node as tail
  this->graph.setTail(std::to_string(Node));

  // Add character to expression stack
  this->addExpression(character);
}

/**
 * @brief
 * Allows a character to be repeated
 * @return void
 */
void Automata::oneOrMore()
{
  this->graph.addEdge(this->graph.getTail(), getTempHeadNode(), "ε");
}

/**
 * @brief
 * Zero or more. Allows a character to be repeated or not
 * @return void
 */

void Automata::zeroOrMore()
{
  oneOrMore();

  // Create 2 new nodes
  int origin = this->graph.createNode();
  int destiny = this->graph.createNode();

  // Verify if a node is already connected to the temp head
  bool found = false;
  for (auto &i : graph.getAdjList())
  {
    for (auto &j : i.second)
    {
      if (std::stoi(i.first) == std::stoi(getTempHeadNode()))
        found = true;

      if (getTempHeadNode() == j.first && found)
        graph.modifyDestiny(i.first, j.first, j.second, std::to_string(origin));
    }
  }

  // Connect origin to temp head through epsilon
  this->graph.addEdge(std::to_string(origin), getTempHeadNode(), "ε");

  // Connect current tail to destiny through epsilon
  this->graph.addEdge(this->graph.getTail(), std::to_string(destiny), "ε");

  // Connect origin to destiny through epsilon
  this->graph.addEdge(std::to_string(origin), std::to_string(destiny), "ε");

  // Set origin as temp head
  setTempHeadNode(std::to_string(origin));

  // Set destiny as tail
  this->graph.setTail(std::to_string(destiny));
}