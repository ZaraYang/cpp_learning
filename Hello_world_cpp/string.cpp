#include <iostream>
#include <string>


void Change_string(std::string str) {
	str += "Lalalal";
}

void Change_string_ref(std::string& str_ref) {
	str_ref += "Lalala";

}

void Change_string_ptr(std::string* str_ptr) {
	*str_ptr += "Lalala";
}

void string_def() {
	char name[] = "Heyang";
	char* name_ptr = name;
	std::cout << name_ptr[2]<< strlen(name_ptr) << std::endl;
	

	char name_1[7] = { 'H','e','y','a','n','g','\0'};
	std::cout << name_1 << strlen(name_1)<<  std::endl;

	// string 可以直接加 const char 不能直接加
	std::string name_2 = "HeYang";
	name_2 += " Hello!";
	name_2.find('H');
	std::string& name_2_ref = name_2;
	std::string* name_2_ptr = &name_2;
	Change_string(name_2);
	Change_string_ref(name_2_ref);  
	Change_string_ptr(name_2_ptr);
	std::cout << name_2 << ','<< name_2.size() << ',' << name_2.find('H') <<std::endl;
	bool contains = name_2.find("ng") != std::string::npos;
	// 检查是否包含某字符
//	using namespace std::string_literals;
//	std::u32string name_3 = U"Heyang"s;
//	std::cout << contains << std::endl;"
//	std::string name_list = R"Heyang";                  ???????

}
