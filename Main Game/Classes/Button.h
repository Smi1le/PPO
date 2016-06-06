#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "GameSprite.h"
#include <string>

enum class TypeButton
{
	LEFT,
	RIGHT,
	DOWN,
	UP
};

class CButton : public cocos2d::Layer
{
public:
	CButton() = default;
	static CButton* create(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag, TypeButton const &tb, std::string const &f);
	bool init(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag, TypeButton const &tb, std::string const &f);
	int getTag() const;
	TypeButton GetTypeButton() const;
	bool IsTouch = false;
	bool IsContainsPoint(cocos2d::Point const &point);
private:
	GameSprite *m_sprite;
	int m_tag;
	TypeButton m_type;
};

#endif // __CBUTTON_H__