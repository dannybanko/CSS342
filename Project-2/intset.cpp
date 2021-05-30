// file intset.cpp
// Member function definitions for class IntSet

#include "intset.hpp"

//---------------------------------------------------------------------------
// constructor
// default constructor for IntSet class
IntSet::IntSet(int a, int b, int c, int d, int e) {
    
    int tempArray[5] = {a, b, c, d, e};
    int largestInt = -1;
    
    for (int i = 0; i < 5; i++) {
        if (tempArray[i] > largestInt) {
            largestInt = tempArray[i];
        }
    }
    
    size = largestInt + 1;
    
    booleanArray = new bool[size];
    
    for (int i = 0; i < size; i++) {
        booleanArray[i] = false;
    }
    
    for (int i = 0; i < 5; i++) {
        if (tempArray[i] >= 0) {
            booleanArray[tempArray[i]] = true;
        }
    }
}

//---------------------------------------------------------------------------
// destructor
// destructor for IntSet class
IntSet::~IntSet() {
    delete [] booleanArray;
    booleanArray = nullptr;
}

//---------------------------------------------------------------------------
// copy constructor
// copy constuctor for IntSet class
IntSet::IntSet(const IntSet &other) {
    copy(other);
}

//---------------------------------------------------------------------------
// operator=
// oberload assignment operator
IntSet& IntSet::operator=(const IntSet &from) {
    if (&from != this) {
       delete [] booleanArray;
       copy(from);
    }
    return *this;
}

//---------------------------------------------------------------------------
// copy
// called in the copy constructor and operator= which does the actual
// copying of the boolean array in the IntSet object
// allocates memory and and copys contents of parameter
void IntSet::copy(const IntSet &toCopy) {
    size = toCopy.size;
    booleanArray = new bool[size];
    
    for (int i = 0; i < size; i++) {
        booleanArray[i] = toCopy.booleanArray[i];
    }
}

//---------------------------------------------------------------------------
// operator+
// will return the union of two sets ex a = {1,2,3} b = {3,4,5}
// a + b = {1,2,3,4,5}
IntSet IntSet::operator+(const IntSet &a) const {
    IntSet combined;
    
    if (this->size > a.size) {
        combined.size = this->size;
    } else {
        combined.size = a.size;
    }
    
    // make the array bigger (combined.size)
    delete [] combined.booleanArray;
    combined.booleanArray = new bool[combined.size];
    
    // sets all values in combined.booleanArray to false
    for (int i = 0; i < combined.size; i++) {
        combined.booleanArray[i] = false;
    }
    
    // makes values feom this->boolArr to true in comb.boolArr
    for (int i = 0; i < this->size; i++) {
        if (this->booleanArray[i] == true) {
            combined.booleanArray[i] = true;
        }
    }
    
    // males values from a.boolArr to true in comb.boolArr
    for (int i = 0; i < a.size; i++) {
        if (a.booleanArray[i] == true) {
               combined.booleanArray[i] = true;
           }
       }
    
    return combined;
}

//---------------------------------------------------------------------------
// operator*
// returns the intersection of two intsets, that is the int values thay share
// ex a = {1,2,3} b = {0,2,3,5}  -> a + b = {2,3}
IntSet IntSet::operator*(const IntSet &b) const {
    IntSet intersection;
    
    if (this->size < b.size) {
        intersection.size = this->size;
    } else {
        intersection.size = b.size;
    }
    
    // make the array bigger (intersection.size)
    delete [] intersection.booleanArray;
    intersection.booleanArray = new bool[intersection.size];
    
    for (int i = 0; i < intersection.size; i++) {
        intersection.booleanArray[i] = false;
    }
    
    for (int i = 0; i < intersection.size; i++) {
        if (b.booleanArray[i] == true && this->booleanArray[i] == true){
            intersection.booleanArray[i] = true;
        }
    }

    return intersection;
}

//---------------------------------------------------------------------------
// operator-
// will make a copy of the local object and then find the differnece
// between the local intset and parameter intset.  ex a = {1, 2, 3, 4, 5}
// b = {2, 4, 5}    a - b = {1. 3}
IntSet IntSet::operator-(const IntSet &c) const {
    IntSet difference(*this);
    
    int smallSize;
    if (this->size > c.size) {
        smallSize = c.size;
    } else {
        smallSize = this->size;
    }
    
    for (int i = 0; i < smallSize; i++) {
        if (this->booleanArray[i] == true && c.booleanArray[i] == true) {
            difference.booleanArray[i] = false;
        }
    }
    
    return difference;
}

//---------------------------------------------------------------------------
// operator+=
// will union the two intsets and then assign the union
IntSet IntSet::operator+=(const IntSet &d) {
    return *this = *this + d;
}

//---------------------------------------------------------------------------
// operator*=
// will intersect the two intsets and then assign the intersection
IntSet IntSet::operator*=(const IntSet &e) {
    return *this = *this * e;
}

//---------------------------------------------------------------------------
// operator-=
// will differentiate the two intsets and then assign the difference
IntSet IntSet::operator-=(const IntSet &f) {
    return *this = *this - f;
}

//---------------------------------------------------------------------------
// operator==
// checks to see if two int sets are equal, runs through every element in
// booleanArray
bool IntSet::operator==(const IntSet &g) const{
    if (size != g.size) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (booleanArray[i] != g.booleanArray[i]) {
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------------------
// operatop!=
// checks to see if two int sets are not equal, runs through every element
// in booleanArray
bool IntSet::operator!=(const IntSet &h) const{
    return !(*this == h);
}

//---------------------------------------------------------------------------
// insert
// takes an int and then inserts a true value into the booleanArray that
// represents the int position
bool IntSet::insert(int number) {
    if (number < 0) {
        return false;
    } else if (number < this->size) {
        booleanArray[number] = true;
        return true;
    } else {
        return true; // need to resize array and then set new value to true
    }
}

//---------------------------------------------------------------------------
// remove
// will turn the value in the booleanArray to false in the position that
// represents the int parameter
bool IntSet::remove(int number) {\
    if (number < 0 || number > size) {
        return false;
    } else if (booleanArray[number] == true) {
        booleanArray[number] = false;
        return true;
    } else {
        return false;
    }
}

//---------------------------------------------------------------------------
// isEmpty
// checks to see if the intset has any elements
bool IntSet::isEmpty() {
    if (size <= 0) {
        return true;
    } else {
        return false;
    }
}

//---------------------------------------------------------------------------
// isInSet
// will check the boolean array for a true value given a specified int
// returns true if int is represented in boolArr, false if otherwise
bool IntSet::isInSet(int number) {
    if (number < 0) {
        return false;
    } else if (booleanArray[number] == true) {
        return true;
    } else {
        return false;
    }
}

//---------------------------------------------------------------------------
// operator<<
// output operator which is used to display an intset
ostream& operator<<(ostream &output, const IntSet &a) {
    output << "{";
    for (int i = 0; i < a.size; i ++) {
        if (a.booleanArray[i] == true) {
            output << " " << i;
        }
    }
    output << "}";
    
    return output;
}

//---------------------------------------------------------------------------
// operator>>
// allows the user to type in int values and inserts them into the boolArr
// will terminate once a negative value is inserted in the prompt
istream& operator>>(istream &input, IntSet &b) {
    int temp;
    while(true) {
        input >> temp;
        
        if(temp < 0) {
            break;
        }
        
        b.insert(temp);
    }
    return input;
}
