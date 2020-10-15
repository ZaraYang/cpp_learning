#include"include.h"
#include "Decision_tree.h"
#include "Data_struct.h"


static string addr = "D:/data/cpp_project/Decision_tree/Decision_tree/data_num.csv";


void main() {

	Decision_tree_data Data(addr);
	Basic_decision_tree Tree(&Data);

	
}