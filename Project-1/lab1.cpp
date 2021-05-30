//-----------------------------------------------------------------------------
// Sorting students by last name, if last names are the same then we sort by
// first name. Displaying a list using insetion sort using standard output.
// Data includes last name, first name, and grade
// Example: Mouse Minne 95

// Assumptions, implementation details:
//    -- Format of data is correct.
//    -- All names are not longer than MAXLENGTH..
//    -- Data above MAXSIZE (100) is not stored in the list.

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;            // maximum number of records in total
int const MAXLENGTH = 31;           // maximum string length
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const GROUP = 10;               // group amount
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/GROUP + 1;   // grouped by GROUP

struct StudentType  {               // information of one student
   int grade;                       // the grade of the student
   char last[MAXLENGTH];            // last name (MAXLENGTH-1 at most)
   char first[MAXLENGTH];           // first name (MAXLENGTH-1 at most)
};

// prototypes
bool sortInput(ifstream&, StudentType [], int&);    // reads and places input
void displayList(StudentType [], int&);             // prints the list
void setHistogram(StudentType [], int[], int&);     // insets grades into histo
void displayHistogram(int[]);  // displays the histo
int findAverage(StudentType[], int&);

//-----------------------------------------------------------------------------

int main()  {
   StudentType students[MAXSIZE];   // list of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE];    // grades grouped by GROUP
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile("data1.txt");
   if (!infile)  {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);
   //    display list, histogram, and class average
   if (successfulRead)  {
      displayList(students, size);
      setHistogram(students, histogram, size);
      displayHistogram(histogram);
      average = findAverage(students, size);
      cout << "Average grade: " << average << endl << endl;
   }
   return 0;
}

// ----------------------------------------------------------------------------
// sortInput
// reading in data from a txt file (first parameter), then sorting the data
// into the correct spot in the array (second parameter), then size (third
// paramteter) is a way to measure the ammount of items in the array always
// less than MAXSIZE

bool sortInput(ifstream& infile, StudentType students[], int& size) {
    StudentType temp;            // temporary location for StudentType
    
    infile >> temp.last;         // reads in last name to temp
    strncpy(students[size].last, temp.last, MAXLENGTH);
    infile >> students[size].first >> students[size].grade;
    size++;                      // adds first person so size is 1
    
    while (size < MAXSIZE) {
        infile >> temp.last;
        
        if (infile.eof()) {      // checks to make sure theres more data
            break;
        }
        
        infile >> temp.first >> temp.grade;
        
        if (temp.grade < LOWGRADE || temp.grade > MAXGRADE) {
            continue;            // ignores bad data
        }
        
        int i;
        
        for (i = size - 1; i >= 0; i--) {
            if (strncmp(temp.last, students[i].last, MAXLENGTH) < 0) {
                students[i + 1] = students [i];
            } else if (strncmp(temp.last, students[i].last, MAXLENGTH) == 0 &&
                       strncmp(temp.first, students[i].first, MAXLENGTH) < 0) {
                students[i + 1] = students [i];
            } else {
                break;
            }
        }
        students[i + 1] = temp;
        size++;
    }
    return true;
}

// ----------------------------------------------------------------------------
// displayList
// loops through the array students (first parameter), then prints the students
// last name, first name, and size (already in sorted order from sortInput).
// size is used to keep track of the number of StudentType in students[]

void displayList(StudentType students[], int& size) {
    cout << "List of names sorted:" << endl;
    
    for(int i = 0; i < size; i++) {
        cout << setw(3) << students[i].grade << " " << students[i].last << " "
        << students[i].first << endl;
    }
    
    cout << endl;
}

// ----------------------------------------------------------------------------
// setHistogram
// Uses the students array to access each students grade and place it into
// grade intervals in the histogram array. For example, if minnie mouse has
// grade 95, then we will increment the count in the interval 90-99. Size is
// used to keep track of how many students are needed to account for.

void setHistogram(StudentType students[], int histogram[], int& size) {
    
    for (int i = 0; i < HISTOGRAMSIZE; i++) {
        histogram[i] = 0;     // sets all values in histogram to 0
    }
    
    for (int i = 0; i < size; i++) {
        if (students[i].grade >= LOWGRADE && students[i].grade <= 9) {
            histogram[0]++;
        } else if (students[i].grade >= 10 && students[i].grade <= 19) {
            histogram[1]++;
        } else if (students[i].grade >= 20 && students[i].grade <= 29) {
            histogram[2]++;
        } else if (students[i].grade >= 30 && students[i].grade <= 39) {
            histogram[3]++;
        } else if (students[i].grade >= 40 && students[i].grade <= 49) {
            histogram[4]++;
        } else if (students[i].grade >= 50 && students[i].grade <= 59) {
            histogram[5]++;
        } else if (students[i].grade >= 60 && students[i].grade <= 69) {
            histogram[6]++;
        } else if (students[i].grade >= 70 && students[i].grade <= 79) {
            histogram[7]++;
        } else if (students[i].grade >= 80 && students[i].grade <= 89) {
            histogram[8]++;
        } else if (students[i].grade >= 90 && students[i].grade <= 99) {
            histogram[9]++;
        } else if (students[i].grade == 100) {
            histogram[10]++;
        }
    }
}

// ----------------------------------------------------------------------------
// displayHistogram
// Will run throught the histogram array (parameter one) and see the values
// that are assigned in the array. After the value of the histogram array is
// found, then it will print out that many * symbols to signify how many
// students got a grade in that range.

void displayHistogram(int histogram[]) {
    cout << "Histogran of grades:" << endl;
    
    for(int i = 0; i < HISTOGRAMSIZE - 1; i++) {
        cout << setw(3) << 10 * i << "--> " << setw(3) << 10 * (i +1) - 1 << ": ";
        for(int j = 0; j < histogram[i]; j++) {
            cout << "*";
        };
        cout << endl;
    }
    
    for(int i = 10; i < HISTOGRAMSIZE; i++) {
        cout << setw(3) << 100 << "--> " << setw(3) << 100 << ": ";
        for(int j = 0; j < histogram[i]; j++) {
            cout << "*";
        };
    }
    
    cout << endl << endl;
}

// ----------------------------------------------------------------------------
// findAverage
// Takes the students array (first parameter) and adds all the students grades
// into local variable (sum). Then uses size (second parameter) to divde the
// sum to comput the average score. Returns int value of average score.

int findAverage(StudentType students[], int& size) {
    int sum = 0;
    
    for (int i = 0; i < size; i++) {
        sum = sum + students[i].grade;
    }
    
    return sum/size;
}
