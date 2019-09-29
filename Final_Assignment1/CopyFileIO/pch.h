
#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class TestIO
{
private:
	std::string in_file;
	std::string out_file;

	std::ifstream infileStream;
	std::ofstream outfileStream;

	bool isOpened;
public:
	TestIO(std::string in, std::string out) :
		in_file{ in }, out_file{ out }, isOpened(false) {
		std::cout << "the source file is " << in_file << '\n';
		std::cout << "the target file is " << out_file << '\n';
	}
	~TestIO()
	{
	}

	bool Opened() const { return isOpened; }

	void process() {
		infileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		outfileStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try {
			// 打开只读模式的文件
			infileStream.open(in_file, std::ios::in);
			outfileStream.open(out_file, std::ios::out | std::ios::trunc);
			isOpened = true;
			// 创建临时缓冲
			std::stringstream inFileBuffer;
			auto buf = infileStream.rdbuf();
			inFileBuffer << buf;

			// 将临时缓冲写入输出文件
			outfileStream << inFileBuffer.str();

			infileStream.close();
			outfileStream.close();
		}
		catch (std::fstream::failure e) {
			std::cerr << e.what() << std::endl;
			exit(-1);
		}
	}

};


#endif //PCH_H
