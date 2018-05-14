//
//  PhaseObserver.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-04-03.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef PhaseObserver_h
#define PhaseObserver_h

#include <stdio.h>
#include <iostream>
#include "Observer.h"
#include "GameManager.h"

class PhaseObserver: public Observer {
private:
    int player_state;   //player #
    int turn_state;     //turn info: PICKS_RACE, CONQUERS, SCORES
    std::string info;   //additional info (ie. region being conquered)
    
    std::string converter();
    
public:
    //constructor & destructor
    PhaseObserver();
    ~PhaseObserver();
    
    void update(Subject* subject);
    
    void printPhase();  //view
};


#endif /* PhaseObserver_h */
