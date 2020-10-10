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
	// 数组是指针，其每次索引在内存中跳跃的步长取决于指针的类型
	// int 为4byte 所以每次跳跃4byte
	// 若改为char* 则每次跳跃1byte

	int* another = new int[5];
	for (int i = 0; i < 5; i++) {
		another[i] = i;
	}
	delete another;


	// array_ptr[3] = 40;
	// example_array 返回一个指针
	std::cout << example_array << std::endl;
}