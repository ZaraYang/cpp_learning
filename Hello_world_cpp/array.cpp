#include <iostream>
#include <array>

void array_def() {
	int example_array[5];
	example_array[0] = 2;
	example_array[4] = 4;
	for (int i = 0; i < 5; i++) {
		example_array[i] = i;
	}

	int count = sizeof(example_array) / sizeof(int);

	int* array_ptr = example_array;
	*(array_ptr + 2) = 6;
	*(int*)((char*)example_array + 8) = 88;
	// ������ָ�룬��ÿ���������ڴ�����Ծ�Ĳ���ȡ����ָ�������
	// int Ϊ4byte ����ÿ����Ծ4byte
	// ����Ϊchar* ��ÿ����Ծ1byte

	int* another = new int[5];
	for (int i = 0; i < 5; i++) {
		another[i] = i;
	}
	delete another;


	// array_ptr[3] = 40;
	// example_array ����һ��ָ��
	std::cout << example_array << std::endl;
}