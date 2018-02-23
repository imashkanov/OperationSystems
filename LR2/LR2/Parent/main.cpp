#include <windows.h>;
#include <iostream>

using namespace std;

int main() {
  //заполняем массив символов
  int arrLen = 5;
  char* arr = new char[5]; 
  arr[0] = 'e';
  arr[1] = 'd';
  arr[2] = 'c';
  arr[3] = 'b';
  arr[4] = '4';

  char* progChild = "..\\Debug\\Child.exe";

  //узнаем будущие длины части строки, где лежит имя программы, которую запускаем, и длина командной строки с символами
  int l = (arrLen*2)+1;

  //выделяем память и копируем в будущую командную строку все по частям
  char* cmdLine = new char[l];
  
  for (int i=0; i<arrLen; i++) {
    cmdLine[2*i] = arr[i];
    cmdLine[2*i+1] = ' ';
  }

  cmdLine[l-1] = '\0';
  printf("%s\n", cmdLine);

  TCHAR Buffer[1024];
  GetCurrentDirectory(1024, Buffer);

  STARTUPINFOA si = { sizeof(STARTUPINFOA) };
  si.dwFlags = STARTF_USESHOWWINDOW;
  si.wShowWindow = SW_SHOW;
  PROCESS_INFORMATION pi;  
  bool res = CreateProcessA(progChild, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
  if (!res) {
    cout << "CreateProcess error: " << GetLastError() << endl;
    return 1;
  }

  printf("Waiting while child process terminates...\n");
  WaitForSingleObject(pi.hProcess, INFINITE);
  printf("...Child process done\n");
  return 0;
}