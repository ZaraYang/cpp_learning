// 头文件保护符，防止单个头文件的多次导入
// 对于在头文件中定义的structure或函数等，会导致重复错误
#pragma once
#include <iostream>

//在头文件中其中存放函数声明，#Include时会统一复制进源代码
void Log(const char* message);
void InitLog();

void Forloop(int times);
void Whileloop(int times);

void pointer_def();
void reference_def();
void Function();

void choice_enum();

// ===================================================
// class 默认内部变量为私有的无法外部调用
// struct 默认为共有的
// 没有其他的差别
class Player_1
{
public:
	int x, y;
	int speed = 1;
	// Constructor 用于class的初始化 __init__()
	// Player() = delete 会使class无法实例化，或者将constructor转为Privite
	// 只能使用class中的方法，无法实例化
	Player_1() {
		std::cout << "Constructed Player!" << std::endl;
		x = 0;
		y = 0;
	}
// 带参数的初始化
//	Player(int a, int b)
//	{
//		x = a;
//		y = b;
//	}
	// 在class从内存中被删除时执行
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
// private 仅有class内部可以调用
// protected 仅有class 和其衍生类可以调用
// public 公开
	float X, Y;
	// =0 纯虚函数，必须在子类中具体实现
	// 带有纯虚函数的class无法被实例化
	// 纯虚函数用于接口，确保实例存在某个方法而不在乎类种类
	// 没有实现纯虚函数的class是无法实例化的
	virtual void PrintName() = 0;
	void Move(float xa, float ya) {
		X += xa;
		Y += ya;
	}
	// 虚函数 对father class method 的改写，建立一个虚函数表来记录对应的改写后的函数
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

