//
//  Subject.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-31.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef Subject_h
#define Subject_h

#include <stdio.h>
#include <vector>
#include "Observer.h"

class Subject {
private:
    std::vector<Observer*> observers;
    
public:
    Subject();
    ~Subject();
    
    virtual void attach(Observer* o) = 0;
    virtual void detach(Observer* o) = 0;
    virtual void notify() = 0;
};

#endif /* Subject_h */
