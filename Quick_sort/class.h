#pragma once
#include "include.h"

// 递归函数每次递归都会将当前的变量存到栈中，直到递归计算完成返回时才会释放
// 所以会消耗大量的栈内存

// 快速排序
class Quick_sort_algoritm {
protected:
	vector<float> sort_vector;
public:
	Quick_sort_algoritm(int data_num)	
	{
		sort_vector.reserve(data_num);
	}
	Quick_sort_algoritm(){}
	// 向vector中导入数据
	void import_data(string addr) {
		ifstream input_file(addr, ios::in);
		if (input_file.is_open()) {
			float buffer;
			while (input_file >> buffer) {
				sort_vector.push_back(buffer);
			}
		}
	}
	// 将vector中的两个元素交换位置
	void Exchange_index(int index_1, int index_2) {
		swap(sort_vector[index_1], sort_vector[index_2]);
	}
	// 将数据划分为 [p,q-1],q,[q+1,r] 三个部分，其中 [p,q-q] < q, [q+1,r] > q
	// 当[p,r]中的元素都一样时，返回(floor((p+r)/2))使数据平衡划分
	int Partition(int p, int r){
		float x = sort_vector[r];
		int i = p - 1;
		bool identical = true;
		for (int j = p; j <= r - 1; j++) {
			if (sort_vector[j] != x) { identical = false; }
			if (sort_vector[j] <= x){
				i++;
				Exchange_index(i,j);
			}
		}
		if (identical) { return floor((p + r) / 2); }
		else { Exchange_index(i + 1, r); }
		return(i + 1);
	}
	// 递归调用快速排序
	virtual void Quick_sort(int p, int r) {
		if (p < r) {
			int q = Partition(p, r);
//			cout << "-----------------" << endl;
//			cout << p << "," << q << "," << r << endl;
			Quick_sort(p, q-1);
			Quick_sort(q+1, r);
		}
	}
	
	virtual void Main_quick_sort() {
		int start = 0;
		int end = sort_vector.size() - 1;
		Quick_sort(start, end);
	}

	void Show_vector() const {
		//cout << "Sort Vector :" << endl;
		for (int i = 0; i < sort_vector.size(); i++) {
			cout << sort_vector[i] << ", ";
		}
		cout << endl;
	}
};

// 随机版快速排序，在划分时随机指定中间值
class Randomized_quick_sort :public Quick_sort_algoritm{
public:
	Randomized_quick_sort():Quick_sort_algoritm(){}
	Randomized_quick_sort(int data_num):Quick_sort_algoritm(data_num){}

	int Random_value(int min, int max) {
		return rand() % (max - min + 1) + min;
	}

	int Randomized_partition(int p, int r) {
		int i = Random_value(p, r);
		Exchange_index(i, r);
		return Partition(p,r);
	}

	void Quick_sort(int p, int r) override {
		if (p < r) {
			int q = Randomized_partition(p, r);
			//			cout << "-----------------" << endl;
			//			cout << p << "," << q << "," << r << endl;
			Quick_sort(p, q - 1);
			Quick_sort(q + 1, r);
		}
	}

};

// 尾递归快速排序，省略了原快速排序中的一个递归
class Tail_recursive_quicksort :public Quick_sort_algoritm {
public:
	Tail_recursive_quicksort() :Quick_sort_algoritm() {}
	Tail_recursive_quicksort(int data_num) :Quick_sort_algoritm(data_num) {}

	void Quick_sort(int p, int r) override {
		while (p < r) {
			int q = Partition(p, r);
			Quick_sort(p, q - 1);
			p = q + 1;
		}
	}
};

// 非递归快速排序
class task {
public:
	int high_index,low_index;
	task(){}
	task(int i ,int j)
		:low_index(i),high_index(j){}
};

class Without_recursive_quicksort:public  Quick_sort_algoritm {
private:
	task task_stack[50]	;
	int stack_size = 0;

	// 将任务放入堆栈
	void Push_stack(int high_index,int low_index) {
		//cout << "PUSH INTO STACK : " << high_index << "," << low_index << endl;
		task_stack[stack_size] = task(high_index, low_index);
		stack_size++;
	}
	// 从堆栈中弹出最后一位的任务
	// 准确的说是将输入的指针重新定位到堆栈中最后一个任务的地址
	// 然后将stack_size 减一
	void Pop_stack(task*& pop_task) {
		//cout << "POP OUT OF STACK : " << task_stack[stack_size - 1].high_index << "," << task_stack[stack_size - 1].low_index << endl;
		pop_task = &task_stack[stack_size - 1];
		stack_size--;
	}
public:
	Without_recursive_quicksort():Quick_sort_algoritm(){}
	Without_recursive_quicksort(int data_num) :Quick_sort_algoritm(data_num) {}
	
	// 非递归调用快速排序
	// 利用堆栈按顺序执行任务
	void Quick_sort(int p, int r)override {
		cout << "Quick Sort without recursive" << endl;
		Push_stack(p, r);
		task* task_buffer = &task_stack[0];
		while (stack_size) {
			Pop_stack(task_buffer);
			// 需要对当前最大和最小的index保存，不然向堆栈中Push时会将原地址覆盖
			int low_buffer = task_buffer->low_index;
			int high_buffer = task_buffer->high_index;

			int middle_index = Partition(task_buffer->low_index,task_buffer->high_index);
			if (middle_index > low_buffer) {
				Push_stack(low_buffer, middle_index - 1);
			}
			if (middle_index + 1 < high_buffer) {
				Push_stack(middle_index + 1, high_buffer);
			}
		}
	}
};
