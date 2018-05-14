//
//  Turn.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Turn.h"

//Constructors & Destructors
Turn::Turn() {
    this->num_players = 0;
    this->round = 0;
    this->maxRound = 0;
    this->turn = 0;
    this->turnCount = 0;
    this->end_turn = false;
}

Turn::Turn(int num_players) {
    this->num_players = num_players;
    this->round = 1;
    
    //set maxRound
    if (num_players == 2)
        maxRound = MAXROUND_2;
    else if (num_players == 3)
        maxRound = MAXROUND_3;
    else if (num_players == 4)
        maxRound = MAXROUND_4;
    else if (num_players == 5)
        maxRound = MAXROUND_5;
    else {
        //error
        std::cout << "error@ Turn object constructor" << std::endl;
        maxRound = -1;
    }
    
    //determine order
    this->order.push(rand() % num_players + 1);
    for (int i = order.front() + 1; i <= num_players; i++) {
        order.push(i);
    }
    for (int i = 1; i < order.front(); i++) {
        order.push(i);
    }
    this->turn = order.front();
    this->turnCount = 0;
}

Turn::~Turn() { }

//acessors and modifiers
int Turn::getRound() { return round; }
void Turn::nextRound() { round++; }
bool Turn::isEndGame() { return round > maxRound; }

int Turn::getTurn() { return turn; }
void Turn::nextTurn() {
    if (order.size() != 0) {
        order.push(order.front());
        order.pop();
        turn = order.front();
        turnCount++;
    }
    if (turnCount == num_players) {
        nextRound();
        turnCount = 0;
    }
}
bool Turn::isEndTurn() { return end_turn; }


//printing
void Turn::printOrder() {
    std::cout << "Here is the turn order: " << std::endl;
    for (int i = 0; i < order.size(); i++) {
        std::cout << "Player " << order.front() << "\n";
        order.push(order.front());
        order.pop();
    }
}

void Turn::printTurn() {
    std::cout << "Current Round: " << round << std::endl;
    std::cout << "Current turn: Player " << turn << std::endl;
}

//inherited virtual def
void Turn::attach(Observer* o) { this->Subject::attach(o); }
void Turn::detach(Observer* o) { this->Subject::detach(o); }
void Turn::notify() { this->Subject::notify(); }

