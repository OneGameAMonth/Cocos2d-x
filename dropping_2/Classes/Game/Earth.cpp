//
//  Earth.cpp
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Earth.h"

using namespace cocos2d;

Earth::Earth()
{
    typeBlock = 1;
    active = false;
}

Earth* Earth::create()
{
    //Create is virtual function from CCSprite
    Earth *pSprite = new Earth();
    if (pSprite && pSprite->initWithFile("earth_tile.png"))
    {
        // Set to autorelease
        pSprite->autorelease();
        
        //assign your attributes here!!
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Earth::update(float dt, float height)
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