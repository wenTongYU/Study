// CopyFileIO.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"


int main()
{
	std::cout << "Please input a source file name: ";
	std::string inFileName;
	std::cin >> inFileName;

	std::cout << "Please input a target file name: ";
	std::string outFileName;
	std::cin >> outFileName;

	TestIO test{ inFileName, outFileName };
	test.process();

	std::cout << "Process complete!";
	return 0;
}
