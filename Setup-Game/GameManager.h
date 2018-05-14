//
//  GameManager.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-31.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>
#include "Turn.h"
#include "SmallWorldGame.h"
#include "Subject.h"
#include "PlayerManager.h"
#include "Offensive.h"
#include "Defensive.h"
#include "StatsDecorator.h"

class GameManager: public Subject {
private:
    Turn* turn;
    SmallWorldGame* game;
    vector<GameStatisticsObserver*> gsos;
    DecorationManager* decorManager;
    bool stopDecor;
    
    vector<PlayerManager*> pManagers;
    
    int turn_component; //PICKS_RACE, CONQUERS, SCORES
    std::string component_info;
    
    void first_turn();
    void following_turn();
    int calculateVictor();
    
    /*
    void redeployment();
    void notifyTokenReq(int offensive, int req_tok); //helper method for conquering phase
    void notifyInvalidReg(bool, bool, bool); //helper method for conquering phase
    */
    
    //moved to Strategy
    //bool edgeCheck(Player* player, int indic, Region* to); //indic: active = 1, passive = 2
    //bool borderCheck(Player* player, Region* to);
    
    
public:
    //virtual inherited methods
    void attach(Observer* o);
    void detach(Observer* o);
    void notify();
    
    //Constructors and destructors
    GameManager();
    GameManager(Turn* turn, SmallWorldGame* game);
    ~GameManager();
    
    
    void main_loop();
    
    void askStrat(Player* player);
    
    void askDecorator();
    
    //Accessors & modifiers
    Turn* getTurn();
    SmallWorldGame* getGame();
    int get_turnComponent();
    std::string getInfo();
    
    //static field
    static const int PICKS_RACE = 1;
    static const int CONQUERS = 2;
    static const int SCORES = 3;
    static const int DECLINE = 4;
    
};

#endif /* GameManager_h */
