//
//  Combo.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include "Combo.h"
#include "Race.h"
#include "Power.h"

Combo::Combo() {
    this->race = NULL;
    this->power = NULL;
    in_Column = true;
    in_Play = false;
    active = false;
    coins = 0;
    tokens = 0;
}
Combo::Combo(Race &race, Power &power) {
    this->race = &race;
    this->power = &power;
    tokens = sumTokens();
    in_Column = true;
    in_Play = false;
    active = false;
    coins = 0;
}

int Combo::sumTokens() {
    return race->getToken() + power->getToken();
}

bool Combo::getInColumn() {
    return in_Column;
}
void Combo::setInColumn(bool status) {
    in_Column = status;
}

bool Combo::getInPlay() {
    return in_Play;
}
void Combo::setInPlay(bool status) {
    in_Play = status;
}

bool Combo::getActive() {
    return active;
}
void Combo::setActive(bool status) {
    active = status;
}

int Combo::getTokens() {
    return tokens;
}
int Combo::getCoins() {
    return coins;
}
void Combo::resetCoins() {
    coins = 0;
}
void Combo::placeCoins() {
    coins++;
}

Race* Combo::getRace() {
    return race;
}
Power* Combo::getPower() {
    return power;
}
