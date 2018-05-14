//
//  GameManager.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-31.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "GameManager.h"

//virtual redefinition
void GameManager::attach(Observer* o) {
    this->Subject::attach(o);
}

void GameManager::detach(Observer* o) {
    this->Subject::detach(o);
}

void GameManager::notify() {
    this->Subject::notify();
}

//constructors & destructors
GameManager::GameManager() {
    turn = nullptr;
    game = nullptr;
    turn_component = 0;
    component_info = "";
    stopDecor = false;
}
GameManager::GameManager(Turn* turn, SmallWorldGame* game) {
    this->turn = turn;
    this->game = game;
    gsos.push_back(new GameStatisticsObserver(game->getNumPlayers(), game->getMap()->get_num_v()));
    turn->attach(gsos[0]);
    decorManager = new DecorationManager();
    turn_component = 0;
    component_info = "";
    pManagers.resize(game->getNumPlayers());
    stopDecor = false;
}
GameManager::~GameManager() {
    delete turn;
    delete game;
    turn = nullptr;
    game = nullptr;
};

//helper
int GameManager::calculateVictor() {
    int maxCoins = 0;
    int player = 0;
    for (int i = 0; i < game->getNumPlayers(); i++) {
        if (game->getPlayer(i)->getCoins() > maxCoins) {
            maxCoins = game->getPlayer(i)->getCoins();
            player = i + 1;
        }
    }
    return player;
}

//private helper methods
//FIRST TURN
void GameManager::first_turn() {
    
    Player* player = game->getPlayer(turn->getTurn() - 1);
    askStrat(player);
    PlayerManager* pm = pManagers[player->getID() - 1];
    
    //PICKING A RACE
    
    int position = pm->execPickRace();
    turn_component = PICKS_RACE;            //NEW PHASE: notify observer
    component_info = "Picked position: ";
    component_info.append(std::to_string(position));
    notify();
    
    //CONQUERING (First Turn)
    
    int entry = pm->execEntry();
    turn_component = CONQUERS;              //NEW PHASE: notify observer
    component_info = "Number of regions conquered: ";
    component_info.append(std::to_string(entry));
    notify();
    
    //REDEPLOYMENT:
    
    pm->execRedepActive();
    
    //SCORING
    turn_component = SCORES;                    //NEW PHASE: notify observers
    int score = pm->execScore();
    component_info = "";
    component_info.append(std::to_string(score));
    notify();
    
    turn->nextTurn();
};

void GameManager::following_turn() {
    
    Player* player = game->getPlayer(turn->getTurn() - 1);
    PlayerManager* pm = pManagers[player->getID() - 1];
    /*
     
     Following Turns :
     
     0) If passive == GHOULS, conquer as ghouls
     1) Decide if conquer or decline
     2) If conquer, ready -> conquer -> redeploy
     4) if Decline, decline -> pick new active
     6) Score
     
     NOTE: if passive is GHOULS, allow passive to conquer
     
     */
    
    //if PassiveRace == GHOULS:
    
    int passiveConq = pm->execConqPassive();
    pm->execRedepPassive();
    turn_component = CONQUERS;            //NEW PHASE: notify observer
    component_info = "Passively Conquered Region: ";
    component_info.append(std::to_string(passiveConq));
    notify();
    
    //CONQUER or DECLINE
    int decline = pm->execDecline();
    turn_component = DECLINE;            //NEW PHASE: notify observer
    component_info = "Decline: ";
    
    if (decline == 0) {
        component_info.append("YES");
        notify();
        
        int position = pm->execPickRace();
        turn_component = PICKS_RACE;            //NEW PHASE: notify observer
        component_info = "Picked position: ";
        component_info.append(std::to_string(position));
        notify();
    }
    else {
        int activeConq = pm->execConqActive();
        pm->execRedepActive();
        turn_component = CONQUERS;            //NEW PHASE: notify observer
        component_info = "Number of regions conquered: ";
        component_info.append(std::to_string(activeConq));
        notify();
    }
    
    //SCORING
    turn_component = SCORES;                    //NEW PHASE: notify observers
    int score = pm->execScore();
    component_info = "";
    component_info.append(std::to_string(score));
    notify();
    
    turn->nextTurn();
}

void GameManager::main_loop() {
    if (!stopDecor) {
        askDecorator();
    }
    if (turn->getRound() == 1) {
        first_turn();
    }
    else {
        while (!turn->isEndGame()) {
            following_turn();
        }
        int playerID = calculateVictor();
        std::cout << "player " << playerID << " won!" << std::endl;
    }
}

void GameManager::askStrat(Player* player) {
    int id = player->getID();
    std::string response = "";
    bool properInput = false;
    while (!properInput) {
        std::cout << "choose strat for player " << id << " (o/d):" << std::endl;
        std::cin >> response;
        if (response == "o") {
            pManagers[id - 1] = new PlayerManager(player, game, new Offensive());
            properInput = true;
        }
        else if (response == "d") {
            pManagers[id - 1] = new PlayerManager(player, game, new Defensive());
            properInput = true;
        }
        else {
            std::cout << "you must choose o or d" << std::endl;
        }
    }
}


void GameManager::askDecorator() {
    int response = 0;
    bool properInput = false;
    while (!properInput) {
        try {
            std::cout << "add decorator? (0 for no, 2 for domination, 3 for hands, 4 for coins)" << std::endl;
            std::cin >> response;
            if (response == 0) {
                throw 0;
            }
            else if ( (response == 2) && !(decorManager->getDom()) ) {
                throw 2;
            }
            else if ( (response == 3) && !(decorManager->getHands()) ) {
                throw 3;
            }
            else if ( (response == 4) && !(decorManager->getCoins()) ) {
                throw 4;
            }
            else {
                std::cout << "ImproperInput" << std::endl;
            }
        }
        catch (int i) {
            properInput = true;
            if (i == 0) {
                stopDecor = true;
            }
            else if (i == 2) {
                decorManager->setDom(true);
                gsos.push_back( new Domination( gsos.back() ) );
                for (int i = 0; i < game->getMap()->get_num_v(); i++) {
                    game->getMap()->getRegion(i + 1)->attach( gsos.back() );
                }
            }
            else if (i == 3) {
                decorManager->setHands(true);
                gsos.push_back( new Hands(gsos.back()) );
                for (int i = 0; i < game->getNumPlayers(); i++) {
                    game->getPlayer(i)->attach( gsos.back() );
                }
            }
            else if (i == 4) {
                decorManager->setCoins(true);
                gsos.push_back( new Coins(gsos.back()) );
                for (int i = 0; i < game->getNumPlayers(); i++) {
                    game->getPlayer(i)->attach( gsos.back() );
                }
            }
        }
    }
}

//accessors & modifiers
Turn* GameManager::getTurn() { return turn; }
SmallWorldGame* GameManager::getGame() { return game; }
int GameManager::get_turnComponent() { return turn_component; }
std::string GameManager::getInfo() { return component_info; }
