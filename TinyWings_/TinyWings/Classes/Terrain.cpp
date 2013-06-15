//
//  Terrain.cpp
//  TinyWings
//
//  Created by Martijn Thorig on 6/15/13.
//
//
// Tutorial: http://www.raywenderlich.com/32954/how-to-create-a-game-like-tiny-wings-with-cocos2d-2-x-part-1

#include "Terrain.h"

using namespace cocos2d;

#define kMaxHillKeyPoints 1000
#define kHillSegmentWidth 10
#define kMaxHillVertices 4000
#define kMaxBorderVertices 800

Terrain::Terrain()
{
    _hillKeyPoints = new CCPoint[kMaxHillKeyPoints];
    _hillVertices = new CCPoint[kMaxHillVertices];
    _hillTexCoords = new CCPoint[kMaxHillVertices];
    _borderVertices = new CCPoint[kMaxBorderVertices];
    
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
    
    generateHills();
    resetHillVertices();
}

Terrain::~Terrain()
{
    delete[] _hillKeyPoints;
    delete stripes;
    delete[] _hillVertices;
    delete[] _hillTexCoords;
    delete[] _borderVertices;
}
/*
 void Terrain::generateHills()
 {
 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 float x = 0;
 float y = winSize.height / 2;
 for(int i = 0; i < kMaxHillKeyPoints; ++i)
 {
 _hillKeyPoints[i] = ccp(x, y);
 x += winSize.width/2;
 y = (random() % (int) winSize.height);
 }
 
 }
 */
void Terrain::generateHills()
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    float minDX = 160;
    float minDY = 60;
    int rangeDX = 80;
    int rangeDY = 40;
    
    float x = -minDX;
    float y = winSize.height/2;
    
    float dy, ny;
    float sign = 1; // +1 - going up, -1 - going  down
    float paddingTop = 20;
    float paddingBottom = 20;
    
    for (int i = 0; i < kMaxHillKeyPoints; i++)
    {
        _hillKeyPoints[i] = ccp(x, y);
        if (i == 0)
        {
            x = 0;
            y = winSize.height/2;
        }
        else
        {
            x += rand()%rangeDX+minDX;
            while(true)
            {
                dy = rand()%rangeDY+minDY;
                ny = y + dy*sign;
                if(ny < winSize.height-paddingTop && ny > paddingBottom)
                {
                    break;
                }
            }
            y = ny;
        }
        sign *= -1;
    }
}

void Terrain::setOffsetX(float newOffsetX)
{
    _offsetX = newOffsetX;
    this->setPosition(ccp(-_offsetX * this->getScale(), 0.0f));
    this->resetHillVertices();
}

void Terrain::resetHillVertices()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    static int prevFromKeyPointI = -1;
    static int prevToKeyPointI = -1;
    
    // key points interval for drawing
    while (_hillKeyPoints[_fromKeyPointI+1].x < _offsetX-winSize.width/8/this->getScale())
    {
        _fromKeyPointI++;
    }
    while (_hillKeyPoints[_toKeyPointI].x < _offsetX+winSize.width*12/8/this->getScale())
    {
        _toKeyPointI++;
    }
    
    float minY = 0;
    if (winSize.height > 480) {
        minY = (1136 - 1024)/4;
    }
    if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI) {
        
        // vertices for visible area
        _nHillVertices = 0;
        _nBorderVertices = 0;
        CCPoint p0, p1, pt0, pt1;
        p0 = _hillKeyPoints[_fromKeyPointI];
        for (int i=_fromKeyPointI+1; i<_toKeyPointI+1; i++)
        {
            p1 = _hillKeyPoints[i];
            
            // triangle strip between p0 and p1
            int hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
            float dx = (p1.x - p0.x) / hSegments;
            float da = M_PI / hSegments;
            float ymid = (p0.y + p1.y) / 2;
            float ampl = (p0.y - p1.y) / 2;
            pt0 = p0;
            _borderVertices[_nBorderVertices++] = pt0;
            for (int j = 1; j < hSegments+1; j++)
            {
                pt1.x = p0.x + j*dx;
                pt1.y = ymid + ampl * cosf(da*j);
                _borderVertices[_nBorderVertices++] = pt1;
                
                _hillVertices[_nHillVertices] = ccp(pt0.x, 0 + minY);
                _hillTexCoords[_nHillVertices++] = ccp(pt0.x/512, 1.0f);
                _hillVertices[_nHillVertices] = ccp(pt1.x, 0 + minY);
                _hillTexCoords[_nHillVertices++] = ccp(pt1.x/512, 1.0f);
                
                _hillVertices[_nHillVertices] = ccp(pt0.x, pt0.y);
                _hillTexCoords[_nHillVertices++] = ccp(pt0.x/512, 0);
                _hillVertices[_nHillVertices] = ccp(pt1.x, pt1.y);
                _hillTexCoords[_nHillVertices++] = ccp(pt1.x/512, 0);
                
                pt0 = pt1;
            }
            
            p0 = p1;
        }
        
        prevFromKeyPointI = _fromKeyPointI;
        prevToKeyPointI = _toKeyPointI;
    }
}

void Terrain::draw()
{
    CC_NODE_DRAW_SETUP();
    
    ccGLBindTexture2D(stripes->getTexture()->getName());
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
    
    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, _hillVertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, _hillTexCoords);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);
    /*
    Draw extra lines. This is not really needed for the end result.
     
    for(int i = MAX(_fromKeyPointI, 1); i <= _toKeyPointI; ++i)
    {
        ccDrawColor4F(1.0, 0, 0, 1.0);
        ccDrawLine(_hillKeyPoints[i-1], _hillKeyPoints[i]);
     
        ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
        
        CCPoint p0 = _hillKeyPoints[i-1];
        CCPoint p1 = _hillKeyPoints[i];
        int hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
        float dx = (p1.x - p0.x) / hSegments;
        float da = M_PI / hSegments;
        float ymid = (p0.y + p1.y) / 2;
        float ampl = (p0.y - p1.y) / 2;
        
        CCPoint pt0, pt1;
        pt0 = p0;
        
        for (int j = 0; j < hSegments+1; ++j)
        {
            pt1.x = p0.x + j*dx;
            pt1.y = ymid + ampl * cosf(da*j);
            //ccDrawLine(pt0, pt1);
            pt0 = pt1;
        }
    }
    */
}

//EOF