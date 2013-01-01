//
//  Ball.cpp
//  bouncingball
//
//  Created by Martijn Thorig on 1/1/13.
//
//

#include "Ball.h"

#include "Ball.h"

#include <tr1/random>
#include <tr1/functional>
#include <algorithm>
#include <stdint.h>
#include <ctime>

using namespace example;

#define speedMin 5.0f
#define defaultAngle 30.0f

//Constructor
Ball::Ball()
{
    //Set the default values
    this->speed = speedMin;
    this->angle = defaultAngle;
    
    
    //Using the random implementation from C++11
    std::tr1::uniform_int<int> distribution(-defaultAngle, defaultAngle);
    std::tr1::mt19937 engine; // Mersenne twister MT19937
    
    clock_t t;
    t = clock();
    
    engine.seed((float)t);
    
    int angleTmp = distribution(engine);
    
    //Set the new angle
    this->angle = (float)angleTmp;
    
    //Correct the angle if the angle is below 0
    if(angleTmp < 0)
        this->angle = 360.0f + (float)angleTmp;
    
    //Calculate the angle in radians
    this->angleRad = this->angle * M_PI/180.0f;
    
    //Calculate the new velocity for the two axis
    this->velocityX = cos(this->angleRad) * this->speed;
    this->velocityY = sin(this->angleRad) * this->speed;
}

//Destructor
Ball::~Ball()
{
    //Nothing to do, since there are only floats as attributes
}

//Returns a pointer to new Ball instance.
Ball* Ball::create(const char *pszFileName)
{
    //Create is virtual function from CCSprite
    Ball *pSprite = new Ball();
    if (pSprite && pSprite->initWithFile(pszFileName))
    {
        // Set to autorelease
        pSprite->autorelease();
        
        //assign your attributes here!!
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

//Called for updating the position.
void Ball::update(float dt, float screenWidth, float screenHeight)
{
    //Get the current position of the ball
    CCPoint position = getPosition();
    
    //Update the position of the ball
    position.x += velocityX;
    position.y += velocityY;
    
    //Check if the ball bounces against the vertical border of the field
    if(position.x < 0.0f || position.x > screenWidth)
    {
        verticalBounce(-90.0f);
    }
    //Check if the ball bounces against the horizontal border of the field
    if(position.y < 0.0f || position.y > screenHeight)
    {
        horizontalBounce(-90.0f);
    }
    
    //Make sure the centre of the ball is not going beyond the border of the field
    if(position.y < 0.0f)
    {
        position.y = 0.0f;
    }
    if(position.x < 0.0f)
    {
        position.x = 0.0f;
    }
    if(position.y > screenHeight)
    {
        position.y = screenHeight;
    }
    if(position.x > screenWidth)
    {
        position.x = screenWidth;
    }
    
    //Set the new position for the ball
    setPosition(position);
}

//Set a new angle where the ball be traveling in.
void Ball::setAngle(float pAngle)
{
    angle = pAngle;
}

//Bouncing against a vertical line.
void Ball::verticalBounce(float pAngle)
{
    if(angle == 0.0f || angle == 180.0f)
        angle += -180.0f;
    else
        angle = 180.0f - angle;
    
    bouncing(angle);
}

//Bouncing against a horizontal line.
void Ball::horizontalBounce(float pAngle)
{
    if(angle == 0.0f || angle == 180.0f)
        angle += -180.0f;
    else
        angle = 360.0f - angle;
    
    bouncing(angle);
}

//Shared bouncing function
void Ball::bouncing(float pAngle)
{
    if(angle < 0.0f) angle += 360.0f;
    if(angle > 360.0f) angle -= 360.0f;
    
    this->angleRad = this->angle * M_PI/180.0f;
    this->velocityX = cos(this->angleRad) * this->speed;
    this->velocityY = sin(this->angleRad) * this->speed;
}

//Increase the speed the ball is traveling in.
void Ball::addSpeed(float extraSpeed)
{
    speed += extraSpeed;
}
