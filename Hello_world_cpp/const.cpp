#include <iostream>
#include <string>

using namespace std::string_literals;


void const_def() {
	const int MAX_LEVEL = 90;
	const int* ptr_1 = new int;     // 可以改指针链接，但是不能更改内存中对应的数值
	int* const ptr_2 = new int;		// 可以更该数值，但是不能改变指针中的链接  can't resign
	const int* const ptr_3 = new int;
	
	// int const* == const int*

	int* a = new int;
	a = (int*)&MAX_LEVEL;
	// MAX_LEVEL = 52;   error
  
	// ptr_2 = &a; error
	// *ptr_1 = 45; error
	*ptr_2 = 45;




	delete ptr_1;
	delete ptr_2;
	delete ptr_3;
}	
