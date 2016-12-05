#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameObject.h"
#include "ObjectFactory.h"

struct StateInfo
{
	std::vector<GameObject*>* m_destroyRequests;
};