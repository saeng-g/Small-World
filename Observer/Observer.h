//
//  Observer.h
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-31.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#ifndef Observer_h
#define Observer_h

#include <stdio.h>

class Subject;

class Observer {
public:
    Observer();
    ~Observer();
    virtual void update(Subject* subject);
};

#endif /* Observer_h */
