//
//  PlayerManager.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "PlayerManager.h"

//constructor & destructor
PlayerManager::PlayerManager() {}
PlayerManager::PlayerManager(Player* player, SmallWorldGame* game, Strategy* initStrat) {
    this->player = player;
    this->game = game;
    this->strategy = initStrat;
}
PlayerManager::~PlayerManager() {
    delete strategy;
    strategy = nullptr;
}

//setStrat
void PlayerManager::setStrat(Strategy* strat) { this->strategy = strat; }

//executeStrat
int PlayerManager::execPickRace() {
    int position = strategy->pickingRace(game, player);
    player->picks_race(position + 1, game->getDeck());
    return position + 1;
}

int PlayerManager::execEntry() {
    int conquests = 0;
    
    //initial entry
    int region = strategy->pickingPoEActive(game, player);
    int req_tok = player->conquerable_Tok(player->getActive(), game->getMap()->getRegion(region));
    player->conquers(player->getActive(), game->getMap()->getRegion(region), req_tok);
    conquests++;
    
    //following conquests
    bool finalConquest = false;
    int offensive = 0;
    while (!finalConquest) {
        region = strategy->pickingConqRegActive(game, player);
        if (region == 0) {
            //0 region means end turn
            return conquests;
        }
        offensive = player->getActive()->getOffensiveTok();
        req_tok = player->conquerable_Tok(player->getActive(), game->getMap()->getRegion(region));
        if (offensive > req_tok) {
            player->conquers(player->getActive(), game->getMap()->getRegion(region), req_tok);
            conquests++;
        }
        else {
            finalConquest = true;
        }
    }
    int diceroll = game->getDice()->roll();
    if (offensive + diceroll > req_tok) {
        player->conquers(player->getActive(), game->getMap()->getRegion(region), req_tok);
        conquests++;
    }
    return conquests;
}

int PlayerManager::execConqActive() {
    int conquests = 0;
    player->readyConquest(1);
    bool finalConquest = false;
    int offensive = 0;
    int req_tok = 0;
    int region = 0;
    while (!finalConquest) {
        region = strategy->pickingConqRegActive(game, player);
        if (region == 0) {
            return conquests;
        }
        offensive = player->getActive()->getOffensiveTok();
        req_tok = player->conquerable_Tok(player->getActive(), game->getMap()->getRegion(region));
        if (offensive > req_tok) {
            player->conquers(player->getActive(), game->getMap()->getRegion(region), req_tok);
            conquests++;
        }
        else {
            finalConquest = true;
        }
    }
    int diceroll = game->getDice()->roll();
    if (offensive + diceroll > req_tok) {
        player->conquers(player->getActive(), game->getMap()->getRegion(region), req_tok);
        conquests++;
    }
    return conquests;
}

int PlayerManager::execConqPassive() {
    int racetype = 0;
    if (player->getPassive() != nullptr) {
        racetype = player->getPassive()->getRace()->getType();
    }
    if (racetype == Race::GHOULS) {
        int conquests = 0 ;
        player->readyConquest(2);
        bool finalConquest = false;
        int offensive = 0;
        int req_tok = 0;
        int region = 0;
        while (!finalConquest) {
            region = strategy->pickingConqRegActive(game, player);
            if (region == 0) {
                return conquests;
            }
            offensive = player->getPassive()->getOffensiveTok();
            req_tok = player->conquerable_Tok(player->getPassive(), game->getMap()->getRegion(region));
            if (offensive > req_tok) {
                player->conquers(player->getPassive(), game->getMap()->getRegion(region), req_tok);
                conquests++;
            }
            else {
                finalConquest = true;
            }
        }
        int diceroll = game->getDice()->roll();
        if (offensive + diceroll > req_tok) {
            player->conquers(player->getPassive(), game->getMap()->getRegion(region), req_tok);
            conquests++;
        }
        return conquests;
    }
    return 0;
}

int PlayerManager::execDecline() {
    int decline = strategy->declOrConq(player);
    if (decline == 0) {
        player->decline(game->getDeck());
    }
    return decline;
}

void PlayerManager::execRedepActive() {
    player->collectTokens(1);
    strategy->redeployActive(game, player);
}

void PlayerManager::execRedepPassive() {
    int racetype = 0;
    if (player->getPassive() != nullptr) {
        racetype = player->getPassive()->getRace()->getType();
    }
    if (racetype == Race::GHOULS) {
        player->collectTokens(2);
        strategy->redeployPassive(game, player);
    }
}

void PlayerManager::execRedepOffTurn() {
    strategy->redeployPassive(game, player);
    strategy->redeployActive(game, player);
}

int PlayerManager::execScore() {
    int score = player->scores();
    return score;
}
