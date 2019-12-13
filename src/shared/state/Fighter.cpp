#include "Fighter.h"
#include <iostream>

using namespace std;

namespace state{


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
	int damage =0;
	if(mana >=30)
	{
		//cout << "enough mana" << endl;
		if(target->getStatus()!=DEFENSE)
		{
			if(attack==COUPDEPOING )
			{
				damage = 20;		//for defining the variable
				target->damageCompute(damage); // attack in Fighter
				mana -= 30;
				status = ATTACK;
			}
			if(attack==COUPDEPIED )
			{
				damage = 30;
				target->damageCompute(damage);
				mana -= 40;
				//status = WAITING;
			}
		}
		else if(target->status == DEFENSE)
		{
			if(attack == COUPDEPOING)
			{
				damage = 10;
				target->damageCompute(damage);
				mana -=30;
				status = ATTACK;
			}
			if(attack == COUPDEPIED )
			{
				damage = 20;
				target->damageCompute(damage);
				mana -=40;
				//status = WAITING;
			}
		} 
		if(attack == SPECIAL)
		{
			if(mana >=60)
			{
				damage = 60;
				target->damageCompute(damage);
				mana -=70;
				//status = WAITING;
			}else{
				cout << "not enough mana for special attack. Peease recharge! ;) "<<endl; 
				status = WAITING;
			}
		}
	}else{
		cout << "Please recharge! ;)" << endl;
	}
	
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

	void Fighter::recharge()
	{
		status = RECHARGE;
		mana += 20;
		if(mana > manaMax) mana = manaMax;
	}

	void Fighter::defend()
	{
		status = DEFENSE;
	}
	
	void Fighter::setPosition( std::shared_ptr<Position> position)
	{
		this->position = position;
	}
    std::shared_ptr<Position> Fighter::getPosition()
	{
		return position;
	}

	


	void Fighter::move (State& state, Direction direction){
			int mapWidth=state.getWidth();
			int mapHeight=state.getHeight();

		switch(direction){
			
		    case RIGHT:
		        if(y<mapWidth-1){
		            y++;
		            this->direction=direction;
		            break;
		        }else{
		            y=mapWidth-1;
		            break;
		        }
		
		    case LEFT:
		        if(y>0){
		            y--;
		            this->direction=direction;
		            break;
		        }else{
		            y=0;
		            break;
		        }
		    default:
		        break;
		}
	}

}
