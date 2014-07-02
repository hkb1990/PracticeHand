//
//  MenuLayer.h
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//  菜单界面

#ifndef XingMissXia_MenuLayer_h
#define XingMissXia_MenuLayer_h

#include "cocos2d.h"
#include "BaseLayer.h"

class MenuLayer : public BaseLayer
{
public:
    bool init();
    
    void onNewGame(cocos2d::Ref* pSender);
    void onCCGame(cocos2d::Ref* pSender);
    void onCredits(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MenuLayer);
};

#endif
