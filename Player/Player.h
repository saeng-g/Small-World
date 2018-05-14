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

class Player : public Subject
{
private:
    int ID;
    int coins;
    int ally; //if the power is Diplomat, the player can choose an ally each turn (if
    Combo* active;
    Combo* passive;
    Combo* passive_spirit; //if the power is spirit, combo can stay as an extra decline race
    
    int num_conq; //number of non-empty land conquered each turn
    int num_conq_passive; //number of non_empty land conquered by passive each turn (only if passive is GHOUL)
    
    std::vector<Region*> active_regions;
    std::vector<Region*> passive_regions;
    std::vector<Region*> spirit_regions;
    
    static int ID_generator;

public:
    //constructor & destructor
    Player();
    ~Player();

    //Accessors & mutators
    int getID();
    
    int getAlly();
    void setAlly(int id);
    
    Combo* getActive();
    void setActive(Combo* combo);
    Combo* getPassive();
    void setPassive(Combo* race);
    Combo* getPassiveSpirit();
    void setPassiveSpirit(Combo* power);
    int getCoins();
    void setCoins(int coins);
    
    std::vector<Region*> getActiveReg();
    std::vector<Region*> getPassiveReg();
    std::vector<Region*> getSpiritReg();
    
    void decline(Deck* deck);
    
    void picks_race(int position, Deck* deck);
    int conquers(Combo* combo, Region* to, int req_tok);
    int scores();
    
    /*
     
     helper methods for conquers():
     getOccupantIndic()
        - returns indicator of whether the land was owned by active, passive combo, or spirit
     eraseOwner(int indic)
        - removes region from the set of regions owned by player's occupant (indicated by indic)
        - employs eraseOwnerTokens
     eraseOwnerTokens
        - removes tokens from the region and adjusts the previous Occupant's token attributes
        - helper for eraseOwner()
     newOwner()
        - change owner to player
     
     */
    
    int getOccupantIndic(Region* to);
    int getOccupantSize(int indic, Region* to);
    void eraseOwner(int indic, int size, Region* to);
    void eraseOwnerTokens(Combo* combo, int redeployable);
    void newOwner(Combo* combo, int conq_tok, Region* to);
    
    /*
     
     Additional methods for conquering:
     conquerable_Type() checks if the region type is conquerable:
        - Is the region an ocean? Is the combo seafaring?
     conquerable_Cond() checks if the region conditions are conquerable:
        - Does the region have a hole-in-the-ground?
        - Is the region occupied by a hero / dragon?
     conquerable_Tok() checks if there is enough region:
        ^ returns number of tokens required to conquer
        - Are there token replacements? (encampments, fortress, troll's lair, etc.)
        - Are you strong / weak against the terrain? (Mountain, Coastal, etc.)
     
     !!These methods should be run to check validity prior to implementing the conquers() method!!
     
     */
    
    bool conquerable_Type(Combo* combo, Region* to);
    bool conquerable_Cond(Combo* combo, Region* to);
    int conquerable_Tok(Combo* combo, Region* to);
    
    //redeployment:
    void collectTokens(int indic);
    void readyConquest(int indic);
    void redeploy(Combo* combo, int num_tokens, Region* to);
    bool redepCheck(int indic, int num_tokens, Region* to);
    
    /*
     
     scoring helper methods:
     active score
     passive score
     spirit score
     race score
     power score
     
     */
    
    int active_score(int active_sz);
    int passive_score(int passive_sz);
    int spirit_score(int spirit_sz);
    int race_score(bool active, int race, Region* region);
    int power_score(int power, Region* region);
    
    
    //printing
    void printInfo();
    void printActiveReg();
    void printPassiveReg();
    
    //inherited Subject
    void attach(Observer* o);
    void detach(Observer* o);
    void notify();
};

#endif /* Player_h */
