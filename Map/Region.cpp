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
    occupant = nullptr;
    owner = nullptr;
    
    mountain = false;
    lost_tribe = false;
    fortress = false;
    trolls_lair = false;
    encampment = false;
    
    num_encampment = 0;
    
    hole = false;
    hero = false;
    dragon = false;
    
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
    occupant = nullptr;
    owner = nullptr;
    
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
    
    num_encampment = 0;
    
    hole = false;
    hero = false;
    dragon = false;
    
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
void Region::setOwner(Player* player) { owner = player; notify(); }

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

bool Region::getHole() { return hole; }
void Region::setHole(bool hole) { this->hole = hole; }
bool Region::getHero() { return hero; }
void Region::setHero(bool hero) { this->hero = hero; }
bool Region::getDragon() { return dragon; }
void Region::setDragon(bool dragon) { this->dragon = dragon; }

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

void Region::getRegionInfo() {
    using std::string;
    using std::cout;
    using std::endl;
    
    string type_str = this->toTypeStr();
    string mmc = ""; //mine, magic, cavern indicator
    if (mine)
        mmc.append("m");
    else
        mmc.append(" ");
    if (magic)
        mmc.append("g");
    else
        mmc.append(" ");
    if (cavern)
        mmc.append("c");
    else
        mmc.append(" ");
    
    cout << ID << "\t" << type_str << "\t" << mmc << "\t\t";
}

void Region::getOwnerInfo() {
    using std::string;
    using std::cout;
    using std::endl;
    
    string hod = "";
    
    if (hole)
        hod.append("h");
    else
        hod.append(" ");
    if (hero)
        hod.append("o");
    else
        hod.append(" ");
    if (dragon)
        hod.append("d");
    else
        hod.append(" ");
    
    string fe = "";
    if (fortress)
        fe.append("f");
    else
        fe.append(" ");
    string encStr =std::to_string(num_encampment);
    fe.append("e(" + encStr + ")");
    
    if (owner == nullptr) {
        cout << "UNKNOWN      OCCUPANT    -\tTok: " << num_tokens << "\t" << hod << "\t" << fe;
    }
    else {
        cout << getOccupant()->getString() << "\tTokens: " << num_tokens << "\t" << hod << "\t" << fe;
    }
}

std::string Region::toTypeStr() {
    using std::string;
    string type_str = "";
    if (type == 0) {
        type_str = "Sea     ";
    }
    else if (type == 1) {
        type_str = "Lake    ";
    }
    else if (type == 2) {
        type_str = "Hill    ";
    }
    else if (type == 3) {
        type_str = "Farmland";
    }
    else if (type == 4) {
        type_str = "Swamp   ";
    }
    else if (type == 5) {
        type_str = "Forest  ";
    }
    else if (type == 6) {
        type_str = "Mountain";
    }
    else { //Improper region type error
        type_str = "@@@@@@@@";
    }
    return type_str;
}

//virtual redefinition
void Region::attach(Observer* o) { this->Subject::attach(o); }

void Region::detach(Observer* o) { this->Subject::detach(o); }

void Region::notify() { this->Subject::notify(); }



