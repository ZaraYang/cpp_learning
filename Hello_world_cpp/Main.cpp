#include <iostream>
#include "Log.h"

void Log(const char* message)
{
	std::cout << message << std::endl;
}


// << overload
std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
	stream << other.x << "," << other.y;
	return stream;
}


int main()
{
//	Log_message log;
//	log.SetLevel(log.Warning);
//	log.RaiseWarn("Hello");
//	log.RaiseInfo("Hello");
//	log.RaiseError("Hello");

//
//	Player* entity1 = new Player(0.5,0.81,"Glace");
//	std::cout << entity1->GetName() << std::endl;

//	Player* player1 = new Player(0.1,0.5,"Yang");
//	std::cout << player1->GetName() << std::endl;

//	player1->PrintName();
//	entity1->PrintName();
	
	
//	int s_Speed = 4;
//	int s_Level = 4;
//	int& speed_ref = s_Speed;
//	int& level_ref = s_Level;
//	tarnart_def(level_ref,speed_ref);
//	std::cout << s_Speed << std::endl;
//	Entity2* e_ptr;
//	{
//		const std::string Player_name = "Yang";
//		Entity2 e(Player_name);
//		e_ptr = &e;
//		std::cout << e.GetName() << std::endl;
//	}

//	{
//		Entity2* e_ptr1 = new Entity2("Yang"); 
//		e_ptr = e_ptr1;
//		std::cout << e_ptr1->GetName() << std::endl;
//	}

//	std::cin.get();
//	delete e_ptr; 

	// Entity3 a("Yang");
	// Entity3(25);
	// Entity3 c = 25;
	// ��ʽת�� ��int ת��ΪEntity3
	// �����ַ����޷������ʽת����Ϊ�䱾�����ַ����飬��Ҫ�Ƚ�����ת��Ϊ�ַ������ڽ��ַ���ת��ΪEntity3������ֻ����һ��ת��
	// Entity3 d = std::string("YANG") will be work
	// ��class������ǰ����explicit�Խ�ֹ��ʽת��


	// operator 
//	Vector2 position(4.0, 5.0);
//	Vector2 Speed(2.0, 2.0);
//	Vector2 a = position + Speed;
//	std::cout << a << std::endl;



	{
		// smart ptr
		// ========================================================
		//Unique ptr ���Զ��ص���new ��delete ��heap�з����ڴ�
		//  std::unique_ptr<Entity4>entity(new Entity4());
		// std::unique_ptr<Entity4> entity = std::make_unique<Entity4>();
		// unique ptr �޷������� ��copy������delete��
		// std::unique_ptr<Entity4> e = entity;
		// entity->Print();
		
		// shared pointer
		// reference counter �������ڴ��м���reference �����Ż��Զ�delete
		// reference counter ������ control block�� ���Ե����������ڴ�ռ�
		// std::shared_ptr<Entity4>shared_eneity = std::make_shared<Entity4>();
		// std::shared_ptr<Entity4>shared_entity_1 = shared_eneity;
		// ��shared ptr ���Ƶ� weak ptr ʱ��������refecence counter 
		// won't keep ptr alive �����Ǽ������Ƿ񻹴��ڲ�����������
		// std::weak_ptr<Entity4>weak_entity = shared_eneity;
	}




}
