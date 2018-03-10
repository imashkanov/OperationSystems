#include <iostream>
#include "windows.h"
#include "structure.h"

using namespace std;

DWORD WINAPI SumElementExecute(LPVOID param) {
  //�������� ��������� �� ���������, �������������� ��� �� ����������� ���� � ����������
  structArr* s = (structArr*)param;
  //����� � ���� ������ .........
  EnterCriticalSection(&s->csArr);
  cout << "----sum: wait for sumAllowed event.." << endl;
  WaitForSingleObject(s->sumAllowed,  INFINITE);
  cout << "----sum: ...event sumAllowed, now start calculate sum" << endl;
  
  //������������
  for (int idx=0; idx<s->k; idx++) {
    s->sum += s->arr[idx];
  }

  cout << "----sum: calculate sum complete" << endl;
  
  //������������� ������� � �������
  LeaveCriticalSection(&s->csArr);
  SetEvent(s->sumComplete);
  cout << "----sum: Set event, done, exit" << endl;
  return 0;
}