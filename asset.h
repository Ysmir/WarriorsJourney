#pragma once

#include <string>

class Asset
{
public:
	Asset(std::string id);
	~Asset();

	std::string id();

private:
	std::string _id;
};