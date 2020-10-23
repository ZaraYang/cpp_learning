#pragma once
#include "include.h"



enum Color{Red,Black};
enum Son_class {Left,Right};

struct Node
{
	int Node_color;
	int Key_word = NULL;
	Node* Father_node = nullptr;
	map<int,Node*> Son_nodes;

	Node():Node_color(Black){}
	Node(int k):Node_color(Red),Key_word(k){}
};

// 红黑性质 平衡搜索树
// 节点颜色为红或者黑
// 根节点为黑
// 叶节点为黑
// 红色节点的子节点一定为黑
// 对每个节点，从该节点到其所有后代叶节点的简单路径上黑色节点的数目相同

// 黑高 black_height 从任意节点到其任意叶节点路径上的黑节点数量
class Red_black_tree {
private:
	Node* Root;
	Node* Sentinel;
public:
	Red_black_tree()
		:Root(new Node()),Sentinel(new Node()){
			Sentinel->Son_nodes[Right] = Root;
			Sentinel->Son_nodes[Left] = Root;
			Sentinel->Father_node = nullptr;
			Root->Father_node = Sentinel;
			Root->Son_nodes[Left] = Sentinel;
			Root->Son_nodes[Right] = Sentinel;
	}
	// 左旋
	void Left_rotate(Node* node) {
		// 目标节点和其右子节点的更换
		// 先将右子节点的左子节点连接到目标节点的右节点
		Node* Right_son = node->Son_nodes[Right];
		node->Son_nodes[Right] = Right_son->Son_nodes[Left];
		if (Right_son->Son_nodes[Left] != Sentinel) { Right_son->Son_nodes[Left]->Father_node = node; }
		// 将目标节点的父节点连接到目标节点的右子节点上
		Right_son->Father_node = node->Father_node;
		if (node->Father_node == Sentinel) { Root = Right_son; }
		else if (node->Father_node->Son_nodes[Left] == node) {
			node->Father_node->Son_nodes[Left] = Right_son;
		}
		else {
			node->Father_node->Son_nodes[Right] = Right_son;
		}
		// 将目标节点连接在目标节点的右子节点的左子节点上（真tm绕）
		node->Father_node = Right_son;
		Right_son->Son_nodes[Left] = node;
	}
	// 右旋
	void Right_rotate(Node* node) {
		Node* Left_son = node->Son_nodes[Left];

		node->Son_nodes[Left] = Left_son->Son_nodes[Right];
		if (Left_son->Son_nodes[Right] != Sentinel) { Left_son->Son_nodes[Right]->Father_node = node; }

		Left_son->Father_node = node->Father_node;
		if (node->Father_node == Sentinel) { Root = Left_son; }
		else if (node->Father_node->Son_nodes[Left] == node) {
			node->Father_node->Son_nodes[Left] = Left_son;
		}
		else {
			node->Father_node->Son_nodes[Right] = Left_son;
		}

		node->Father_node = Left_son;
		Left_son->Son_nodes[Right] = node;
	}
	// 向树中插入节点
	void RB_insert(int& key) {
		Node* father_buffer = Sentinel;
		Node* son_buffer = Root;
		if (son_buffer->Key_word == NULL) { Root->Key_word = key;}
		else {
			Node* add_node = new Node(key);
			while (son_buffer != Sentinel) {
				father_buffer = son_buffer;
				if (key < son_buffer->Key_word) { son_buffer = son_buffer->Son_nodes[Left]; }
				else { son_buffer = son_buffer->Son_nodes[Right]; }
			}
			add_node->Father_node = father_buffer;
			if (key < father_buffer->Key_word) { 
				father_buffer->Son_nodes[Left] = add_node; 
			}
			else { 
				father_buffer->Son_nodes[Right] = add_node; 
			}
			add_node->Son_nodes[Left] = Sentinel;
			add_node->Son_nodes[Right] = Sentinel;
			//CALLING RT_INSERT_FIX_UP
			RB_insert_fix_up(add_node);
		}
	}
	// 在插入时维护红黑树规则
	void RB_insert_fix_up(Node* node) {
		while (node->Father_node->Node_color == Red) {
			if (node->Father_node == node->Father_node->Father_node->Son_nodes[Left]) {
				Node* Uncle_node = node->Father_node->Father_node->Son_nodes[Right];
				if (Uncle_node->Node_color == Red) {
					node->Father_node->Node_color = Black;
					Uncle_node->Node_color = Black;
					node->Father_node->Father_node->Node_color = Red;
					node = node->Father_node->Father_node;
				}
				else if (Uncle_node->Node_color == Black && node == node->Father_node->Son_nodes[Right]) {
					node = node->Father_node;
					Left_rotate(node);
				}
				else if (Uncle_node->Node_color == Black && node == node->Father_node->Son_nodes[Left]) {
					node->Father_node->Node_color = Black;
					node->Father_node->Father_node->Node_color = Red;
					Right_rotate(node->Father_node->Father_node);
				}
			}
			else{
				Node* Uncle_node = node->Father_node->Father_node->Son_nodes[Left];
				if (Uncle_node->Node_color == Red) {
					node->Father_node->Node_color = Black;
					Uncle_node->Node_color = Black;
					node->Father_node->Father_node->Node_color = Red;
					node = node->Father_node->Father_node;
					continue;
				}
				else if (Uncle_node->Node_color == Black && node == node->Father_node->Son_nodes[Left]) {
					node = node->Father_node;
					Right_rotate(node);
				}
				else if (Uncle_node->Node_color == Black && node == node->Father_node->Son_nodes[Right]) {
					node->Father_node->Node_color = Black;
					node->Father_node->Father_node->Node_color = Red;
					Left_rotate(node->Father_node->Father_node);
				}
			}
		}
		Root->Node_color = Black;
	}
	// 搜索树中的节点
	Node* RB_search(int& k) {
		Node* node_buffer = Root;
		while (node_buffer != Sentinel) {
			if (node_buffer->Key_word == k) { return node_buffer; }
			else if (k < node_buffer->Key_word) {
				node_buffer = node_buffer->Son_nodes[Left];
			}
			else {
				node_buffer = node_buffer->Son_nodes[Right];
			}
		}
		return nullptr;
	}
	// 将一棵子树换为另一颗
	void RB_transplant(Node* a, Node* b) {
		if (a == Root) { b->Father_node = Sentinel; Root = b; }
		else if (a == a->Father_node->Son_nodes[Left]) {
			a->Father_node->Son_nodes[Left] = b;
		}
		else {
			a->Father_node->Son_nodes[Right] = b;
		}
		if (b != Sentinel) {
			b->Father_node = a->Father_node;
		}
	}
	// 返回树中最小的节点
	Node* RB_minimum(Node* r) {
		Node* node_buffer = r;
		while (node_buffer->Son_nodes[Left] != Sentinel)
		{
			node_buffer = node_buffer->Son_nodes[Left];
		}
		return node_buffer;
	}
	// 删除树中的节点
	void RB_delete(Node* node) {
		int orginal_color = node->Node_color;
		Node* fix_up_node;
		if (node->Son_nodes[Left] == Sentinel) {
			fix_up_node = node->Son_nodes[Right];
			RB_transplant(node, node->Son_nodes[Right]);
		}
		else if (node->Son_nodes[Right] == Sentinel) {
			fix_up_node = node->Son_nodes[Left];
			RB_transplant(node, node->Son_nodes[Left]);
		}
		else {
			Node* node_buffer = RB_minimum(node->Son_nodes[Right]);
			orginal_color = node_buffer->Node_color;
			fix_up_node = node_buffer->Son_nodes[Right];
			if (node_buffer->Father_node != node) {
				RB_transplant(node_buffer, node_buffer->Son_nodes[Right]);
				node_buffer->Son_nodes[Right] = node->Son_nodes[Right];
				if (node->Son_nodes[Right] != Sentinel) { node->Son_nodes[Right]->Father_node = node_buffer; }
			}
			RB_transplant(node, node_buffer);
			node_buffer->Son_nodes[Left] = node->Son_nodes[Left];
			if (node->Son_nodes[Left] != Sentinel) { node->Son_nodes[Left]->Father_node = node_buffer; }
			node_buffer->Node_color = node->Node_color;
		}
		
		if (orginal_color == Black) {
			// CALL-DELETE-FIXUP
			fix_up_node->Father_node = node->Father_node;
			RB_delete_fix_up(fix_up_node);
			fix_up_node->Father_node = nullptr;
		}
		delete node;
	}
	// 根据关键值删除节点
	void RB_delete(int& k) {
		RB_delete(RB_search(k));
	}
	// 在删除时维护红黑树规则
	void RB_delete_fix_up(Node* node) {
		while (node != Root && node->Node_color == Black) {
			if (node == node->Father_node->Son_nodes[Left]){
				Node* sibling_node = node->Father_node->Son_nodes[Right];
				if (sibling_node->Node_color == Red) {
					sibling_node->Node_color = Black;
					node->Father_node->Node_color = Red;
					Left_rotate(node->Father_node);
					sibling_node = node->Father_node->Son_nodes[Right];
				}
				if (sibling_node->Son_nodes[Left]->Node_color == Black && sibling_node->Son_nodes[Right]->Node_color == Black) {
					sibling_node->Node_color = Red;
					node = node->Father_node;
				}
				else {
					if (sibling_node->Son_nodes[Right]->Node_color == Black) {
						sibling_node->Son_nodes[Left]->Node_color = Black;
						sibling_node->Node_color = Red;
						Right_rotate(sibling_node);
					}
					sibling_node->Node_color = node->Father_node->Node_color;
					node->Father_node->Node_color = Black;
					sibling_node->Son_nodes[Right]->Node_color = Black;
					Left_rotate(node->Father_node);
					node = Root;
				}
			}
			else {
				Node* sibling_node = node->Father_node->Son_nodes[Left];
				if (sibling_node->Node_color == Red) {
					sibling_node->Node_color = Black;
					node->Father_node->Node_color = Red;
					Right_rotate(node->Father_node);
					sibling_node = node->Father_node->Son_nodes[Left];
				}
				if (sibling_node->Son_nodes[Left]->Node_color == Black && sibling_node->Son_nodes[Right]->Node_color == Black) {
					sibling_node->Node_color = Red;
					node = node->Father_node;
				}
				else {
					if (sibling_node->Son_nodes[Left]->Node_color == Black) {
						sibling_node->Son_nodes[Right]->Node_color = Black;
						sibling_node->Node_color = Red;
						Left_rotate(sibling_node);
						sibling_node = node->Father_node->Son_nodes[Left];
					}
					sibling_node->Node_color = node->Father_node->Node_color;
					node->Father_node->Node_color = Black;
					sibling_node->Son_nodes[Left]->Node_color = Black;
					Right_rotate(node->Father_node);
					node = Root;
				}
			}
		}
		node->Node_color = Black;
	}
	// 返回根节点
	Node* Tree_root() { return Root; }
	// 返回哨兵
	Node* Tree_sentinel() { return Sentinel; }
};