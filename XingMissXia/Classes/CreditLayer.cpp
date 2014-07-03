//
//  CreditLayer.cpp
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//

#include "CreditLayer.h"
USING_NS_CC;

CreditLayer::CreditLayer()
{
}

CreditLayer::~CreditLayer()
{
}

bool CreditLayer::init()
{
    if(!BaseLayer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    MenuItemFont *back = MenuItemFont::create("back", CC_CALLBACK_1(CreditLayer::back, this));
    Menu *menu = Menu::create(back, NULL);
    menu->setPosition(visibleSize.width*9/10, visibleSize.height*9/10);
    this->addChild(menu);

    return true;
}

void CreditLayer::back(Ref* pSender)
{
    SceneManager::goMenu();
}
