//
//  GameStatisticsObserver.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef GameStatisticsObserver_h
#define GameStatisticsObserver_h

#include <stdio.h>
#include "Observer.h"
#include "Region.h"
#include "Player.h"
#include "Turn.h"
#include <vector>

using std::vector;

class GameStatisticsObserver : public Observer {
protected:
    int round;
    int num_players;
    int num_regions;
    std::vector<int> owned; //player i's # goes into index i-1
    
public:
    GameStatisticsObserver();
    GameStatisticsObserver(int num_players, int num_regions);
    ~GameStatisticsObserver();
    
    void update(Subject* subject);
    int getOwned(int index);
    void setOwned(int index, int value);
    int getNum_Players();
    
    void print();
};

#endif /* GameStatisticsObserver_h */
