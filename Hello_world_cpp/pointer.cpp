#include "Log.h"
#include <iostream>

void pointer_def()
{
//	int a = 8;
//	int* ptr = &a;
//	*ptr += 8;
//	std::cout << a << std::endl;

	// �������Ҫ�ڴ�
	char* buffer = new char[8];
	//ÿ��char��СΪһ���ֽ�
	memset(buffer,0,8);
	// ʹ���ض�����������ڴ�

	// ʹ��new�����Ӧ��ʹ��deleteɾ��
	delete[] buffer;
// ָ�������ֻ������Ҫ�޸��ڴ��е�����ʱ��ȷ���޸����͵�����
	// �����ã������ڴ��е�����
	//void* ptr = 0;
	// Ϊ0��ָ������Ч�ģ�������Ч���ڴ��ַ��Ҳ����дNULL/nullptr


}