//
//  PlayLayerCC.h
//  XingMissXia
//
//  Created by 邱涔佞 on 14-7-2.
//
//

#ifndef XingMissXia_PlayLayerCC_h
#define XingMissXia_PlayLayerCC_h

#include "cocos2d.h"
#include "SceneManager.h"
#include "BaseLayer.h"

USING_NS_CC;

class PlayLayerCC : public BaseLayer
{
public:
    PlayLayerCC();
    ~PlayLayerCC();
    bool init();
    void back(Ref* pSender);
    
    Sprite *playerCC;
    Sprite *target;
    Sprite *projectile;
    Array *monsters;
    Array *projectiles;
    
    void addTarget();
    void spriteMoveFinished(Node *sender);
    void gameLogic(float dt);
    void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    void update(float delta);
    
    CREATE_FUNC(PlayLayerCC);
};


#endif