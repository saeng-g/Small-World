//
//  Race.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include <iostream>
#include "Race.h"

Race::Race() {
    type = 0;
    token = 0;
    maxToken = 0;
}

Race::Race(int type) {
    this->type = type;
    tokenizer();
    maxTokenizer();
}

void Race::tokenizer() {
    //RATMEN = 8 tokens
    if (type == RATMEN)
        token = 8;
    //DWARVES = 3 tokens
    else if (type == DWARVES)
        token = 3;
    //rest are either 6 tokens or 5
    else
        token = (type < 8 ? 6 : 5);
}

void Race::maxTokenizer() {
    //SKELETONS = 20 tokens
    //SORCERERS = 18 tokens
    //AMAZONS = 15 tokens
    //RATMEN = 13 tokens
    //DWARVES = 8 tokens
    //ELVES, TRITONS, GIANTS, HALFLINGS = 11 tokens
    //GHOULS, HUMANS, ORCS, TROLLS, WIZARDS = 10 tokens
    if (type == SKELETONS)
        maxToken = 20;
    else if (type == SORCERERS)
        maxToken = 18;
    else if (type == AMAZONS)
        maxToken = 15;
    else if (type == RATMEN)
        maxToken = 13;
    else if (type == DWARVES)
        maxToken = 8;
    else if (type == ELVES || type == TRITONS || type == GIANTS || type == HALFLINGS)
        maxToken = 11;
    else
        maxToken = 10;
}

int Race::getType() {
    return type;
}

int Race::getToken() {
    return token;
}

int Race::getMaxToken() {
    return maxToken;
}
