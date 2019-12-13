#include "MoveArray.h"

using namespace std;
using namespace state;

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