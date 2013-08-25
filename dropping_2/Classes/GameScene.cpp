#include "GameScene.h"
#include "AppMacros.h"
#include "Interface.h"

USING_NS_CC;

#define INTERFACE_ID    10
#define BOMB_ID         100
#define PARACHUTE_ID    101
#define BLOCK           200
#define BONUS           500

#define GAME_STATE_PLAY     100
#define GAME_STATE_GAMEOVER 200

//i=1527;while [ 1 ];do screencapture -t jpg -x ~/Desktop/screencapture/$i.jpg; let i++;sleep 4; done

CCScene* Game::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Game *layer = Game::create();
    
    layer->setTag(1001);
    
    Interface* interface = Interface::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->addChild(interface, 3);
    
    interface->setTag(INTERFACE_ID);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    coinCounterPlayer = 0;
    this->gameState = GAME_STATE_PLAY;
    this->restartGame = false;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // add "Game" splash screen"
    CCSprite* pSprite = CCSprite::create("background.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    float scaleX = visibleSize.width / pSprite->getContentSize().width;
    float scaleY = visibleSize.height / pSprite->getContentSize().height;
    
    pSprite->setScaleX(scaleX);
    pSprite->setScaleY(scaleY);
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, -1);
    
    
    Parachute* para = Parachute::create();
    para->setAnchorPoint(ccp(0.5f, 0.0f));
    
    para->setPosition(ccp(-300.0f, -300.0f));
    
    para->setTag(PARACHUTE_ID);
    this->addChild(para, 0);
    
    Bomb* bomb = Bomb::create();
    bomb->setAnchorPoint(ccp(0.5f, 0.5f));
    
    // position the sprite on the center of the screen
    bomb->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    
    // add the sprite as a child to this layer
    this->addChild(bomb, 0);
    
    bomb->setTag(BOMB_ID);
    
    this->generateCoins();
    
    this->generateBlocks();
    
    //Place two blocks under the player
    for(int i = BLOCK; i < BLOCK+2; i++)
    {
        CCSprite* block = (CCSprite*)this->getChildByTag(i);
        
        if(i == BLOCK)
            block->setPosition(ccp((visibleSize.width/2) - (block->getContentSize().width/2.0f), 0.0f - (block->getContentSize().height/2.0f)));
        else
            block->setPosition(ccp((visibleSize.width/2) + (block->getContentSize().width/2.0f), 0.0f - (block->getContentSize().height/2.0f)));
        
        int* blockType = (int*)block->getUserData();
        
        if(*blockType == 0)
        {
            Water* water = (Water*)block;
            water->active = true;
        }
        if(*blockType == 1)
        {
            Earth* earth = (Earth*)block;
            earth->active = true;
        }
    }
    parachute = false;
    moveLeft = false;
    moveRight = false;
    
#ifdef CC_TARGET_OS_MAC
    this->addListener(this);
#endif
    
    this->addBlockCounter = 0.0f;
    
    this->getScheduler()->scheduleSelector(schedule_selector(Game::update), this, 1.0f/60.0f, false);
    
    return true;
}

void Game::update(float dt)
{
    if(this->gameState == GAME_STATE_GAMEOVER)
    {
        if(restartGame)
        {
#ifdef CC_TARGET_OS_MAC
            this->removeListener();
#endif
            CCDirector* pDirector = CCDirector::sharedDirector();
            
            // create a scene. it's an autorelease object
            CCScene *pScene = Game::scene();
            
            // run
            pDirector->replaceScene(pScene);
        }
    }
    if(this->gameState == GAME_STATE_PLAY)
    {
        this->addBlockCounter += dt;
        CCPoint tmpPos = ccp(0.0f, 0.0f);
        
        if(this->addBlockCounter > 3.0f)
        {
            int newBlock = 1 + rand() % 3;
            
            this->addBlockCounter = 0.0f;
            
            for(int i = 0; i < newBlock; i++)
            {
                tmpPos = this->addBlocks(tmpPos);
            }
        }
        
        this->addCoinCounter += dt;
        
        
        tmpPos = ccp(0.0f, 0.0f);
        
        if(this->addCoinCounter > 1.2f)
        {
            int newCoin = 1 + rand() % 5;
            
            this->addCoinCounter = 0.0f;
            
            for(int i = 0; i < newCoin; i++)
            {
                tmpPos = this->addCoins(tmpPos);
            }
        }
        
        float screenHeight = this->getContentSize().height;
        
        int maxBlock = BLOCK + blockCounter;
        for(int i = BLOCK; i < maxBlock; i++)
        {
            CCSprite* block = (CCSprite*)this->getChildByTag(i);
            
            int* blockType = (int*)block->getUserData();
            
            if(*blockType == 0)
            {
                Water* water = (Water*)block;
                if(water->active)
                    water->update(dt, screenHeight);
            }
            if(*blockType == 1)
            {
                Earth* earth = (Earth*)block;
                if(earth->active)
                    earth->update(dt, screenHeight);
            }
        }
        
        int maxCoin = (BONUS + coinCounter);
        
        for(int i = BONUS; i < maxCoin; i++)
        {
            Coin* coin = (Coin*)this->getChildByTag(i);
            
            if(coin->active)
                coin->update(dt, screenHeight);
        }
        
        Bomb* bomb = (Bomb*)this->getChildByTag(BOMB_ID);
        
        Parachute* parachute_ = (Parachute*)this->getChildByTag(PARACHUTE_ID);
        
        if(parachute_->meter > 0.0f)
            bomb->parachute = parachute;
        
        if(!bomb->update(dt, screenHeight, this->getContentSize().width, moveLeft, moveRight, this))
        {
            CCRect bombRect = CCRect(bomb->getPosition().x - (bomb->getContentSize().width/2.0f),
                                      bomb->getPosition().y - (bomb->getContentSize().height/2.0f),
                                      bomb->getContentSize().width,
                                      bomb->getContentSize().height);
            
            for(int i = BLOCK; i < maxBlock; i++)
            {
                CCSprite* block = (CCSprite*)this->getChildByTag(i);
                
                int* blockType = (int*)block->getUserData();
                
                if(*blockType == 0)
                {
                    Water* water = (Water*)block;
                    if(water->active)
                    {
                        CCRect blockRect = CCRect(water->getPosition().x - (water->getContentSize().width/2.0f),
                                                   water->getPosition().y - (water->getContentSize().height/2.0f),
                                                   water->getContentSize().width,
                                                   water->getContentSize().height);
                        if(bombRect.intersectsRect(blockRect))
                        {
                            if(bomb->block1 == 0)
                            {
                                bomb->block1 = i;
                            }
                            else if(bomb->block2 == 0)
                            {
                                bomb->block2 = i;
                            }
                        }
                    }
                }
                if(*blockType == 1)
                {
                    Earth* earth = (Earth*)block;
                    if(earth->active)
                    {
                        
                        CCRect blockRect = CCRect(earth->getPosition().x - (earth->getContentSize().width/2.0f),
                                                  earth->getPosition().y - (earth->getContentSize().height/2.0f),
                                                  earth->getContentSize().width,
                                                  earth->getContentSize().height);
                        
                        if(bombRect.intersectsRect(blockRect))
                        {
                            if(bomb->block1 == 0)
                            {
                                bomb->block1 = i;
                            }
                            else if(bomb->block2 == 0)
                            {
                                bomb->block2 = i;
                            }
                        }
                    }
                }
            }
            
            for(int i = BONUS; i < maxCoin; i++)
            {
                Coin* coin = (Coin*)this->getChildByTag(i);
                if(coin->active)
                {
                    CCRect coinRect = CCRect(coin->getPosition().x - (coin->getContentSize().width/2.0f),
                                         coin->getPosition().y - (coin->getContentSize().height/2.0f),
                                         coin->getContentSize().width,
                                         coin->getContentSize().height);
                
                    if(coinRect.intersectsRect(bombRect))
                    {
                        coin->active = false;
                        coin->setPosition(ccp(-200.0f, -200.0f));
                        coinCounterPlayer++;
                        Interface* interface = (Interface*)this->getChildByTag(INTERFACE_ID);
                        interface->setCoins(coinCounterPlayer);
                    }
                }
            }
            
            if(bomb->parachute)
            {
                parachute_->meter -= dt;
                
                Interface* interface = (Interface*)this->getChildByTag(INTERFACE_ID);
                if(parachute_->meter < 0.0f)
                    parachute_->meter = 0.0f;
                interface->setParachute(parachute_->meter);
                
                parachute_->setPosition(bomb->getPosition());
            }
            else
            {
                parachute_->setPosition(ccp(-300.0f, -300.0f));
            }
        }
        else
        {
            Interface* interface = (Interface*)this->getChildByTag(INTERFACE_ID);
            interface->setGameOver();
            this->gameState = GAME_STATE_GAMEOVER;
        }
    }
}

void Game::generateBlocks()
{
    for(int i = 0; i < 20; i++)
    {
        Earth* earth = Earth::create();
        earth->setAnchorPoint(ccp(0.5f, 0.5f));
        earth->setPosition(ccp(-200.0f, -200.0f));
        
        // add the sprite as a child to this layer
        this->addChild(earth, 1);
        
        earth->setTag(BLOCK + blockCounter);
        
        earth->setUserData(&earth->typeBlock);
        
        blockCounter++;
        
        Water* water = Water::create();
        water->setAnchorPoint(ccp(0.5f, 0.5f));
        
        water->setPosition(ccp(-200.0f, -200.0f));
        
        // add the sprite as a child to this layer
        this->addChild(water, 1);
        
        water->setTag(BLOCK + blockCounter);
        
        water->setUserData(&water->typeBlock);
        
        blockCounter++;
    }
}

void Game::generateCoins()
{
    coinCounter = 0;
    addCoinCounter = 0.0f;
    
    for(int i = 0; i < 50; i++)
    {
        Coin* coin = Coin::create();
        coin->setAnchorPoint(ccp(0.5f, 0.5f));
        coin->setPosition(ccp(-200.0f, -200.0f));
        
        // add the sprite as a child to this layer
        this->addChild(coin, 2);
        
        coin->setTag(BONUS + coinCounter);
        
        coin->setUserData(&coin->typeBlock);
        
        coinCounter++;
    }
}

void Game::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

CCPoint Game::addBlocks(CCPoint oldPosition)
{
    CCPoint posBlock;
    posBlock.x += oldPosition.x;
    posBlock.y += oldPosition.y;
    
    float screenHeight = this->getContentSize().height;
    float screenWidth = this->getContentSize().width;
    
    int type = rand() % 100;
    
    int maxBlock = BLOCK + blockCounter;
    for(int i = BLOCK; i < maxBlock; i++)
    {
        CCSprite* block = (CCSprite*)this->getChildByTag(i);
        if(type < 50)
        {
            int* blockType = (int*)block->getUserData();
            
            if(*blockType == 0)
            {
                Water* water = (Water*)block;
                if(!water->active)
                {
                    int positionX;
                    if(posBlock.x == 0.0f)
//                        positionX = block->getContentSize().width +
                        positionX = block->getContentSize().width + (rand() % (int)(screenWidth - block->getContentSize().width));
                    else
                    {
                        positionX = block->getContentSize().width + posBlock.x;
                    }
                    water->active = true;
                    CCPoint pos = water->getPosition();
                    pos.x = positionX;
                    pos.y = 0.0f - water->getContentSize().height;
                    water->setPosition(pos);
                    i = maxBlock;
                    posBlock.x += pos.x;
                    posBlock.y += pos.y;
                }
            }
        }
        else
        {
            int* blockType = (int*)block->getUserData();
            
            if(*blockType == 1)
            {
                Earth* earth = (Earth*)block;
                if(!earth->active)
                {
                    int positionX;
                    if(posBlock.x == 0.0f)
                        //                        positionX = block->getContentSize().width +
                        positionX = block->getContentSize().width +(rand() % (int)(screenWidth - block->getContentSize().width));
                    else
                    {
                        positionX = block->getContentSize().width + posBlock.x;
                    }
                    earth->active = true;
                    CCPoint pos = earth->getPosition();
                    pos.x = positionX;
                    pos.y = 0.0f - earth->getContentSize().height;
                    earth->setPosition(pos);
                    i = maxBlock;
                    posBlock.x += pos.x;
                    posBlock.y += pos.y;
                }
            }
        }
    }
    return posBlock;
}

CCPoint Game::addCoins(CCPoint oldPosition)
{
    CCPoint posBlock;
    posBlock.x += oldPosition.x;
    posBlock.y += oldPosition.y;
    
    float screenWidth = this->getContentSize().width;
    
    int maxBlock = BONUS + coinCounter;
    for(int i = BONUS; i < maxBlock; i++)
    {
        Coin* block = (Coin*)this->getChildByTag(i);
        if(!block->active)
        {
            int positionX;
            if(posBlock.x == 0.0f)
                //                        positionX = block->getContentSize().width +
                positionX = block->getContentSize().width + (rand() % (int)(screenWidth - block->getContentSize().width));
            else
            {
                positionX = block->getContentSize().width + posBlock.x;
            }
            block->active = true;
            CCPoint pos = block->getPosition();
            pos.x = positionX;
            pos.y = 0.0f - block->getContentSize().height;
            block->setPosition(pos);
            i = maxBlock;
            posBlock.x += pos.x;
            posBlock.y += pos.y;
        }
    }
    return posBlock;
}

#ifdef CC_TARGET_OS_MAC

void Game::keyDown(int key)
{
    if(key == 0 || key == 123)
    {
        this->moveLeft = true;
    }
    if(key == 2 || key == 124)
    {
        this->moveRight = true;
    }
    if(key == 49)
    {
        parachute = true;
    }
    if(key == 11)
    {
        this->restartGame = true;
    }
}

void Game::keyUp(int key)
{
    if(key == 0 || key == 123)
    {
        this->moveLeft = false;
    }
    if(key == 2 || key == 124)
    {
        this->moveRight = false;
    }
    if(key == 49)
    {
        parachute = false;
    }
}

#endif


#ifdef OUYA_BUILD

void Game::keyControllerPressed(int player, int keycode)
{
    if(keycode == 21)
    {
        this->moveLeft = true;
    }
    if(keycode == 22)
    {
        this->moveRight = true;
    }
    
    if(keycode == 105)
    {
        parachute = true;
    }
    
    if(keycode == 97)
    {
        this->restartGame = true;
    }
}

void Game::keyControllerReleased(int player, int keycode)
{
    if(keycode == 21)
    {
        this->moveLeft = false;
    }
    if(keycode == 22)
    {
        this->moveRight = false;
    }
    
    if(keycode == 105)
    {
        parachute = false;
    }
    
    if(keycode == 97)
    {
        this->restartGame = false;
    }
}

void Game::controllerMotion(int player, float LS_X, float LS_Y, float RS_X, float RS_Y)
{
    
}

#endif