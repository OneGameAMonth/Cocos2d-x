//
//  bomb.cpp
//  Dropping2
//
//  Created by Martijn Thorig on 8/24/13.
//  Copyright (c) 2013 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Bomb.h"
#include "Parachute.h"

using namespace cocos2d;

#define DROPSPEED                   40.0f
#define MOVE_SIDE_WAYS_SPEED        15.0f
#define MOVE_SIDE_WAYS_SPEED_BONUS  1.0f
#define MOVE_DOWN_WAYS_SPEED        .50f

//Returns a pointer to new Ball instance.
Bomb* Bomb::create()
{
    //Create is virtual function from CCSprite
    Bomb *pSprite = new Bomb();
    if (pSprite && pSprite->initWithFile("bomb.png"))
    {
        // Set to autorelease
        pSprite->autorelease();
        
        //assign your attributes here!!
        pSprite->returnValue = false;
        pSprite->isInWater = false;
        pSprite->moveLeftSpeed = 0.0f;
        pSprite->moveRightSpeed = 0.0f;
        
        pSprite->block1 = 0;
        pSprite->block2 = 0;
        
        pSprite->posInWater = 0.0f;
        
        pSprite->state = BOMB_FALLING;
        
        pSprite->parachute = false;
        
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

bool Bomb::update(float dt, float screenHeight, float screenWidth, bool moveLeft, bool moveRight, CCLayer* parent)
{
    CCPoint pos = this->getPosition();
    oldPosition = pos;
    
    if(this->block1 == 0 && this->block2 == 0)
    {
        this->isInWater = false;
        this->posInWater = .10f;
        
        float parachuteBonus = 1.0f;
        if(this->parachute)
        {
            parachuteBonus = 0.5f;
        }
        
        pos.y -= ((DROPSPEED * dt) + moveDownSpeed) * parachuteBonus;
        moveDownSpeed += (MOVE_DOWN_WAYS_SPEED * dt);
        
        if(screenHeight < (pos.y - this->getContentSize().height))
        {
            returnValue = true;
            pos.x = 0.0f - this->getContentSize().width;
            pos.y = 0.0f - this->getContentSize().height;
        }
        if((pos.y + this->getContentSize().height / 2.0f) < 0.0f)
        {
            returnValue = true;
        }
    }
    else
    {
        this->parachute = false;
        CCSprite* block = NULL;
        
        if(block1 > 0)
        {
            block = (CCSprite*)parent->getChildByTag(block1);
            
            int* blockType = (int*)block->getUserData();
            
            if(*blockType == 0)
            {
                if(block2 > 0)
                {
                    CCSprite* block2_ = (CCSprite*)parent->getChildByTag(block2);
                    int* blockType2 = (int*)block2_->getUserData();
                    if(*blockType2 == 0)
                    {
                        isInWater = true;
                    }
                }
                else
                    isInWater = true;
            }
        }
        else if(block2 > 0)
        {
            block = (CCSprite*)parent->getChildByTag(block2);
        }
        float blockTop = block->getPosition().y + (block->getContentSize().height / 2.0f);
        blockTop += this->getContentSize().height / 2.0f;
        
        if(!this->isInWater)
        {
            this->posInWater = 0.0f;
            pos.y = blockTop - 1.0f;
        }
        else
        {
            pos.y = blockTop - this->posInWater;
            this->posInWater += 1.50f;
            if(this->posInWater > 28.0f)
                this->posInWater = 28.0f;
        }
    }
    
    if(moveLeft)
    {
        if(!this->isInWater)
        {
            pos.x -= (MOVE_SIDE_WAYS_SPEED * dt) + moveLeftSpeed;
            moveLeftSpeed += (MOVE_SIDE_WAYS_SPEED * dt);
            if(pos.x < (this->getContentSize().width/2.0f))
            {
                pos.x = this->getContentSize().width/2.0f;
            }
        }
        else
        {
            pos.x -= ((MOVE_SIDE_WAYS_SPEED/2.0f) * dt) + moveLeftSpeed;
            moveLeftSpeed += ((MOVE_SIDE_WAYS_SPEED/2.0f) * dt);
            if(pos.x < (this->getContentSize().width/2.0f))
            {
                pos.x = this->getContentSize().width/2.0f;
            }
        }
    }
    else
    {
        moveLeftSpeed = 0.0f;
    }
    
    if(moveRight)
    {
        if(!this->isInWater)
        {
            pos.x += (MOVE_SIDE_WAYS_SPEED * dt) + moveRightSpeed;
            moveRightSpeed += (MOVE_SIDE_WAYS_SPEED * dt);
            
            if(pos.x > (screenWidth) - (this->getContentSize().width/2.0f))
            {
                pos.x = (screenWidth) - (this->getContentSize().width/2.0f);
            }
        }
        else
        {
            pos.x += ((MOVE_SIDE_WAYS_SPEED/2.0f) * dt) + moveRightSpeed;
            moveRightSpeed += ((MOVE_SIDE_WAYS_SPEED/2.0f) * dt);
            
            if(pos.x > (screenWidth) - (this->getContentSize().width/2.0f))
            {
                pos.x = (screenWidth) - (this->getContentSize().width/2.0f);
            }
        }
    }
    else
    {
        moveRightSpeed = 0.0f;
    }
    
    this->setPosition(pos);

    this->block1 = 0;
    this->block2 = 0;
    
    return returnValue;
}