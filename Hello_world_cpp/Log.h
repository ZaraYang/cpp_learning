// ͷ�ļ�����������ֹ����ͷ�ļ��Ķ�ε���
// ������ͷ�ļ��ж����structure�����ȣ��ᵼ���ظ�����
#pragma once
#include <iostream>
#include <string>
#include <memory>


//��ͷ�ļ������д�ź���������#Includeʱ��ͳһ���ƽ�Դ����
void Log(const char* message);
void InitLog();

void Forloop(int times);
void Whileloop(int times);

void pointer_def();
void reference_def();
void Function();

void choice_enum();

void array_def();
void string_def();

void const_def();

void tarnart_def(int& s_Level,int& s_Speed);

// ===================================================
// class Ĭ���ڲ�����Ϊ˽�е��޷��ⲿ����
// struct Ĭ��Ϊ���е�
// û�������Ĳ��
class Player_1
{
public:
	int x, y;
	int speed = 1;
	// Constructor ����class�ĳ�ʼ�� __init__()
	// Player() = delete ��ʹclass�޷�ʵ���������߽�constructorתΪPrivite
	// ֻ��ʹ��class�еķ������޷�ʵ����
	Player_1() {
		std::cout << "Constructed Player!" << std::endl;
		x = 0;
		y = 0;
	}
// �������ĳ�ʼ��
//	Player(int a, int b)
//	{
//		x = a;
//		y = b;
//	}
	// ��class���ڴ��б�ɾ��ʱִ��
	~Player_1()
	{
		std::cout << "Destroyed Player!" << std::endl;
	}

	void move(int xa, int ya)
	{
		x += xa * speed;
		y += ya * speed;
	}
};
// ================================
class Log_message
{
public:
	enum Level {
		Error,Warning,Info
	}; 
private:
	Level m_LogLevel = Info;
public:
	void SetLevel(Level level)
	{
		m_LogLevel = level;
	}
	void RaiseWarn(const char* message)
	{
		if (m_LogLevel >= Warning)
			std::cout << "[WARNING]:" << message << std::endl;
	}
	void RaiseError(const char* message)
	{
		if (m_LogLevel >= Error)
			std::cout << "[ERROR]:" << message << std::endl;
	}
	void RaiseInfo(const char* message)
	{
		if (m_LogLevel >= Info)
			std::cout << "[INFO]:" << message << std::endl;
	}
};

class Entity {
protected:  
// private ����class�ڲ����Ե���
// protected ����class ������������Ե���
// public ����
	float X, Y;
	// =0 ���麯���������������о���ʵ��
	// ���д��麯����class�޷���ʵ����
	// ���麯�����ڽӿڣ�ȷ��ʵ������ĳ�����������ں�������
	// û��ʵ�ִ��麯����class���޷�ʵ������
	virtual void PrintName() = 0;
	void Move(float xa, float ya) {
		X += xa;
		Y += ya;
	}
	// �麯�� ��father class method �ĸ�д������һ���麯��������¼��Ӧ�ĸ�д��ĺ���
	virtual std::string GetName() {
		return("Entity");
	}
};

class Player :public Entity {
private:
	std::string Player_Name;
public:
	Player(float X_init,float Y_init,const std::string Name){
		X = X_init;
		Y = Y_init;
		Player_Name = Name;
	}
	void PrintName() override {
		std::cout << Player_Name << std::endl;
	}
	std::string GetName() override {
		return(Player_Name);
	}
	void Show_position() {
		std::cout << X << "," << Y << std::endl;
	}
};

class Entity1 {
private:
	std::string m_name;
	int m_score;
public:
	Entity1():m_name("Unknow"),m_score(0){
	}
};

class Entity2 {
private:
	std::string m_name;
public:
	Entity2():m_name("Unknow") {}
	Entity2(const std::string& name) :m_name(name) {}

	const std::string& GetName() const { return m_name; }
};

class Entity3 {
private:
	std::string m_Name;
	int m_Age;
public:
	Entity3(const std::string& name)
		:m_Name(name), m_Age(-1) {}
//	Entity3(int age)
//		:m_Age(age) {}
	explicit Entity3(int age)
		:m_Age(age) {}

};
// operator  overload
struct Vector2 {
	float x, y;
	Vector2(float x,float y)
		:x(x),y(y) {}
	Vector2 Add(Vector2& other) const {
		return(Vector2(x + other.x, y + other.y));
	}
	Vector2 operator+(Vector2& other) const{
		return Add(other);
	}
};

class Entity4 {
public:
	Entity4() {
		std::cout << "Created Entity !" << std::endl;
	}
	~Entity4() {
		std::cout << "Destroyed Entity!" << std::endl;
	}
	void Print() {
		std::cout << "Ptint func" << std::endl;
	}

};




