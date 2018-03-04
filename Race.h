//
//  Race.h
//  SMALL WORLD
//
//  Created by Kyungjin Kim on 2018-02-07.
//  Copyright © 2018 Ky Kim. All rights reserved.
//

#ifndef Race_h
#define Race_h

#include <stdio.h>

class Race
{
private:
    int type;
    int token;
    int maxToken;
    
    void tokenizer();
    void maxTokenizer();
    
public:
    //Numerification of types organizaed by # of starting tokens
    //8 tokens
    static const int RATMEN = 1;
    //6 tokens
    static const int AMAZONS = 2;
    static const int ELVES = 3;
    static const int GIANTS = 4;
    static const int HALFLINGS = 5;
    static const int SKELETONS = 6;
    static const int TRITONS = 7;
    //5 tokens
    static const int GHOULS = 8;
    static const int HUMANS = 9;
    static const int ORCS = 10;
    static const int SORCERERS = 11;
    static const int TROLLS = 12;
    static const int WIZARDS = 13;
    //3 tokens
    static const int DWARVES = 14;
    
    //Constructors
    Race();
    Race(int type);
    
    //Destructors
    ~Race() {};
    
    //Accessors
    int getType();
    int getToken();
    int getMaxToken();
};

#endif /* Race_hpp */
