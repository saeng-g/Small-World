//
//  SmallWorldGame.hpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef SmallWorldGame_h
#define SmallWorldGame_h

#include <stdio.h>
#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include "Dice.h"
#include <iostream>

class SmallWorldGame {
    
private:
    int num_players;
    Map* map;
    vector<Player*> players;
    Deck* deck;
    Dice* dice;
    
    //Turn* turn;
    
public:
    
    //constructors & Destructor
    SmallWorldGame();
    SmallWorldGame(int num_players);
    ~SmallWorldGame();
    
    void printMap();
    void printPlayers();
    void printDeck();
    void printDice();
    
    void startGame();
    void startingCoins();
    void setDeck();
    
    //accessors & mutators
    int getNumPlayers();
    Map* getMap();
    void setMap(Map* map);
    vector<Player*> getPlayers();
    Player* getPlayer(int index);
    Deck* getDeck();
    Dice* getDice();
};

#endif /* SmallWorldGame_h */
