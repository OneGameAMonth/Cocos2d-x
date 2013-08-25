//
//  Coin.cpp
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Coin.h"

using namespace cocos2d;

Coin::Coin()
{
    typeBlock = 2;
    active = false;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
Coin* Coin::create(void)
{
    //Create is virtual function from CCSprite
    Coin *pSprite = new Coin();
    if (pSprite && pSprite->initWithFile("coin.png"))
    {
        // Set to autorelease
        pSprite->autorelease();
        
        //assign your attributes here!!
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Coin::update(float dt, float height)
{
    CCPoint pos = this->getPosition();
    pos.y += (DEFAULT_SPEED * 1.5f) * dt;
    
    if(height < (pos.y - this->getContentSize().height))
    {
        active = false;
        pos.x = 0.0f - this->getContentSize().width;
        pos.y = 0.0f - this->getContentSize().height;
    }
    
    this->setPosition(pos);
}