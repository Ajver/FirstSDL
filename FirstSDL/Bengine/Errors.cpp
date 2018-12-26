#include "Errors.h"

namespace Bengine
{

	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		system("pause");

		SDL_Quit();
		exit(69);
	}

}