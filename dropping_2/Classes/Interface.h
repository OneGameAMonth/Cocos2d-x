//
//  Interface.h
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef __Dropping2__Interface__
#define __Dropping2__Interface__

#include "cocos2d.h"

class Interface : public cocos2d::CCLayer
{
private:
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Interface);
    
    virtual void setCoins(int coins);
    
    virtual void setParachute(float parachute);
    
    virtual void setGameOver();    
};

#endif /* defined(__Dropping2__Interface__) */
