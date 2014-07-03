//
//  MenuLayer.cpp
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//

#include "MenuLayer.h"

#include "MenuLayer.h"
#include "SceneManager.h"
USING_NS_CC;

bool MenuLayer::init()
{
    if ( !BaseLayer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    TTFConfig config_font96("Marker Felt.ttf", 96);
    TTFConfig config_font52("Marker Felt.ttf", 52);

    Label *titleLeft = Label::createWithTTF(config_font96, "Menu");
    Label *titleRight = Label::createWithTTF(config_font96, "HHHHHH");
    Label *titleQuotes = Label::createWithTTF(config_font96, ""                        "");
    Label *titleCenterTop = Label::createWithTTF(config_font96, "Blablabla...");
    Label *titleCenterBottom = Label::createWithTTF(config_font52, "By HKB");

    MenuItemFont *startNew = MenuItemFont::create("New Game", CC_CALLBACK_1(MenuLayer::onNewGame, this));

    MenuItemFont *startNewByCC = MenuItemFont::create("CC Game", CC_CALLBACK_1(MenuLayer::onCCGame, this));
    //用图片代替文字
    //MenuItemImage *startNew = MenuItemImage::create("newGameBtn.png","newGameBtn_over.png","newGameBtn.png",CC_CALLBACK_1(MenuLayer::onNewGame, this))
    MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(MenuLayer::onCredits, this));

    Menu *menu = Menu::create(startNew, startNewByCC, credits, NULL);

    titleCenterTop->setPosition(Point( (visibleSize.width - titleCenterTop->getContentSize().width)/2,visibleSize.height - 100) );
    this->addChild(titleCenterTop);

    titleQuotes->setPosition(Point((visibleSize.width - titleQuotes->getContentSize().width)/2,titleCenterTop->getPosition().y - titleQuotes->getContentSize().height - 40) );
    this->addChild(titleQuotes);

    int tileWidth = titleLeft->getContentSize().width + titleRight->getContentSize().width + 50;
    titleLeft->setPosition(Point( (visibleSize.width - tileWidth)/2,titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40) );
    this->addChild(titleLeft);

    titleRight->setPosition(Point( (visibleSize.width - tileWidth)/2 + titleLeft->getContentSize().width + 50,titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40) );
    this->addChild(titleRight);

    titleCenterBottom->setPosition(Point( (visibleSize.width - titleCenterBottom->getContentSize().width)/2,titleRight->getPosition().y - titleCenterBottom->getContentSize().height - 40) );
    this->addChild(titleCenterBottom);

    menu->setPosition(Point( visibleSize.width / 2,titleCenterBottom->getPosition().y-150 ) );
    menu->alignItemsVerticallyWithPadding(80.0f);
    this->addChild(menu, 2);

    return true;
}

void MenuLayer::onNewGame(Ref* pSender)
{
    SceneManager::goPlay();
}

void MenuLayer::onCCGame(Ref* pSender)
{
    SceneManager::goPlayCC();
}

void MenuLayer::onCredits(Ref* pSender)
{
    SceneManager::goCredit();
}
