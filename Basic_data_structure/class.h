#pragma once
#include "include.h"
#define stack_capable 10
#define queue_capable 10

// ջ �Ƚ����
class stack {
public:
	int stack_array[stack_capable];
	int stack_top = 0;

	// ����stack�Ƿ�Ϊ��
	bool Stack_empty() {
		return(!stack_top);
	}
	// ����stack��ǰ��size
	int* Size() {
		return &stack_top;
	}
	// ��stack�е����������Ԫ��
	int Pop() {
		if (stack_top == stack_capable - 1) {
			throw "Stack Underflow!";
		}
		else {
			stack_top--;
			return stack_array[stack_top];
		}
	}
	// ��stack������Ԫ��
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


// ����

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

// ˫������
class Singly_linked_list {
protected:
	// �ڱ�
	Link_Node* Sentinel;
	// �������Ȳ����Ԫ��
	Link_Node* Currently_ptr;
public:
	Singly_linked_list() 
	:Sentinel(new Link_Node(nullptr, nullptr, -1)),Currently_ptr(Sentinel){
	}

	// ��������ձ��˲���Ԫ��
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
	
	// �������и������������������������ĵ�һ����
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

	// ����ָ��ɾ�������е�Ԫ��
	void Delete(Link_Node* ptr) {
		ptr->Front()->Set_rear(ptr->Rear());
		ptr->Rear()->Set_front(ptr->Front());
		if (ptr->Rear() == Sentinel) {
			Currently_ptr = ptr->Front();
		}
		delete ptr;
	}
	
	// ��������ɾ�� ���ȵ�������
	void Delete(int context) {
		Link_Node* search_result = Search(context);
		if (search_result == nullptr) {
			cout << "NO SUCN NODE IN LINK LIST !" << endl;
		}
		else {
			Delete(search_result);
		}
	}

	// ���ز�ɾ�������Ԫ��
	Link_Node Pop() {
		Link_Node temp = *Currently_ptr;
		Delete(Currently_ptr);
		return temp;
	}

	// ����Ԫ�أ�ûɶ���þ������һ��Pop ��>
	void Push(int context) {
		Insert(context);
	}

	// ���������������
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

// ���� �Ƚ��ȳ�
class Queue:public Singly_linked_list {
public:
	Queue():Singly_linked_list(){}

	// ���
	void Enqueue(int context) {
		Push(context);
	}
	// ����
	// ����ʱ����Pop�ĸ������ã������캯�����������
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




