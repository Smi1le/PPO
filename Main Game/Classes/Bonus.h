#ifndef __BONUS_H__
#define __BONUS_H__

#include "GameSprite.h"
#include "Config.h"

class CBonus : public cocos2d::Layer
{
public:
	static CBonus* create(cocos2d::Vec2 const &pos, cocos2d::Layer *layer, int tag);
private:
	CBonus(cocos2d::Vec2 const &pos, cocos2d::Layer *layer, int tag);
	GameSprite *m_bonus;
	cocos2d::Vec2 m_position;
	cocos2d::Layer *m_layer;
	int m_tag;
	bool init();

};

#endif // __BONUS_H__