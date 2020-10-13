#pragma once
#include "include.h"
#define stack_capable 10
#define queue_capable 10

// 栈 先进后出
class stack {
public:
	int stack_array[stack_capable];
	int stack_top = 0;

	// 返回stack是否为空
	bool Stack_empty() {
		return(!stack_top);
	}
	// 返回stack当前的size
	int* Size() {
		return &stack_top;
	}
	// 从stack中弹出最后进入的元素
	int Pop() {
		if (stack_top == stack_capable - 1) {
			throw "Stack Underflow!";
		}
		else {
			stack_top--;
			return stack_array[stack_top];
		}
	}
	// 向stack中推入元素
	void Push(int& num) {
		if (stack_top == stack_capable-1){
			throw "Stack Overflow!";
		}
		else {
			stack_top++;
			stack_array[stack_top - 1] = num;
		}
	}
};


// 链表

class Link_Node {
private:
	Link_Node* header;
	Link_Node* tailer;
	int context;
public:
//	~Link_Node() {
//		cout << "DELETE LINK NODE :"<< context << endl;
//	}

	Link_Node(Link_Node* front_node, Link_Node* rear_node, int node_context)
		:header(front_node),tailer(rear_node),context(node_context){}

	Link_Node* Front() const{
		return header;
	}
	Link_Node* Rear() const {
		return tailer;
	}

	void Set_front(Link_Node* ptr) {
		header = ptr;
	}

	void Set_rear(Link_Node* ptr) {
		tailer = ptr;
	}

	int Context() const {
		return context;
	}


};

// 双向链表
class Singly_linked_list {
protected:
	// 哨兵
	Link_Node* Sentinel;
	// 链表最先插入的元素
	Link_Node* Currently_ptr;
public:
	Singly_linked_list() 
	:Sentinel(new Link_Node(nullptr, nullptr, -1)),Currently_ptr(Sentinel){
	}

	// 向链表的烧饼端插入元素
	virtual void Insert(int context){
		Link_Node* temp_node = new Link_Node(Sentinel, nullptr, context);

		if (Sentinel->Rear() != nullptr) {
			temp_node->Set_rear(Sentinel->Rear());
			Sentinel->Rear()->Set_front(temp_node);
		}
		else {
			Currently_ptr = temp_node;
			temp_node->Set_rear(Sentinel);
			Sentinel->Set_front(temp_node);
		}
		Sentinel->Set_rear(temp_node);
	}
	
	// 在链表中根据内容搜索（返回搜索到的第一个）
	Link_Node* Search(int context) {
		Link_Node* temp_node = Sentinel->Rear();
		while (temp_node->Rear() != Sentinel) {
			if (temp_node->Context() == context) {
				return temp_node;
			}
			temp_node = temp_node->Rear();
		}
		return nullptr;
	}

	// 根据指针删除链表中的元素
	void Delete(Link_Node* ptr) {
		ptr->Front()->Set_rear(ptr->Rear());
		ptr->Rear()->Set_front(ptr->Front());
		if (ptr->Rear() == Sentinel) {
			Currently_ptr = ptr->Front();
		}
		delete ptr;
	}
	
	// 根据内容删除 首先调用搜索
	void Delete(int context) {
		Link_Node* search_result = Search(context);
		if (search_result == nullptr) {
			cout << "NO SUCN NODE IN LINK LIST !" << endl;
		}
		else {
			Delete(search_result);
		}
	}

	// 返回并删除最早的元素
	Link_Node Pop() {
		Link_Node temp = *Currently_ptr;
		Delete(Currently_ptr);
		return temp;
	}

	// 插入元素，没啥卵用就是配合一下Pop ：>
	void Push(int context) {
		Insert(context);
	}

	// 迭代输出整个链表
	virtual void Show_link_list() const {
		if (Sentinel->Rear() == nullptr) {
			exit(0);
		}
		Link_Node* temp_ptr = Sentinel->Rear();
		
		while (temp_ptr->Rear() != Sentinel) {
			cout << temp_ptr->Context() << " <-> ";
			temp_ptr = temp_ptr->Rear();
		}
		cout << "Nullptr" << endl;
	}

};

// 队列 先进先出
class Queue:public Singly_linked_list {
public:
	Queue():Singly_linked_list(){}

	// 入队
	void Enqueue(int context) {
		Push(context);
	}
	// 出队
	// 出队时由于Pop的复制作用，反构造函数会调用三次
	Link_Node Dequeue() {
		return Pop();
	}

	void Show_link_list() const {
		if (Sentinel->Rear() == nullptr) {
			exit(0);
		}
		Link_Node* temp_ptr = Sentinel->Rear();

		while (temp_ptr->Rear() != Sentinel) {
			cout << temp_ptr->Context() << " - ";
			temp_ptr = temp_ptr->Rear();
		}
		cout << "Nullptr" << endl;
	}
};




