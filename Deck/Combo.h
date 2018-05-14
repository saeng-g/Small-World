//
//  Combo.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef COMBO_H
#define COMBO_H

#include <stdio.h>
#include "Race.h"
#include "Power.h"

class Combo
{
private:
    bool in_Column;
    bool in_Play;
    bool active;
    
    int coins;
    int total_tokens;
    int offensive_tokens;
    int redeployable_tokens;
    int defensive_tokens;
    
    Race* race;
    Power* power;
    
    int sumTokens();

public:
    Combo();
    Combo(Race &race, Power &power);
    
    ~Combo() {};
    
    bool getInDeck();
    void setInDeck(bool status);
    bool getInColumn();
    void setInColumn(bool status);
    bool getInPlay();
    void setInPlay(bool status);
    bool getActive();
    void setActive(bool status);
    
    int getTotalTokens();
    void removeOneTotalToken();
    int getOffensiveTok();
    void setOffensiveTok(int tokens);
    int getRedeployable();
    void setRedeployable(int tokens);
    int getDefensiveTok();
    void setDefensiveTok(int tokens);
    int getCoins();
    void resetCoins();
    void placeCoins();
    
    Race* getRace();
    void setRaceNull();
    Power* getPower();
    void setPowerNull();
    std::string getString();
    std::string getString(int coin_indic);
};
#endif /* COMBO_H */
