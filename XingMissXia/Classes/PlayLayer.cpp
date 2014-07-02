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

    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("UI.plist", "UI.png");

    mJoystick = NULL;
    mJoystick = new SneakyJoystick();
    mJoystick->initWithRect(Rect::ZERO);
    mJoystick->setAutoCenter(true);
    mJoystick->setHasDeadzone(true);
    mJoystick->setDeadRadius(10);
    SneakyJoystickSkinnedBase* jstickSkin = new SneakyJoystickSkinnedBase();
    jstickSkin->autorelease();
    jstickSkin->init();
    jstickSkin->setBackgroundSprite(CCSprite::createWithSpriteFrameName("JoyStick-base.png"));
    jstickSkin->setThumbSprite(CCSprite::createWithSpriteFrameName("JoyStick-thumb.png"));
    //jstickSkin->getThumbSprite()->setScale(0.5f);
    jstickSkin->setPosition(visibleSize.width*1/10, visibleSize.width*1/10);
    jstickSkin->setJoystick(mJoystick);
    this->addChild(jstickSkin);

    mButtonA = NULL;
    mButtonA = new SneakyButton();
    mButtonA->initWithRect(Rect::ZERO);
    mButtonA->setIsToggleable(false);
    mButtonA->setIsHoldable(true);
    SneakyButtonSkinnedBase* btnASkin = new SneakyButtonSkinnedBase();
    btnASkin->autorelease();
    btnASkin->init();
    btnASkin->setPosition(visibleSize.width*9/10, visibleSize.width*1/10);
    btnASkin->setDefaultSprite(CCSprite::createWithSpriteFrameName("button-default.png"));
    btnASkin->setPressSprite(CCSprite::createWithSpriteFrameName("button-pressed.png"));
    btnASkin->setActivatedSprite(CCSprite::createWithSpriteFrameName("button-activated.png"));
    //btnASkin->setDisabledSprite(CCSprite::createWithSpriteFrameName("button-disabled.png"));
    btnASkin->setButton(mButtonA);
    this->addChild(btnASkin);

    this->schedule(schedule_selector(PlayLayer::inputUpdate));

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
}


void PlayLayer::inputUpdate(float dt)
{
    Point velocity = mJoystick->getVelocity();
    //std::cout << velocity.x << std::endl;

    if (velocity.x >= 0.4f || velocity.x <= -0.4f ||
            velocity.y >= 0.4f || velocity.y <= -0.4f) {
        Vect force = Vect(10000.0f * velocity.x, 10000.0f * velocity.y);
        ball->getPhysicsBody()->applyImpulse(force);
        Point p = paddle->getPosition();
        float s = p.x + velocity.x * 5;
        if(s < 0)
            s = 0;
        else if (s > Director::getInstance()->getVisibleSize().width)
            s = Director::getInstance()->getVisibleSize().width;
        else{
            s = s;
        }
        paddle->setPositionX(s);
    }
    if(mButtonA->getIsActive()){
        ball->setPosition(100,100);
    }
}

void PlayLayer::onEnter()
{
    Layer::onEnter();
}

bool PlayLayer::onContactBegin(PhysicsContact& contact)
{
    return true;
}

void PlayLayer::back(Ref* pSender)
{
    SceneManager::goMenu();
}
