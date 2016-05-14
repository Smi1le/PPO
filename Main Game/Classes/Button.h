#pragma once
#include "GameSprite.h"
#include <string>

enum class TypeButton
{
	LEFT,
	RIGHT,
	DOWN,
	UP
};

class CButton
{
public:
	bool init(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag, TypeButton const &tb, std::string const &f, std::string const &s);
	void del(cocos2d::Layer * layer);
	int getTag() const;
	TypeButton GetTypeButton() const;
	bool IsTouch = false;
	bool IsContainsPoint(Point const &point);
	void Change(cocos2d::Layer * layer);
private:
	GameSprite *m_sprite;
	GameSprite *m_firstSprite;
	GameSprite *m_secondSprite;
	int numberSprite;
	int m_tag;
	cocos2d::Vec2 m_origin;
	cocos2d::Size m_visibleSize;
	TypeButton m_type;
};