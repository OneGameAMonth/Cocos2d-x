//
//  SGKeyboardEventHandlerMac.m
//  TheEpicQuest
//
//  Created by Martijn Thorig on 4/27/13.
//
//

#import "SGKeyboardEventHandlerMac.h"
#import "cocos2d.h"

SGKeyboardEventHandlerMac* singletonKeyboardEventHandler;

extern std::vector<SGKeyboardEventListener*> listeners;

@implementation SGKeyboardEventHandlerMac

//create and add to the notification server
+ (SGKeyboardEventHandlerMac*) create
{
    if(!([singletonKeyboardEventHandler isKindOfClass:[SGKeyboardEventHandlerMac class]]))
    {
        singletonKeyboardEventHandler = [[SGKeyboardEventHandlerMac alloc] init];
        [singletonKeyboardEventHandler addToNotificationServer];
    }
    
    return singletonKeyboardEventHandler;
}

//Remove from the notification server
+ (void) cleanup
{
    if(([singletonKeyboardEventHandler isKindOfClass:[SGKeyboardEventHandlerMac class]]))
    {
        [singletonKeyboardEventHandler removeFromNotificationServer];
        [singletonKeyboardEventHandler release];
        singletonKeyboardEventHandler = nil;
    }
}

// add to the notification server
- (void)addToNotificationServer
{
    NSString* name = [[NSString alloc] initWithCString:"SGKeyDown" encoding:NSUTF8StringEncoding];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyDown:)
                                                 name:name object:nil];
    
    name = [[NSString alloc] initWithCString:"SGKeyUp" encoding:NSUTF8StringEncoding];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyUp:)
                                                 name:name object:nil];
}

//Remove from the notification server
- (void)removeFromNotificationServer
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

//The key down notification
- (void)keyDown:(NSNotification *)notification
{
#ifdef CC_TARGET_OS_MAC
    NSDictionary *userInfo = notification.userInfo;
    NSEvent *event = [userInfo objectForKey:@"event"];
    
    cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
    cocos2d::CCScene *scene = pDirector->getRunningScene();
    
    if(scene && listeners.size() > 0)
    {
        SGKeyboardEventListener* listener = listeners[0];
        listener->keyDown([event keyCode]);
    }
#endif
}

//The key up notification
- (void)keyUp:(NSNotification *)notification
{
#ifdef CC_TARGET_OS_MAC
    NSDictionary *userInfo = notification.userInfo;
    NSEvent *event = [userInfo objectForKey:@"event"];
    
    cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
    cocos2d::CCScene *scene = pDirector->getRunningScene();
    
    if(scene && listeners.size() > 0)
    {
        SGKeyboardEventListener* listener = listeners[0];
        listener->keyUp([event keyCode]);
    }
#endif
}

@end

//Add the client to the SGKeyboardEventHandler for Mac
void SGKeyboardEventListener::addListener(SGKeyboardEventListener* listener)
{
    listeners.push_back(listener);
}

//Remove the client to the SGKeyboardEventHandler for Mac
void SGKeyboardEventListener::removeListener()
{
    listeners.clear();
}


//EOF