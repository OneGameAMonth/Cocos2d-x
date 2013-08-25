//
//  Parachute.h
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef __Dropping2__Parachute__
#define __Dropping2__Parachute__

#include "cocos2d.h"

using namespace cocos2d;

class Parachute : public CCSprite
{
public:
    Parachute();
    static Parachute* create();
    virtual void update(float, CCPoint);
    
    bool active;
    
    float meter;
};

#endif /* defined(__Dropping2__Parachute__) */
