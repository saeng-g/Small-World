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
    token = 0;
}

Power::Power(int type) {
    this->type = type;
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
