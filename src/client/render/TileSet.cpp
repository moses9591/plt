#include "TileSet.h"
#include <iostream>

using namespace std;
using namespace render;


TileSet::TileSet(std::string path)
{
	this->path = path;
}
 
bool TileSet::loadTexture()
{
	
	bool result;
	result = this->textureTileSet.loadFromFile(path);
	return result;
}

const sf::Texture& TileSet::getTexture() 
{
	return this->textureTileSet;
}



