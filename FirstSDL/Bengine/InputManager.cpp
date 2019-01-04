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

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		if (keysMap.find(keyID) != keysMap.end())
		{
			return keysMap[keyID];
		}

		return false;
	}

}