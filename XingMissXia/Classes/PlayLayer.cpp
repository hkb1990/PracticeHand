//
//  PlayLayer.cpp
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//

#include "PlayLayer.h"
USING_NS_CC;

PlayLayer::PlayLayer()
{
}

PlayLayer::~PlayLayer()
{
}

bool PlayLayer::init()
{
    if(!BaseLayer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();

    MenuItemFont *back = MenuItemFont::create("back", CC_CALLBACK_1(PlayLayer::back, this));
    Menu *menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width*9/10, visibleSize.height*9/10);
    
    this->addChild(menu);
    
    startPlay();
    
    return true;
}

void PlayLayer::startPlay()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    edgeSp = Sprite::create();
    auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    boundBody->getShape(0)->setRestitution(1.0f);
    boundBody->getShape(0)->setFriction(0.0f);
    boundBody->getShape(0)->setDensity(1.0f);
    edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    edgeSp->setPhysicsBody(boundBody);
    this->addChild(edgeSp);
    edgeSp->setTag(0);
    
    ball = Sprite::create("CloseNormal.png", Rect(0, 0, 52, 52));
    ball->setPosition(100, 100);
    auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2.);
    ballBody->getShape(0)->setRestitution(1.0f);
    ballBody->getShape(0)->setFriction(0.0f);
    ballBody->getShape(0)->setDensity(1.0f);
    ballBody->setGravityEnable(false);
    Vect force = Vect(1000000.0f, 1000000.0f);
    ballBody->applyImpulse(force);
    ball->setPhysicsBody(ballBody);
    ball->setTag(1);
    this->addChild(ball);
    
    paddle = Sprite::create("paddle.png");
    auto paddleBody = PhysicsBody::createBox(paddle->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
    paddleBody->getShape(0)->setRestitution(1.0f);
    paddleBody->getShape(0)->setFriction(0.0f);
    paddleBody->getShape(0)->setDensity(10.0f);
    paddleBody->setGravityEnable(false);
    paddleBody->setDynamic(false);
    paddle->setPosition(visibleSize.width / 2, 50);
    paddle->setPhysicsBody(paddleBody);
    ball->setTag(2);
    this->addChild(paddle);
}

void PlayLayer::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PlayLayer::onContactBegin, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool PlayLayer::onTouchBegan(Touch *Touch, Event *Event)
{
    return true;
}

bool PlayLayer::onContactBegin(PhysicsContact& contact)
{
    return true;
}

void PlayLayer::onTouchMoved(Touch* touch, Event* event)
{
    Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
    paddle->setPositionX(touchLocation.x);
    
}

void PlayLayer::back(Ref* pSender)
{
    SceneManager::goMenu();
}