//
//  SceneManager.h
//  XingMissXia
//
//  Created by 黄凯滨 on 14-6-26.
//
//  控制场景切换

#ifndef XingMissXia_SceneManager_h
#define XingMissXia_SceneManager_h

#include "cocos2d.h"
#include "MenuLayer.h"

class SceneManager : public cocos2d::Ref
{
public:
    SceneManager() {};
    ~SceneManager() {};

    static void goMenu();
    static void goPlay();
    static void goCredit();
private:
    static void go(cocos2d::Layer* layer);
    static cocos2d::Scene* wrap(cocos2d::Layer *layer);
};

#endif
