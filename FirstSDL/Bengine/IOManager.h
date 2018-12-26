#pragma once

#include <vector>

namespace Bengine
{

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string, std::vector<unsigned char> &);
	};
}

