#include "../engine.h"
#include "../state.h"
#include "../ai.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace std;
using namespace ai;

//Constructor

DeepAiNode::DeepAiNode(){
    /*this->ptrParent=0;
    this->score=-1000;
    this->executedCommand=0;
    this->childDeepAiNodeList=childDeepAiNodeList;*/
}

DeepAiNode::DeepAiNode (std::shared_ptr<DeepAiNode> ptrParent, std::shared_ptr<engine::Command> executedCommand):ptrParent(ptrParent),score(-1000),executedCommand(executedCommand),childDeepAiNodeList(childDeepAiNodeList){

}


//Getters and Setters

std::shared_ptr<DeepAiNode> DeepAiNode::getPtrParent (){
    return ptrParent; 
}

std::vector<std::shared_ptr<DeepAiNode>> DeepAiNode::getChildDeepAiNodeList (){
    return childDeepAiNodeList;
}

int DeepAiNode::getScore (){
    return score;
}

std::shared_ptr<engine::Command> DeepAiNode::getExecutedCommand (){
    return executedCommand;
}

void DeepAiNode::setPtrParent (std::shared_ptr<DeepAiNode> ptrParent){
    this->ptrParent=ptrParent;
}

void DeepAiNode::setChildDeepAiNodeList (std::vector<std::shared_ptr<DeepAiNode>> childDeepAiNodeList){
    this->childDeepAiNodeList=childDeepAiNodeList;
}

void DeepAiNode::setScore (int score){
    this->score=score;
}

void DeepAiNode::setExecutedCommand (std::shared_ptr<engine::Command> executedCommand){
    this->executedCommand=executedCommand;
}


