#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
class CardSprite;
class SimpleRecognizer;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    ~GameScene();
    
    //触摸事件监听回调函数
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    
    void createCardSprite(cocos2d::Size size);
    void createCardNumber(bool animation = true);
    void newNumber(int i, int j, int num);
    void setScore(int score);
    void doCheck();
    bool shouldCreateCardNumber();
    
    bool isWin();
    void removeSuccessLayer();
    
    void saveStatus();
    void resumeStatus();
    
    void onPause(Ref* pSender);
    
    
    cocos2d::Point getPosition(int i, int j);
    
    /////////////////
    //左滑动
    bool doLeft();
    //右滑动
    bool doRight();
    //上滑动
    bool doUp();
    //下滑动
    bool doDown();
    
private:
    
    cocos2d::Size visibleSize;
    
    //定义cellSize/cellSpace
    int cellSize = 0;
    int cellSpace = 10;
    //分数
    int score;
    //显示分数控件
    cocos2d::Label *cardNumberTTF;
    
    //储存卡片类
    CardSprite *cardArr[4][4];
    
    SimpleRecognizer *recognizer;
    
    cocos2d::LayerColor *successLayer;

};

#endif // __GAME_SCENE_H__
