#pragma once
#include"include.h"

// 矩阵本身的类
template<class T> class Matrix {
private:
	T** matrix;
public:
	const int row_size, col_size;
	// 构造函数
	Matrix(int rs, int cs)
		:row_size(rs), col_size(cs) {
		matrix = new T * [row_size];
		for (int i = 0; i < row_size; i++) {
			matrix[i] = new T[col_size];
		}
	}
	Matrix(int rs, int cs, initializer_list<T> li) :Matrix(rs, cs) {
		if (li.size() != rs * cs) {
			cout << "Number doesn't match !";
			exit(-1);
		}
		else {
			int index = 0;
			for (auto it = li.begin(); it != li.end(); it++) {
				int y_pos = floor(index / cs);
				int x_pos = index % cs;
				matrix[y_pos][x_pos] = *it;
				index++;
			}
		}

	}
	Matrix(int rs, int cs, int num) :Matrix(rs, cs) {
		for (int i = 0; i < rs; i++) {
			for (int j = 0; j < cs; j++) {
				this->matrix[i][j] = num;
			}
		}
	}
	Matrix(Matrix& m) :Matrix(m.row_size, m.col_size) {
		for (int i = 0; i < m.row_size; i++) {
			for (int j = 0; j < m.col_size; j++) {
				this->matrix[i][j] = m.matrix[i][j];
			}
		}
	}
	~Matrix() {
		for (int i = 0; i < row_size; i++) {
			delete matrix[i];
		}
		delete matrix;
	}
	// 输出矩阵
	void Display() {
		cout << "[";
		for (int i = 0; i < row_size; i++) {
			if (i == 0)cout << "[";
			else cout << " [";
			for (int j = 0; j < col_size; j++) {
				cout << " " << matrix[i][j];
			}
			if (i == row_size - 1)cout << "]";
			else cout << "]" << endl;
		}
		cout << "]" << endl;
	}
	// 查询矩阵的值
	T Query(int x, int y) const {
		return(matrix[x][y]);
	}
	// 修改矩阵的值
	void Set_value(int row_index, int col_index, T value) {
		if (row_index >= row_size || col_index >= col_size) {
			cout << "Index is bigger than matrix shape in " << row_index << " ; " << col_index << endl;
			exit(-1);
		}
		else {
			matrix[row_index][col_index] = value;
		}
	}
	// 重构操作符
	void operator=(const Matrix<T>& m) {
		if (this->row_size != m.row_size || this->col_size != m.col_size) {
			cout << "Shape doesn't match !" << endl;
			exit(-1);
		}
		else {
			for (int rs = 0; rs < row_size; rs++) {
				for (int cs = 0; cs < col_size; cs++) {
					this->matrix[rs][cs] = m.Query(rs, cs);
				}
			}
		}
	}
	Matrix<T> operator+(const Matrix<T>& m) {
		if (this->row_size != m.row_size || this->col_size != m.col_size) {
			cout << "Shape doesn't match !" << endl;
			exit(-1);
		}
		else {
			Matrix<T> output(this->row_size, this->col_size);
			for (int rs = 0; rs < this->row_size; rs++) {
				for (int cs = 0; cs < this->col_size; cs++) {
					output.Set_value(rs, cs, this->matrix[rs][cs] + m.Query(rs, cs));
				}
			}
			return(output);
		}
	}
	Matrix<T> operator-(const Matrix<T>& m) {
		if (this->row_size != m.row_size || this->col_size != m.col_size) {
			cout << "Shape doesn't match !" << endl;
			exit(-1);
		}
		else {
			Matrix<T> output(this->row_size, this->col_size);
			for (int rs = 0; rs < this->row_size; rs++) {
				for (int cs = 0; cs < this->col_size; cs++) {
					output.Set_value(rs, cs, this->matrix[rs][cs] - m.Query(rs, cs));
				}
			}
			return(output);
		}
	}
	Matrix<T> operator*(const Matrix<T>& m) {
		if (this->col_size != m.row_size) {
			cout << "Shape doesn't match !" << endl;
			exit(-1);
		}
		else {
			Matrix<T> output(this->row_size, m.col_size);
			for (int i = 0; i < this->row_size; i++) {
				for (int j = 0; j < m.col_size; j++) {
					T buffer = 0;
					for (int k = 0; k < this->col_size; k++) {
						buffer += this->Query(i, k) * m.Query(k, j);
					}
					output.Set_value(i, j, buffer);
				}
			}
			return(output);
		}
	} 
};

class Bio_seq {
private:
	string seq;
public:
	Bio_seq(string i):seq(i){}
	Bio_seq(Bio_seq& c):seq(c.Sequence()){}
	string Sequence() {
		return(seq);
	}
	int Length() const {
		return(seq.length());
	}
	char& operator[](int i) {
		if (i >= seq.length() || i < 0) {
			cout << "Index is Wrong in " << i << "with seq length "<< seq.length() << endl;
			exit(-1);
		}
		else {
			return(seq[i]);
		}
	}

};

