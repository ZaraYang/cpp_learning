#include <iostream>
#include "Log.h"

int Increment(int value)
{
	value++;
	return value;
}
int Increment_ptr(int* value_ptr)
{
	(*value_ptr)++;
	return(*value_ptr);
}

int Increment_ref(int& value_ref)
{
	value_ref++;
	return(value_ref);
}


void reference_def()
{
	int a = 5;
	int& ref = a;
	int* ptr = &a;
	// reference ��Ϊ���� alies ��ռ���ڴ�
	// Increment_ptr(ptr);
	Increment_ref(ref);
	// passing by value ֻ�ǽ�a����ֵ���������ڲ����±����У�����������Ӱ��
	std::cout << a << std::endl;
}