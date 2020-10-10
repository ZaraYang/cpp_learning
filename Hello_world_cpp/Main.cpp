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
	// 隐式转换 将int 转换为Entity3
	// 但是字符串无法完成隐式转换因为其本质是字符数组，需要先将数组转化为字符串，在将字符串转化为Entity3，但是只能有一次转换
	// Entity3 d = std::string("YANG") will be work
	// 在class构造体前加入explicit以禁止隐式转换


	// operator 
//	Vector2 position(4.0, 5.0);
//	Vector2 Speed(2.0, 2.0);
//	Vector2 a = position + Speed;
//	std::cout << a << std::endl;



	{
		// smart ptr
		// ========================================================
		//Unique ptr 会自动地调用new 和delete 在heap中分配内存
		//  std::unique_ptr<Entity4>entity(new Entity4());
		// std::unique_ptr<Entity4> entity = std::make_unique<Entity4>();
		// unique ptr 无法被复制 其copy方法被delete了
		// std::unique_ptr<Entity4> e = entity;
		// entity->Print();
		
		// shared pointer
		// reference counter 计数该内存有几个reference 归零后才会自动delete
		// reference counter 保存在 control block中 所以调用了两块内存空间
		// std::shared_ptr<Entity4>shared_eneity = std::make_shared<Entity4>();
		// std::shared_ptr<Entity4>shared_entity_1 = shared_eneity;
		// 将shared ptr 复制到 weak ptr 时不会增加refecence counter 
		// won't keep ptr alive 仅仅是检查变量是否还存在并且做出操作
		// std::weak_ptr<Entity4>weak_entity = shared_eneity;
	}




}
