//
//  PlayerManager.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef PlayerManager_h
#define PlayerManager_h

#include <stdio.h>
#include "Strategy.h"
#include "SmallWorldGame.h"

class PlayerManager {
private:
    Player* player;
    SmallWorldGame* game;
    Strategy* strategy;
    
public:
    //constructor & destructor
    PlayerManager();
    PlayerManager(Player* player, SmallWorldGame* game, Strategy* initStrat);
    ~PlayerManager();
    
    //setStrat
    void setStrat(Strategy* strat);
    
    //executeStrat
    int execEntry();
    int execPickRace();
    int execConqActive();
    int execConqPassive();
    int execDecline();
    void execRedepActive();
    void execRedepPassive();
    void execRedepOffTurn();
    int execScore();
    
};

#endif /* PlayerManager_h */
