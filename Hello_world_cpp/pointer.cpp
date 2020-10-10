#include "Log.h"
#include <iostream>

void pointer_def()
{
//	int a = 8;
//	int* ptr = &a;
//	*ptr += 8;
//	std::cout << a << std::endl;

	// 向电脑索要内存
	char* buffer = new char[8];
	//每个char大小为一个字节
	memset(buffer,0,8);
	// 使用特定的数据填充内存

	// 使用new分配的应当使用delete删除
	delete[] buffer;
// 指针的类型只有在需要修改内存中的数据时起到确定修改类型的作用
	// 解引用，访问内存中的数据
	//void* ptr = 0;
	// 为0的指针是无效的，不是有效的内存地址，也可以写NULL/nullptr


}