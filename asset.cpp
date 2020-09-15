#include "asset.h"

Asset::Asset(std::string id)
{
	_id = id;
}

Asset::~Asset()
{
}

std::string Asset::id()
{
	return _id;
}
