#pragma once
#include <string>
#include <fstream>

class Debugger
{
private:
	bool m_active;
	std::ofstream m_writer;
public:
	Debugger(std::string _file);
	~Debugger();
	void setActive(bool _active);
	void print(std::string _text, bool _printToFile = false);
};