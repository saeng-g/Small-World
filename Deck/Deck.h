//
//  Deck.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-08.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef DECK_H
#define DECK_H

#include <stdio.h>
#include "Race.h"
#include "Power.h"
#include "Combo.h"
#include <vector>

using std::vector;

class Deck
{
private:
    std::vector<Race*> races;
    std::vector<Power*> powers;
    bool races_isEmpty;
    bool powers_isEmpty;
    
    void shuffleRace();
    void shufflePowers();
public:
    
    std::vector<Combo*> comboColumn;
    
    Deck();
    Deck(vector<Race*> races, vector<Power*> powers);
    ~Deck() {};
    void start();
    void refill();
    void remove(int index);
    void restock(Combo* combo);
    void restock(Power* power);
    void restock(Race* race);
    
};
#endif /* DECK_H */
