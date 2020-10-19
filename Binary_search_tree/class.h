#pragma once
#include "include.h"


// 二叉搜索树节点
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

	// 建树
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

	// 中序遍历
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

	// 二叉搜索树的递归搜索
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

	// 二叉搜索树的迭代搜索
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

	// 二叉树或者子树的最小值
	Node* Tree_minimun(Node* node) {
		while (node->Left_son_node != nullptr) {
			node = node->Left_son_node;
		}
		return node;
	}
	Node* Tree_minimun() {
		return Tree_minimun(Root);
	}

	// 二叉树或者子树的最大值
	Node* Tree_maximum(Node* node) {
		while (node->Right_son_node != nullptr) {
			node = node->Right_son_node;
		}
		return node;
	}
	Node* Tree_maximum() {
		Tree_maximum(Root);
	}
	
	// 中序遍历的下一位
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

	// 中序遍历上一位
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
	// 二叉搜索树的插入
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
	// 节点之间指针的调换
	void Transplant(Node*& a, Node*& b) {
		// 当被删除节点为根节点，特殊处理
		if (a == Root) {
			b->Father_node = nullptr;
			Root = b;
		}
		// 在这部分仅仅改变了被替换节点的父节点的子节点指针和替换节点的父节点指针
		else {
			Node*& pos_in_parent = (*a) < *(a->Father_node) ? a->Father_node->Left_son_node : a->Father_node->Right_son_node;
			if (b != nullptr) {
				b->Father_node = a->Father_node;
			}
			pos_in_parent = b;
		}
	}

	// 二叉搜索树的删除
	void Tree_delete(Node* delete_ptr) {
		// 待删除节点为空
		if (delete_ptr == nullptr) { throw "Node don't exists!"; }
		// 待删除节点有一个子节点为空，直接替换
		// 当两个节点都为空时，也一样
		if (delete_ptr->Left_son_node == nullptr) {
			Transplant(delete_ptr, delete_ptr->Right_son_node);
		}
		else if (delete_ptr->Right_son_node == nullptr) {
			Transplant(delete_ptr, delete_ptr->Left_son_node);
		}
		// 待删除节点存在两个子字节点，找到下一位继承者，将待删除节点的左子节点连接到继承者的左子节点上（继承者一定没有左子节点）
		// 同时如果继承者并非待删除节点子右子节点，需要将继承节点的与其右子节点互换，然后将待删除节点的右子节点连接到继承节点的右子节点上。然后按照上一条注释那样正常处理（就是把继承节点提上来）
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



