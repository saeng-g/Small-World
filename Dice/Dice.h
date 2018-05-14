//
//  Dice.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-09.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef Dice_h
#define Dice_h

#include <stdio.h>

class Dice
{
private:
    static const int sides[];
    static int total;
    static int num0;
    static int num1;
    static int num2;
    static int num3;
    static int percent0;
    static int percent1;
    static int percent2;
    static int percent3;
    
public:
    //constructor & destructor
    Dice() {};
    ~Dice() {};
    
    int roll(); //returns value of dice after a roll
    int getPercentage(int num); //returns percentage of num outcome so far
};
#endif /* Dice_h */
