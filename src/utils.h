#ifndef UTILS_H
#define UTILS_H

// C++ standard library
#include <random>

namespace utils
{
  // creates random number generator
  std::random_device rd;
  std::mt19937 gen(rd());

  /**
   * @brief
   * Generates a random number between min and max
   * @param min Minimum value
   * @param max Maximum value
   * @return int Random number
   */

  int random(int min, int max)
  {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
  }

  /**
   * @brief
   * Print vector
   * @param v Vector to print
   * @return void
   */
  template <typename T>
  void printVector(std::vector<T> v)
  {
    for (auto i : v)
      std::cout << i << std::endl;
  }

  /**
   * @brief
   * Verify operator precedence weight
   * @param op Operator
   * @return int Weight
   */

  int precedence(std::string op)
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
}

#endif // UTILS_H