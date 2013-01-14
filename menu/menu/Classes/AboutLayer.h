//
//  AboutLayer.h
//  menu
//
//  Created by Martijn Thorig on 1/14/13.
//
//

#ifndef __menu__AboutLayer__
#define __menu__AboutLayer__

#include "cocos2d.h"

class AboutLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(AboutLayer);
    
    void backCallback(CCObject* pSender);
};

#endif /* defined(__menu__AboutLayer__) */
