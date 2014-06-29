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
    
    m_pJoystick = Sprite::create("joystick.png");
    m_pJoystickBg = Sprite::create("joystick_bg.png");
    this->addChild(m_pJoystickBg, 0);
    this->addChild(m_pJoystick, 1);
    
    this->hideJoystick();
}

void PlayLayer::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    //listener->setSwallowTouches(true);
    
    listener->onTouchesBegan = CC_CALLBACK_2(PlayLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(PlayLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(PlayLayer::onTouchesEnded, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PlayLayer::onContactBegin, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void PlayLayer::showJoystick(Point pos)
{
	m_pJoystick->setPosition(pos);
	m_pJoystickBg->setPosition(pos);
    
	m_pJoystick->setVisible(true);
	m_pJoystickBg->setVisible(true);
}

void PlayLayer::hideJoystick()
{
	m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	m_pJoystickBg->setVisible(false);
}

void PlayLayer::updateJoystick(Point direction, float distance)
{
	Point start = m_pJoystickBg->getPosition();
    
	if(distance < 33)
	{
		m_pJoystick->setPosition(start + (direction * distance));
	}else if(distance > 78) {
		m_pJoystick->setPosition(start + (direction * 45));
	}else {
		m_pJoystick->setPosition(start + (direction * 33));
	}
}

bool PlayLayer::onContactBegin(PhysicsContact& contact)
{
    return true;
}

void PlayLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	Size winSize = Director::getInstance()->getWinSize();
	Vector<Touch*>::const_iterator touchIter = touches.begin();
	while(touchIter != touches.end())
	{
		Touch *pTouch = (Touch*)(*touchIter);
		Point p = pTouch->getLocation();
		if(p.x <= winSize.width / 2)
		{
			this->showJoystick(p);
		}else {
			//m_pHero->attack();
		}
        
		++ touchIter;
	}
}

void PlayLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    Size winSize = Director::getInstance()->getWinSize();
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch *pTouch = (Touch*)(*touchIter);
	Point start = pTouch->getStartLocation();
	if(start.x > winSize.width / 2)
	{
		return;
	}
	Point dest = pTouch->getLocation();
	float distance = start.getDistance(dest);
	Point direction = (dest - start).normalize();
	this->updateJoystick(direction, distance);

    //Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(pTouch));
    //paddle->setPositionX(touchLocation.x);
    
    Vect force = Vect(10000.0f * direction.x, 10000.0f * direction.y);
    ball->getPhysicsBody()->applyImpulse(force);
}

void PlayLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
	this->hideJoystick();
}

void PlayLayer::back(Ref* pSender)
{
    SceneManager::goMenu();
}