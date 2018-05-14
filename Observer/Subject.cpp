//
//  Subject.cpp
//  SmallWorldGame
//
//  Created by Kyungjin Kim on 2018-03-31.
//  Copyright © 2018 Kyungjin Kim. All rights reserved.
//

#include "Subject.h"

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach(Observer* o) { observers.push_back(o); }
void Subject::detach(Observer* o) {
    int size = (int)observers.size();
    for (int i = 0; i < size; i++) {
        if (observers[i] == o) {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}
void Subject::notify() {
    int size = (int)observers.size();
    for (int i = 0; i < size; i++) {
        observers[i]->update(this);
    }
}
