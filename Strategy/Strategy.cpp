//
//  Strategy.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-11.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "Strategy.h"


bool Strategy::edgeCheck(Player* player, int indic, Map* map, Region* to) {
    //indic: active = 1, passive = 2
    //if active, go through the regions occupied by active combo
    //if passive, go through the regions occupied by passive combo
    //note: spirit passives cannot conquer
    
    bool check = false;
    
    if (indic == 1) {
        int power = player->getActive()->getPower()->getType();
        //if active has FLYING as its power, then it can defy bordering region rule
        if (power == Power::FLYING) {
            check = true;
        }
        else {
            for (int i = 0; i < player->getActiveReg().size(); i++) {
                bool edgecheck = map->is_edge(player->getActiveReg()[i], to);
                if (edgecheck) {
                    check = true;
                    break;
                }
            }
        }
    }
    else if (indic == 2) {
        for (int i = 0; i < player->getActiveReg().size(); i++) {
            bool check = map->is_edge(player->getActiveReg()[i], to);
            if (check) {
                check = true;
                break;
            }
        }
    }
    
    return check;
}

bool Strategy::borderCheck(Player* player, Region* to) {
    //Checks if to Region is on a border of the game
    //This rule doesn't apply to HALFLINGS race or FLYING power
    
    int race = player->getActive()->getRace()->getType();
    int power = player->getActive()->getPower()->getType();
    
    if (race == Race::HALFLINGS || power == Power::FLYING) {
        return true;
    }
    else {
        return to->getIsBorder();
    }
}
