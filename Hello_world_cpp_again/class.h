#pragma once
#include"include.h"


class Entity {
public:
	Entity() {
		cout << "Created entity!" << endl;
	}
	~Entity() {
		cout << "Destroyed entity!" << endl;
	}
	void Print(string s) {
		cout << s << endl;
	}
};

struct Vertex {
	int x, y, z;
	Vertex(int x, int y,int z):x(x),y(y),z(z){}
	Vertex(const Vertex& vertex)
		:x(vertex.x),y(vertex.y),z(vertex.z)
		{
		cout << "Copied!" << endl;
	} 
};

ostream& operator<<(ostream& stream, const Vertex& vertex) {
	stream << vertex.x << "," << vertex.y << "," << vertex.z;
	return stream;
}

template<typename T ,int N>
class Array {
private:
	T m_array[N];
public:
	int Getsize() const { return N; }
};
