//
//  Player.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <vector> //std::vector
#include "Combo.h"
#include "Race.h"
#include "Power.h"
#include "Dice.h"
#include "Deck.h"
#include "Map.h"

class Player
{
private:
    int ID;
    int coins;
    Combo* active;
    Race* passive;
    Combo* passive_spirit;
    
    std::vector<Region*> owned_regions;
    std::vector<Region*> conq_regions;
    std::vector<Region*> decl_regions;
    
    static int ID_generator;

public:
    //constructor & destructor
    Player();
    ~Player();

    //Accessors & mutators
    int getID();
    
    Combo* getActive();
    void setActive(Combo* combo);
    Race* getPassive();
    void setPassive(Race* race);
    Combo* getPassiveSpirit();
    void setPassiveSpirit(Combo* power);
    int getCoins();
    void setCoins(int coins);
    
    std::vector<Region*> getOwned();
    std::vector<Region*> getConq();
    std::vector<Region*> getDecl();
    
    void decline();
    
    void picks_race(int racetype, Deck* deck);
    int conquers(Region* from, Region* to, Dice* dice); //returns 1 if diced rolled, 0 if not
    void scores();
};

#endif /* Player_h */
