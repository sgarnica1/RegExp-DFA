#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "automata.cpp"

int main(int argc, char *argv[])
{
  // Receive input prompt
  std::string input;

  std::cout << "Enter a regular expression: ";
  std::getline(std::cin, input);

  // Temporary logic
  Automata automata;
  automata.readExpression(input);

  return 0;
}