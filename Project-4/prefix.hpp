//----------------------------------------------------------------------------
// Prefix class:
// Takes arithmetic opperations in prefix notation. Eg (*+51-24) and
// can compute a prefix expression and produce an answer, as well as display
// the prefix expression in postfix notation (used to efficiently calculate
// arithmetic operations because the computer can easily figure out which
// operatios to do fisrt)
//
// Implementation and Assumptions:
//   -- assume data is in proper format (prefix data is displayed properrly
//      in the data file, there is no extra operators, and all digits are
//      intgers, no spaces)
//   -- every operator is followed by two operands
//   -- data is read in from a .txt file
//   -- operators are either + - * /
//   -- answers are computed as ints
//----------------------------------------------------------------------------

#ifndef PREFIX_H
#define PREFIX_H
#include <iostream>
#include <fstream>
using namespace std;

int const MAXSIZE = 100; // used to fize postfix arrray

class Prefix {
    friend ostream& operator<<(ostream&, const Prefix&); // operator<<

public:
    Prefix();                             // constructor
    void setPrefix(ifstream& infile);     // setPrefix (reads prefix)
    int evaluatePrefix() const;           // evaluatePrefix, calls ePH
    void outputAsPostfix(ostream&) const; // outpusAsPostfix, calls toPostfix

private:
    char expr[MAXSIZE+1];
    
    // (ePH) produces output using recursion
    int evaluatePrefixHelper(int&) const;
   
    // displays prefix expression in postfix notation using recusrion
    void toPostfix(int&, char [], int&) const;
};

#endif

