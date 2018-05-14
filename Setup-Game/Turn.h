//
//  Turn.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef Turn_h
#define Turn_h

#include <stdio.h>
#include <queue>
#include <vector>
#include "Subject.h"

class Turn : public Subject {
private:
    int num_players;
    int round;          //what round it is
    int maxRound;       //maximum number of rounds
    int turn;           //who's turn it is
    int turnCount;
    bool end_turn;
    std::queue<int> order;                  //set of orders that cycle with every turn
    
public:
    static const int MAXROUND_2 = 10;
    static const int MAXROUND_3 = 10;
    static const int MAXROUND_4 = 9;
    static const int MAXROUND_5 = 8;
    
    //constructor & destructor
    Turn();
    Turn(int num_players);
    ~Turn();
    
    //accessors & modifiers
    int getRound();
    void nextRound();
    bool isEndGame();
    int getTurn();
    void nextTurn();
    bool isEndTurn();
    
    //display
    void printTurn();
    void printOrder();
    
    void attach(Observer* o);
    void detach(Observer* o);
    void notify();
};

#endif /* Turn_h */
