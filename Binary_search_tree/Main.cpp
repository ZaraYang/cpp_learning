#include "include.h"
#include "class.h"

int main() {
	Binary_search_tree* e = new Binary_search_tree();
	e->Build_tree(Data);
	e->Inorder_tree_walk();

	int b = 34;
	Node* a = e->Tree_search(b);
	Node* r = e->Tree_successor(a);
	Node* p = e->Tree_predecessor(a);
	cout << a->Key_word << endl;
	cout << r->Key_word << endl;
	cout << p->Key_word << endl;

	int c = 666;
	e->Tree_insert(c);
	e->Inorder_tree_walk();

	int g = 12;
	Node* d = e->Tree_search_iterative(g);
	e->Tree_delete(d);
	e->Inorder_tree_walk();
}