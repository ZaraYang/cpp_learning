#include"include.h"
#include"class.h"
#include"func.h"



int main() {


	Matrix<int> a(30,35,0);
	Matrix<int> b(35, 15, 0);
	Matrix<int> c(15, 5, 0);
	Matrix<int> d(5, 10, 0);
	Matrix<int> f(10, 20, 0);
	Matrix<int> g(20, 25, 0);
	Matrix_chain_multiply({ a,b,c,d,f,g });
}