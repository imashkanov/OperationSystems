#include "Windows.h";

struct structArr {
  int length;
  int k;
  
  CRITICAL_SECTION csArr; //������ ������� arr ����������� �������
  char* arr;

  int sum;
  HANDLE sortingComplete; //������� �� ��������� ����������
  HANDLE sumAllowed; //������� �� ���������� ������ ������������
  HANDLE sumComplete; //�������� �� ��������� ������������
};