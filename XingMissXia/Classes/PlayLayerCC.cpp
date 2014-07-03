//
//  PlayLayerCC.cpp
//  XingMissXia
//
//  Created by 邱涔佞 on 14-7-2.
//
//

#include "PlayLayerCC.h"
USING_NS_CC;

PlayLayerCC::PlayLayerCC()
{
    monsters = NULL;
    projectiles = NULL;
}

PlayLayerCC::~PlayLayerCC()
{
}


void PlayLayerCC::spriteMoveFinished(cocos2d::Node *sender)
{
    Sprite *sprite = (Sprite *)sender;
    this->removeChild(sprite);
    
    if (sprite->getTag() == 1) {
        monsters->removeObject(sprite);
    }
    else if (sprite->getTag() == 2)
    {
        projectiles->removeObject(sprite);
    }

}

void PlayLayerCC::addTarget()
{
    
    Sprite *target = Sprite::create("Target.png", Rect(0, 0, 27, 40));
    Size winSize = Director::getInstance()->getWinSize();
    int minY = target->getContentSize().height/2;
    int maxY = winSize.height-minY;
    int rangeY = maxY-minY;
    int actualY = rand() % rangeY + minY;
    target->setPosition(Point(winSize.width+target->getContentSize().width/2, actualY));
    this->addChild(target);
    
    int actualDuration = rand() % 2 + 2;
    FiniteTimeAction *actionMove = MoveTo::create(actualDuration, Point(0-target->getContentSize().width/2, actualY));
    //const std::function<void(Node*)> &func
    FiniteTimeAction *actionMoveDone = CallFuncN::create(std::bind(&PlayLayerCC::spriteMoveFinished, this, target));
    target->runAction(Sequence::create(actionMove,actionMoveDone, NULL));
    target->setTag(1);
    monsters->addObject(target);
}

bool PlayLayerCC::init()
{
    if(!BaseLayer::init())
    {
        return false;
    }
    this->removeAllChildren();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MenuItemFont *back = MenuItemFont::create("back", CC_CALLBACK_1(PlayLayerCC::back, this));
    Menu *menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width*9/10, visibleSize.height*9/10);
    
    this->addChild(menu);
    
    LayerColor *layer1 = LayerColor::create(Color4B(255, 255, 255, 255));
    layer1->ignoreAnchorPointForPosition(false);
    layer1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    BlendFunc bf = {GL_ONE_MINUS_DST_COLOR, GL_ZERO}; //这里定义背景的颜色
    layer1->setBlendFunc(bf);
    
    this->addChild(layer1);
    
    playerCC = Sprite::create("Player.png");
    playerCC->setPosition(visibleSize.width/2,20);
    
    this->addChild(playerCC);

    
    this->setTouchEnabled(true);
    this->scheduleUpdate();

    this->monsters = Array::create();
    this->monsters->retain();
    
    this->projectiles = Array::create();
    this->projectiles->retain();
    
    this->schedule(schedule_selector(PlayLayerCC::gameLogic),1.0);
    this->schedule(schedule_selector(PlayLayerCC::update));
    
    return true;
}

void PlayLayerCC::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    
    Touch* touch = touches.front();
    Point location = this->convertTouchToNodeSpace(touch);
    
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite* projectile = Sprite::create("Projectile.png");
    projectile->setScale(2);
    
    projectile->setPosition(Point(winSize.width/2,20));
    Point offset = ccpSub(location, projectile->getPosition());
    int offX = location.x - projectile->getContentSize().width;
    int offY = location.y - projectile->getContentSize().height;
    if(offY<0){
        offY=-offY;
    }
    this->addChild(projectile);
    
    int realX = winSize.width + projectile->getContentSize().width / 2;
    float ratio = (float)offset.y / (float)offset.x;
    if(ratio<0){
        ratio=-ratio;
    }
    int realY = realX * ratio + projectile->getPosition().y;
    Point realDest = Point(realX, realY);
    
    int offRealX = realX - projectile->getPosition().x;
    int offRealY = realY - projectile->getPosition().y;
    float length = sqrtf(offRealX * offRealX + offRealY * offRealY);
    float velocity = sqrtf(winSize.width/2*winSize.width/2 +winSize.height/2*winSize.height/2)/1;
    
    float realMoveDuration = length / velocity;
    
    projectile->runAction(Sequence::create(MoveTo::create(realMoveDuration, realDest),CallFuncN::create(std::bind(&PlayLayerCC::spriteMoveFinished, this,projectile)), NULL));
    projectile->setTag(2);
    projectiles->addObject(projectile);
}

void PlayLayerCC::gameLogic(float dt) {
    addTarget();
}

void PlayLayerCC::back(Ref* pSender)
{
    SceneManager::goMenu();
}

void PlayLayerCC::update(float delta)
{
    Array *projectilesToDelete = Array::create();
    
    Object *pObject = NULL;
    Object *pObject2 = NULL;
    
    CCARRAY_FOREACH(projectiles, pObject)
    {
        Sprite *projectile = (Sprite *)pObject;
        Array *monstersToDelete = Array::create();
        
        CCARRAY_FOREACH(monsters, pObject2)
        {
            Sprite *target = (Sprite *)pObject2;
            if (projectile->getBoundingBox().intersectsRect(target->getBoundingBox())) {
                monstersToDelete->addObject(target);
            }
        }
        
        CCARRAY_FOREACH(monstersToDelete, pObject2)
        {
            Sprite *target = (Sprite *)pObject2;
            monsters->removeObject(target);
            this->removeChild(target);
        }
        
        if (monstersToDelete->count() > 0) {
            projectilesToDelete->addObject(projectile);
        }
//        monstersToDelete->release();
    }
    
    CCARRAY_FOREACH(projectilesToDelete, pObject)
    {
        Sprite *projectile = (Sprite *)pObject;
        projectiles->removeObject(projectile);
        this->removeChild(projectile);
    }
    
//    projectilesToDelete->release();
}
