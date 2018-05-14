//
//  Offensive.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "Offensive.h"

int Offensive::pickingRace(SmallWorldGame* gm, Player* player) {
    int index = 0;
    int maxTok = 0;
    int offTok = 0;
    for (int i = 0; i < 6; i++) {
        offTok = gm->getDeck()->comboColumn[i]->getOffensiveTok();
        if (offTok > maxTok) {
            index = i;
            maxTok = offTok;
        }
    }
    return index;
}

int Offensive::pickingPoEActive(SmallWorldGame* gm, Player* player) {
    int result = 0;
    Region* to = nullptr;
    bool check = false;
    int num_regions = gm->getMap()->get_num_v();
    for (int i = 0; i < num_regions; i++) {
        to = gm->getMap()->getRegion(i + 1);
        if (to->getOwner() != player) {
            check = borderCheck(player, to)
                    && player->conquerable_Type(player->getActive(), to)
                    && player->conquerable_Cond(player->getActive(), to);
            if (check) {
                result = i + 1;
                break;
            }
        }
    }
    to = nullptr;
    return result;
}

int Offensive::declOrConq(Player* player) {
    int num_regions = (int) player->getActiveReg().size();
    int num_tokens = player->getActive()->getTotalTokens();
    if (num_regions + 5 < num_tokens) {
        return 1; //1 = conquest
    }
    else {
        return 0; //0 = decline
    }
}

int Offensive::pickingConqRegActive(SmallWorldGame* gm, Player* player) {
    int result = 0;
    Region* to = nullptr;
    bool check = false;
    int num_regions = gm->getMap()->get_num_v();
    for (int i = 0; i < num_regions; i++) {
        to = gm->getMap()->getRegion(i + 1);
        if (to->getOwner() != player) {
            check = ( borderCheck(player, to) || edgeCheck(player, 1, gm->getMap(), to) )
            && player->conquerable_Type(player->getActive(), to)
            && player->conquerable_Cond(player->getActive(), to);
            if (check) {
                result = i + 1;
                break;
            }
        }
    }
    to = nullptr;
    return result;
}

int Offensive::pickingConqRegPassive(SmallWorldGame* gm, Player* player) {
    int result = 0;
    Region* to = nullptr;
    bool check = false;
    int num_regions = gm->getMap()->get_num_v();
    for (int i = 0; i < num_regions; i++) {
        to = gm->getMap()->getRegion(i + 1);
        if (to->getOwner() != player) {
            check = ( edgeCheck(player, 1, gm->getMap(), to) )
            && player->conquerable_Type(player->getPassive(), to)
            && player->conquerable_Cond(player->getPassive(), to);
            if (check) {
                result = i + 1;
                break;
            }
        }
    }
    to = nullptr;
    return result;
}

void Offensive::redeployActive(SmallWorldGame* gm, Player* player) {
    //places all redeployable onto one region:
    //minimizes loss of tokens per conquest
    int num_redeployable = player->getActive()->getRedeployable();
    player->redeploy(player->getActive(), num_redeployable, player->getActiveReg()[0]);
}

void Offensive::redeployPassive(SmallWorldGame* gm, Player* player) {
    int num_redeployable = player->getPassive()->getRedeployable();
    player->redeploy(player->getPassive(), num_redeployable, player->getPassiveReg()[0]);
}
