//
//  SmallWorldGame.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "SmallWorldGame.h"


SmallWorldGame::SmallWorldGame() { 
    num_players = 0;
    map = NULL;
    deck = NULL;
    dice = NULL;
}

SmallWorldGame::SmallWorldGame(int num_players) {
    this->num_players = num_players;
    map = NULL;
    players.resize(num_players);
    for (int i = 0; i < num_players; i++) {
        players[i] = new Player();
    }
    deck = NULL;
    dice = NULL;
}

SmallWorldGame::~SmallWorldGame() {
    delete map;
    delete deck;
    delete dice;
}

void SmallWorldGame::printMap() {
    map->printMap();
}

void SmallWorldGame::printPlayers() {
    for (int i = 0; i < num_players; i++) {
        players[i]->printInfo();
    }
}

void SmallWorldGame::printDeck() {
    std::cout << "Here are the combos in the deck:" << std::endl;
    for (int i = 0; i < 6; i++) {
        if (deck->comboColumn[i] != nullptr) {
            std::cout << i + 1 << ": " << deck->comboColumn[i]->getString(4) << std::endl;
        }
        else {
            std::cout << i + 1 << ": " << std::endl;
        }
    }
    std::cout << std::endl; //separator line for visual clarity
}

//accessors and mutators
int SmallWorldGame::getNumPlayers() { return num_players; }
Map* SmallWorldGame::getMap() { return map; }
void SmallWorldGame::setMap(Map* map) { this->map = map; }
vector<Player*> SmallWorldGame::getPlayers() { return players; }
Player* SmallWorldGame::getPlayer(int index) { return players[index]; }
Deck* SmallWorldGame::getDeck() { return deck; }
Dice* SmallWorldGame::getDice() { return dice; }

void SmallWorldGame::startGame() {
    if(num_players >= 2 && num_players <= 5) {
        this->deck = new Deck();
        this->dice = new Dice();
        startingCoins();
    }
    for (int i = 0; i < map->get_num_v(); i++) {
        if (map->getRegion(i+1)->getLostTribe()) {
            map->getRegion(i+1)->setTokens(1);
        }
    }
}
void SmallWorldGame::startingCoins() { 
    for (int i = 0; i < num_players; i++) {
        players[i]->setCoins(5);
    }
}

