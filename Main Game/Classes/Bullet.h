#ifndef __BULLET_H__
#define __BULLET_H__

#include "GameSprite.h"
#include "Config.h"

class CBullet : public cocos2d::Layer
{
public:
	static CBullet* create(cocos2d::Vec2 const &pos, STATE const &state, cocos2d::Layer *layer);
private:
	CBullet(cocos2d::Vec2 const &pos, STATE const &state, cocos2d::Layer *layer);
	GameSprite *m_bulletSprite;
	cocos2d::Vec2 m_origin;
	cocos2d::Vec2 m_position;
	cocos2d::Vec2 m_visibleSize;
	cocos2d::CCSize m_screenSize;
	cocos2d::Layer *m_layer;
	STATE m_state;
	bool init();

};

#endif // __GAMESPRITE_H__y