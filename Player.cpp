//
//  Player.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include <iostream>
#include "Player.h"

int Player::ID_generator = 0;

//constructor & destructor
Player::Player() {
    ID_generator++;
    ID = ID_generator;
    coins = 0;
    active = NULL;
    passive = NULL;
    passive_spirit = NULL;
}

Player::~Player() {}

//Accessors and Modifiers
int Player::getID() { return ID; }

Combo* Player::getActive() { return active; }
void Player::setActive(Combo* combo) { active = combo; }
Race* Player::getPassive() { return passive; }
void Player::setPassive(Race* race) { passive = race; }
Combo* Player::getPassiveSpirit() { return passive_spirit; }
void Player::setPassiveSpirit(Combo* combo) { passive_spirit = combo; }

int Player::getCoins() { return coins; }
void Player::setCoins(int coins) { this->coins = coins; }

std::vector<Region*> Player::getOwned() { return owned_regions; }
std::vector<Region*> Player::getConq() { return conq_regions; }
std::vector<Region*> Player::getDecl() { return decl_regions; }

void Player::decline() {
    if (active->getPower()->getType() == Power::SPIRIT) {
        setPassiveSpirit(active);
        active = NULL;
        
    }
    else {
        setPassive(active->getRace());
        active = NULL;
    }
}

/* inputs race indicator and deck object;
directs the race combo to the Player's attributes */

void Player::picks_race(int racetype, Deck* deck) {
    for (int i = 0; i < 6; i++) {
        if (deck->comboColumn.at(i)->getRace()->getType() == racetype) {
            deck->comboColumn.at(i)->setInColumn(false);
            deck->comboColumn.at(i)->setInPlay(true);
            deck->comboColumn.at(i)->setActive(true);
            coins = (deck->comboColumn.at(i)->getCoins());
            active = deck->comboColumn.at(i);
            break;
            }
        else {
            deck->comboColumn.at(i)->placeCoins();
            coins--;
        }
    }
}

/* conquering:
 Inputs:
 from - the region the player is moving from
 to - the region trying to conquer
 dice - dice object
 
 output:
 int - 0 if dice is NOT rolled; 1 if dice is rolled
 If 1 is returned, conquering ends for the player this turn
*/

int Player::conquers(Region* from, Region* to, Dice* dice) {
    //from and to must pass map->is_edge(from, to) before method call
    bool owned = true;
    if (to->getOwner() == nullptr) {
        owned = false;
    }
    
    int req_tok = to->getTokens() + to->getLostTribe()
    + to->getMountain() + to->getFortress() + to->getTrollsLair() + to->getNumEncampment();
    
    if (from->getTokens() >= req_tok + 2) {
        
        if (owned) {
            //remove from ex-owner's list of regions
            for (int i = 0; i < to->getOwner()->getOwned().size(); i++) {
                std::vector<Region*> temp = to->getOwner()->getOwned();
                if (temp[i] == to) {
                    temp.erase(temp.begin() + i - 1);
                    to->getOwner()->getOwned() = temp;
                    temp.~vector();
                }
            }
            //change to new owner
            to->setOwner(this);
            to->setOccupant(this->active);
            conq_regions.push_back(to); //add to owner's list
        }
        
        else {
            //change to new owner
            to->setOwner(this);
            to->setOccupant(this->active);
            owned_regions.push_back(to); //add to owner's list
        }
        return 0; //indicates dice has not been rolled; may continue conquest
    }
    
    else {
        int diceroll = dice->roll();
        if (from->getTokens() + diceroll >= req_tok + 2) {
            if (owned) {
                //remove from ex-owner's list of regions
                for (int i = 0; i < to->getOwner()->getOwned().size(); i++) {
                    std::vector<Region*> temp = to->getOwner()->getOwned();
                    if (temp[i] == to) {
                        temp.erase(temp.begin() + i - 1);
                        to->getOwner()->getOwned() = temp;
                        temp.~vector();
                    }
                }
                //change to new owner
                to->setOwner(this);
                to->setOccupant(this->active);
                to->setTokens(from->getTokens() - 1);
                conq_regions.push_back(to); //add to owner's list
            }
            
            else {
                //change to new owner
                to->setOwner(this);
                to->setOccupant(this->active);
                owned_regions.push_back(to); //add to owner's list
            }
            return 1;
        }
        else {
            return 1;
        }
    }
}

void Player::scores() {
    int coins = 0;
    
    //special case types counters
    int farmland = 0;
    int mine = 0;
    int magic = 0;
    int forest = 0;
    int swamp = 0;
    int hill = 0;
    int fortress = 0;
    int owned = (int) owned_regions.size();
    for (int i = 0; i < owned; i++) {
        if (owned_regions[i]->getType() == Region::FARMLAND
            && owned_regions[i]->getOccupant()->getRace()->getType() == Race::HUMANS) {
            farmland++;
        }
        if (owned_regions[i]->getMine() == true
            && owned_regions[i]->getOccupant()->getRace()->getType() == Race::DWARVES) {
            mine++;
        }
        if (owned_regions[i]->getMagic() == true
            && owned_regions[i]->getOccupant()->getRace()->getType() == Race::WIZARDS) {
            magic++;
        }
        if (owned_regions[i]->getType() == Region::FOREST
            && owned_regions[i]->getOccupant()->getPower()->getType() == Power::FOREST) {
            forest++;
        }
        else if (owned_regions[i]->getType() == Region::SWAMP
            && owned_regions[i]->getOccupant()->getPower()->getType() == Power::SWAMP) {
            swamp++;
        }
        else if (owned_regions[i]->getType() == Region::HILL
            && owned_regions[i]->getOccupant()->getPower()->getType() == Power::HILL) {
            hill++;
        }
        else if (owned_regions[i]->getFortress() == true
            && owned_regions[i]->getOccupant()->getPower()->getType() == Power::FORTIFIED) {
            fortress++;
        }
    }
    int conquered = (int) conq_regions.size();
    for (int i = 0; i < conquered; i++) {
        if (owned_regions[i]->getType() == Region::FARMLAND
            && owned_regions[i]->getOccupant()->getRace()->getType() == Race::HUMANS) {
            farmland++;
        }
        if (owned_regions[i]->getMine() == true
            && owned_regions[i]->getOccupant()->getRace()->getType() == Race::DWARVES) {
            mine++;
        }
        if (owned_regions[i]->getMagic() == true
            && owned_regions[i]->getOccupant()->getRace()->getType() == Race::WIZARDS) {
            magic++;
        }
        if (owned_regions[i]->getType() == Region::FOREST
            && owned_regions[i]->getOccupant()->getPower()->getType() == Power::FOREST) {
            forest++;
        }
        else if (owned_regions[i]->getType() == Region::SWAMP
                 && owned_regions[i]->getOccupant()->getPower()->getType() == Power::SWAMP) {
            swamp++;
        }
        else if (owned_regions[i]->getType() == Region::HILL
                 && owned_regions[i]->getOccupant()->getPower()->getType() == Power::HILL) {
            hill++;
        }
        else if (owned_regions[i]->getFortress() == true
                 && owned_regions[i]->getOccupant()->getPower()->getType() == Power::FORTIFIED) {
            fortress++;
        }
        owned_regions.push_back(conq_regions[i]);
        conq_regions.erase(conq_regions.begin() + i - 1);
    }
    
    //special cases: conquered & owned
    if (active->getRace()->getType() == Race::ORCS) {
        coins += conquered;
    }
    if (active->getPower()->getType() == Power::PILLAGING) {
        coins += conquered;
    }
    else if (active->getPower()->getType() == Power::MERCHANT) {
        coins += owned + conquered;
    }
    coins += owned + conquered;
    coins += farmland + mine + magic + forest + swamp + hill + fortress;
    
    this->coins += coins;
}
