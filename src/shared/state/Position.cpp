#include "Position.h"
#include <iostream>

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
    std::cout << this->x << std::endl;
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