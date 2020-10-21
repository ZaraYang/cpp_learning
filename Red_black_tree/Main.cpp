#include"include.h"
#include"class.h"

void Show_me_the_fucking_tree(Node* root);

int main() {
	Red_black_tree e;

	for (array<int, 20>::iterator iter = Data->begin(); iter != Data->end(); ++iter) {
		e.RB_insert(*iter);
	}
	cout << "=======================================" << endl;
	Show_me_the_fucking_tree(e.Tree_root());

}