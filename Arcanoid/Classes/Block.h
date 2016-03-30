#pragma once
#include "GameSprite.h"


class CBlock
{
public:
	CBlock(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag);
	~CBlock() = default;
	int getTag();
	void del(cocos2d::Layer * layer);
private:
	cocos2d::Vec2 m_origin;
	cocos2d::Size m_visibleSize;
	GameSprite *m_block;
	int m_tag;
};