#include "include.h"
#include "class.h"



// �㷨����p129 ���������ݽṹ
void main() {
//	Singly_linked_list e;
//	for (int i = 0; i < 10; i++) {
//		e.Insert(i);
//	}
//	e.Show_link_list();
//	e.Delete(5);
//	e.Show_link_list();

	Queue e;
	for (int i = 0; i < 10; i++) {
		e.Enqueue(i);
	}
	e.Show_link_list();
	e.Dequeue();
	e.Show_link_list();
}



