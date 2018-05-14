//
//  GameCreator.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef GameCreator_h
#define GameCreator_h

#include <stdio.h>
#include <iostream>
#include "MapLoader.h"
#include "SmallWorldGame.h"

using std::string;

class GameCreator {
    
private:
    //response validity indicator
    bool proper_default;
    bool proper_num;
    bool proper_name;
    
    //response storage
    char response;
    string fileName;
    bool use_default;
    int num_players;
    
    //MapLoader & Map
    MapLoader* loader;
    Map* map;
    
    //game
    SmallWorldGame* game;
    
public:
    GameCreator();
    ~GameCreator();
    
    void askUserInputs();
    void makeGame();
    SmallWorldGame* getGame();
};

#endif /* GameCreator_h */
