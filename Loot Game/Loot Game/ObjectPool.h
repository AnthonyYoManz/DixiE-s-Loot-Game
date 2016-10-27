#pragma once
#include <vector>

template <typename T>
class ObjectPool
{
private:
	int m_maxObjects;
	std::vector<T*> m_activeObjects;
	std::vector<T*> m_inactiveObjects;
public:
	ObjectPool(int _maxObjects, T* (*_creationFunc)())
	{
		m_maxObjects = _maxObjects;
		m_activeObjects.capacity(m_maxObjects);
		m_inactiveObjects.capacity(m_maxObjects);
		for (int i = 0; i < m_maxObjects; i++)
		{
			m_inactiveObjects.push_back(_creationFunc());
		}
	}

	~ObjectPool()
	{
		for (auto& object : m_activeObjects)
		{
			delete object;
		}
		m_activeObjects.clear();
		for (auto& object : m_inactiveObjects)
		{
			delete object;
		}
		m_inactiveObjects.clear();
	}

	T* activateObject()
	{
		if (m_inactiveObjects.size() > 0)
		{
			if (m_activeObjects.size() < m_maxObjects)
			{
				m_activeObjects.push_back(m_inactiveObjects.back());
				m_inactiveObjects.pop_back();
				return m_activeObjects.back();
			}
		}
		return nullptr;
	}
};