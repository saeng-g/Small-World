//
//  Deck.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-08.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include <iostream>
#include "Deck.h"
#include "Race.h"
#include "Power.h"
#include <cstdlib>

using std::vector;

Deck::Deck() {
    for (int i = 0; i < 14; i++) {
        races.push_back(new Race (i+ 1));
    }
    for (int i = 0; i < 20; i++) {
        powers.push_back(new Power (i + 1));
    }
    start();
}

void Deck::start() {
    shuffleRace();
    shufflePowers();
    for (int i = 0; i < 6; i++) {
        comboColumn.push_back(new Combo(*races.front(), *powers.front()));
        races.erase(races.begin());
        powers.erase(powers.begin());
    }
}

void Deck::refill() {
    if (races.front() != nullptr && powers.front() != nullptr) {
        comboColumn.push_back(new Combo(*races.front(), *powers.front()));
        races.erase(races.begin());
        powers.erase(powers.begin());
    }
}

void Deck::remove(int index) {
    comboColumn.erase(comboColumn.begin() + index);
}

void Deck::restock(Combo* combo) {
    races.push_back(combo->getRace());
    powers.push_back(combo->getPower());
    combo->setRaceNull();
    combo->setPowerNull();
    
    delete combo;
    combo = nullptr;
}

void Deck::restock(Race* race) {
    races.push_back(race);
}

void Deck::restock(Power* power) {
    powers.push_back(power);
}

void Deck::shuffleRace() {
    for (int i = 0; i < races.size(); i++) {
        int swapIndex = rand() % races.size();
        Race* temp = races.at(i);
        races.at(i) = races.at(swapIndex);
        races.at(swapIndex) = temp;
        temp = NULL;
        delete temp;
    }
}

void Deck::shufflePowers() {
    for (int i = 0; i < powers.size(); i++) {
        int swapIndex = rand() % races.size();
        Power* temp = powers.at(i);
        powers.at(i) = powers.at(swapIndex);
        powers.at(swapIndex) = temp;
        temp = NULL;
        delete temp;
    }
}
