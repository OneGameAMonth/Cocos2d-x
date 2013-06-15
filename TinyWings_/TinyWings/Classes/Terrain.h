//
//  Terrain.h
//  TinyWings
//
//  Created by Martijn Thorig on 6/15/13.
//
//
// Tutorial: http://www.raywenderlich.com/32954/how-to-create-a-game-like-tiny-wings-with-cocos2d-2-x-part-1

#ifndef __TinyWings__Terrain__
#define __TinyWings__Terrain__

#include "cocos2d.h"

using namespace cocos2d;

class Terrain : public cocos2d::CCNode
{
protected:
    int _offsetX;
    cocos2d::CCPoint* _hillKeyPoints;
    int _fromKeyPointI;
    int _toKeyPointI;
    
    int _nHillVertices;
    CCPoint* _hillVertices;
    CCPoint* _hillTexCoords;
    int _nBorderVertices;
    CCPoint* _borderVertices;
    
public:
    cocos2d::CCSprite* stripes;
    
    Terrain();
    ~Terrain();
    void setOffsetX(float newOffsetX);
    void generateHills();
    void resetHillVertices();
    void draw();
};

#endif /* defined(__TinyWings__Terrain__) */
