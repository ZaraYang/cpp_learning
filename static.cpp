#include <iostream>
#include "Log.h"



// �����ڲ���static��������Ϊ��������ʱ�䣬������Ϊ�ú����ڲ�

void Function()
{
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}

