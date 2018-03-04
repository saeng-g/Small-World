//
//  Combo.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef Combo_hpp
#define Combo_hpp

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
    int tokens;
    
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
    
    int getTokens();
    int getCoins();
    void resetCoins();
    void placeCoins();
    
    Race* getRace();
    Power* getPower();
};
#endif /* Combo_hpp */
