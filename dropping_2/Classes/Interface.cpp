//
//  Interface.cpp
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Interface.h"
#include "AppMacros.h"

#include "Coin.h"
#include "Parachute.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool Interface::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("0", "Arial", TITLE_FONT_SIZE);
    
    pLabel->setAnchorPoint(ccp(0.0f, 0.5f));
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    pLabel->setTag(10);
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    Coin* coin = Coin::create();
    coin->setAnchorPoint(ccp(0.5f, 0.5f));
    coin->setScale(2.0f);
    coin->setPosition(ccp((origin.x + visibleSize.width/2) - coin->getContentSize().width,
                              origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the sprite as a child to this layer
    this->addChild(coin, 2);
    
    
    CCLabelTTF* parachuteLabel = CCLabelTTF::create("10 sec", "Arial", TITLE_FONT_SIZE);
    
    parachuteLabel->setAnchorPoint(ccp(0.0f, 0.5f));
    
#ifdef CC_TARGET_OS_MAC
    // position the label on the center of the screen
    parachuteLabel->setPosition(ccp(50.0f,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
#endif
    
#ifdef OUYA_BUILD
    // position the label on the center of the screen
    parachuteLabel->setPosition(ccp(60.0f,
                                    origin.y + visibleSize.height - pLabel->getContentSize().height));
#endif
    
    parachuteLabel->setTag(20);
    
    // add the label as a child to this layer
    this->addChild(parachuteLabel, 1);
    
    
    Parachute* parachute = Parachute::create();
    parachute->setAnchorPoint(ccp(0.5f, 0.5f));
    parachute->setScale(1.0f);
#ifdef CC_TARGET_OS_MAC
    parachute->setPosition(ccp((50.0f) - parachute->getContentSize().width / 2.0f,
                               origin.y + visibleSize.height - pLabel->getContentSize().height));
#endif
#ifdef OUYA_BUILD
    parachute->setPosition(ccp((60.0f) - parachute->getContentSize().width / 2.0f,
                          origin.y + visibleSize.height - pLabel->getContentSize().height));
#endif
    // add the sprite as a child to this layer
    this->addChild(parachute, 3);
    
    return true;
}

void Interface::setCoins(int coins)
{
    //Set text on label
    std::ostringstream s;
    s << coins;
    
    CCLabelTTF* label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString(s.str().c_str());
}

void Interface::setParachute(float parachute)
{
    //Set text on label
    std::ostringstream s;
    s << parachute;
    std::string a = s.str();
    a.resize(4);
    a.append(" sec");
    
    CCLabelTTF* label = (CCLabelTTF*)this->getChildByTag(20);
    label->setString(a.c_str());
}

void Interface::setGameOver()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF* pLabel = CCLabelTTF::create("GAME OVER", "Arial", TITLE_FONT_SIZE);
    
    pLabel->setAnchorPoint(ccp(0.50f, 0.5f));
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 10);
#ifdef CC_TARGET_OS_MAC
    CCLabelTTF* pLabel_ = CCLabelTTF::create("PRESS B TO RESTART", "Arial", TITLE_FONT_SIZE / 2.0f);
#endif
#ifdef OUYA_BUILD
    CCLabelTTF* pLabel_ = CCLabelTTF::create("PRESS A TO RESTART", "Arial", TITLE_FONT_SIZE / 2.0f);
#endif
    pLabel_->setAnchorPoint(ccp(0.50f, 0.5f));
    
    // position the label on the center of the screen
    pLabel_->setPosition(ccp(origin.x + visibleSize.width/2,
                            (origin.y + visibleSize.height/2) - 90.0f));
    
    // add the label as a child to this layer
    this->addChild(pLabel_, 10);
}

//EOF