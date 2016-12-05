#include "Debugger.h"
#include <iostream>

Debugger::Debugger(std::string _file)
{
	m_writer.open(_file.c_str());
}

Debugger::~Debugger()
{
	if (m_writer.is_open())
	{
		m_writer.close();
	}
}

void Debugger::setActive(bool _active)
{
	m_active = _active;
}

void Debugger::print(std::string _text, bool _printToFile)
{
	if (m_active)
	{
		std::cout << _text;
		if (m_writer.is_open())
		{
			m_writer << _text;
		}
	}
}
