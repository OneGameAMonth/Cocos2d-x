//
//  Block.h
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef __Dropping2__Block__
#define __Dropping2__Block__

#define DEFAULT_SPEED 50.0f

class Block
{
public:
    int typeBlock;
    
    bool active;
    
    virtual void update(float, float) = 0;
};

#endif /* defined(__Dropping2__Block__) */
