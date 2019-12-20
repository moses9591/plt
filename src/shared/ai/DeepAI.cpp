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
void DeepAI::storeAttackCommands (std::shared_ptr<engine::Engine> copiedEngine, std::vector<std::shared_ptr<Command>> commandList)
{
        //Initialize the Attack constrctor with attacker and target
        AttackCommand attackCommand(copiedEngine->getState().getPlayerList()[0]->getFighter(), 
                                            copiedEngine->getState().getPlayerList()[1]->getFighter());
        unique_ptr<Command> ptr_attack (new AttackCommand(attackCommand));
        copiedEngine->addCommand(0, move(ptr_attack));   
        cout << "att is coming" <<endl;

        //convert unique_ptr into _shared_ptr
        std::shared_ptr<Command> ptr_attack_shared = std::move(ptr_attack);
        commandList.push_back(ptr_attack_shared);
        cout << "att is coming" <<endl;
}

void DeepAI::storeDefenseCommands(std::shared_ptr<engine::Engine> copiedEngine, std::vector<std::shared_ptr<Command>> commandList)                                
{
    cout << "def is coming" <<endl;
    DefenseCommand defense(copiedEngine->getState().getPlayerList()[0]->getFighter());
    cout << "def is coming" <<endl;
    unique_ptr<Command> ptr_defense (new DefenseCommand(defense));
    cout << "def is coming" <<endl;
    copiedEngine->addCommand(0, move(ptr_defense));
    cout << "def is coming" <<endl;

    //convert unique_ptr into _shared_ptr
    std::shared_ptr<Command> ptr_defense_shared = std::move(ptr_defense);
    commandList.push_back(ptr_defense_shared);
    cout << "def is coming 1" <<endl;

}

void DeepAI::storeRechargeCommands(std::shared_ptr<engine::Engine> copiedEngine,std::vector<std::shared_ptr<Command>> commandList)                                
{
    RechargeCommand recharge(copiedEngine->getState().getPlayerList()[0]->getFighter());
    unique_ptr<Command> ptr_recharge (new RechargeCommand(recharge));
    
    copiedEngine->addCommand(0, move(ptr_recharge));
    cout << "rech is coming" <<endl;
    //convert unique_ptr into _shared_ptr
    std::shared_ptr<Command> ptr_recharge_shared = std::move(ptr_recharge);
    commandList.push_back(ptr_recharge_shared);
    cout << "rech is coming" <<endl;
}

std::vector<shared_ptr<Command>> DeepAI::getCommand()
{
    int action = rand()%2;
    std::shared_ptr<engine::Engine> engine;
    std::vector<shared_ptr<Command>> commandList;
    cout << "getting cmd" <<endl;
    switch (action)
    {
    case 0:
        cout << "getting att" <<endl;
        storeAttackCommands(engine,commandList);
        break;
    case 1:
        cout << "getting def" <<endl;
        storeDefenseCommands(engine,commandList);
        break;
    case 2:
        cout << "getting rech" <<endl;
        storeRechargeCommands(engine,commandList);
        break;
    default:
        break;
    }
    return commandList;
}


void DeepAI::run(std::shared_ptr<engine::Engine> engine)
{
   
    if(engine->getState().getCurrentPlayerID()==ArtificialId){
        //cout << "in" <<endl;
        int action;
        while (engine->getState().getPlayerList()[ArtificialId]->getFighter()->getStatus()!=DEAD)
        {
            std::shared_ptr<Engine> copiedEngine;
            //copy engine
            
            copyEngine(engine,copiedEngine);

            cout << "engine copied" <<endl;
            std::vector<shared_ptr<Command>> commandList;
            commandList = getCommand();
            cout << "command init" <<endl;
           







            // std::shared_ptr<ai::DeepAiNode> ptrHeadNode(std::make_shared<DeepAiNode>());

            // std::vector<std::shared_ptr<ai::DeepAiNode>> childNodesList= ptrHeadNode->getChildDeepAiNodeList();
            // cout << "ptr" <<endl;
            //     std::shared_ptr<DeepAiNode> ptrChildNode(std::make_shared<DeepAiNode>());
            //     ptrChildNode->setPtrParent(ptrHeadNode);
            //     ptrChildNode->setExecutedCommand(commandList[0]);
            //     childNodesList.push_back(ptrChildNode);
            // cout << "ptr" <<endl;
            // ptrHeadNode->setChildDeepAiNodeList(childNodesList);
            //  cout << "ptr" <<endl;
          
            // for (uint i = 0; i < ptrHeadNode->getChildDeepAiNodeList().size(); i++)
            // {
            //     for (uint j = 0; j < ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList().size(); j++)
            //     {
            //         copyEngine(engine,copiedEngine);
            //         ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]->getExecutedCommand()->execute(copiedEngine->getState());
                
            //         ptrHeadNode->getChildDeepAiNodeList()[i]->getChildDeepAiNodeList()[j]->setScore(evalSituation(copiedEngine));

            //     }
            //     minimiseScore(ptrHeadNode->getChildDeepAiNodeList()[i]);
            // }
            // maximiseScore(ptrHeadNode);

            // int optimalCommandIndex=findOptimalCommandIndex(ptrHeadNode);
            // executeOptimalCommand(engine,optimalCommandIndex,ptrHeadNode);
            // engine->update();
        }
    }
}

void DeepAI::copyEngine (std::shared_ptr<engine::Engine> engine,std::shared_ptr<engine::Engine> copiedEngine){
    copiedEngine->setCurrentState(engine->getState());
    // cout << "in copyengine" <<endl;
    // copiedEngine->setCurrentState(move(engine->getState()));
    // cout << "setState OK" <<endl;
    // copiedEngine->setCurrentCommands(move(engine->getCurrentCommands()));
    // cout << "comd ok" <<endl;
    // copiedEngine->setChangeRound(engine->getChangeRound());
    // cout << "round ok" <<endl;
    // copiedEngine->setStop(engine->getStop());
    // cout << "stop ok" <<endl;
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


void DeepAI::minimiseScore (std::shared_ptr<DeepAiNode>& ptrEvaluatedNode){
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









