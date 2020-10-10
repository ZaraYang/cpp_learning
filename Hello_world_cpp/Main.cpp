#include <iostream>
#include "Log.h"

void Log(const char* message)
{
	std::cout << message << std::endl;
}


int main()
{
//	Log_message log;
//	log.SetLevel(log.Warning);
//	log.RaiseWarn("Hello");
//	log.RaiseInfo("Hello");
//	log.RaiseError("Hello");


	Player* entity1 = new Player(0.5,0.81,"Glace");
	std::cout << entity1->GetName() << std::endl;

	Player* player1 = new Player(0.1,0.5,"Yang");
	std::cout << player1->GetName() << std::endl;

	player1->PrintName();
	entity1->PrintName();

	std::cin.get();
}
