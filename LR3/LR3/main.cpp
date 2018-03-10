#include <iostream>
#include <Windows.h>
#include "structure.h"
#include "work.h"
#include "SumElement.h"

using namespace std;

structArr structure; //экземпл€р структуры, содержащей всю информацию о массиве, размерности и тд  
DWORD IDThreadWork; //id потока work
DWORD IDThreadSumElement; //id потока SumElement
HANDLE work; //дескриптор потока work
HANDLE SumElement; //дескриптор потока SumElement


void initData() {
  structure.length = 9;
  structure.arr = new char[structure.length];
  InitializeCriticalSection(&structure.csArr); 
 // EnterCriticalSection(&structure.csArr);
  structure.arr[0] = 'e';
  structure.arr[1] = 'd';
  structure.arr[2] = 'c';
  structure.arr[3] = 'b';
  structure.arr[4] = '4';
  structure.arr[5] = '5';
  structure.arr[6] = 'j';
  structure.arr[7] = 's';
  structure.arr[8] = 'f';
  LeaveCriticalSection(&structure.csArr);
  structure.k = 4;
  structure.sum = 0;
  structure.sortingComplete = CreateEvent(NULL, false, false, NULL);
  structure.sumComplete = CreateEvent(NULL, false, false, NULL);
}

void initThreads() {
  work = CreateThread(NULL, 0, workExecute, &structure, 0, &IDThreadWork);
  if (work == NULL) {
    int err = GetLastError();
    cout << "CreateWork error: " << err << endl;
    return;
  }
  SumElement = CreateThread(NULL, 0, SumElementExecute, &structure, 0, &IDThreadSumElement);
    if (SumElement == NULL) {
    int err = GetLastError();
    cout << "CreateSumElement error: " << err << endl;
    return;
  }
}

int main() {
  initData();
  initThreads();
  cout << "All threads started" << endl;

  cout << "main: wait for sortingComplete event... " << endl;
  WaitForSingleObject(structure.sortingComplete, INFINITE);
  cout << "main: ...event sortingComplete reached." << endl;
  SetEvent(structure.sumAllowed);

  cout << "main: wait for sumComplete event... " << endl;
  //WaitForSingleObject(structure.sumComplete,  INFINITE);
  EnterCriticalSection(&structure.csArr);
  cout << "main: ...event sumComplete reached." << endl;

  cout << "main: Calculated sum is: " << structure.sum << endl;
  LeaveCriticalSection(&structure.csArr);
  system("pause");
}