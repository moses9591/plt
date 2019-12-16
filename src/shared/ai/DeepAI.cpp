#include "DeepAI.h"
#include "engine.h"
#include "../engine/AttackCommand.h"
#include "../engine/DefenseCommand.h"
#include "../engine/RechargeCommand.h"
#include "../engine.h"
#include "../state.h"
#include "../ai.h"

#include <iostream>
#include <unistd.h>


using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

DeepAI::DeepAI(int AiID):depth(depth)
{
    ArtificialId=AiID;
}

//function with the commands
void storeAttackCommands (std::shared_ptr<engine::Engine> engine, std::vector<shared_ptr<Command>> commandList)
{
        //Initialize the Attack constrctor with attacker and target
        AttackCommand attackCommand(engine->getState().getPlayerList()[0]->getFighter(), 
                                            engine->getState().getPlayerList()[1]->getFighter());
        unique_ptr<Command> ptr_attack (new AttackCommand(attackCommand));
        engine->addCommand(0, move(ptr_attack));   

        //convert unique_ptr into _shared_ptr
        std::shared_ptr<Command> ptr_attack_shared = std::move(ptr_attack);
        commandList.push_back(ptr_attack_shared);
}

void storeDefenseCommands(std::shared_ptr<engine::Engine> engine, std::vector<shared_ptr<Command>> commandList)                                
{
    DefenseCommand defense(engine->getState().getPlayerList()[0]->getFighter());
    unique_ptr<Command> ptr_defense (new DefenseCommand(defense));
    engine->addCommand(0, move(ptr_defense));

    //convert unique_ptr into _shared_ptr
    std::shared_ptr<Command> ptr_defense_shared = std::move(ptr_defense);
    commandList.push_back(ptr_defense_shared);

}

void storeRechargeCommands(std::shared_ptr<engine::Engine> engine,std::vector<shared_ptr<Command>> commandList)                                
{
    RechargeCommand recharge(engine->getState().getPlayerList()[0]->getFighter());
    unique_ptr<Command> ptr_recharge (new RechargeCommand(recharge));
    
    engine->addCommand(0, move(ptr_recharge));
    //convert unique_ptr into _shared_ptr
    std::shared_ptr<Command> ptr_recharge_shared = std::move(ptr_recharge);
    commandList.push_back(ptr_recharge_shared);
}

std::vector<shared_ptr<Command>> getCommand()
{
    int action = rand()%3;
    std::shared_ptr<engine::Engine> engine;
    std::vector<shared_ptr<Command>> commandList;
    switch (action)
    {
    case 0:
        storeAttackCommands(engine,commandList);
        break;
    case 1:
        storeDefenseCommands(engine,commandList);
        break;
    case 2:
        storeRechargeCommands(engine,commandList);
        break;
    default:
        break;
    }
    return commandList;
}


void DeepAI::run(std::shared_ptr<engine::Engine> engine)
{
    //The current player ID is equal AI ID -> AI turn
    if(engine->getState().getCurrentPlayerID()==ArtificialId){
        cout << "in" <<endl;
        int action;
        while (engine->getState().getPlayerList()[ArtificialId]->getFighter()->getStatus()!=DEAD)
        {
            std::shared_ptr<Engine> copiedEngine;
            //copy engine
            cout << "in 1" <<endl;
            copyEngine(engine,copiedEngine);
            cout << "in" <<endl;
            std::vector<shared_ptr<Command>> commandList;

            /***************************************/
            /*"createNodes" function test*/
            /***************************************/
            //Init Parent Node
            std::shared_ptr<ai::DeepAiNode> ptrHeadNode(std::make_shared<DeepAiNode>());

            std::vector<std::shared_ptr<ai::DeepAiNode>> childNodesList= ptrHeadNode->getChildDeepAiNodeList();
           
                std::shared_ptr<DeepAiNode> ptrChildNode(std::make_shared<DeepAiNode>());
                ptrChildNode->setPtrParent(ptrHeadNode);
                ptrChildNode->setExecutedCommand(commandList[0]);
                childNodesList.push_back(ptrChildNode);
           
            ptrHeadNode->setChildDeepAiNodeList(childNodesList);

            /***************************************/
            /*"evalSituation" function test*/
            /***************************************/
            for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
            {
                for (uint j = 0; j < ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(); j++)
                {
                    copyEngine(engine,copiedEngine);
                    ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]->getExecutedCommand()->execute(copiedEngine->getState());
                
                    ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]->setScore(evalSituation(copiedEngine));

                }
                minimixeScore(ptrHeadNode->getChildDeepAiNodeList()[i]);
            }
            maximiseScore(ptrHeadNode);

            int optimalCommandIndex=findOptimalCommandIndex(ptrHeadNode);
            executeOptimalCommand(engine,optimalCommandIndex,ptrHeadNode);
            engine->update();
        }
    }
}

void DeepAI::copyEngine (std::shared_ptr<engine::Engine> engine,std::shared_ptr<engine::Engine> copiedEngine){
    cout << "in copyengine" <<endl;
    copiedEngine->setCurrentState(move(engine->getState()));
    cout << "setState OK" <<endl;
    copiedEngine->setCurrentCommands(move(engine->getCurrentCommands()));
    cout << "comd ok" <<endl;
    copiedEngine->setChangeRound(engine->getChangeRound());
    cout << "round ok" <<endl;
    copiedEngine->setStop(engine->getStop());
    cout << "stop ok" <<endl;
}

int DeepAI::evalSituation(std::shared_ptr<engine::Engine> copiedEngine)
{
    int score=0; 
    for(uint i=0; i<copiedEngine->getState().getPlayerList().size(); i++)
    {
        //if IA is playing
        if(i == ArtificialId)
        {
            score += copiedEngine->getState().getPlayerList()[ArtificialId]->getFighter()->getHealthPoints() + 
                    copiedEngine->getState().getPlayerList()[ArtificialId]->getFighter()->getMana();
        }else{//if IA isn't playing
            score += copiedEngine->getState().getPlayerList()[!ArtificialId]->getFighter()->getHealthPoints() + 
                    copiedEngine->getState().getPlayerList()[!ArtificialId]->getFighter()->getMana();
        }
    }    
    return score;
}


void DeepAI::maximiseScore (std::shared_ptr<DeepAiNode>& ptrEvaluatedNode){
    int actualScore=-100;
    std::vector<std::shared_ptr<DeepAiNode>> childNodes=ptrEvaluatedNode->getChildDeepAiNodeList();
    int maxScore=childNodes[0]->getScore();
    for (uint i = 0; i < childNodes.size(); i++)
    {
        actualScore=childNodes[i]->getScore();
        if(maxScore<actualScore){
            maxScore=actualScore;
        }
    }
    ptrEvaluatedNode->setScore(maxScore);
}


void DeepAI::minimixeScore (std::shared_ptr<DeepAiNode>& ptrEvaluatedNode){
    int actualScore;
    std::vector<std::shared_ptr<DeepAiNode>> childNodes=ptrEvaluatedNode->getChildDeepAiNodeList();
    int minScore=childNodes[0]->getScore();
    for (uint i = 0; i < childNodes.size(); i++)
    {
        actualScore=childNodes[i]->getScore();
        if(minScore>actualScore){
            minScore=actualScore;
        }
    }
    ptrEvaluatedNode->setScore(minScore);
}



int DeepAI::findOptimalCommandIndex (std::shared_ptr<DeepAiNode>& ptrHeadNode){
    int maxScoreIndex=0;
    int maxScore=ptrHeadNode->getChildDeepAiNodeList()[0]->getScore();
    int actualScore=ptrHeadNode->getChildDeepAiNodeList()[0]->getScore();
    for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
    {
        actualScore=ptrHeadNode->getChildDeepAiNodeList()[i]->getScore();
        if(maxScore<actualScore){
            maxScore=actualScore;
            maxScoreIndex=i;
        }
    }
    return maxScoreIndex;
}

void DeepAI::executeOptimalCommand (std::shared_ptr<engine::Engine> engine, int optimalCommandIndex, std::shared_ptr<DeepAiNode>& ptrHeadNode){
    ptrHeadNode->getChildDeepAiNodeList()[optimalCommandIndex]->getExecutedCommand()->execute(engine->getState());
}









