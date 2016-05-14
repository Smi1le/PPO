#include "Config.h"
#include "Button.h"

using namespace cocos2d;

bool CButton::init(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag, TypeButton const &tb, std::string const &f, std::string const &s)
{
	m_type = tb;
	/*auto controlUp = MenuItemImage::create("Game//" + f, "Game//" + s);
	controlUp->setPosition(coordinates);
	auto contolUpButton = Menu::create(controlUp, NULL);
	contolUpButton->setPosition(Point::ZERO);
	layer->addChild(contolUpButton);*/
	auto path = "Game//";
	m_firstSprite = GameSprite::gameSpriteWithFile(cocos2d::String(path + f).getCString());
	m_secondSprite = GameSprite::gameSpriteWithFile(cocos2d::String(path + s).getCString());
	cocos2d::CCSize m_pScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_sprite = m_firstSprite;
	numberSprite = 1;
	

	auto buttonBody = PhysicsBody::createCircle(m_sprite->getContentSize().width / 2);
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

void CButton::Change(cocos2d::Layer * layer)
{
	layer->removeChildByTag(m_tag);
	if (numberSprite == 1)
	{
		CCLOG("numberSprite == 1");
		m_sprite = m_secondSprite;
		m_sprite->setTag(m_tag);
		++numberSprite;
	}
	else
	{
		CCLOG("numberSprite ==2 ");
		m_sprite = m_firstSprite;
		m_sprite->setTag(m_tag);
		--numberSprite;
	}
	layer->addChild(m_sprite);
}

TypeButton CButton::GetTypeButton() const
{
	return m_type;
}

bool CButton::IsContainsPoint(Point const &point)
{
	return m_sprite->boundingBox().containsPoint(point);
}

void CButton::del(cocos2d::Layer * layer)
{
	layer->removeChildByTag(m_tag, true);
}