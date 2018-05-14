//
//  Strategy.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef Strategy_h
#define Strategy_h

#include <stdio.h>
#include "SmallWorldGame.h"

class Strategy {
protected:
    bool edgeCheck(Player* player, int indic, Map* map, Region* to);
    bool borderCheck(Player* player, Region* to);
    
public:
    virtual int pickingRace(SmallWorldGame* gm, Player* player) = 0;
    
    virtual int pickingPoEActive(SmallWorldGame* gm, Player* player) = 0;
    
    virtual int declOrConq(Player* player) = 0;
    
    virtual int pickingConqRegActive(SmallWorldGame* gm, Player* player) = 0;
    virtual void redeployActive(SmallWorldGame* gm, Player* player) = 0;
    
    //Only if in-decline race is GHOULS
    virtual int pickingConqRegPassive(SmallWorldGame* gm, Player* player) = 0;
    virtual void redeployPassive(SmallWorldGame* gm, Player* player) = 0;
};

#endif /* Strategy_h */
