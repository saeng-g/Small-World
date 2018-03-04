//
//  Region.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include "Region.h"

//default constructor
Region::Region() {
    ID = 0;
    type = 0;
    num_tokens = 0;
    occupied = false;
    occupant = NULL;
    owner = NULL;
    
    mountain = false;
    lost_tribe = false;
    fortress = false;
    trolls_lair = false;
    encampment = false;
    
    mine = false;
    magic = false;
    cavern = false;
    beside_mt = false;
    coastal = false;
}

//(ID, type) constructor
Region::Region(int ID, int type) {
    this->ID = ID;
    this->type = type;
    num_tokens = 0;
    occupied = false;
    occupant = NULL;
    owner = NULL;
    
    if (type == MOUNTAIN) {
        mountain = true;
    }
    else {
        mountain = false;
    }
    
    lost_tribe = false;
    fortress = false;
    trolls_lair = false;
    encampment = false;
    
    mine = false;
    magic = false;
    cavern = false;
    beside_mt = false;
    coastal = false;
}

//Accessors & Modifiers
int Region::getID() { return this->ID; }

int Region::getType() { return type; }
void Region::setType(int type) { this->type = type; }
int Region::getTokens() { return num_tokens; }
void Region::setTokens(int tokens) { this->num_tokens = tokens; }
bool Region::getOccupied() { return occupied; }
void Region::setOccupied(bool occupied) { this->occupied = occupied; }
Combo* Region::getOccupant() { return occupant; }
void Region::setOccupant(Combo* combo) { this->occupant = combo; }
Player* Region::getOwner() { return owner; }
void Region::setOwner(Player* player) { owner = player; }

bool Region::getMountain() { return mountain; }
void Region::setMountain(bool mountain) { this->mountain = mountain; }
bool Region::getLostTribe() { return lost_tribe; }
void Region::setLostTribe(bool lost_tribe) { this->lost_tribe = lost_tribe; }
bool Region::getFortress() { return fortress; }
void Region::placeFortress() { fortress = true; }
void Region::removeFortress() { fortress = false; }
bool Region::getTrollsLair() { return trolls_lair; }
void Region::setTrollsLair(bool trolls) { trolls_lair = trolls; }
bool Region::getEncampment() { return encampment; }
void Region::setEncampment(bool encampment) { this->encampment = encampment; }
int Region::getNumEncampment() { return num_encampment; }
void Region::setNumEncampment(int num) { num_encampment = num; }

bool Region::getIsBorder() { return by_border; }
void Region::setIsBorder(bool by_border) { this->by_border = by_border; }
bool Region::getMine() { return mine; }
void Region::setMine(bool mine) { this->mine = mine; }
bool Region::getMagic() { return magic; }
void Region::setMagic(bool magic) { this->magic = magic; }
bool Region::getCavern() { return cavern; }
void Region::setCavern(bool cavern) { this->cavern = cavern; }
bool Region::getBesideMt() { return beside_mt; }
void Region::setBesideMt(bool beside_mt) { this->beside_mt = beside_mt; }
bool Region::getCoastal() { return coastal; }
void Region::setCoastal(bool coastal) { this->coastal = coastal; }

