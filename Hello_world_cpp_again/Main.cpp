#include"include.h"
#include"class.h"


void smart_ptr() {

	{
		// Ψһָ���޷������ƣ�ָ��ɾ��ʱ���Զ����ͷ��ڴ�
		// �޷������ݽ�����������
		// copy������delete��
		unique_ptr<Entity>entity = make_unique<Entity>();
		entity->Print("Hello! Yang!");
	}

	{
		shared_ptr<Entity>e0;
		{
			// ����ָ�룬ͨ��������reference counter����������м���reference����counter����ʱ�ͷ��ڴ�
			shared_ptr<Entity>entity = make_shared<Entity>();
			// ���Ը���shared_ptr���ǲ�������reference counter
			weak_ptr<Entity>weak_eneity = entity;
			e0 = entity;
		}
		// ֻ�е�ָ����ڴ��ȫ��reference����ɾ��ʱ���ڴ�Żᱻ�ͷ�
	}

}

void vector_func() {
	vector<Vertex> vertices;
	vertices.reserve(3);
//	vertices.push_back(Vertex(1, 2, 3));
//	vertices.push_back(Vertex(4, 5, 6));
//	vertices.push_back(Vertex(7, 8, 9));

	// push_back�Ὣ������stack�н���Ȼ���ƽ��ڴ�
	// emplace_backֱ�����ڴ��ｨ��	vertices.push_back(Vertex(1, 2, 3));
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
	// ����template�ĺ���ֻ���ڵ��õ�ʱ��Ÿ��ݵ��õĲ�������������ʽ
	// ���û�е��ã��ú����������� 
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