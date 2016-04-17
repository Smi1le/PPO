#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"
#include "GameSprite.h"

class CBall : public cocos2d::CCSprite
{
public:
	CBall* init(cocos2d::Layer * layer, float acceleration, float pos);
	void Start();
	void Move(cocos2d::Point pos);
private:
	//bool initBall(float acc);
	cocos2d::Vec2 m_origin;
	cocos2d::Size m_visibleSize;
	cocos2d::Sprite *m_ball;
	Point m_pos;
	float m_acc = 1.05f;
	float m_width;
};

#endif // __BALL_H__