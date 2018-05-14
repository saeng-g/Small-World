//
//  Region.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef REGION_H
#define REGION_H

#include <stdio.h>
#include <iostream>
#include "Combo.h"
#include "Subject.h"

class Player; //uses a pointer to this object

class Region : public Subject
{
private:
    int ID;
    int type;
    int num_tokens; //number of token player has on the region
    bool occupied;
    Combo* occupant;
    Player* owner;
    
    //extra token indicator
    bool mountain;
    bool lost_tribe;
    bool fortress;
    bool trolls_lair;
    bool encampment;
    
    //token related int
    int num_encampment;
    
    //Hole-in-the-ground, Hero, dragon
    bool hole;
    bool hero;
    bool dragon;
    
    //special regional characteristics indicator
    bool by_border;
    bool mine;
    bool magic;
    bool cavern;
    bool beside_mt;
    bool coastal;
    
public:
    //numerification of region types
    static const int SEA = 0;
    static const int LAKE = 1;
    static const int HILL = 2;
    static const int FARMLAND = 3;
    static const int SWAMP = 4;
    static const int FOREST = 5;
    static const int MOUNTAIN = 6;
    
    //constructors and deconstructors
    Region();
    Region(int ID, int type);
    ~Region() {};
    
    //Accessors & Modifiers
    int getID();
    
    int getType();
    void setType(int type);
    int getTokens();
    void setTokens(int tokens);
    bool getOccupied();
    void setOccupied(bool occupied);
    Combo* getOccupant();
    void setOccupant(Combo* combo);
    Player* getOwner();
    void setOwner(Player* player);
    
    bool getMountain();
    void setMountain(bool mountain);
    bool getLostTribe();
    void setLostTribe(bool lost_tribe);
    bool getFortress();
    void placeFortress();
    void removeFortress();
    bool getTrollsLair();
    void setTrollsLair(bool trolls);
    bool getEncampment();
    void setEncampment(bool encampment);
    int getNumEncampment();
    void setNumEncampment(int num);
    
    bool getHole();
    void setHole(bool hole);
    bool getHero();
    void setHero(bool hero);
    bool getDragon();
    void setDragon(bool dragon);
    
    bool getIsBorder();
    void setIsBorder(bool by_border);
    bool getMine();
    void setMine(bool mine);
    bool getMagic();
    void setMagic(bool magic);
    bool getCavern();
    void setCavern(bool cavern);
    bool getBesideMt();
    void setBesideMt(bool beside_mt);
    bool getCoastal();
    void setCoastal(bool coastal);
    
    void getRegionInfo(); //prints region info on screen
    void getOwnerInfo(); //prints info about the owner/occupant of the region
    std::string toTypeStr(); //converts numeric type to string type
    
    //virtual from Subject
    void attach(Observer* o);
    void detach(Observer* o);
    void notify();
};

#endif /* REGION_H */
