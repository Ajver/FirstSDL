#include "InputManager.h"

namespace Bengine
{

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::pressKey(unsigned int keyID)
	{
		keysMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		keysMap[keyID] = false;
	}

	void InputManager::setMousePosition(float x, float y)
	{
		mousePosition.x = x;
		mousePosition.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		if (keysMap.find(keyID) != keysMap.end())
		{
			return keysMap[keyID];
		}

		return false;
	}

	glm::vec2 InputManager::getMousePosition() const
	{
		return mousePosition;
	}
}