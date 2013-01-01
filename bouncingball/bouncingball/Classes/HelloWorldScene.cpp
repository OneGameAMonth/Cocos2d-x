#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Ball.h"

#define ballTagId 1

using namespace example;
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

    /////////////////////////////
    // 3. add your codes below...

    // Ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //Create the instance of the Ball class.
    CCSprite* pBall = Ball::create("ball.png");
    
    //Set the tag for the instance
    pBall->setTag(ballTagId);
    
    //Position the ball on the center of the screen
    pBall->setPosition( ccp(size.width/2, size.height/2) );
    
    //Add the ball to the scene
    this->addChild(pBall, 1);
    
    //Make sure the update function is called every 1/60 of a second
    this->getScheduler()->scheduleSelector(schedule_selector(HelloWorld::update), this, 1/60, false);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float dt)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //Get the ball instance via the tag id
    Ball* ball = (Ball*)getChildByTag(ballTagId);
    
    //Update the ball position
    ball->update(dt, size.width, size.height);
}
