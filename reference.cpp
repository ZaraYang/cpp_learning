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
	// reference 作为别名 alies 不占用内存
	// Increment_ptr(ptr);
	Increment_ref(ref);
	// passing by value 只是将a的数值传到函数内部的新变量中，并不会对造成影响
	std::cout << a << std::endl;
}