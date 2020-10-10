#include "include.h"
#include "class.h"


void Create_random_data(string addr, int data_num,int min, int max) {
	ofstream output(addr, ios::out);
	if (output.is_open())
		for (int i = 0; i < data_num; i++) {
			output << (rand() % (max - min)) + min <<' ';
			}
		output << endl;
		output.close();
	}


static string addr = "D:/data/cpp_project/Heap_sort/Data/data";
static string addr_1 = "D:/data/cpp_project/Heap_sort/Data/data2";
static int data_num = 1000;


int main() {
//	Heap_sort Main_heap(data_num);
//	Main_heap.Heap_import_from_file(addr);
//	Main_heap.Sort();
//	Main_heap.Show_heap();

//	Priority_queue Main_Queue;
//	Main_Queue.Heap_import_from_file(addr_1);
//	Main_Queue.Show_heap();

//	int a = 1;
//	float b = 55.44;
//	Main_Queue.Increase_priority(a,b);
//	Main_Queue.Show_heap();

//	Heap_element element = Main_Queue.Return_maximum();
//	cout << element.Show_priority() << endl;

//	cout << "============================" << endl;
//	Heap_element element = Main_Queue.Extract_maximum();
//	Main_Queue.Show_heap();
//	cout << element.Show_priority() << endl;

//	int index = 1;
//	Main_Queue.Delete_task(index);
//	Main_Queue.Show_heap();


//	}
}
