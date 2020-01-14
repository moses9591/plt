#include "MoveArray.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace state;

MoveArray::MoveArray()
{
    width = 5;
    height = 1;
    
    sf::Sprite grid[width][height];

}

int MoveArray::getHeight()
{
    return height;
}

int MoveArray::getWidth()
{
    return width;
}

std::vector<std::shared_ptr<Fighter>> MoveArray::getMoveArray()
{
    return moveArray;
}