#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "AboutLayer.h"
#include "SettingsLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    
    // add the about button. it's an autorelease object
    CCMenuItemImage *pAboutItem = CCMenuItemImage::create(
                                                          "about-button.png",
                                                          "about-button-selected.png",
                                                          this, menu_selector(HelloWorld::aboutCallback) );
    pAboutItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    
    pMenu->addChild(pAboutItem, 1, 1);
    
    
    //Bonus: add the settings button. it's an autorelease object
    CCMenuItemImage *pSettingsItem = CCMenuItemImage::create(
                                                          "settings-button.png",
                                                          "settings-button-selected.png",
                                                          this, menu_selector(HelloWorld::settingCallback) );
    pSettingsItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 60.0f) );
        
    pMenu->addChild(pSettingsItem, 1, 2);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


// Callback function for the about button
void HelloWorld::aboutCallback(CCObject* pSender)
{
    //All Cocos2d applications are build via a CCScene holding one are more layers.
    //The CCDirector object will hold the active CCSene, so this CCScene object will be requests from the CCDirector.
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene *scene = pDirector->getRunningScene();
    
    //Now the current CCLayer will be popped from the CCScene object.
    scene->removeChild(this);
    
    //The about layer will be pushed to the CCScene object.
    // 'layer' is an autorelease object
    AboutLayer *layer = AboutLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
}

// Callback function for the settings button
void HelloWorld::settingCallback(CCObject* pSender)
{
    //All Cocos2d applications are build via a CCScene holding one are more layers.
    //The CCDirector object will hold the active CCSene, so this CCScene object will be requests from the CCDirector.
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene *scene = pDirector->getRunningScene();
    
    //Now the current CCLayer will be popped from the CCScene object.
    scene->removeChild(this);
    
    //The about layer will be pushed to the CCScene object.
    // 'layer' is an autorelease object
    SettingsLayer *layer = SettingsLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
}

