#ifndef __GAME_OVER_LAYER_H__
#define __GAME_OVER_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public LayerColor
{
public:
    static GameOverLayer* create(const Color4B& color);
    virtual bool initWithColor(const Color4B& color);
    
    //触摸事件监听回调函数
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    void onRestart(Ref* pSender);
};

#endif // __GAME_OVER_LAYER_H__