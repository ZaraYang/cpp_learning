#include <iostream>
#include <string>

using namespace std::string_literals;


void const_def() {
	const int MAX_LEVEL = 90;
	const int* ptr_1 = new int;     // ���Ը�ָ�����ӣ����ǲ��ܸ����ڴ��ж�Ӧ����ֵ
	int* const ptr_2 = new int;		// ���Ը�����ֵ�����ǲ��ܸı�ָ���е�����  can't resign
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
