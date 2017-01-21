#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <math.h>

using namespace std;

void OutputText(vector<int> myVector, string label)
/*
Outputs the contents of the vector with proper labeling
of sorting algorithms to a text file.
*/
{
  ofstream myFile;
  //Open file
  myFile.open ("results.txt", ofstream::app);
  myFile << label << ": ";
  for (vector<int>::const_iterator i=myVector.begin();i!=myVector.end();i++)
  {
    myFile << *i << " ";
  }
  myFile << endl;
  //Close file
  myFile.close();
}

void DeleteText()
/*
Deletes the contents of the text file.
*/
{
    ofstream myFile;
    //Opening text file causes contents to be emptied
    myFile.open ("results.txt");
    //Close text file
    myFile.close ();
}

void PrintVector(vector<int> myVector)
/*
Print out all contents of vector to console.
*/
{
    for (vector<int>::const_iterator i=myVector.begin();i!=myVector.end();i++)
        {
            cout<<*i<< " ";
        }
    cout << endl;
}

void GetLines (int choice, vector<int> &dataVector)
/*
Gets a user-specifiable number of numbers from text file and stores them
in a vector.
*/
{
    //Make sure vector is empty
    dataVector.clear();

    string inputLine;
    ifstream myFile;
    int counter = 0;

    //Open file
    myFile.open ("data.txt");

    while ((myFile.good()) && (counter < choice)){
        //Read in numbers
        getline(myFile,inputLine);
        dataVector.push_back(atoi(inputLine.c_str()));
        counter++;
    }
    //Close file
    myFile.close();
}

void SelectionSort(vector<int> &vectorToSort, int vectorSize)
/*
Selection Sort algorithm
*/
{
      int i, j, minIndex, temp;
      for (i = 0; i < vectorSize - 1; i++) {
            minIndex = i;
            for (j = i + 1; j < vectorSize; j++)
                  if (vectorToSort[j] < vectorToSort[minIndex])
                        minIndex = j;
            if (minIndex != i) {
                  temp = vectorToSort[i];
                  vectorToSort[i] = vectorToSort[minIndex];
                  vectorToSort[minIndex] = temp;
            }
      }
}

void BubbleSort(vector<int> &vectorToSort, int vectorSize)
/*
Bubble Sort algorithm
*/
{
      int i, j, flag = 1;
      int temp;
      for(i = 1; (i <= vectorSize) && flag; i++)
     {
          flag = 0;
          for (j=0; j < (vectorSize -1); j++)
         {
               if (vectorToSort[j+1] < vectorToSort[j])
              {
                    temp = vectorToSort[j];
                    vectorToSort[j] = vectorToSort[j+1];
                    vectorToSort[j+1] = temp;
                    flag = 1;
               }
          }
     }
}

void Merge(vector<int> &vectorToSort, int Start, int Mid, int End)
/*Merges two sorted portions of A
Pre: A[Start..Mid] is sorted, A[Mid+1..End] is sorted
Start <= Mid <= End
Post: A[Start..End] is sorted */
{
    vector<int> Temp(vectorToSort.size());
    int P1 = Start; int P2 = Mid+1; // Indexes of current item in each sublist int
    int Spot = Start; // Present location in Temp int
    while(!(P1>Mid && P2>End)) {
        if ((P1>Mid) || ((P2<=End) && (vectorToSort[P2]<vectorToSort[P1]))) {
            Temp[Spot] = vectorToSort[P2];
            P2++;
        }
        else {
            Temp[Spot] = vectorToSort[P1];
            P1++;
        }
    Spot++;
}
    // Copy values from Temp back to A
    for (int i=Start; i<=End; i++)
        vectorToSort[i] = Temp[i];
}
//--------------------------------------------------------------------------------
void MergeSort(vector<int> &vectorToSort, int Start, int End)
/*Sorts A[Start..End] elements from low to high
Pre: Start, End >= 0
Post: Elements A[Start..End] are sorted from low to high */
{
    if (Start < End) {
        int Mid = (Start+End)/2;
        MergeSort(vectorToSort, Start, Mid);
        MergeSort(vectorToSort, Mid+1, End);
        Merge(vectorToSort, Start, Mid, End);
    }
}

void QuickSort(vector<int>& vectorToSort, int left, int right)
/*
Quick Sort algorithm
*/
{
      int i = left, j = right;
      int temp;
      int pivot = vectorToSort[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (vectorToSort[i] < pivot)
                  i++;
            while (vectorToSort[j] > pivot)
                  j--;
            if (i <= j) {
                  temp = vectorToSort[i];
                  vectorToSort[i] = vectorToSort[j];
                  vectorToSort[j] = temp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            QuickSort(vectorToSort, left, j);
      if (i < right)
            QuickSort(vectorToSort, i, right);
}

//Bucket Sort
//Splits the N elements of the unsorted Vector into m buckets, each of which stores a range of data with range N/m
//These elements are then sorted using Insertion Sort and merged together to form the sorted list; in this implementation, the data will be sorted in ascending order
void BucketSort(vector<int> &dataVector, int vectorSize)
{
//Number of buckets, m, is defined as one greater than the range of data; in this case, we are assuming from 0 – 10,000
  int m = 10001;

  //Create m empty buckets
  int buckets[m];

  //Initialize all buckets to 0
  for (int i = 0; i < m; i++)
    buckets[i] = 0;

  //Puts elements into buckets
  for (int i = 0; i < vectorSize; i++)
    buckets[dataVector[i]]++;

  //Sort using Insertion Sort and merge
  for (int i = 0, j = 0; j < m; j++)
    for (int k = buckets[j]; k > 0; k--)
      dataVector[i++] = j;
}

int main(){
    //Declare vector
    vector<int> dataVector;
    //Empty contents of text file
    DeleteText();
    //Open text file in append mode so that writes do not automatically erase file contents
    ofstream myFile;
    myFile.open ("results.txt", ofstream::app);

for (int power = 1; power < 5; power++)
{
    myFile << "Size: " << pow(10, power) << endl;
    cout << "Size: " << pow(10, power) << endl;

    //Determines sorting algorithm to use
    for (int counter = 0; counter < 5; counter++)
    {
        //Timer
        //Starts clock
        clock_t begin = clock();
        //Gets user-specifiable number of numbers from text file and stores them in a vector
        GetLines(pow(10, power), dataVector);

        //Allows all algorithms to be compared through 'switching'
        switch(counter)
       {
           case 0 : //Selection Sort
            SelectionSort(dataVector, dataVector.size());
            OutputText(dataVector, "Selection Sort");
            cout << "Selection Sort: ";
            myFile << "Selection Sort: ";
            break;
           case 1 : //Bubble Sort
            BubbleSort(dataVector, dataVector.size());
            OutputText(dataVector, "Bubble Sort");
            cout << "Bubble Sort: ";
            myFile << "Bubble Sort: ";
            break;
           case 2 : // Merge Sort
            MergeSort(dataVector, 0, dataVector.size()-1);
            OutputText(dataVector, "Merge Sort");
            cout << "Merge Sort: ";
            myFile << "Merge Sort: ";
            break;
           case 3 : //Quick Sort
            QuickSort(dataVector, 0, dataVector.size()-1);
            OutputText(dataVector, "Quick Sort");
            cout << "Quick Sort: ";
            myFile << "Quick Sort: ";
            break;
           case 4 :
            BucketSort(dataVector, dataVector.size());
            OutputText(dataVector, "Standard Sort");
            cout << "Bucket Sort: ";
            myFile << "Bucket Sort: ";
            break;
           default : //Safety feature; in case loop goes 'out of bounds'
            cout << "Invalid" << endl;
       }

        //Stops clock
        clock_t end = clock();
        //Measures time elapsed; printed onto console and into text file
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        printf ("Elapsed time is %.3lf seconds.", elapsed_secs);
        myFile << "Time elapsed: " << elapsed_secs << " seconds" << endl;
        myFile << elapsed_secs << " ";
        cout << endl;
    }

    cout << endl;
    myFile << endl;
}
//}

//Close file
myFile.close();

    return 0;
}


