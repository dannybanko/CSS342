#include "prefix.hpp"

//-----------------------------------------------------------------------------
// constructor
// initialize the array to the empty string,
// char arrays end with '\0' (null character) so operator<< works properly

Prefix::Prefix() {
   expr[0] = '\0';
}

//-----------------------------------------------------------------------------
// setPrefix
// Set a prefix expression made of single digit operands, operators +,-,*,/
// and no blanks or tabs contained in a file. The expression is valid in
// that each valid operator has two valid operands.

void Prefix::setPrefix(ifstream& infile) {
    infile >> expr;
}

//-----------------------------------------------------------------------------
// evaluatePrefix
// Evaluate a prefix expr made of single digit operands and operators +,-,*,/
// Return the answer (integer arithmetic).

int Prefix::evaluatePrefix() const {
    if (expr[0] == '\0')                          // empty string
        return 0;

    int index = -1;                               // to walk through expr
    return evaluatePrefixHelper(index);
}

//-----------------------------------------------------------------------------
// evaluatePrefixHelper
// identify the opperator, and then find the following digits to perform the
// operator on. Recusrsively calls itself until the operation is perfomed on
// the two digits.

int Prefix::evaluatePrefixHelper(int& index) const {
    char symbol = expr[++index];
    
    // base case
    // if symbol is a number 1 through 9, stop recursive calls
    // and return
    if (isdigit(symbol)) {
        return symbol - '0'; // converts symbol to int
    }

    // checks to see which operator symbol, then recursively calls until
    // two digits are found to perform the operation
    switch (symbol) {
        case '+':
            return evaluatePrefixHelper(index) + evaluatePrefixHelper(index);
            break;
        case '-':
            return evaluatePrefixHelper(index) - evaluatePrefixHelper(index);
            break;
        case '*':
            return evaluatePrefixHelper(index) * evaluatePrefixHelper(index);
            break;
        case '/':
            return evaluatePrefixHelper(index) / evaluatePrefixHelper(index);
            break;
    }
    return -1;
}

//-----------------------------------------------------------------------------
// outputAsPostfix, toPostfix
// Convert prefix expression to postfix and output

void Prefix::outputAsPostfix(ostream& out) const {
    if (expr[0] == '\0')                      // empty string
        return;

    int index = -1;                           // to walk through expr
    int count = -1;                           // used to build postfix array
    char postfix[MAXSIZE+1];                  // holds postfix expression
    toPostfix(index, postfix, count);
    postfix[++count] = '\0';
    out << postfix;
}

//-----------------------------------------------------------------------------
// toPostfix
// Recusively turns prefix expression into postfix expression

void Prefix::toPostfix(int& index, char postfix[], int& count) const {
    char symbol = expr[++index];

    // base csae, if didgit is found, put in in postfix[]
    if (isdigit(symbol)) {
        ++count;
        postfix[count] = symbol;               // put digit in postfix[]
    } else {
        toPostfix(index, postfix, count);      // find first digit
        toPostfix(index, postfix, count);      // find second digit
        count++;
        postfix[count] = symbol;               // add operator to postfix[]
    }
}

//-----------------------------------------------------------------------------
// operator<<
// display prefix expression as a string (char array)

ostream& operator<<(ostream& output, const Prefix& expression) {
    output << expression.expr;
    return output;
}
