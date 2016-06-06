#ifndef __CBLOCK_H__
#define __CBLOCK_H__
#include "GameSprite.h"


class CBrick
{
public:
	bool init(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag);
	int getTag();
private:
	GameSprite *m_block;
	int m_tag;
};
#endif // __CBLOCK_H__