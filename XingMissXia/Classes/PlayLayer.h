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

class PlayLayer : public BaseLayer
{
public:
    PlayLayer();
    ~PlayLayer();
    bool init();
    void back(cocos2d::Object* pSender);
    
    CREATE_FUNC(PlayLayer);
};

#endif
