//
//  Water.cpp
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Water.h"

using namespace cocos2d;

Water::Water()
{
    typeBlock = 0;
    active = false;
}

Water* Water::create()
{
    //Create is virtual function from CCSprite
    Water *pSprite = new Water();
    if (pSprite && pSprite->initWithFile("water_tile.png"))
    {
        // Set to autorelease
        pSprite->autorelease();
        
        //assign your attributes here!!
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Water::update(float dt, float height)
{
    CCPoint pos = this->getPosition();
    pos.y += DEFAULT_SPEED * dt;
    
    if(height < (pos.y - this->getContentSize().height))
    {
        active = false;
        pos.x = 0.0f - this->getContentSize().width;
        pos.y = 0.0f - this->getContentSize().height;
    }
    
    this->setPosition(pos);
}