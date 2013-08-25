//
//  Parachute.cpp
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Parachute.h"

Parachute::Parachute()
{
    this->meter = 10.0f;
    this->active = false;
}

Parachute* Parachute::create()
{
    //Create is virtual function from CCSprite
    Parachute *pSprite = new Parachute();
    if (pSprite && pSprite->initWithFile("parachute.png"))
    {
        // Set to autorelease
        pSprite->autorelease();
        
        //assign your attributes here!!
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Parachute::update(float dt, CCPoint player)
{
    
}