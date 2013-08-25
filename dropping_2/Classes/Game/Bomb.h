//
//  bomb.h
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//			

#ifndef __Dropping2__bomb__
#define __Dropping2__bomb__

#include "cocos2d.h"

#define BOMB_FALLING    10
#define BOMB_STANDING   20


class Bomb : public cocos2d::CCSprite
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    static Bomb * create(void);
    
    virtual bool update(float, float, float, bool, bool, cocos2d::CCLayer* parent);
    
    float moveLeftSpeed;
    float moveRightSpeed;
    float moveDownSpeed;
    
    float posInWater;
    
    bool isInWater;
    bool returnValue;
    
    bool parachute;
    
    cocos2d::CCPoint oldPosition;
    
    int block1;
    int block2;
    
    int state;
};

#endif /* defined(__Dropping2__bomb__) */
