//
//  Powers.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include "Power.h"

Power::Power() {
    type = 0;
    type_str = "";
    token = 0;
}

Power::Power(int type) {
    this->type = type;
    typeToString();
    tokenizer();
}

void Power::tokenizer() {
    if (type == MERCHANT)
        token = 2;
    else if (type == FORTIFIED)
        token = 3;
    else
        token = (type < 11 ? 4 : 5);
}

int Power::getType() {
    return type;
}

int Power::getToken() {
    return token;
}

std::string Power::getString() {
    return type_str;
}

void Power::typeToString() {
    if (type == 1)
        type_str = "MERCHANT    ";
    else if (type == 2)
        type_str = "FORTIFIED   ";
    else if (type == 3)
        type_str = "ALCHEMIST   ";
    else if (type == 4)
        type_str = "BERSERK     ";
    else if (type == 5)
        type_str = "COMMANDO    ";
    else if (type == 6)
        type_str = "FOREST      ";
    else if (type == 7)
        type_str = "HILL        ";
    else if (type == 8)
        type_str = "STOUT       ";
    else if (type == 9)
        type_str = "SWAMP       ";
    else if (type == 10)
        type_str = "WEALTHY     ";
    else if (type == 11)
        type_str = "BIVOUACKING ";
    else if (type == 12)
        type_str = "DIPLOMAT    ";
    else if (type == 13)
        type_str = "DRAGONMASTER";
    else if (type == 14)
        type_str = "FLYING      ";
    else if (type == 15)
        type_str = "HEROIC      ";
    else if (type == 16)
        type_str = "MOUNTED     ";
    else if (type == 17)
        type_str = "PILLAGING   ";
    else if (type == 18)
        type_str = "SEAFARING   ";
    else if (type == 19)
        type_str = "SPIRIT      ";
    else if (type == 20)
        type_str = "UNDERWORLD  ";
}
