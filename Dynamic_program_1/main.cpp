#include"include.h"
#include"class.h"

// �Զ�����ʵ�ֵ��и����ŷ������д������ظ�����,���������ͬ��������
int Cut_rod(map<int, int> price_table, int length) {
	if (length == 0) {
		return(0);
	}
	int price = -99999;
	for (int i = 1; i <= length; i++) {
		int buffer = price_table[i] + Cut_rod(price_table, length - i);
		price = max(price, buffer);
	}
	return(price);
}
// �Զ����µ��и���ǽ��Ѿ�����Ľ��������vector�У������ظ�����
int Cut_rod_aux(map<int, int> price_table, int length, vector<int>& memory) {
	if (memory[length] >= 0) {
		return(memory[length]);
	}
	int price;
	if (length == 0) {
		price = 0;
	}
	else {
		price = -9999;
		for (int i = 1; i <= length; i++) {
			price = max(price, price_table[i] + Cut_rod_aux(price_table, length - i, memory));
		}
	}
	memory[length] = price;
	return(price);
}
int Cut_rod_with_memoized(map<int, int> price_table, int length) {
	vector<int> memory;
	for (int i = 0; i <= length; i++) {
		memory.push_back(-999);
	}
	int result = Cut_rod_aux(price_table, length, memory);
	return(result);
}
// ���¶��ϵ��и�
int Bottom_up_cut_rod(map<int, int> price_table, int length) {
	vector<int> memory;
	memory.push_back(0);
	for (int j = 0; j <= length; j++) {
		int price = -999;
		for (int i = 1; i <= j; i++) {
			price = max(price, price_table[i] + memory[j - i]);
		}
		memory.push_back(price);
	}
	return(memory[length]);
}
// �����и�������¶����и�
array<int, 2> Extend_bottom_up_cut_rod(map<int, int> price_table,int length) {
	vector<int> memory, strategy;
	memory.push_back(0);
	for (int j = 0; j <= length; j++)strategy.push_back(0);

	for (int j = 1; j <= length; j++) {
		int price = -99;
		for (int i = 1; i <= j; i++) {
			if (price < price_table[i] + memory[j - i]) {
				price = price_table[i] + memory[j - i];
				strategy[j] = i;
			}
		}
		memory.push_back(price);
	}
	array<int, 2> result{ memory[length],strategy[length] };
	return(result);
}


int main() {
	int best_price = Cut_rod(*Price_table, 4);
	cout << best_price << endl;

	int best_price_1 = Cut_rod_with_memoized(*Price_table, 4);
	cout << best_price_1 << endl;

	int best_price_2 = Bottom_up_cut_rod(*Price_table, 4);
	cout << best_price_1 << endl;

	array<int, 2> result = Extend_bottom_up_cut_rod(*Price_table, 10);
	cout << result[0] << " ; " << result[1] << endl;
}