//
//  CreditLayer.h
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//  相关说明

#ifndef XingMissXia_CreditLayer_h
#define XingMissXia_CreditLayer_h

#include "cocos2d.h"
#include "SceneManager.h"
#include "BaseLayer.h"

class CreditLayer : public BaseLayer
{
public:
    CreditLayer();
    ~CreditLayer();
    bool init();
    void back(cocos2d::Ref* pSender);
    
    CREATE_FUNC(CreditLayer);
};

#endif
