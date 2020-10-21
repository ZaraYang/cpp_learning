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

// ������� ƽ��������
// �ڵ���ɫΪ����ߺ�
// ���ڵ�Ϊ��
// Ҷ�ڵ�Ϊ��
// ��ɫ�ڵ���ӽڵ�һ��Ϊ��
// ��ÿ���ڵ㣬�Ӹýڵ㵽�����к��Ҷ�ڵ�ļ�·���Ϻ�ɫ�ڵ����Ŀ��ͬ

// �ڸ� black_height ������ڵ㵽������Ҷ�ڵ�·���ϵĺڽڵ�����
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
	// ����
	void Left_rotate(Node* node) {
		// Ŀ��ڵ�������ӽڵ�ĸ���
		// �Ƚ����ӽڵ�����ӽڵ����ӵ�Ŀ��ڵ���ҽڵ�
		Node* Right_son = node->Son_nodes[Right];
		node->Son_nodes[Right] = Right_son->Son_nodes[Left];
		if (Right_son->Son_nodes[Left] != Sentinel) { Right_son->Son_nodes[Left]->Father_node = node; }
		// ��Ŀ��ڵ�ĸ��ڵ����ӵ�Ŀ��ڵ�����ӽڵ���
		Right_son->Father_node = node->Father_node;
		if (node->Father_node == Sentinel) { Root = Right_son; }
		else if (node->Father_node->Son_nodes[Left] == node) {
			node->Father_node->Son_nodes[Left] = Right_son;
		}
		else {
			node->Father_node->Son_nodes[Right] = Right_son;
		}
		// ��Ŀ��ڵ�������Ŀ��ڵ�����ӽڵ�����ӽڵ��ϣ���tm�ƣ�
		node->Father_node = Right_son;
		Right_son->Son_nodes[Left] = node;
	}
	// ����
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
	// �����в���ڵ�
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
	// �ڲ���ʱά�����������
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
	// ���ظ��ڵ�
	Node* Tree_root() { return Root; }
	// �����ڱ�
	Node* Tree_sentinel() { return Sentinel; }

};