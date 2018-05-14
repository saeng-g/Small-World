//
//  StatsDecorator.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef StatsDecorator_h
#define StatsDecorator_h

#include <stdio.h>
#include "GameStatisticsObserver.h"

class StatsDecorator : public GameStatisticsObserver {
protected:
    GameStatisticsObserver* gso;
public:
    StatsDecorator(GameStatisticsObserver* gso);
    void update(Subject* subject);
};

class Domination : public StatsDecorator {
private:
    void printStats();
public:
    Domination(GameStatisticsObserver* gso);
    void update(Subject* subject);
};

class Hands : public StatsDecorator {
public:
    Hands(GameStatisticsObserver* gso);
    void update(Subject* subject);
};

class Coins : public StatsDecorator {
public:
    Coins(GameStatisticsObserver* gso);
    void update(Subject* subject);
};

class DecorationManager {
private:
    bool domination;
    bool hands;
    bool coins;
public:
    DecorationManager();
    ~DecorationManager();
    
    bool getDom();
    void setDom(bool);
    bool getHands();
    void setHands(bool);
    bool getCoins();
    void setCoins(bool);
};

#endif /* StatsDecorator_h */
