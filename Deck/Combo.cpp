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
    total_tokens = 0;
}
Combo::Combo(Race &race, Power &power) {
    this->race = &race;
    this->power = &power;
    total_tokens = sumTokens();
    offensive_tokens = total_tokens;
    defensive_tokens = 0;
    in_Column = true;
    in_Play = false;
    active = false;
    coins = 0;
}

int Combo::sumTokens() { return race->getToken() + power->getToken(); }

bool Combo::getInColumn() { return in_Column; }
void Combo::setInColumn(bool status) { in_Column = status;}

bool Combo::getInPlay() { return in_Play; }
void Combo::setInPlay(bool status) { in_Play = status; }

bool Combo::getActive() { return active; }
void Combo::setActive(bool status) { active = status; }

int Combo::getTotalTokens() { return total_tokens; }
void Combo::removeOneTotalToken() { this->total_tokens--; }
int Combo::getOffensiveTok() { return offensive_tokens; }
void Combo::setOffensiveTok(int num_tok) { this->offensive_tokens = num_tok; }
int Combo::getRedeployable() { return redeployable_tokens; }
void Combo::setRedeployable(int num_tok) { this->redeployable_tokens = num_tok; }
int Combo::getDefensiveTok() { return defensive_tokens; }
void Combo::setDefensiveTok(int num_tok) { this->defensive_tokens = num_tok; }
int Combo::getCoins() { return coins; }
void Combo::resetCoins() { coins = 0; }
void Combo::placeCoins() { coins++; }

Race* Combo::getRace() { return race; }
void Combo::setRaceNull() { race = nullptr; }
Power* Combo::getPower() { return power; }
void Combo::setPowerNull() { power = nullptr; }

std::string Combo::getString() {
    std::string power_str = "";
    std::string race_str = "";
    if (power != nullptr)
        power_str = power->getString();
    if (race != nullptr)
        race_str = race->getString();
    return power_str + " " + race_str;
}

std::string Combo::getString(int coins_indic) {
    return this->getString() + "(coins: " + std::to_string(coins) + ")";
}
