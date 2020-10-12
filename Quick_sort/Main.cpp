#include "include.h"
#include "class.h"


int main() {
	Without_recursive_quicksort e;
	e.import_data("D:/data/cpp_project/Heap_sort/Data/data");
	e.Show_vector();
	cout << "===============" << endl;
	e.Main_quick_sort();
	e.Show_vector();
}
