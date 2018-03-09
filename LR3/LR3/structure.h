#include "Windows.h";

struct structArr {
  int length;
  int k;
  
  CRITICAL_SECTION csArr; //защита массива arr критической секцией
  char* arr;

  int sum;
  HANDLE sortingComplete; //событие на окончение сортировки
  HANDLE sumAllowed; //событие на разрешение начала суммирования
  HANDLE sumComplete; //сообытие на окончание суммирования
};