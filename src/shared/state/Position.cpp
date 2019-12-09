#include "Position.h"

using namespace std;
using namespace state;

Position::Position()
{

}

Position::Position(float x,float y){
    this->x=x;
    this->y=y;
}


void Position::setX(float x)
{
    this->x=x;
}

void Position::setY(float y)
{
    this->y=y;
}

float Position::getX()
{
    return x;
}

float Position::getY()
{
    return y;
}




Position::~Position()
{
    
}