/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

int main()
{
  // TODO - Declare a stack to hold the operands
  RPNCalculator calculator;
  
  std::cout << "Enter the operators and operands ('+', '*') in a postfix format" << std::endl;

  while(true)
  {

    string input;
    cout << "#> ";
    getline(cin, input);

    if (input == "=") {

      if (calculator.isEmpty()) {
        std::cout << "No operands: Nothing to evaluate" << std::endl;
        return 0;
      }

      float result = calculator.peek()->number;
      calculator.pop();

      if (calculator.isEmpty()) { //This is the if the should handle the result   TODO: fix to 4 decimal places
        std::cout << result << std::endl;
        return 0;
      }
      else {
        std::cout << "Invalid expression" << std::endl;
        return 0;
      }
    }
    else if (isNumber(input)) { //Add number to a stack
      calculator.push(stof(input));
    }
    else {
      calculator.compute(input);
    }
  }

  return 0;
}
