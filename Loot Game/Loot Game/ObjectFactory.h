#pragma once

#include <map>
#include <string>
#include <functional>

template <typename T>
class ObjectFactory 
{
private:
	std::map<std::string, std::function<T*()>> m_creatorFunctions;
	//not a linked list, but the list the factory is linked to
	std::vector<T*>* m_linkedList;
public:
	ObjectFactory()
	{
		m_linkedList = nullptr;
	}

	~ObjectFactory()
	{

	}

	//Add object creation function to map
	void addCreator(std::string _className, std::function<T*()> _func)
	{
		if (m_creatorFunctions.find(_className) == m_creatorFunctions.end())
		{
			m_creatorFunctions[_className] = _func;
		}
	}

	//Removes specified object creation function
	void removeCreator(std::string _className)
	{
		if (m_creatorFunctions.find(_className) != m_creatorFunctions.end())
		{
			m_creatorFunctions.erase(m_creatorFunctions.find(_className));
		}
	}

	//Create object by class name entered as a string in addCreator args
	T* createObject(std::string _className)
	{
		if (m_creatorFunctions.find(_className) == m_creatorFunctions.end())
		{
			return nullptr;
		}
		T* object = m_creatorFunctions[_className]();
		if (m_linkedList)
		{
			m_linkedList->push_back(object);
		}
		return object;
	}

	//Pass nullptr to deselect lists
	void linkList(std::vector<T*>* _list)
	{
		m_linkedList = _list;
	}
};