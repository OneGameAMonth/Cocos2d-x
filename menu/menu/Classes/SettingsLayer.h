//
//  SettingsLayer.h
//  menu
//
//  Created by Martijn Thorig on 1/14/13.
//
//

#ifndef __menu__SettingsLayer__
#define __menu__SettingsLayer__

#include "cocos2d.h"

class SettingsLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(SettingsLayer);
    
    void backCallback(CCObject* pSender);
    
    void soundSwitchCallback(CCObject* pSender);
    
    void musicSwitchCallback(CCObject* pSender);
};

#endif /* defined(__menu__SettingsLayer__) */
