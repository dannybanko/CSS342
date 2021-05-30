// file intset.h
// class for intset (for postivie integers)

#ifndef intset_hpp
#define intset_hpp

#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// intset class:
//  -- allows input and output of the whole intset
//  -- allows for different coomparisons of intsets element by element
//  -- size is part of class, doesn't need to be passed as param
//  -- allows for assingments of two intsets
// Implementation and assumptions:
//  -- constructor size ranges from 0 to 5, if more space is needed space
//     will be added
//  -- defuault values for use on one constructor are set to 0
//  -- user must enter + integers, if they are negative they will be ignored
//---------------------------------------------------------------------------

class IntSet {
    friend ostream& operator<<(ostream &, const IntSet &);     //output
    friend istream& operator>>(istream &, IntSet &);           //input
    
public:
    IntSet(int = -1, int = -1, int = -1, int = -1, int = -1);  //const
    ~IntSet();                                                 //dest
    IntSet(const IntSet &);                                    //copy const

    IntSet& operator=(const IntSet &);                         //assignment
    
    IntSet operator+(const IntSet &) const;     //union of two sets
    IntSet operator*(const IntSet &) const;     //intersection of two sets
    IntSet operator-(const IntSet &) const;     //difference of two sets
    
    IntSet operator+=(const IntSet &);          //+= assingment
    IntSet operator*=(const IntSet &);          //*= assignment
    IntSet operator-=(const IntSet &);          //-= assignment

    bool operator==(const IntSet &) const;      //comparison
    bool operator!=(const IntSet &) const;      //comparison

    
    bool insert(int);                           //inserts element
    bool remove(int);                           //removes element
    bool isEmpty();                             //checks for empty set
    bool isInSet(int);                          //checks if element is in
                                                // set
    
private:
    int size;                                   //size of bool array
    bool* booleanArray;                         //bool array represents ints
    void copy(const IntSet &);                  //copy using in = operator
    
};

#endif
 
