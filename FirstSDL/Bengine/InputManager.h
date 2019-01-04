#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace Bengine
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		void setMousePosition(float x, float y);

		bool isKeyPressed(unsigned int keyID);
		glm::vec2 getMousePosition() const;

	private:
		std::unordered_map<unsigned int, bool> keysMap;
		glm::vec2 mousePosition;
	};

}
