#include <iostream>
#include "windows.h"
#include "structure.h"

using namespace std;

DWORD WINAPI SumElementExecute(LPVOID param) {
  //�������� ��������� �� ���������, �������������� ��� �� ����������� ���� � ����������
  structArr* s = (structArr*)param;

  cout << "----sum: wait for sumAllowed event.." << endl;
  WaitForSingleObject(s->sumAllowed,  INFINITE);
  cout << "----sum: ...event sumAllowed, now start calculate sum" << endl;
  
  //������������
  for (int idx=0; idx<s->k; idx++) {
    s->sum += s->arr[idx];
  }

  cout << "----sum: calculate sum complete" << endl;

  //������������� ������� � �������
  SetEvent(s->sumComplete);
  cout << "----sum: Set event, done, exit" << endl;
  return 0;
}