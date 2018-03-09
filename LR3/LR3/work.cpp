#include <iostream>
#include "windows.h"
#include "structure.h"

using namespace std;

void choicesSort(int arrLen, char* arr) {
  for (int i = 0; i < arrLen; i++) {
    char temp = arr[i]; // ��������� ���������� ��� �������� �������� ������������
    for (int j = i + 1; j < arrLen; j++) {
      if (arr[i] > arr[j]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    Sleep(200);
  }
}

void printArr(char* caption, int arrLen, char* arr) {
  cout << caption;
  for (int idx = 0; idx<arrLen; idx++) {
    cout << arr[idx];
  }
  cout << endl;
}

//����� ������� ������ ������������� ������� ������ � ��������� ������� � ���������
DWORD WINAPI workExecute(LPVOID param) {
  //�������� ��������� �� ���������, �������������� ��� �� ����������� ���� � ����������
  structArr* s = (structArr*)param;
  printArr("--work: Arr before sort ", s->length, s->arr);
  //����������
  EnterCriticalSection(&s->csArr);
  choicesSort(s->length, s->arr);
  LeaveCriticalSection(&s->csArr);
  printArr("--work: Arr after sort ", s->length, s->arr);
  //������������� ������� � �������
  SetEvent(s->sortingComplete);
  cout << "--work: done, exit" << endl;
  return 0;
}