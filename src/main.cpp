#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "automata.cpp"

int main(int argc, char *argv[])
{
  // Check if the number of arguments is correct
  if (argc != 3)
  {
    std::cout
        << "Usage: " << argv[0]
        << " <input_filename> <output_filename>" << std::endl;

    return 1;
  }

  std::ifstream inputFile;
  std::ofstream outputFile;

  // Open the input file
  inputFile.open(argv[1]);

  if (!inputFile.is_open())
  {
    std::cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  // Open the output file
  outputFile.open(argv[2]);

  if (!outputFile.is_open())
  {
    std::cout << argv[0] << ": File \"" << argv[2] << "\" not found\n";
    return -1;
  }

  // Read the input file
  std::string line;
  while (std::getline(inputFile, line))
  {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word)
    {
      outputFile << word << std::endl;
    }
  }

  // Close the files
  inputFile.close();
  outputFile.close();

  // Temporary logic
  Automata automata;
  automata.readExpression("a|b");

  return 0;
}