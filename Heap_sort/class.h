#pragma once
#include "include.h"

// source heap
// �ѵĻ��࣬����vector�����б�����е�Ԫ�أ�Heap_element��
// ����vextor�ڵ�indexȷ�����ӹ�ϵ
// ��ʼ��ʱ����ڼ�����-1����ȷ�����еļ�����1��ʼ
// Max_heapify �����еݹ�͵�������д�������ڴ�ʹ�õ�������δ����


// ��Ԫ��
class Heap_element{
protected:
	float Priority;

	Heap_element(float priority)
		: Priority(priority){}
	bool Bigger_than(Heap_element& other) const {
		return (Priority > other.Priority);
	}

	bool Smaller_than(Heap_element& other) const {
		return (Priority < other.Priority);
	}
public:
	// ��������ĳelement��Priority
	void Reset_priority(float& priority) {
		Priority = priority;
	}
	// ��д > ����
	bool operator>(Heap_element& other) {
		return Bigger_than(other);
	}
	// ��д < ����
	bool operator<(Heap_element& other) {
		return Smaller_than(other);
	}
	// ����Priority
	float Show_priority() const  {
		return Priority;
	}
};
// ��
class Heap {
protected:
	int heap_capcity;
	vector<Heap_element> heap_vector;
public:
	Heap(int count)
		:heap_capcity(count)
	{
		heap_vector.reserve(heap_capcity+1);
		heap_vector.push_back(-1);
		cout << "Source heap has been established, whose capacity is " << heap_vector.capacity() << endl;
	}

	virtual void Heap_import_from_file(string addr) {
		ifstream input_file(addr, ios::in);
		if (input_file.is_open()) {
			int buffer;
			while (input_file >> buffer) {
				heap_vector.push_back(Heap_element(buffer));
			}
		}
	}
	// ���ظ�Ԫ�ص�index
	int Parents(int child_index) {
		if (child_index == 0) {
			return NULL;
		}
		else {
			return (int)(floor(child_index / 2));
		}
	}
	// ������ຢ�ӵ�index
	int Left_child(int parent_index) {
		return parent_index * 2;
	}
	//�����Ҳຢ�ӵ�index
	int Right_child(int parent_index) {
		return parent_index * 2 + 1;
	}
	// ��vector�е�����Ԫ�ؽ���λ��
	void Exchange_index(int index_1, int index_2) {
		swap(heap_vector[index_1], heap_vector[index_2]);
	}
	// ��ά����������
	void Max_heapify_with_loop(int index) {
		for (int i = index, j = index * 2; j <= heap_capcity; i = j, j = i * 2) {
			if (j + 1 <= heap_capcity && heap_vector[j + 1] > heap_vector[j]) {
				j += 1;
			}
			if (heap_vector[i] > heap_vector[j]) {
				break;
			}
			else {
				Exchange_index(i, j);
			}
		}
	}
	// ��ά�����ݹ飩
	void Max_heapify(int index) {
		int Left_index = Left_child(index);
		int Right_index = Right_child(index);
		int Largest_index = index;
		if (Left_index <= heap_capcity && heap_vector[Left_index] > heap_vector[Largest_index]) {
			Largest_index = Left_index;
		}
		if (Right_index <= heap_capcity && heap_vector[Right_index] > heap_vector[Largest_index]) {
			Largest_index = Right_index;
		}
		if (Largest_index != index) {
			Exchange_index(index, Largest_index);
			Max_heapify_with_loop(Largest_index);
		}
	}
	// ��������
	void Build_max_heap() {
		for (int i = floor(heap_capcity / 2); i >= 1; i--) {
			//			Max_heapify(i);
			Max_heapify_with_loop(i);
		}
	}
	// �߳����е����һλԪ�ز�capcity��һ
	void heap_pop_back(){
		heap_capcity--;
		heap_vector.pop_back();
	}
	// չʾ�������е�Ԫ��
	virtual void Show_heap() {
		for (int i = 1; i < heap_vector.size(); i++) {
			cout << this->heap_vector[i].Show_priority() << endl;
		}
	}
};

// heap sort
// ���ڶ����������
class Heap_sort :public Heap{
public:
	Heap_sort(int count):Heap(count){}
	// ��ʼ�������ν����ڵ�λ�õ�Ԫ�أ���������Ԫ�أ��ŵ����ͬʱ��heap_capcity��һ������δ�߳����һλ��Ԫ�أ�
	void Sort() {
		Build_max_heap();
		for (int i = heap_capcity; i >= 2; i--) {
			Exchange_index(1, i);
			heap_capcity --;
			//			Max_heapify(1);
			Max_heapify_with_loop(1);
		}
	}
};

// priority queue
// ���ڹ����������е�����
// �����ȶ����в�δ�����ƶ�element������������ͨ������ķ�ʽ����
// ����vector�᲻�ϵ�����
class Priority_queue :public Heap{
public:
	Priority_queue() :Heap(0) {}
	// ���ļ��ж�ȡ���ݣ����Ե�������ķ���ֱ�ӽ�������
	void Heap_import_from_file(string addr) override {
		ifstream input_file(addr, ios::in);
		if (input_file.is_open()) {
			float buffer;
			while (input_file >> buffer) {
				Insert_task(buffer);
			}
		}
	}
	//�򼫴���в���element
	void Insert_task(float& priority){
		heap_capcity++;
		heap_vector.push_back(Heap_element(-1));
		Increase_priority(heap_capcity,priority);
	}
	// �Ӽ������ɾ��element
	void Delete_task(int& index) {
		if (index > heap_capcity) {
			throw "Bigger than heap capcity";
		}
		Exchange_index(index, heap_capcity);
		heap_pop_back();
		Max_heapify(index);
	}
	// ���ضѸ��ڵ㴦��element
	Heap_element Return_maximum() const {
		return heap_vector[1];
	}
	// ���ز�ɾ������㴦��element
	Heap_element Extract_maximum(){
		if (heap_capcity < 1) {
			throw "Heap underflow";
		}
		Heap_element max = heap_vector[1];
		Exchange_index(1, heap_capcity);
		heap_pop_back();
		Max_heapify(1);
		return max;
	}
	// ������ĳ��element��Priority������ add_num
	void Increase_priority(int& index, float& add_num){
		if (heap_vector[index].Show_priority() > add_num) {
			throw "New key is smaller than current key";
		}
		heap_vector[index].Reset_priority(add_num);
		while (index > 1 && heap_vector[Parents(index)] < heap_vector[index] ){
			Exchange_index(index, Parents(index));
			index = Parents(index);
		}
	}

};




