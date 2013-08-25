//
//  SGKeyboardEventHandlerMac.h
//  TheEpicQuest
//
//  Created by Martijn Thorig on 4/27/13.
//
//

#import <Foundation/Foundation.h>
#import "SGKeyboardEventListener.h"
#import <vector>

@interface SGKeyboardEventHandlerMac : NSObject
{
}

+ (SGKeyboardEventHandlerMac*) create;
+ (void)cleanup;
- (void)addToNotificationServer;
- (void)removeFromNotificationServer;

@end
