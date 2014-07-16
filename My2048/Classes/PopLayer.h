#ifndef __POP_LAYER_H__
#define __POP_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class PopLayer : public LayerColor
{
public:
    static PopLayer* create(const Color4B& color);
    virtual bool initWithColor(const Color4B& color);
    
    //触摸事件监听回调函数
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    void onRestart(Ref* pSender);
    void onExit(Ref* pSender);
    void onContinue(Ref* pSender);
};

#endif //__POP_LAYER_H__
