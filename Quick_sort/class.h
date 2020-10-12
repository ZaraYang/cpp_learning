#pragma once
#include "include.h"

// �ݹ麯��ÿ�εݹ鶼�Ὣ��ǰ�ı����浽ջ�У�ֱ���ݹ������ɷ���ʱ�Ż��ͷ�
// ���Ի����Ĵ�����ջ�ڴ�

// ��������
class Quick_sort_algoritm {
protected:
	vector<float> sort_vector;
public:
	Quick_sort_algoritm(int data_num)	
	{
		sort_vector.reserve(data_num);
	}
	Quick_sort_algoritm(){}
	// ��vector�е�������
	void import_data(string addr) {
		ifstream input_file(addr, ios::in);
		if (input_file.is_open()) {
			float buffer;
			while (input_file >> buffer) {
				sort_vector.push_back(buffer);
			}
		}
	}
	// ��vector�е�����Ԫ�ؽ���λ��
	void Exchange_index(int index_1, int index_2) {
		swap(sort_vector[index_1], sort_vector[index_2]);
	}
	// �����ݻ���Ϊ [p,q-1],q,[q+1,r] �������֣����� [p,q-q] < q, [q+1,r] > q
	// ��[p,r]�е�Ԫ�ض�һ��ʱ������(floor((p+r)/2))ʹ����ƽ�⻮��
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
	// �ݹ���ÿ�������
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

// �������������ڻ���ʱ���ָ���м�ֵ
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

// β�ݹ��������ʡ����ԭ���������е�һ���ݹ�
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

// �ǵݹ��������
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

	// ����������ջ
	void Push_stack(int high_index,int low_index) {
		//cout << "PUSH INTO STACK : " << high_index << "," << low_index << endl;
		task_stack[stack_size] = task(high_index, low_index);
		stack_size++;
	}
	// �Ӷ�ջ�е������һλ������
	// ׼ȷ��˵�ǽ������ָ�����¶�λ����ջ�����һ������ĵ�ַ
	// Ȼ��stack_size ��һ
	void Pop_stack(task*& pop_task) {
		//cout << "POP OUT OF STACK : " << task_stack[stack_size - 1].high_index << "," << task_stack[stack_size - 1].low_index << endl;
		pop_task = &task_stack[stack_size - 1];
		stack_size--;
	}
public:
	Without_recursive_quicksort():Quick_sort_algoritm(){}
	Without_recursive_quicksort(int data_num) :Quick_sort_algoritm(data_num) {}
	
	// �ǵݹ���ÿ�������
	// ���ö�ջ��˳��ִ������
	void Quick_sort(int p, int r)override {
		cout << "Quick Sort without recursive" << endl;
		Push_stack(p, r);
		task* task_buffer = &task_stack[0];
		while (stack_size) {
			Pop_stack(task_buffer);
			// ��Ҫ�Ե�ǰ������С��index���棬��Ȼ���ջ��Pushʱ�Ὣԭ��ַ����
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
