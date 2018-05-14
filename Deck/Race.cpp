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
    type_str = "";
    token = 0;
    maxToken = 0;
}

Race::Race(int type) {
    this->type = type;
    typeToString();
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
    //AMAZONS get 4 extra for offensive
    else if (type == AMAZONS)
        token = 10;
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

std::string Race::getString() {
    return type_str;
}

void Race::typeToString() {
    if (type == 1)
        type_str = "RATMEN   ";
    else if (type == 2)
        type_str = "AMAZONS  ";
    else if (type == 3)
        type_str = "ELVES    ";
    else if (type == 4)
        type_str = "GIANTS   ";
    else if (type == 5)
        type_str = "HALFLINGS";
    else if (type == 6)
        type_str = "SKELETONS";
    else if (type == 7)
        type_str = "TRITONS  ";
    else if (type == 8)
        type_str = "GHOULS   ";
    else if (type == 9)
        type_str = "HUMANS   ";
    else if (type == 10)
        type_str = "ORCS     ";
    else if (type == 11)
        type_str = "SORCERERS";
    else if (type == 12)
        type_str = "TROLLS   ";
    else if (type == 13)
        type_str = "WIZARDS  ";
    else if (type == 14)
        type_str = "DWARVES  ";
}

