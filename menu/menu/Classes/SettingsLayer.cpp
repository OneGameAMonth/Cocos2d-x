//
//  SettingsLayer.cpp
//  menu
//
//  Created by Martijn Thorig on 1/14/13.
//
//

#include "SettingsLayer.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "AboutLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* SettingsLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SettingsLayer *layer = SettingsLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingsLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add the about button. it's an autorelease object
    CCMenuItemImage *pBackItem = CCMenuItemImage::create(
                                                         "back-button.png",
                                                         "back-button-selected.png",
                                                         this, menu_selector(AboutLayer::backCallback) );
    pBackItem->setPosition( ccp(60.0f, 30.0f) );
    pBackItem->setScale(0.5f);
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pBackItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    //Sound settings
    CCMenuItem *soundOnItem;
    
    soundOnItem = CCMenuItemImage::create("sound-on-button.png",
                                          "sound-on-button-selected.png",
                                          NULL,
                                          NULL);
    
    CCMenuItem *soundOffItem;
    
    soundOffItem = CCMenuItemImage::create("sound-off-button.png",
                                           "sound-off-button-selected.png",
                                           NULL,
                                           NULL);
    
    CCMenuItemToggle *soundToggleItem = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingsLayer::soundSwitchCallback), soundOnItem, soundOffItem, NULL);
    
    //soundToggleItem->setAnchorPoint(ccp(0.5f, 1.0f));
    
    soundToggleItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2,
                                      (CCDirector::sharedDirector()->getWinSize().height/2 + 75)) );
    
    pMenu->addChild(soundToggleItem);
    
    //Music settings
    CCMenuItem *musicOnItem;
    
    musicOnItem = CCMenuItemImage::create("music-on-button.png",
                                          "music-on-button-selected.png",
                                          NULL,
                                          NULL);
    
    CCMenuItem *musicOffItem;
    
    musicOffItem = CCMenuItemImage::create("music-off-button.png",
                                           "music-off-button-selected.png",
                                           NULL,
                                           NULL);
    
    CCMenuItemToggle *musicToggleItem = CCMenuItemToggle::createWithTarget(this, menu_selector(SettingsLayer::musicSwitchCallback), musicOnItem, musicOffItem, NULL);
    
    //musicToggleItem->setAnchorPoint(ccp(0.5f, 1.0f));
    
    musicToggleItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, (CCDirector::sharedDirector()->getWinSize().height/2) - 75) );
    
    pMenu->addChild(musicToggleItem);
    
    //Creating a label for the about menu
    CCLabelBMFont * pLabel = CCLabelBMFont::create("GAME SETTINGS", "formata.fnt");
       
    pLabel->setAnchorPoint(ccp(0.5f, 1.0f));
    
    pLabel->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2.0f, CCDirector::sharedDirector()->getWinSize().height - 145.0f) );
    
    this->addChild(pLabel);
    
    return true;
}

void SettingsLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


// Callback function for the about button
void SettingsLayer::backCallback(CCObject* pSender)
{
    //All Cocos2d applications are build via a CCScene holding one are more layers.
    //The CCDirector object will hold the active CCSene, so this CCScene object will be requests from the CCDirector.
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene *scene = pDirector->getRunningScene();
    
    //Now the current CCLayer will be popped from the CCScene object.
    scene->removeChild(this);
    
    //The about layer will be pushed to the CCScene object.
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
}

void SettingsLayer::soundSwitchCallback(CCObject* pSender)
{
    printf("sounds switch pressed!!\n");
}

void SettingsLayer::musicSwitchCallback(CCObject* pSender)
{
    printf("music switch pressed!!\n");
}
