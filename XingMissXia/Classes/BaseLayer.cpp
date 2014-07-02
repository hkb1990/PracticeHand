//
//  BaseLayer.cpp
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//

#include "BaseLayer.h"
USING_NS_CC;

BaseLayer::BaseLayer()
{
}

BaseLayer::~BaseLayer()
{
}

bool BaseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite *bg = Sprite::create("background.jpg");
    bg->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(bg, 0);

    return true;
}
