#include <iostream>
#include "Log.h"

void Forloop(int times)
{
	for (int i = 0; i <= times; i++)
	{
		const char* s = "This is in loop:%d\n";
		printf_s(s, i);
	}
}

void Whileloop(int times)
{
	int i = 0;
	while (i < times)
	{
		Log("HELLO CPP");
		i++;
	}
}
