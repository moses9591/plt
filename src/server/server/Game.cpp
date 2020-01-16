#include "../server.h"
#include <memory>
#include <map>
#include <vector>
#include <set>

using namespace server;
using namespace std;
using std::unique_ptr;
using std::map;
using std::vector;


// Constructor

Game::Game():idseq(1){   
}

// Functions

std::map<int, std::shared_ptr<Player>>& Game::getPlayersList(){
	std::map<int, std::shared_ptr<Player>>& ref=playersList;
	return ref;
}

Player* Game::getPlayer (int id) {
    auto ite = playersList.find(id);
    if (ite == playersList.cend())
        return nullptr;
    return ite->second.get();
}

int Game::addPlayer (std::shared_ptr<Player> player) {
    int id = idseq++;
    playersList.insert(std::make_pair(id, std::move(player)));
    return id;
}

void Game::setPlayer (int id, std::shared_ptr<Player> player) {
    playersList[id] = std::move(player);
    if (id > idseq) {
        idseq = id;
    }
}

void Game::removePlayer (int id) {
    auto ite = playersList.find(id);
    if (ite == playersList.end())
        return;
    playersList.erase(ite);
}

int Game::getIDseq(){
	return idseq;
}