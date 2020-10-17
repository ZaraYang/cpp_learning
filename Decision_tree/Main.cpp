#include"include.h"
#include "class.h"


static string addr = "D:/data/cpp_project/Decision_tree/Decision_tree/data_num.csv";


int main() {

	DT_data data(addr);
	Decision_tree tree;
	tree.Main_build_tree(&data);
	tree.Show_me_the_fucking_tree();

}