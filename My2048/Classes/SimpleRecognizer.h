#ifndef __SIMPLE_RECOGNIZER_H__
#define __SIMPLE_RECOGNIZER_H__

#include "cocos2d.h"


typedef enum {
	SimpleGesturesRight,
	SimpleGesturesLeft,
	SimpleGesturesUp,
	SimpleGesturesDown,
	SimpleGesturesError,
	SimpleGesturesNotSupport
    
} SimpleGestures;

class SimpleRecognizer
{
protected:
	//--- These are variables because C++ doesn't (easily) allow
	//---  constants to be floating point numbers
	double X;
	double Y;
	SimpleGestures result;
    std::vector<cocos2d::Point> points;
    
public:
	SimpleRecognizer();
    
	void beginPoint(cocos2d::Point point);
	void movePoint(cocos2d::Point point);
	SimpleGestures endPoint(cocos2d::Point point);
    
    std::vector<cocos2d::Point>& getPoints();
    
};

#endif // __SIMPLE_RECOGNIZER_H__
