//
//  GameStatisticsObserver.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "GameStatisticsObserver.h"

GameStatisticsObserver::GameStatisticsObserver() {
    this->num_players = 0;
    this->num_regions = 0;
    owned.resize(num_regions);
}
GameStatisticsObserver::GameStatisticsObserver(int num_players, int num_regions) {
    this->round = 0;
    this->num_players = num_players;
    this->num_regions = num_regions;
    owned.resize(num_regions);
    for (int i = 0; i < num_regions; i++) {
        owned[i] = 0;
    }
}
GameStatisticsObserver::~GameStatisticsObserver() {}

void GameStatisticsObserver::update(Subject* subject) {
    Turn* r = (Turn*)subject;
    int round = r->getRound();
    this->round = round;
    print();
}

int GameStatisticsObserver::getOwned(int index) {
    return this->owned[index];
}

void GameStatisticsObserver::setOwned(int index, int value) {
    this->owned[index] = value;
}

int GameStatisticsObserver::getNum_Players() {
    return this->num_players;
}

void GameStatisticsObserver::print() {
    std::cout << "ROUND " << round << ": " << std::endl;
}
