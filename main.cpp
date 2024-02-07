#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

void ADD(int numAdded, int num, int* &heap) ;
void DELETE(int &numAdded, int* &heap);
void PRINT(int numAdded, int* heap, int index, int count);
void REMOVEALL(int& numAdded, int* &heap);

//anika gupta 2/7 max heap 



int main() {
  int numAdded = 0; //variable to keep trakc of size of heap
  int quit = 0;
  
  int* heap = new int[101];
  
  while (quit==0) {
    cout << "Options are: ADD  REMOVE   REMOVEALL  PRINT  QUIT" << endl;
    char input[50];
    cin >> input;
    if (strcmp(input, "ADD")==0) {
      cout << "Options are: FILE   MANUAL" << endl;
      char inputdos[10];
      cin >> inputdos;
      if (strcmp(inputdos, "FILE")==0) {
	// prompt for filename etc
	char fileName[20];
	cout << "What's the name of the file to open? include the .txt at the end :)" << endl;
	cin >> fileName;

	ifstream fin;
	fin.open(fileName);
	int input;
	while(fin>>input) {
	  ADD(numAdded, input, heap);
	  numAdded++;
	}
      }
      else if (strcmp(inputdos, "MANUAL")==0) {
	int n;
	cout << "What number would you like to add: ";
	cin >> n;
	if (numAdded>99) {
	  cout << "reached maximum number of numbers to add into heap." << endl;
	  cout << "quitting now." << endl;
	  quit = 1;
	}
	ADD(numAdded, n, heap);
	numAdded++;
      }
    }
    else if (strcmp(input, "PRINT")==0) {
      PRINT(numAdded+1, heap, 1, 0);
    }
    else if (strcmp(input, "QUIT")==0) {
      cout << "quitting program." << endl;
      quit = 1;
    }
    else if (strcmp(input, "REMOVE")==0) {
      DELETE(numAdded, heap);
    }
    else if (strcmp(input, "REMOVEALL")==0) {
      REMOVEALL(numAdded, heap);
    }
  }
  
  return 0;
}

void ADD(int numAdded, int num, int* &heap) {
  //cout << "reached add funct" << endl;
  int j = floor((numAdded+1)/2);
  if (numAdded==0) {
    // if theres nothing there yet
    heap[1] = num;
  }
  //int j = floor((numAdded+1)/2);
  else if (heap[j] > num) {
    // if num is the smallest value that has been added so far
    //cout << "the number you added is the smallest so far: " << num << endl;
    heap[numAdded+1] = num;
  }
  else {
    // search through heap
    int currentIndex = numAdded+1;
    heap[currentIndex] = num;
    //cout << "currentIndex: " << currentIndex << endl;
    int prevIndex = floor(currentIndex/2);
    //cout << "heap of prev: " << heap[prevIndex] << endl;
    //cout << "heap of current: " << heap[currentIndex] << endl;
    while(heap[prevIndex] < heap[currentIndex] && prevIndex>0) {
      //cout << "previous index: " << prevIndex << endl;
      //cout << "current index: " << currentIndex << endl;
      int p = heap[prevIndex];
      heap[prevIndex] = num;
      //cout << "prevIndex: " << prevIndex << " num: " << num << endl;
      heap[currentIndex] = p;
      int pivalue = prevIndex;
      currentIndex = pivalue;
      prevIndex = floor(currentIndex/2);
    }
    //cout << prevIndex << " : " << heap[prevIndex] << endl;
    //cout << currentIndex << " : " << heap[currentIndex] << endl;
    // check this .. definitely not working ?!
  }
}
void DELETE(int &numAdded, int* &heap) {

  // removes max value in heap

  
  int head = heap[1];
  heap[1] = heap[numAdded];
  heap[numAdded] = 0;
  numAdded--;
  int currentIndex = 1;
  int leftChild = heap[currentIndex*2];
  int rightChild = heap[(currentIndex*2)+1];
  while (leftChild > heap[currentIndex] || rightChild > heap[currentIndex] ) {
    
    if (leftChild > rightChild) {
      // switch to left child
      int stored = heap[currentIndex];
      heap[currentIndex] = leftChild;
      heap[currentIndex*2] = stored;
      currentIndex = currentIndex*2;
    }
    else {
      // switch to right child
      int stored = heap[currentIndex];
      heap[currentIndex] = rightChild;
      heap[(currentIndex*2)+1] = stored;
      currentIndex = (currentIndex*2)+1;
    }
    leftChild = heap[currentIndex*2];
    rightChild = heap[(currentIndex*2)+1];
    
  }
  cout << "removed: " << head << endl;
  
}
void PRINT(int numAdded, int* heap, int index, int count) {
  // checking for right

  if (((index*2)+1) < numAdded) {
    PRINT(numAdded, heap, ((index*2)+1), (count+1));
    
  }

  for (int a=0; a < count; a++) {
    cout << '\t' ;
  }
  cout << heap[index] << endl;
  if ((index*2) < numAdded) {
    count++;
    PRINT(numAdded, heap, (index*2), count);
  }
  
}

void REMOVEALL(int &numAdded, int* &heap) {

  // removes every single value in heap !
  // prints it out so you get to see all nums in descending order.
  int t = numAdded;
  for (int a=0; a<t; a++) {
    DELETE(numAdded, heap);
    //PRINT(numAdded, heap);
    //cout << a+1 << endl;
    //cout << endl;
  }
}
