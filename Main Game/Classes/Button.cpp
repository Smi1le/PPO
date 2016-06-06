#include "Config.h"
#include "Button.h"

using namespace cocos2d;

CButton* CButton::create(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag, TypeButton const &tb, std::string const &f)
{
	auto pBut = new CButton();
	if (pBut && pBut->init(layer, coordinates, tag, tb, f)) {
		pBut->autorelease();
		return pBut;
	}
	CC_SAFE_DELETE(pBut);
	return NULL;
}

bool CButton::init(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag, TypeButton const &tb, std::string const &f)
{
	m_type = tb;
	cocos2d::String path = cocos2d::String("Game/");
	path.append(f);
	if (!(m_sprite = GameSprite::gameSpriteWithFile(path.getCString())))
	{
		return false;
	}

	auto buttonBody = PhysicsBody::createCircle(m_sprite->getContentSize().width / 2);
	buttonBody->setDynamic(false);
	m_sprite->setPhysicsBody(buttonBody);
	m_sprite->setPosition(coordinates);
	layer->addChild(m_sprite);
	m_sprite->setTag(tag);
	m_tag = tag;
	return true;
}

int CButton::getTag() const
{
	return m_tag;
}

TypeButton CButton::GetTypeButton() const
{
	return m_type;
}

bool CButton::IsContainsPoint(Point const &point)
{
	if (m_sprite != NULL)
	{
		return m_sprite->boundingBox().containsPoint(point);
	}
	return false;
}