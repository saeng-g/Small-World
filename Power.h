//
//  Powers.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef Powers_hpp
#define Powers_hpp

#include <stdio.h>

class Power
{
private:
    int type;
    int token;
    
    void tokenizer();
    
public:
    //Numerification of special powers organized by # of tokens
    //2 tokens
    static const int MERCHANT = 1;
    //3 tokens
    static const int FORTIFIED = 2;
    //4 tokens
    static const int ALCHEMIST = 3;
    static const int BERSERK = 4;
    static const int COMMANDO = 5;
    static const int FOREST = 6;
    static const int HILL = 7;
    static const int STOUT = 8;
    static const int SWAMP = 9;
    static const int WEALTHY = 10;
    //5 tokens
    static const int BIVOUACKING = 11;
    static const int DIPLOMAT = 12;
    static const int DRAGONMASTER = 13;
    static const int FLYING = 14;
    static const int HEROIC = 15;
    static const int MOUNTED = 16;
    static const int PILLAGING = 17;
    static const int SEAFARING = 18;
    static const int SPIRIT = 19;
    static const int UNDERWORLD = 20;
    
    //Constructors
    Power();
    Power(int type);
    
    //Destructors
    ~Power() {};
    
    //Accessors
    int getType();
    int getToken();
};


#endif /* Powers_hpp */
