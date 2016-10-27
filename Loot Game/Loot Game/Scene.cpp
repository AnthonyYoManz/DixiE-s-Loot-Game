#include "scene.h"
#include "sceneObject.h"

void Scene::addObject(SceneObject* _object, sf::Vector2f _position)
{
    if(m_currentHandle == 0)
	{
        m_currentHandle = 1;
    }
    _object->initialise(m_currentHandle, _position);
    m_objectList.push_back(_object);
    m_currentHandle++;
}
void Scene::removeObject(unsigned int _handle)
{
    m_removalList.push_back(_handle);
}
void Scene::uncleanRemoveObject(unsigned int _handle)
{
    m_uncleanRemovalList.push_back(_handle);
}
void Scene::moveCamera(float _x, float _y)
{
    m_cameraPosition.x += _x;
    m_cameraPosition.y += _y;
}
void Scene::offsetCamera(float _x, float _y)
{
    m_cameraOffset.x += _x;
    m_cameraOffset.y += _y;
}
sf::Vector2f Scene::getCameraPosition()
{
    return m_cameraPosition + m_cameraOffset;
}
unsigned int Scene::getObjectCount()
{
    return m_objectList.size();
}

SceneObject* Scene::getObjectByID(unsigned int _objectID)
{
    if(_objectID < m_objectList.size())
	{
        return m_objectList.at(_objectID);
    }
    return NULL;
}

SceneObject* Scene::getObjectByHandle(unsigned int _handle)
{
    if(_handle != 0)
	{
        for(SceneObject* object : m_objectList)
		{
            if(object->getHandle() == _handle)
			{
                return object;
            }
        }
    }
    return NULL;
}

void Scene::removeObjectFromList(unsigned int _handle)
{
    if(_handle != 0)
	{
        for(unsigned int i=0; i<m_objectList.size(); i++)
		{
            if(m_objectList.at(i)->getHandle() == _handle)
			{
                m_objectList.at(i)->cleanup();
                delete m_objectList.at(i);
                m_objectList.erase(m_objectList.begin()+i);
                break;
            }
        }
    }
}
void Scene::processRemovalList()
{
    for(unsigned int i=0; i<m_removalList.size(); i++)
	{
        removeObjectFromList(m_removalList.at(i));
    }
    m_removalList.clear();
}
void Scene::processUncleanRemovalList()
{
    for(unsigned int i=0; i<m_uncleanRemovalList.size(); i++)
	{
        unsigned int handle = m_uncleanRemovalList.at(i);
        if(handle != 0)
		{
            for(unsigned int i=0; i<m_objectList.size(); i++)
			{
                if(m_objectList.at(i)->getHandle() == handle)
				{
                    m_objectList.erase(m_objectList.begin()+i);
                    break;
                }
            }
        }
    }
}
