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

	int a = 42;
	cout << e.RB_search(a)->Father_node->Key_word << endl;
	
	cout << e.RB_minimum(e.Tree_root())->Key_word << endl;

	int t = 42;
	e.RB_delete(t);
	Show_me_the_fucking_tree(e.Tree_root());
}