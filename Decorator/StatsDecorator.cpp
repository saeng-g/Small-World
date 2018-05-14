//
//  StatsDecorator.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "StatsDecorator.h"

StatsDecorator::StatsDecorator(GameStatisticsObserver* gso) { this->gso = gso; }
void StatsDecorator::update(Subject* subject) {
    gso->update(subject);
}


Domination::Domination(GameStatisticsObserver* gso) : StatsDecorator(gso) { }
void Domination::update(Subject* subject) {
    gso->print();
    Region* r = (Region*)subject;
    int index = r->getID() - 1;
    gso->setOwned(index, r->getOwner()->getID());
    r = nullptr;
    printStats();
}

void Domination::printStats() {
    using std::cout;
    using std::endl;
    
    vector<int> counter;
    counter.resize(num_players + 1);
    
    for (int i = 0; i < owned.size(); i++) {
        counter[owned[i]] ++;
    }
    
    cout << "\nPrinting game statistic: " << endl;
    for (int i = 0; i < counter.size(); i++) {
        int reps = counter[i];
        if (i == 0) {
            cout << "UNOWNED: ";
        }
        else {
            cout << "PLAYER" << i << ": ";
        }
        for (int j = 0; j < reps; j++) {
            cout << "|";
        }
        cout << " (" << 100*counter[i]/gso->getNum_Players() << "%) " << endl;
    }
}

Hands::Hands(GameStatisticsObserver* gso) : StatsDecorator(gso) {  }
void Hands::update(Subject* subject) {
    //print GSO
    gso->print();
    
    //Print player hands
    Player* r = (Player*)subject;
    int id = r->getID();
    std::cout << "Player " << id << "'s hand:\n\tActive: " << r->getActive()->getString();
    if (r->getPassive() != nullptr) {
        std::cout << "\n\tPassive: " << r->getPassive()->getString();
    }
    if (r->getPassiveSpirit() != nullptr) {
        std::cout << "\n\tSpirit: " << r->getPassiveSpirit()->getString();
    }
    r = nullptr;
}

Coins::Coins(GameStatisticsObserver* gso) : StatsDecorator(gso) {  };
void Coins::update(Subject* subject) {
    gso->print();
    Player* r = (Player*)subject;
    int id = r->getID();
    std::cout << "Player " << id << "'s score: " << r->getCoins();
    r = nullptr;
}

DecorationManager::DecorationManager() {
    this->domination = false;
    this->hands = false;
    this->coins = false;
}

DecorationManager::~DecorationManager() { }

bool DecorationManager::getDom() { return domination; }
bool DecorationManager::getHands() { return hands; }
bool DecorationManager::getCoins() { return coins; }
void DecorationManager::setDom(bool dom) { domination = dom; }
void DecorationManager::setHands(bool hands) { this->hands = hands; }
void DecorationManager::setCoins(bool coins) { this->coins = coins; }


