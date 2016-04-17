#ifndef __RACKET_H__
#define __RACKET_H__

#include "cocos2d.h"
#include "GameSprite.h"

class CRacket : public cocos2d::Sprite
{
public:
	CRacket* init(cocos2d::Layer * layer);
	bool isTouch = false;
	void SetPosition(cocos2d::Point pos);
	float GetPosition();
	void Move(cocos2d::Point pos);
private:
	cocos2d::Vec2 m_origin;
	cocos2d::Size m_visibleSize;
	Sprite *m_racket;
	float m_width;
};

#endif // __RACKET_H__