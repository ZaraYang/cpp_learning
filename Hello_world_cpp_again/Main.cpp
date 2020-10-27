#include"include.h"
#include"class.h"


void smart_ptr() {

	{
		// 唯一指针无法被复制，指针删除时会自动地释放内存
		// 无法被传递进函数或者类
		// copy函数被delete了
		unique_ptr<Entity>entity = make_unique<Entity>();
		entity->Print("Hello! Yang!");
	}

	{
		shared_ptr<Entity>e0;
		{
			// 分享指针，通过变量的reference counter来计算变量有几个reference，当counter归零时释放内存
			shared_ptr<Entity>entity = make_shared<Entity>();
			// 可以复制shared_ptr但是不会增加reference counter
			weak_ptr<Entity>weak_eneity = entity;
			e0 = entity;
		}
		// 只有当指向该内存的全部reference都被删除时该内存才会被释放
	}

}

void vector_func() {
	vector<Vertex> vertices;
	vertices.reserve(3);
//	vertices.push_back(Vertex(1, 2, 3));
//	vertices.push_back(Vertex(4, 5, 6));
//	vertices.push_back(Vertex(7, 8, 9));

	// push_back会将变量在stack中建立然后复制进内存
	// emplace_back直接在内存里建立	vertices.push_back(Vertex(1, 2, 3));
	vertices.emplace_back(1, 2, 3);
	vertices.emplace_back(4, 5, 6);
	vertices.emplace_back(7, 8, 9);


	for (int i = 0; i < vertices.size(); i++) {
		cout << vertices[i] << endl;
	}
	for (Vertex& v : vertices) {
		cout << v << endl;
	}
	vertices.erase(vertices.begin()+1);
	vertices.clear();
	
	// How can we avoid copying vector




}


template<typename T>
void Template(T value) {
	// 带有template的函数只有在调用的时候才根据调用的参数决定函数形式
	// 如果没有调用，该函数并不存在 
	cout << value << endl;

	Array<int,6> array;
	cout << array.Getsize() << endl;

}

int main() {
	//	smart_ptr();
	//	vector_func();
	
	Template(4);
	Template("String");
	Template(2.7);

}