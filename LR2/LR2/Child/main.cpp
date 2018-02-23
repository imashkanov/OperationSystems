#include <windows.h>;
#include <iostream>

using namespace std;

void choicesSort(int arrLen, char* arr[]) {
  for (int i = 0; i < arrLen; i++) {
    char* temp = arr[i]; // временная переменная для хранения значения перестановки
    for (int j = i + 1; j < arrLen; j++) {
      if (*arr[i] > *arr[j]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

int main(int argCnt, char* argValues[]) {
  printf("Child process started\n");
  choicesSort(argCnt, argValues);
  for (int i=0; i< argCnt; i++) {
    printf("%s ", argValues[i]);
  }
  printf("\n");
  printf("Child process is done\n");
  system("pause");
  return 0;
}