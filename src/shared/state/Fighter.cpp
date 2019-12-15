#include "Fighter.h"
#include <iostream>
#include "State.h"
#include "MoveArray.h"

using namespace std;

using namespace state;

Fighter:: Fighter()
{
	
}

Fighter:: Fighter(int playerID, FighterName name)
{
	this-> playerID = playerID;
	this-> name = name;
}

Fighter::Fighter(FighterName name, int playerID, FighterStatus status, int healthPointsMax, int healthPoints,int movePoints,int combo,Attack attack, int mana)
{
	this->name = name;
	this->playerID = playerID;
	this->status = status;
	this->healthPointsMax = healthPointsMax;
	this->healthPoints = healthPoints;
	this->combo=combo;
	this->attack=attack;
	this->mana = mana;
}

int Fighter::damageCompute(int damage)
{	
	this->healthPoints = healthPoints - damage;
	if(healthPoints <0) 
	{
		healthPoints=0;
	}
	return healthPoints;
}



void Fighter::fight(std::shared_ptr<Fighter> target, Attack attack)
{
	int tabDamage[3] = {20,30,40};
	int damage =rand()%3;
	if(mana >=30)
	{
		//cout << "enough mana" << endl;
		if(target->getStatus()!=DEFENSE)
		{
			if(attack==COUPDEPOING )
			{
				//for defining the variable
				target->damageCompute(tabDamage[damage]); // attack in Fighter
				mana -= 30;
				status = WAITING;
			}
			if(attack==COUPDEPIED )
			{
				damage = 30;
				target->damageCompute(tabDamage[damage]); 
				mana -= 40;
				status = WAITING;
			}
		}
		else if(target->status == DEFENSE)
		{
			if(attack == COUPDEPOING)
			{
				target->damageCompute(tabDamage[damage]); 
				mana -=30;
				status = WAITING;
			}
			if(attack == COUPDEPIED )
			{
				target->damageCompute(tabDamage[damage]); 
				mana -=40;
				status = WAITING;
			}
		} 
		if(attack == SPECIAL)
		{
			if(mana >=60)
			{
				target->damageCompute(tabDamage[damage]); 
				mana -=70;
				
			}else{
				cout << "not enough mana for special attack. Peease recharge! ;) "<<endl; 
				status = WAITING;
			}
		}
	}else{
		cout << "Please recharge! ;)" << endl;
		status = WAITING;
	}
	
}

void Fighter::recharge()
{
	manaMax = 100;
	mana += 20;
	if(mana > manaMax) mana = manaMax;
	status = RECHARGE;
}

void Fighter::defend()
{
	status = DEFENSE;
}


FighterName Fighter::getName()
{
	return name;
}

void Fighter::setName(FighterName name)
{
	this->name = name;
}

int Fighter::getHealthPoints()
{
	return healthPoints;
}

void Fighter::setHealthPoints(int healthPoints)
{
	this->healthPoints = healthPoints;
}

void Fighter::setHealthPointsMax(int healthPointsMax)
{
	this->healthPointsMax = healthPointsMax;
}

int Fighter::getHealthPointsMax()
{
	return healthPointsMax;
}

void Fighter::setCombo(int combo)
{
	this->combo=combo;
}

int Fighter::getCombo()
{
	return combo;
}

void Fighter::setStatus(FighterStatus status)
{
	this->status = status;
}

FighterStatus Fighter::getStatus()
{
	return status;
}

void Fighter::setAttack(Attack attack)
{
	this->attack = attack;
}

Attack Fighter::getAttack()
{
	return attack;
}

void Fighter::setMana(int mana)
{
	this->mana = mana;
}

int Fighter::getMana()
{
	return mana;
}


void Fighter::setPosition(std::shared_ptr<Position> position)
{
	this->position = position;
}

std::shared_ptr<Position> Fighter::getPosition()
{
	return position;
}

void Fighter::move(std::shared_ptr<State> state, Direction direction){

	if(direction == RIGHT)
	{
		if(state->getCurrentPlayerID() == 0){
			cout << "right" <<endl;
			std::shared_ptr<Position> pos1 = state->getPlayerList()[0]->getFighter()->getPosition();
			pos1->setX(pos1->getX() + 200);
			state->getPlayerList()[0]->getFighter()->setPosition(pos1);
		}
		if(state->getCurrentPlayerID() == 1){
			cout << "right" <<endl;
			std::shared_ptr<Position> pos1 = state->getPlayerList()[1]->getFighter()->getPosition();
			pos1->setX(pos1->getX() + 200);
			state->getPlayerList()[0]->getFighter()->setPosition(pos1);
		}
	}
	if(direction == LEFT)
	{
		if(state->getCurrentPlayerID() == 0){
			cout << "left" <<endl;
			std::shared_ptr<Position> pos1 = state->getPlayerList()[0]->getFighter()->getPosition();
			pos1->setX(pos1->getX() - 200);
			state->getPlayerList()[0]->getFighter()->setPosition(pos1);
		}
		if(state->getCurrentPlayerID() == 1){
			cout << "left" <<endl;
			std::shared_ptr<Position> pos1 = state->getPlayerList()[1]->getFighter()->getPosition();
			pos1->setX(pos1->getX() - 200);
			state->getPlayerList()[0]->getFighter()->setPosition(pos1);
		}
	}
}

