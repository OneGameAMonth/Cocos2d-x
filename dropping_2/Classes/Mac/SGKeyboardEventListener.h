//
//  SGKeyboardEventListener.h
//  TheEpicQuest
//
//  Created by Martijn Thorig on 4/27/13.
//
//

#ifndef __TheEpicQuest__SGKeyboardEventListener__
#define __TheEpicQuest__SGKeyboardEventListener__

#include <vector>

    class SGKeyboardEventListener
    {
    public:
        
        virtual void keyDown(int key) = 0;
        virtual void keyUp(int key) = 0;
        
        virtual void addListener(SGKeyboardEventListener* listener);
        virtual void removeListener();
    };

#endif /* defined(__TheEpicQuest__SGKeyboardEventListener__) */
