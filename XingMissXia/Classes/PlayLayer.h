//
//  PlayLayer.h
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//  游戏界面

#ifndef XingMissXia_PlayLayer_h
#define XingMissXia_PlayLayer_h

#include "cocos2d.h"
#include "SceneManager.h"
#include "BaseLayer.h"

#include "Sneaky/SneakyButton.h"
#include "Sneaky/SneakyButtonSkinnedBase.h"
#include "Sneaky/SneakyJoystick.h"
#include "Sneaky/SneakyJoystickSkinnedBase.h"

USING_NS_CC;

class PlayLayer : public BaseLayer
{
public:
    PlayLayer();
    ~PlayLayer();
    bool init();
    void back(Ref* pSender);

    Sprite* ball;
    Sprite* paddle;
    Sprite* edgeSp;

    PhysicsWorld* m_world;

    void startPlay();
    void onEnter();
    bool onContactBegin(PhysicsContact& contact);
    void setPhyWorld(PhysicsWorld* world){ m_world = world; };

    void inputUpdate(float dt);

    CREATE_FUNC(PlayLayer);

private:
    SneakyButton* mButtonA;
    SneakyJoystick* mJoystick;
};

#endif
