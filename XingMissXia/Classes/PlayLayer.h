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
    bool onTouchBegan(Touch *Touch, Event *Event);
    void onTouchMoved(Touch* touch, Event* event);
    void setPhyWorld(PhysicsWorld* world){ m_world = world; };

    CREATE_FUNC(PlayLayer);
};

#endif
