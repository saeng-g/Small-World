//
//  Defensive.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef Defensive_h
#define Defensive_h

#include <stdio.h>
#include "Strategy.h"

class Defensive: public Strategy {
public:
    int pickingRace(SmallWorldGame* gm, Player* player);
    
    int pickingPoEActive(SmallWorldGame* gm, Player* player);
    
    int declOrConq(Player* player);
    
    int pickingConqRegActive(SmallWorldGame* gm, Player* player);
    void redeployActive(SmallWorldGame* gm, Player* player);
    
    //Only if in-decline race is GHOULS
    int pickingConqRegPassive(SmallWorldGame* gm, Player* player);
    void redeployPassive(SmallWorldGame* gm, Player* player);
};
#endif /* Defensive_h */
