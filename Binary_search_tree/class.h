#pragma once
#include "include.h"


// �����������ڵ�
struct Node
{	
	Node* Father_node=nullptr;
	Node* Left_son_node=nullptr;
	Node* Right_son_node=nullptr;
	int Key_word = NULL;

	Node(){}
	Node(Node* father,int k)
		:Father_node(father),Key_word(k){}
	Node(int k)
		:Key_word(k){}
	bool operator>(Node& node) {
		return Key_word >= node.Key_word;
	}
	bool operator<(Node& node) {
		return Key_word < node.Key_word;
	}
};

class Binary_search_tree {
private:
	Node* Root = new Node;
public:
	Node* My_root() { return Root; }

	// ����
	void Build_tree(array<int, 20>* data) {
		array<int, 20>::iterator iter = data->begin();
		for (; iter != data->end(); ++iter) {
			Build_tree_with_recursive(*iter,Root);
		}
	}
	int Build_tree_with_recursive(int& data, Node* node) {
		if (node->Key_word == NULL) {
			node->Key_word = data;
			return NULL;
		}
		else {
			
			if (node->Key_word > data) {
				if (node->Left_son_node == nullptr) {
					Node* temp_node_ptr = new Node(data);
					node->Left_son_node = temp_node_ptr;
					temp_node_ptr->Father_node = node;
					return NULL;
				}
				else {
					Build_tree_with_recursive(data, node->Left_son_node);
				}
			}
			else {
				if (node->Right_son_node == nullptr) {
					Node* temp_node_ptr = new Node(data);
					node->Right_son_node = temp_node_ptr;
					temp_node_ptr->Father_node = node;
					return NULL;
				}
				else {
					Build_tree_with_recursive(data, node->Right_son_node);
				}

			}

		}
	}

	// �������
	int Inorder_tree_walk(Node* node_ptr) {
		if (node_ptr == nullptr) { return NULL; }
		Inorder_tree_walk(node_ptr->Left_son_node);
		cout << node_ptr->Key_word << " , ";
		Inorder_tree_walk(node_ptr->Right_son_node);
	}
	void Inorder_tree_walk() {
		Inorder_tree_walk(Root);
		cout << endl;
	}

	// �����������ĵݹ�����
	Node* Tree_search(Node* node,int& k) {
		if ((node == nullptr) || (node->Key_word == k)) {
			return node;
		}
		else {
			if (k < node->Key_word) {
				return Tree_search(node->Left_son_node, k);
			}
			else {
				return Tree_search(node->Right_son_node, k);
			}
		}
	}
	Node* Tree_search(int& k) {
		return Tree_search(Root, k);
	}

	// �����������ĵ�������
	Node* Tree_search_iterative(Node* n, int& k) {
		while (n != nullptr && n->Key_word != k) {
			if (k < n->Key_word) {
				n = n->Left_son_node;
			}
			else {
				n = n->Right_son_node;
			}
		}
		return n;
	}
	Node* Tree_search_iterative(int& k) {
		Node* temp_root = Root;
		return Tree_search_iterative(temp_root, k);
	}

	// ������������������Сֵ
	Node* Tree_minimun(Node* node) {
		while (node->Left_son_node != nullptr) {
			node = node->Left_son_node;
		}
		return node;
	}
	Node* Tree_minimun() {
		return Tree_minimun(Root);
	}

	// �������������������ֵ
	Node* Tree_maximum(Node* node) {
		while (node->Right_son_node != nullptr) {
			node = node->Right_son_node;
		}
		return node;
	}
	Node* Tree_maximum() {
		Tree_maximum(Root);
	}
	
	// �����������һλ
	Node* Tree_successor(Node* node_ptr) {
		if (node_ptr->Right_son_node != nullptr) {
			return Tree_minimun(node_ptr->Right_son_node);
		}
		Node* parent_ptr = node_ptr->Father_node;
		while (parent_ptr != nullptr && parent_ptr->Right_son_node == node_ptr) {
			node_ptr = parent_ptr;
			parent_ptr = parent_ptr->Father_node;
		}
		return parent_ptr;
	}

	// ���������һλ
	Node* Tree_predecessor(Node* node_ptr) {
		if (node_ptr->Left_son_node != nullptr) {
			return node_ptr->Left_son_node;
		}
		else {
			Node* parent_ptr = node_ptr->Father_node;
			while (parent_ptr != nullptr && node_ptr == parent_ptr) {
				node_ptr = parent_ptr;
				parent_ptr = parent_ptr->Father_node;
			}
			return parent_ptr;
		}
	}
	// �����������Ĳ���
	void Tree_insert(int& value) {
		if (Root->Key_word == NULL) { Root->Key_word = value; }
		else {
			Node* r = new Node(value);
			Node* target_parent = nullptr;
			Node* target = Root;
			while (target != nullptr) {
				target_parent = target;
				if (value < target->Key_word) { target = target->Left_son_node; }
				else { target = target->Right_son_node; }
			}
			r->Father_node = target_parent;
			if (value < target_parent->Key_word) { target_parent->Left_son_node = r; }
			else { target_parent->Right_son_node = r; }
		}
	}
	// �ڵ�֮��ָ��ĵ���
	void Transplant(Node*& a, Node*& b) {
		// ����ɾ���ڵ�Ϊ���ڵ㣬���⴦��
		if (a == Root) {
			b->Father_node = nullptr;
			Root = b;
		}
		// ���ⲿ�ֽ����ı��˱��滻�ڵ�ĸ��ڵ���ӽڵ�ָ����滻�ڵ�ĸ��ڵ�ָ��
		else {
			Node*& pos_in_parent = (*a) < *(a->Father_node) ? a->Father_node->Left_son_node : a->Father_node->Right_son_node;
			if (b != nullptr) {
				b->Father_node = a->Father_node;
			}
			pos_in_parent = b;
		}
	}

	// ������������ɾ��
	void Tree_delete(Node* delete_ptr) {
		// ��ɾ���ڵ�Ϊ��
		if (delete_ptr == nullptr) { throw "Node don't exists!"; }
		// ��ɾ���ڵ���һ���ӽڵ�Ϊ�գ�ֱ���滻
		// �������ڵ㶼Ϊ��ʱ��Ҳһ��
		if (delete_ptr->Left_son_node == nullptr) {
			Transplant(delete_ptr, delete_ptr->Right_son_node);
		}
		else if (delete_ptr->Right_son_node == nullptr) {
			Transplant(delete_ptr, delete_ptr->Left_son_node);
		}
		// ��ɾ���ڵ�����������ֽڵ㣬�ҵ���һλ�̳��ߣ�����ɾ���ڵ�����ӽڵ����ӵ��̳��ߵ����ӽڵ��ϣ��̳���һ��û�����ӽڵ㣩
		// ͬʱ����̳��߲��Ǵ�ɾ���ڵ������ӽڵ㣬��Ҫ���̳нڵ���������ӽڵ㻥����Ȼ�󽫴�ɾ���ڵ�����ӽڵ����ӵ��̳нڵ�����ӽڵ��ϡ�Ȼ������һ��ע�����������������ǰѼ̳нڵ���������
		else {
			Node* successor_node = Tree_minimun(delete_ptr->Right_son_node);
			if (successor_node->Father_node != delete_ptr) {
				Transplant(successor_node, successor_node->Right_son_node);
				successor_node->Right_son_node = delete_ptr->Right_son_node;
				delete_ptr->Right_son_node->Father_node = successor_node;
			}
			successor_node->Left_son_node = delete_ptr->Left_son_node;
			Transplant(delete_ptr, successor_node);	
		}
		delete delete_ptr;
	}

};



