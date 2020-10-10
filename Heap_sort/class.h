#pragma once
#include "include.h"

// source heap
// 堆的基类，利用vector建立列表保存堆中的元素（Heap_element）
// 根据vextor内的index确定父子关系
// 初始化时向堆内加入了-1，以确保堆中的计数从1开始
// Max_heapify 部分有递归和迭代两种写法，其内存使用的区别尚未分析


// 堆元素
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
	// 重新设置某element的Priority
	void Reset_priority(float& priority) {
		Priority = priority;
	}
	// 重写 > 方法
	bool operator>(Heap_element& other) {
		return Bigger_than(other);
	}
	// 重写 < 方法
	bool operator<(Heap_element& other) {
		return Smaller_than(other);
	}
	// 返回Priority
	float Show_priority() const  {
		return Priority;
	}
};
// 堆
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
	// 返回父元素的index
	int Parents(int child_index) {
		if (child_index == 0) {
			return NULL;
		}
		else {
			return (int)(floor(child_index / 2));
		}
	}
	// 返回左侧孩子的index
	int Left_child(int parent_index) {
		return parent_index * 2;
	}
	//返回右侧孩子的index
	int Right_child(int parent_index) {
		return parent_index * 2 + 1;
	}
	// 将vector中的两个元素交换位置
	void Exchange_index(int index_1, int index_2) {
		swap(heap_vector[index_1], heap_vector[index_2]);
	}
	// 堆维护（迭代）
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
	// 堆维护（递归）
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
	// 建立最大堆
	void Build_max_heap() {
		for (int i = floor(heap_capcity / 2); i >= 1; i--) {
			//			Max_heapify(i);
			Max_heapify_with_loop(i);
		}
	}
	// 踢出堆中的最后一位元素并capcity减一
	void heap_pop_back(){
		heap_capcity--;
		heap_vector.pop_back();
	}
	// 展示堆中所有的元素
	virtual void Show_heap() {
		for (int i = 1; i < heap_vector.size(); i++) {
			cout << this->heap_vector[i].Show_priority() << endl;
		}
	}
};

// heap sort
// 用于堆排序的子类
class Heap_sort :public Heap{
public:
	Heap_sort(int count):Heap(count){}
	// 开始排序，依次将根节点位置的元素（堆中最大的元素）放到最后，同时将heap_capcity减一（但并未踢出最后一位的元素）
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
// 用于构建优先序列的子类
// 在优先队列中并未事先制定element的数量，而是通过插入的方式建堆
// 所以vector会不断地扩张
class Priority_queue :public Heap{
public:
	Priority_queue() :Heap(0) {}
	// 从文件中读取数据，并以迭代插入的方法直接建立最大堆
	void Heap_import_from_file(string addr) override {
		ifstream input_file(addr, ios::in);
		if (input_file.is_open()) {
			float buffer;
			while (input_file >> buffer) {
				Insert_task(buffer);
			}
		}
	}
	//向极大堆中插入element
	void Insert_task(float& priority){
		heap_capcity++;
		heap_vector.push_back(Heap_element(-1));
		Increase_priority(heap_capcity,priority);
	}
	// 从极大堆中删除element
	void Delete_task(int& index) {
		if (index > heap_capcity) {
			throw "Bigger than heap capcity";
		}
		Exchange_index(index, heap_capcity);
		heap_pop_back();
		Max_heapify(index);
	}
	// 返回堆根节点处的element
	Heap_element Return_maximum() const {
		return heap_vector[1];
	}
	// 返回并删除根结点处的element
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
	// 将堆中某个element的Priority增加至 add_num
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




