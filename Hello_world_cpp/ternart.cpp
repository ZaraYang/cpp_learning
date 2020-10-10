#include <iostream>
#include "Log.h"
#include <string>



void tarnart_def(int& s_Level, int& s_Speed ){
//	if (s_Level >= 5)
//		s_Speed = 10;
//	else
//		s_Speed = 8;

	s_Speed = s_Level > 5 ? 10 : 8;
	std::string Rank = s_Level > 5 ? "You are a Master" : "You are a beginner";
	std::cout << Rank << std::endl;
	
}