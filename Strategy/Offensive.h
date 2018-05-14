//
//  Offensive.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef Offensive_h
#define Offensive_h

#include <stdio.h>
#include "Strategy.h"

class Offensive: public Strategy {
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

#endif /* Offensive_h */
