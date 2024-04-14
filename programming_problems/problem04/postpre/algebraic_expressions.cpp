#include <string>
using std::string;
#include <stack>
using std::stack;
#include <vector>
using std::vector;
#include <iostream>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {
    
     stack<string, vector<string>> expressionStack;

         // loop through the postfix string
    for (char c : postfix) {
        // If character is an operand, push it onto the stack
        if (!isoperator(c)) {
            expressionStack.push(std::string(1, c)); // Convert char to string and push onto stack
        } else {
            // If character is an operator, pop two operands from stack, concatenate them with the operator, and push back
            std::string operand2 = expressionStack.top();
            expressionStack.pop();
            std::string operand1 = expressionStack.top();
            expressionStack.pop();
            prefix = c + operand1 + operand2; // Construct prefix expression
            expressionStack.push(prefix);
        }
    }
  
}
