#pragma once
#include"include.h"
#include"class.h"


enum Strategy{Left,Up,Exact,None};

int Print_Lcs(Matrix<int> Lcs_matrix, Bio_seq& x,Bio_seq& y, int i, int j,string& result_x,string& result_y,string& margin,int& score) {
	if (i == 0 && j == 0) {
		result_x += x[0];
		result_y += y[0];
		margin += " ";
		return(0);
	}
	else if (i == 0 && j != 0) {
		result_y += y[0];
		result_x += "-";
		margin += " ";
		return(0);
	}
	else if (i != 0 && j == 0) {
		result_x += x[0];
		result_y += "-";
		margin += " ";
		return(0);
	}
	else {
		if (Lcs_matrix.Query(i, j) == Exact) {
			Print_Lcs(Lcs_matrix, x, y, i - 1, j - 1, result_x, result_y,margin,score);
			result_x += x[i - 1];
			result_y += y[j - 1];
			margin += "|";
			score += 1;
		}
		else if (Lcs_matrix.Query(i, j) == Up) {
			Print_Lcs(Lcs_matrix, x, y, i - 1, j, result_x, result_y, margin,score);
			result_x += x[i - 1];
			result_y += "-";
			margin += " ";
		}
		else {
			Print_Lcs(Lcs_matrix, x, y, i, j - 1, result_x, result_y, margin,score);
			result_x += "-";
			result_y += y[j - 1];
			margin += " ";
		}
	}

}


void Longest_common_sequence(Bio_seq& x, Bio_seq& y) {
	int x_length = x.Length();
	int y_length = y.Length();
	Matrix<int> Strategy_buffer(x_length+1,y_length+1,None);
	Matrix<int> Lcs_buffer(x_length+1, y_length+1, 0);

	for (int i = 0; i < x_length; i++) {
		for (int j = 0; j < y_length; j++) {
			if (x[i] == y[j]) {
				Lcs_buffer.Set_value(i+1, j+1, Lcs_buffer.Query(i, j) + 1);
				Strategy_buffer.Set_value(i+1, j+1, Exact);
			}
			else if (Lcs_buffer.Query(i, j+1) >= Lcs_buffer.Query(i+1, j)) {
				Lcs_buffer.Set_value(i+1, j+1, Lcs_buffer.Query(i, j+1));
				Strategy_buffer.Set_value(i + 1, j + 1, Up);
			}
			else {
				Lcs_buffer.Set_value(i+1, j+1, Lcs_buffer.Query(i+1, j));
				Strategy_buffer.Set_value(i + 1, j + 1, Left);
			}
		}
	}
	int score = 0;
	string result_x = "";
	string result_y = "";
	string margin = "";
	Print_Lcs(Strategy_buffer, x,y, x.Length(), y.Length(),result_x,result_y,margin,score);
	cout << result_x << endl;
	cout << margin << endl;
	cout << result_y << endl;
	cout << "Score : " << score << endl;
}	


