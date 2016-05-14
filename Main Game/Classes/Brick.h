#ifndef __CBLOCK_H__
#define __CBLOCK_H__
#include "GameSprite.h"


class CBrick
{
public:
	bool init(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag);
	int getTag();
	void del(cocos2d::Layer * layer);
private:
	cocos2d::Vec2 m_origin;
	cocos2d::Size m_visibleSize;
	GameSprite *m_block;
	int m_tag;
};
#endif // __CBLOCK_H__