//
//  Coin.h
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef __Dropping2__Coin__
#define __Dropping2__Coin__

#include "cocos2d.h"

#include "Block.h"

class Coin : public cocos2d::CCSprite, public Block
{
public:
    Coin();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    static Coin * create(void);
    
    virtual void update(float, float);
};

#endif /* defined(__Dropping2__Coin__) */
