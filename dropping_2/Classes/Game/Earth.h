//
//  Earth.h
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef __Dropping2__Earth__
#define __Dropping2__Earth__

#include "cocos2d.h"

#include "Block.h"

class Earth : public cocos2d::CCSprite, public Block
{
public:
    Earth();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    static Earth * create(void);
    
    virtual void update(float, float);
};

#endif /* defined(__Dropping2__Earth__) */
