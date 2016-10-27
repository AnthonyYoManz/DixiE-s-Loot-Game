#pragma once

#include <map>
#include <string>

template <typename T>
class ObjectFactory 
{
private:
	std::map<std::string, T* (*)()> m_creatorFunctions;
public:
	ObjectFactory()
	{

	}
	~ObjectFactory()
	{

	}

	//Add object creation function to map
	void addCreator(std::string className, T* (*_func)())
	{
		if (m_creatorFunctions[className] == 0)
		{
			m_creatorFunctions[className] = func;
		}
	}

	//Create object by class name entered as a string in addCreator args
	T* createObject(std::string _className)
	{
		if (m_creatorFunctions[className] == 0)
		{
			return nullptr;
		}
		return m_creatorFunctions[className]();
	}
};