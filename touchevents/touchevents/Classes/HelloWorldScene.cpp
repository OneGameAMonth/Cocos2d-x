#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    this->touchOne.x = -1.0f;
    this->touchOne.y = -1.0f;
    
    this->touchTwo.x = -1.0f;
    this->touchTwo.y = -1.0f;
    
    //Enable touch
    this->setTouchEnabled(true);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

CCPoint HelloWorld::touchToPoint(CCTouch* touch)
{
	// convert the touch object to a position in our cocos2d space
	return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    for( auto it = pTouches->begin(); it != pTouches->end(); it++)
    {
        CCTouch* touch = dynamic_cast<CCTouch*>(*it);
        
        if(this->touchOne.x == -1.0f && this->touchOne.y == -1.0f)
        {
            this->touchOne = this->touchToPoint(touch);
            printf("touchOne location is: %f %f\n", touchOne.x, touchOne.y);
        }
        else if(this->touchTwo.x == -1.0f && this->touchTwo.y == -1.0f)
        {
            this->touchTwo = this->touchToPoint(touch);
            printf("touchTwo location is: %f %f\n", touchTwo.x, touchTwo.y);
        }
    }
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    for( auto it = pTouches->begin(); it != pTouches->end(); it++)
    {
        CCTouch* touch = dynamic_cast<CCTouch*>(*it);
        
        // set the new touch position
        if( touch && touch->getPreviousLocation().x == this->touchOne.x
           && touch->getPreviousLocation().y == this->touchOne.y )
        {
            this->touchOne = this->touchToPoint(touch);
            printf("touchOne new location is: %f %f\n", touchOne.x, touchOne.y);
        }
        if( touch && touch->getPreviousLocation().x == this->touchTwo.x
           && touch->getPreviousLocation().y == this->touchTwo.y )
        {
            this->touchTwo = this->touchToPoint(touch);
            printf("touchTwo new location is: %f %f\n", touchTwo.x, touchTwo.y);
        }
    }
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    for( auto it = pTouches->begin(); it != pTouches->end(); it++)
    {
        CCTouch* touch = dynamic_cast<CCTouch*>(*it);
        
        // set the new touch position
        if( touch && touch->getPreviousLocation().x == this->touchOne.x
           && touch->getPreviousLocation().y == this->touchOne.y )
        {
            this->touchOne.x = -1.0f;
            this->touchOne.y = -1.0f;
            printf("touchOne new location is: %f %f\n", touchOne.x, touchOne.y);
        }
        if( touch && touch->getPreviousLocation().x == this->touchTwo.x
           && touch->getPreviousLocation().y == this->touchTwo.y )
        {
            this->touchTwo.x = -1.0f;
            this->touchTwo.y = -1.0f;
            printf("touchTwo new location is: %f %f\n", touchTwo.x, touchTwo.y);
        }
    }
}

void HelloWorld::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

//EOF