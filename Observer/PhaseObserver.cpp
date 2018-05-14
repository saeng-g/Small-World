//
//  PhaseObserver.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "PhaseObserver.h"

PhaseObserver::PhaseObserver() {
    player_state = 0;
    turn_state = 0;
    info = "";
}

PhaseObserver::~PhaseObserver() {};


void PhaseObserver::update(Subject* subject) {   //gm for Game Master
    GameManager* gm = (GameManager*)subject;
    player_state = gm->getTurn()->getTurn();
    turn_state = gm->get_turnComponent();
    info = gm->getInfo();
    printPhase();
}

void PhaseObserver::printPhase() {
    std::cout << "Player " << player_state << ": " << converter() << " - " << info << std::endl;
}

std::string PhaseObserver::converter() { //for turn state
    if (turn_state == GameManager::PICKS_RACE) {
        return "PICKING RACE";
    }
    else if (turn_state == GameManager::CONQUERS) {
        return "CONQUERING";
    }
    else if (turn_state == GameManager::SCORES) {
        return "SCORING";
    }
    else {
        return "";
    }
}
