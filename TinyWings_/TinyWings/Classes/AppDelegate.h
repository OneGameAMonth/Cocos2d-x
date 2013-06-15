//
//  TinyWingsAppDelegate.h
//  TinyWings
//
//  Created by Martijn Thorig on 6/15/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
// Tutorial: http://www.raywenderlich.com/32954/how-to-create-a-game-like-tiny-wings-with-cocos2d-2-x-part-1

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"

/**
@brief    The cocos2d Application.

The reason to implement with private inheritance is to hide some interface details of CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function is called when the application enters the background
    @param  the pointer of the application instance
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function is called when the application enters the foreground
    @param  the pointer of the application instance
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

