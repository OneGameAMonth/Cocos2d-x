#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
protected:
    cocos2d::CCSprite* _background;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    cocos2d::CCSprite* spriteWithColor(cocos2d::ccColor4F bgColor, float textureWidth, float textureHeight);
    
    cocos2d::CCSprite* stripedSpriteWithColor1(cocos2d::ccColor4F c1, cocos2d::ccColor4F c2, float textureWidth, float textureHeight, int nStripes);
    
    cocos2d::ccColor4F randomBrightColor();
    
    void update(float dt);
    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void genBackground();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
