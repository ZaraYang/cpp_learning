#pragma once
#include"include.h"
#include"class.h"


// 根据表格输出最优乘法顺序
void Print_optimal_strategy(Matrix<int> strategy_matrix, int i, int j) {
	if (i == j) {
		cout << "Matrix_" << i << " ";
	}
	else {
		cout << "( ";
		Print_optimal_strategy(strategy_matrix, i, strategy_matrix.Query(i, j));
		Print_optimal_strategy(strategy_matrix, strategy_matrix.Query(i, j) + 1, j);
		cout << " )";
	}
}
// 矩阵链乘法的动态规划
template<typename T>
void Matrix_chain_multiply(initializer_list<Matrix<T>> li) {
	vector<int> size_vector;
	size_vector.push_back(li.begin()->row_size);
	for (auto it = li.begin(); it != li.end(); it++) {
		size_vector.push_back(it->col_size);
	}
	int p_length = size_vector.size();
	int n_length = p_length - 1;

	Matrix<int> price_buffer(n_length, n_length, -99);
	Matrix<int> strategy_buffer(n_length - 1, n_length, 0);

	for (int i = 0; i < n_length; i++) {
		price_buffer.Set_value(i, i, 0);
	}

	for (int length_buffer = 2; length_buffer <= n_length; length_buffer++) {
		for (int i = 0; i < n_length - length_buffer + 1; i++) {
			int j = i + length_buffer - 1;
			price_buffer.Set_value(i, j, 99999);
			for (int k = i; k <= j - 1; k++) {
				int price = price_buffer.Query(i, k) + price_buffer.Query(k + 1, j) + size_vector[i] * size_vector[k+1] * size_vector[j+1];
				if (price < price_buffer.Query(i, j)) {
					price_buffer.Set_value(i, j, price);
					strategy_buffer.Set_value(i, j, k);
				}
			}
		}
	}
	price_buffer.Display();
	strategy_buffer.Display();
	Print_optimal_strategy(strategy_buffer, 0, 5);
}

