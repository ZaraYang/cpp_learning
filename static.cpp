#include <iostream>
#include "Log.h"



// 函数内部的static变量寿命为整个程序时间，作用域为该函数内部

void Function()
{
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}

