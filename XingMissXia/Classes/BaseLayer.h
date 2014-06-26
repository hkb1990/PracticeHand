//
//  BaseLayer.h
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//  背景层

#ifndef XingMissXia_BaseLayer_h
#define XingMissXia_BaseLayer_h

#include "cocos2d.h"

class BaseLayer : public cocos2d::Layer
{
public:
    BaseLayer();
    ~BaseLayer();
    bool init();
    
    CREATE_FUNC(BaseLayer);
};

#endif
