#include <iostream>
#include "Log.h"

void choice_enum()
{
	enum color_set {red,yellow,blue,green,white,black};
	color_set color;
	int counter = 0;
	for (int i = red; i <= black; i++) {
		for (int j = red; j <= black; j++) {
			if (i != j) {
				for (int k = red; k <= black; k++) {
					if (k != i && k != j) {
						counter++;
						for (int loop=0;loop<3;loop++){
							switch (loop) {
								case 0:color = (color_set)i; break;
								case 1:color = (color_set)j; break;
								case 2:color = (color_set)k; break;
							}
							switch (color){
								case red: std::cout << "red "; break;
								case yellow: std::cout << "yellow "; break;
								case blue: std::cout << "blue "; break;
								case green: std::cout << "green "; break;
								case white: std::cout << "white "; break;
								case black: std::cout << "black "; break;
							}
						}
						std::cout << std::endl;
					}
				}
			}
		}
	}
}
