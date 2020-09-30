#include <iostream>
// 预处理指令 发生在编译之前，将该文件（iostream）中所有复制到本文件中
// header file

int multiply(int a, int b)
{
    return a*b;
}

void multiplyandlog(int a,int b)
{
    int result = multiply(a,b);
    std::cout << result << std::endl;
}

int main()
// entry point 程序入口
{   // char : 1byte
    // short : 2byte
    // long : 4byte
    // long long : 8byte
    // << reload 重载
    // << endl endline
    std::cout << "hello world" << std::endl;
    int variable_0=8;
    unsigned int variable_1=6;
    //原则上c++中字符就是数字，char只是对数字的解释,决定编译器如何解释数据
    // float doble
    float variable_2=5.5f;  // float 与 double 的定义仅仅在于最后的“f”， 4 byte
    double variable_3=5.4;  // 而与前面的定义无关                       8 byte
    bool variable_4=0;   // 1 byte 内存在寻找地址时无法定位bit，只能定位byte，因此哦需要1byte
    
    //integer 4byte sign or unsign
    // 1 byte = 8 bit
    std::cout << sizeof(variable_0) << std::endl;
    std::cout << sizeof(variable_1) << std::endl;
    std::cout << sizeof(variable_2) << std::endl;
    std::cout << sizeof(variable_3) << std::endl;
    std::cout << sizeof(variable_4) << std::endl;

    multiplyandlog(3,2);
    multiplyandlog(5,9);
    multiplyandlog(786,34);

    // printers 指针  bool*
    //reference 引用 bool&

    std::cin.get();
}

// c++ 中变量类型之间的唯一区别就是在内存中占用的大小
//
