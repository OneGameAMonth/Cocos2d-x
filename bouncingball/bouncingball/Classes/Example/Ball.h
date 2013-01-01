//
//  Ball.h
//  bouncingball
//
//  Created by Martijn Thorig on 1/1/13.
//
//

#ifndef __bouncingball__Ball__
#define __bouncingball__Ball__

#include "cocos2d.h"

using namespace cocos2d;

namespace example
{
    class Ball : public CCSprite
    {
    protected:
        //The traveling speed of the ball on the horizontal line.
        float velocityX;
        
        //The traveling speed of the ball on the vertical line.
        float velocityY;
        
        //The angle the ball is traveling in.
        float angle;
        
        //The angle in radians the ball is traveling in.
        float angleRad;
        
        //The speed the ball is traveling in ( pixels per update :P ).
        float speed;
        
    public:
        //Constructor
        Ball();
        
        //Destructor
        ~Ball();
        
        //Returns a pointer to new Ball instance.
        static Ball* create(const char *pszFileName);
        
        //Called for updating the position.
        virtual void update(float dt, float screenWidth, float screenHeight);
        
        //Set a new angle where the ball be traveling in.
        virtual void setAngle(float pAngle);
        
        //Bouncing against a vertical line.
        virtual void verticalBounce(float pAngle);
        
        //Bouncing against a horizontal line.
        virtual void horizontalBounce(float pAngle);
        
        //Shared bouncing function
        virtual void bouncing(float pAngle);
        
        //Increase the speek the ball is traveling in.
        virtual void addSpeed(float extraSpeed);
    };
}

#endif /* defined(__bouncingball__Ball__) */
