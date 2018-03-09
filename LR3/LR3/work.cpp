#include <iostream>
#include "windows.h"
#include "structure.h"

using namespace std;

void choicesSort(int arrLen, char* arr) {
  for (int i = 0; i < arrLen; i++) {
    char temp = arr[i]; // временная переменная для хранения значения перестановки
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

//поток который должен отсортировать выбором массив с заданными паузами в итерациях
DWORD WINAPI workExecute(LPVOID param) {
  //получаем указатель на структуру, преобразовывая его из обобщенного типа в конкретный
  structArr* s = (structArr*)param;
  printArr("--work: Arr before sort ", s->length, s->arr);
  //сортировка
  EnterCriticalSection(&s->csArr);
  choicesSort(s->length, s->arr);
  LeaveCriticalSection(&s->csArr);
  printArr("--work: Arr after sort ", s->length, s->arr);
  //устанавливаем событие и выходим
  SetEvent(s->sortingComplete);
  cout << "--work: done, exit" << endl;
  return 0;
}