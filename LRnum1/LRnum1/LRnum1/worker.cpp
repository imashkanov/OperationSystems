#include <iostream>
#include <windows.h>
#include "structure.h"

using namespace std;


DWORD WINAPI Execute(LPVOID param) {
  structArr* str = (structArr*)param;
  int cnt = 0;
  for (int i=0; i< str->length; i++) {
    if (str->arr[i] == 0) 
      cnt++;
    Sleep(12);
  }
  cout << endl << "   Count for 0's elements: " << cnt << endl;
  return 0;
}