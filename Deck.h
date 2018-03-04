//
//  Deck.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-08.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include "Race.h"
#include "Power.h"
#include "Combo.h"
#include <vector>

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
    ~Deck() {};
    void start();
    void refill();
    void remove(int racetype);
    void flip();
    void restock(Combo* combo);
    
};
#endif /* Deck_hpp */
