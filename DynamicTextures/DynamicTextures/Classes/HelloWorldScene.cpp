#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    //Add a background
    ccColor4F bgColor = this->randomBrightColor();
    ccColor4F color2 = this->randomBrightColor();
    int nStripes = ((arc4random() % 4) + 1) * 2;
    
    _background = this->stripedSpriteWithColor1(bgColor, color2, 512, 512, nStripes);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _background->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    this->addChild(_background, -1);
    
    genBackground();
    
    //Enable touch
    this->setTouchEnabled(true);
    
    //60 fps callback
    this->getScheduler()->scheduleSelector(schedule_selector(HelloWorld::update), this, 1.0f/60.0f, false);
    
    return true;
}


//This is the old function
cocos2d::CCSprite* HelloWorld::spriteWithColor(cocos2d::ccColor4F bgColor, float textureWidth, float textureHeight)
{
    // 1: Create new CCRenderTexture
    CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);
    
    // 2: Call CCRenderTexture:begin
    rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    
    CC_NODE_DRAW_SETUP();
    
    // 3: Draw into the texture
    float gradientAlpha = 0.7f;
    CCPoint vertices[4];
    ccColor4F colors[4];
    int nVertices = 0;
    
    vertices[nVertices] = ccp(0, 0);
    colors[nVertices++] = (ccColor4F){0, 0, 0, 0 };
    vertices[nVertices] = ccp(textureWidth, 0);
    colors[nVertices++] = (ccColor4F){0, 0, 0, 0};
    vertices[nVertices] = ccp(0, textureHeight);
    colors[nVertices++] = (ccColor4F){0, 0, 0, gradientAlpha};
    vertices[nVertices] = ccp(textureWidth, textureHeight);
    colors[nVertices++] = (ccColor4F){0, 0, 0, gradientAlpha};
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position  | kCCVertexAttribFlag_Color);
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
    
    CCSprite *noise = CCSprite::create("Noise.png");
    ccBlendFunc bf = {GL_DST_COLOR, GL_ZERO};
    noise->setBlendFunc(bf);
    noise->setPosition(ccp(textureWidth/2, textureHeight/2));
    noise->visit();
    
    // 4: Call CCRenderTexture:end
    rt->end();
    
    // 5: Create a new Sprite from the texture
    return CCSprite::createWithTexture(rt->getSprite()->getTexture());    
}

cocos2d::CCSprite* HelloWorld::stripedSpriteWithColor1(cocos2d::ccColor4F c1, cocos2d::ccColor4F c2, float textureWidth, float textureHeight, int nStripes)
{
    // 1: Create new CCRenderTexture
    CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);
    
    // 2: Call CCRenderTexture:begin
    rt->beginWithClear(c1.r, c1.g, c1.b, c1.a);
    
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    
    // 3: Draw into the texture
    
    // Layer 1: Stripes
    CCPoint* vertices = new CCPoint[nStripes*6];
    ccColor4F colors[nStripes*6];
    
    int nVertices = 0;
    float x1 = -textureHeight;
    float x2;
    float y1 = textureHeight;
    float y2 = 0;
    float dx = textureWidth / nStripes * 2;
    float stripeWidth = dx/2;
    
    for (int i=0; i<nStripes; i++)
    {
        x2 = x1 + textureHeight;
        
        vertices[nVertices] = ccp(x1, y1);
        colors[nVertices++] = (ccColor4F){c2.r, c2.g, c2.b, c2.a};
        
        vertices[nVertices] = ccp(x1+stripeWidth, y1);
        colors[nVertices++] = (ccColor4F){c2.r, c2.g, c2.b, c2.a};
        
        vertices[nVertices] = ccp(x2, y2);
        colors[nVertices++] = (ccColor4F){c2.r, c2.g, c2.b, c2.a};
        
        vertices[nVertices] = vertices[nVertices-2];
        colors[nVertices++] = (ccColor4F){c2.r, c2.g, c2.b, c2.a};
        
        vertices[nVertices] = vertices[nVertices-2];
        colors[nVertices++] = (ccColor4F){c2.r, c2.g, c2.b, c2.a};
        
        vertices[nVertices] = ccp(x2+stripeWidth, y2);
        colors[nVertices++] = (ccColor4F){c2.r, c2.g, c2.b, c2.a};
        x1 += dx;
    }
    
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    
    // Layer 2: Noise
    CCSprite *noise = CCSprite::create("Noise.png");
    ccBlendFunc bf = {GL_DST_COLOR, GL_ZERO};
    noise->setBlendFunc(bf);
    noise->setPosition(ccp(textureWidth/2, textureHeight/2));
    noise->visit();
    
    // Layer 3: Stripes
    CC_NODE_DRAW_SETUP();
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
    
    float gradientAlpha = 0.7;
    
    nVertices = 0;
    
    vertices[nVertices] = ccp(0, 0);
    colors[nVertices++] = (ccColor4F){0, 0, 0, 0};
    
    vertices[nVertices] = ccp(textureWidth, 0);
    colors[nVertices++] = (ccColor4F){0, 0, 0, 0};
    
    vertices[nVertices] = ccp(0, textureHeight);
    colors[nVertices++] = (ccColor4F){0, 0, 0, gradientAlpha};
    
    vertices[nVertices] = ccp(textureWidth, textureHeight);
    colors[nVertices++] = (ccColor4F){0, 0, 0, gradientAlpha};
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
    
    // layer 3: top highlight
    float borderHeight = textureHeight/16;
    float borderAlpha = 0.3f;
    nVertices = 0;
    
    vertices[nVertices] = ccp(0, 0);
    colors[nVertices++] = (ccColor4F){1, 1, 1, borderAlpha};
    
    vertices[nVertices] = ccp(textureWidth, 0);
    colors[nVertices++] = (ccColor4F){1, 1, 1, borderAlpha};
    
    vertices[nVertices] = ccp(0, borderHeight);
    colors[nVertices++] = (ccColor4F){0, 0, 0, 0};
    
    vertices[nVertices] = ccp(textureWidth, borderHeight);
    colors[nVertices++] = (ccColor4F){0, 0, 0, 0};
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
    
    // 4: Call CCRenderTexture:end
    rt->end();
    
    delete[] vertices;
    
    // 5: Create a new Sprite from the texture
    return CCSprite::createWithTexture(rt->getSprite()->getTexture());
}

ccColor4F HelloWorld::randomBrightColor()
{
    ccColor4B randomColor;
    bool stop = false;
    
    while (!stop)
    {
        float requiredBrightness = 192;
        randomColor =
        ccc4(arc4random() % 255,
             arc4random() % 255,
             arc4random() % 255,
             255);
        if (randomColor.r > requiredBrightness ||
            randomColor.g > requiredBrightness ||
            randomColor.b > requiredBrightness)
        {
            stop = true;
        }
    }
    
    return ccc4FFromccc4B(randomColor);
}

void HelloWorld::genBackground()
{
    _background->removeFromParentAndCleanup(true);
    
    ccColor4F bgColor = this->randomBrightColor();
    ccColor4F color2 = this->randomBrightColor();
    int nStripes = ((arc4random() % 4) + 1) * 2;
    
    _background = this->stripedSpriteWithColor1(bgColor, color2, 512, 512, nStripes);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _background->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    _background->getTexture()->setTexParameters(&tp);
    
    this->addChild(_background, -1);
}

/* Old genBackground()
void HelloWorld::genBackground()
{
    _background->removeFromParentAndCleanup(true);
    
    ccColor4F bgColor = this->randomBrightColor();
    
    _background = this->spriteWithColor(bgColor, 512, 512);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _background->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    this->addChild(_background, -1);
}
*/

void HelloWorld::update(float dt)
{
    float PIXELS_PER_SECOND = 100;
    static float offset = 0;
    offset += PIXELS_PER_SECOND * dt;
    
    CCSize textureSize = _background->getTextureRect().size;
    
    _background->setTextureRect(CCRectMake(offset, 0, textureSize.width, textureSize.height));
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    this->genBackground();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
