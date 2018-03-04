//
//  Dice.cpp
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-09.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#include "Dice.h"
#include <iostream>
#include <cstdlib>


//Dice has 6 sides with 3 blanks and 1, 2, 3 on the other 3 sides
const int Dice::sides[] = {0,0,0,1,2,3};

int Dice::total = 0;
int Dice::num0;
int Dice::num1;
int Dice::num2;
int Dice::num3;
int Dice::percent0;
int Dice::percent1;
int Dice::percent2;
int Dice::percent3;

//requires srand to be set 
int Dice::roll() {
    int facevalue = rand() % 6;
    facevalue = sides[facevalue];
    total++;
    if (facevalue == 0) {
        num0++;
        percent0 = (int) (100*(double)num0/(double)total);
    }
    else if (facevalue == 1) {
        num1++;
        percent1 = (int) (100*(double)num1/(double)total);
    }
    else if (facevalue == 2) {
        num2++;
        percent2 = (int) (100*(double)num2/(double)total);
    }
    else if (facevalue == 3) {
        num3++;
        percent3 = (int) (100*(double)num3/(double)total);
    }
    
    return facevalue;
}

int Dice::getPercentage(int num) {
    if (num == 0) {
        return percent0;
    }
    else if (num == 1) {
        return percent1;
    }
    else if (num == 2) {
        return percent2;
    }
    else if (num == 3) {
        return percent3;
    }
    else {
        return 0;
    }
}
