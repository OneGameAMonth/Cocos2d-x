#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"

#include "Bomb.h"
#include "Earth.h"
#include "Water.h"
#include "Parachute.h"
#include "Coin.h"

#include <vector>

using namespace std;

#ifdef CC_TARGET_OS_MAC
#include "SGKeyboardEventListener.h"
#endif

class Game : public cocos2d::CCLayer
#ifdef CC_TARGET_OS_MAC
, public SGKeyboardEventListener
#endif
{
private:
    
public:
    int blockCounter;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(Game);
    
    bool moveLeft;
    bool moveRight;
    bool parachute;
    
    bool restartGame;
    
    int gameState;
    
    float addBlockCounter;
    float addCoinCounter;
    
    int coinCounter;
    
    int coinCounterPlayer;
    
    virtual void update(float);
    
    virtual void generateBlocks();
    
    virtual void generateCoins();
    
    virtual cocos2d::CCPoint addBlocks(cocos2d::CCPoint);
    virtual cocos2d::CCPoint addCoins(cocos2d::CCPoint);
    
#ifdef CC_TARGET_OS_MAC
    virtual void keyDown(int key);
    virtual void keyUp(int key);
#endif
#ifdef OUYA_BUILD
    void controllerMotion(int player, float LS_X, float LS_Y, float RS_X, float RS_Y);
    void keyControllerReleased(int player, int keycode);
    void keyControllerPressed(int player, int keycode);
#endif
};

#endif // __Game_SCENE_H__
