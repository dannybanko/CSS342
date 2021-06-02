#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <fstream>
using namespace std;

//----------------------------------------------------------------------------
// List class:
// ordered list of any size, the ordering is from smallest to bigges,
// which depends on the T class' operator<
// Implementation and Assumptions:
//   -- operator <, ==, etc, of T class depend on T class definitions
//   -- head will point to a real node, no fake head nodes
//   -- empty list has a head value of NULL
//   -- The insert allocates memory for a Node, ptr to the data is passed in.
//      Allocating memory and setting data is the responsibility of the caller.
//   -- data read in from file into buildList is in correct format
//----------------------------------------------------------------------------

template <typename T>
class List {

   // output operator for class List, print data,
   // responsibility for output is left to object stored in the list
   friend ostream& operator<<(ostream& output, const List<T>& thelist) {
      typename List<T>::Node* current = thelist.head;
      while (current != NULL) {
         output << *current->data;
         current = current->next;
      }
      return output;
}

public:
    List();                               // default constructor
    ~List();                              // destructor
    List(const List&);                    // copy constructor
   
    const List& operator=(const List &);  // assignment operator
    bool operator==(const List &) const;  // operator ==
    bool operator!=(const List &) const;  // operator !=
    
    bool insert(T*);                      // insert one Node into list
    bool isEmpty() const;                 // is list empty?
    void buildList(ifstream&);            // build a list from datafile
    bool retrieve(const T &, T *&);       // retrieve
    bool remove(const T&, T*&);           // remoce
    
    void merge(List&, List&);             // merge
    void intersect(const List&, const List&); // intersect
    void makeEmpty();                     // deletes every element
                                          // in the list

private:
   struct Node {            // the node in a linked list
      T* data;              // pointer to actual data, operations in T
      Node* next;
   };

    Node* head;             // pointer to first node in list
    
    void copy(const List &); // copy (used in operator = and copy const)
};

//----------------------------------------------------------------------------
// Constructor
template <typename T>
List<T>::List() {
   head = NULL;
}

//----------------------------------------------------------------------------
// Destructor *uses makeEmpty()*
template <typename T>
List<T>::~List() {
    makeEmpty();
}

//----------------------------------------------------------------------------
// copy constructor (calls copy())
template <typename T>
List<T>::List(const List& other) {
    copy(other);
}

//----------------------------------------------------------------------------
// operator =
// overload assignment operator
template <typename T>
const List<T>& List<T>::operator=(const List & other) {
    if (other.head == NULL) {
        this->makeEmpty();
    } else {
        this->makeEmpty();
        copy(other);
    }
    return *this;
}

//----------------------------------------------------------------------------
// operator ==
// checks if two lists contain the same data
template <typename T>
bool List<T>::operator==(const List & other) const {
    
    Node* current = head;             //current list head
    Node* otherCur = other.head;      //other list head

    // walk until end of the list or out of one list
    while (current != NULL && otherCur != NULL) {
        if (*current->data != *otherCur->data) {
            return false;
        }
        otherCur = otherCur->next;            // increment next
        current = current->next;              // increment next
    }
    
    return true;
}

//----------------------------------------------------------------------------
// operator !=
// checks if the two lists don't share the same data
template <typename T>
bool List<T>::operator!=(const List & other) const {
    return !(*this == other);                // calls operator==
}

//----------------------------------------------------------------------------
// copy (used in copy const. and operator=)
// makes a deep copy of the parameter list
template <typename T>
void List<T>::copy(const List& other) {

    // base case, break out of copy
    if (other.head == NULL) {
        return;
    }
    
    Node* current = new Node();    // new node for head
    Node* temp = other.head;       // pointer to head of other

    current->data = new T;         // create new data for new node
    *current->data = *temp->data;  // assign other data to new list
    this->head = current;          // assign head to the new node
    temp = temp->next;

    while (temp != NULL) {
        current->next = new Node();      // create next node
        current->next->data = new T;     // create new nodes data
        *current->next->data = *temp->data;   // assign data
        temp = temp->next;
        current = current->next;
    }

}

//----------------------------------------------------------------------------
// isEmpty
// check to see if List is empty as defined by a NULL head
template <typename T>
bool List<T>::isEmpty() const {
   return head == NULL;
}

//----------------------------------------------------------------------------
// insert
// insert an item into list; operator< of the T class
// has the responsibility for the sorting criteria
template <typename T>
bool List<T>::insert(T* dataptr) {

   Node* ptr= new Node;
   if (ptr == NULL) return false;                 // out of memory, bail
   ptr->data = dataptr;                           // link the node to data

   // if the list is empty or if the node should be inserted before
   // the first node of the list
   if (isEmpty() || *ptr->data < *head->data) {
      ptr->next = head;
      head = ptr;
   }
     
   // then check the rest of the list until we find where it belongs
   else {
      Node* current = head->next;          // to walk list
      Node* previous = head;               // to walk list, lags behind

      // walk until end of the list or found position to insert
      while (current != NULL && *current->data < *ptr->data) {
            previous = current;                  // walk to next node
            current = current->next;
      }

      // insert new node, link it in
      ptr->next = current;
      previous->next = ptr;
   }
   return true;
}

//----------------------------------------------------------------------------
// buildList
// continually insert new items into the list
template <typename T>
void List<T>::buildList(ifstream& infile) {
   T* ptr;
   bool successfulRead;                            // read good data
   bool success = false;                           // successfully insert
   for (;;) {
      ptr = new T;
      successfulRead = ptr->setData(infile);       // fill the T object
      if (infile.eof()) {
         delete ptr;
         ptr = NULL;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) {
         success = insert(ptr);
      }
      else {
         delete ptr;
         ptr = NULL;
      }
      if (!success) break;
   }
}

//----------------------------------------------------------------------------
// retrieve
// will see if list contains targeted object, and if it does we will use the
// pointer parameter to point to the target object
// returns true if target is found
template <typename T>
bool List<T>::retrieve(const T& target, T*& p) {
    
    // checks if the list has elements in it
    if (isEmpty()) {
        p = nullptr;
        return false;
    }
    
    // checks if head is the object we are looking for
    if (target == *head->data) {
           p = head->data;
           return true;
       }
    
    Node* current = head;
    
    // iterates through the list
    while (current->next != NULL && target != *current->next->data) {
        current = current->next;
    }
    
    // checks to see if the node is in the list
    if (current->next == NULL) {
        p = nullptr;
        return false;
    }
    
    // checks if current object data is equal to the target
    if (target == *current->next->data) {
        p = current->next->data;
        return true;
    }
    return false;
    p = nullptr;
}

//----------------------------------------------------------------------------
// remove
// will check the list for the desired target and then remove the target
// from the list
// returns true if sucessful remove
template <typename T>
bool List<T>::remove(const T& target, T*& p) {
    
    // checks if the list contains at least one element
    if (isEmpty()) {
        p = nullptr;
        return false;
    }
    
    // checks if the head is the target and if head-> exists
    if (target == *head->data && head->next != NULL) {
        head = head->next;
        return true;
    }
    
    Node * current = head;
    
    // will iterate through list
    while (current->next != NULL && target != *current->next->data) {
        current = current->next;
    }
    
    // checks if the node actually exists
    if (current->next == NULL) {
        p = nullptr;
        return false;
    }
    
    // removes node from the list
    p = current->next->data;
    current->next = current->next->next;
    return true;
}

//----------------------------------------------------------------------------
// merge
// takes two lists as a parameter and then merges the two lists into sorted
// order (dependent on the objects overload operators)
// no new memory allocations
// empties parameter lists if current object isn't one of the parameter
template <typename T>
void List<T>::merge(List & list1, List & list2) {
    Node* fakeHead = NULL;    // used for head of merged list
    
    Node* temp1 = list1.head;    // head of first param
    Node* temp2 = list2.head;    // head of second param
    Node* buildTemp = NULL;   // keeps track of location in merged list
    
    
    if (list1.head == NULL) {
        fakeHead = list2.head;
        
    } else if (list2.head == NULL) {
        fakeHead = list1.head;
        
    } else {
    
        // checks to see which list has the smaller head value, and then
        // assigns fakeHead
        if (*list1.head->data < *list2.head->data) {
            fakeHead = temp1;
            buildTemp = temp1;
            temp1 = temp1->next;
        } else {
            fakeHead = temp2;
            buildTemp = temp2;
            temp2 = temp2->next;
        }
    
        // will iterate until it walks off one of the lists. Assigns next
        // nodes to the fakeHead (merged list)
        while (temp1 != NULL && temp2 != NULL) {
            if (*temp1->data < *temp2->data) {
                buildTemp->next = temp1;
                temp1 = temp1->next;
            } else {
                buildTemp->next = temp2;
                temp2 = temp2->next;
            }
            buildTemp = buildTemp->next;
        }
    
        // checks to see which list was walked off
        if (temp1 == NULL) {
            buildTemp->next = temp2;
        } else if (temp2 == NULL){
            buildTemp->next = temp1;
        }
    }
    // checks if current object was a parameter list
    if (this != &list1 && this != &list2) {
        this->makeEmpty();
    }
    
    list1.head = NULL;
    list2.head = NULL;
    this->head = fakeHead;
    fakeHead = NULL;
}

//----------------------------------------------------------------------------
// intersect
// will loop through lists and find the intersecting (shared) values
// allocates new memory for intersect list
template <typename T>
void List<T>::intersect(const List & list1, const List & list2) {
    
    Node* temp1 = list1.head;
    Node* temp2 = list2.head;
    
    Node* current;
    Node* prev;
    
    Node* fakeHead = new Node();
    prev = fakeHead;
    current = fakeHead->next;

    // loops through the liats
    while (temp1 != nullptr && temp2 != nullptr) {
        // checks to see if data in list1 and list2 are equal
        if (*temp1->data == *temp2->data) {
            // sees if data has been assignes or if its duplicated
            if (prev->data == nullptr || *prev->data != *temp1->data) {
                current = new Node();
                prev->next = current;
               
                T* copyData = new T;
                *copyData = *temp1->data;
                current->data = copyData;
               
                prev = prev->next;
                current = current->next;
            }
            temp1 = temp1->next;
          // increments list1
        } else if (*temp1->data < *temp2->data) {
            temp1 = temp1->next;
          // increments list2
        } else {
            temp2 = temp2->next;
        }
    }
    
    prev->next = nullptr;
    current = fakeHead;
    fakeHead = fakeHead->next;
    head = fakeHead;
    
    delete current;
    temp1 = temp2 = fakeHead = prev = nullptr;
}

//----------------------------------------------------------------------------
// makeEmpty()
// will delete all the data and nodes in the list that its called on
template <typename T>
void List<T>::makeEmpty() {
    
    Node* current = head;
    // checks to make sure there is another node to be deleted
    while (head != NULL) {
        current = head;
        head = head->next;
        current->next = nullptr;
        delete current->data;
        current->data = nullptr;
        delete current;
    }
    head = nullptr;
}
#endif
