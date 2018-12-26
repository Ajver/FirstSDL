#pragma once

#include <vector>

class IOManager
{
public:
	static bool readFileToBuffer(std::string, std::vector<unsigned char> &);
};

