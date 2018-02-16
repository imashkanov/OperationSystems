#include <iostream>
#include <windows.h>
#include "worker.h"
#include "structure.h"

using namespace std;


int main() {
  
  DWORD IDThread;
  HANDLE worker;
  structArr structure;
  cout << "Enter arr length: ";
  cin >> structure.length;
  structure.arr = new int[structure.length];
  for (int i=0; i< structure.length; i++) {
    cout << "enter element of array #" << i+1 << " ";
    cin >> structure.arr[i];
  }
  int work_time_limit;
  cout << "Enter worker's time limit(ms): ";
  cin >> work_time_limit;
   
  cout << "1. Run thread main " << work_time_limit << " ms..." << endl;

  worker =  CreateThread(NULL, 0, Execute, &structure, 0, &IDThread);
  if (worker == NULL) {
    int err = GetLastError();
    cout << "CreateWorker error: " << err << endl;
    return -1;
  }
  
  Sleep(work_time_limit);

  cout << "2. Do suspend worker " << work_time_limit << " ms..." << endl;

  SuspendThread(worker);

  cout << "3. Wait main for " << work_time_limit << " ms..." << endl;

  Sleep(work_time_limit);

  cout << "4. Resume worker " << work_time_limit << " ms..." << endl;

  ResumeThread(worker);

  cout << "5. Wait while worker is finished... " << endl;

  WaitForSingleObject(worker, INFINITE);

  cout << "6. Worker done." << endl;
  system("pause");

  CloseHandle(worker);
  return 0;
}