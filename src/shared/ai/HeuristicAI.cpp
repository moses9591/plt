#include "HeuristicAI.h"
#include <iostream>
#include "RandomAI.h"
#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <unistd.h>

using namespace std;
using namespace engine;
using namespace state;
using namespace ai;

HeuristicAI::HeuristicAI(int AiID)
{
    ArtificialId=AiID;
}

void HeuristicAI::run(std::shared_ptr<Engine> engine)
{

    int choice;
    //IA is still alive
    while (engine->getState().getPlayerList()[ArtificialId]->getFighter()->getStatus()!=DEAD)
    {
        engine->getState().getPlayerList()[ArtificialId]->getFighter()->setStatus(WAITING);
        //IA in danger 
        if (engine->getState().getPlayerList()[ArtificialId]->getFighter()->getHealthPoints()
             < engine->getState().getPlayerList()[ArtificialId]->getFighter()->getHealthPointsMax() / 4)
        {
            //but if opponent can't attack 
            if(engine->getState().getPlayerList()[!ArtificialId]->getFighter()->getMana()
                <engine->getState().getPlayerList()[!ArtificialId]->getFighter()->getHealthPointsMax() / 4)
                choice = 0; //then IA will attack
            else  choice = 1; //if not IA is going to defend
        }
        else if (engine->getState().getPlayerList()[ArtificialId]->getFighter()->getMana() < 40)
        {
        // Mana is low, regen.
            choice = 3;
        }
        else
        {
            choice = 0;
        }
        
        int waitingTime = 4;
        
        if(choice==0) 
        {
            cout << "IA is attacking" <<endl;
            AttackCommand attack(engine->getState().getPlayerList()[ArtificialId]->getFighter(), engine->getState().getPlayerList()[1]->getFighter());
            unique_ptr<Command> ptr_attack (new AttackCommand(attack));
            engine->addCommand(0, move(ptr_attack));

            ChangeRound changeRound(engine->getState().getPlayerList()[!ArtificialId]->getFighter());
            unique_ptr<Command> ptr_change (new ChangeRound(changeRound));
            engine->addCommand(1, move(ptr_change));

            engine->update();
            usleep(waitingTime);
            break;
            
        }
        else if(choice == 1) 
        {
            cout << "IA is defending" <<endl;
            DefenseCommand defense(engine->getState().getPlayerList()[ArtificialId]->getFighter());
            unique_ptr<Command> ptr_defense (new DefenseCommand(defense));
            engine->addCommand(0, move(ptr_defense));

            ChangeRound changeRound(engine->getState().getPlayerList()[!ArtificialId]->getFighter());
            unique_ptr<Command> ptr_change (new ChangeRound(changeRound));
            engine->addCommand(1, move(ptr_change));

            engine->update();
            usleep(waitingTime);
            break;
            
        }
        else{ 
            cout << "IA is recharging" <<endl;
            RechargeCommand recharge(engine->getState().getPlayerList()[ArtificialId]->getFighter());
            unique_ptr<Command> ptr_recharge (new RechargeCommand(recharge));
            engine->addCommand(0, move(ptr_recharge));

            ChangeRound changeRound(engine->getState().getPlayerList()[!ArtificialId]->getFighter());
            unique_ptr<Command> ptr_change (new ChangeRound(changeRound));
            engine->addCommand(1, move(ptr_change));

            engine->update();
            usleep(waitingTime);
            break;
            
        }
    }   
}