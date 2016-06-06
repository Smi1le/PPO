#include "Bonus.h"

using namespace cocos2d;

CBonus* CBonus::create(cocos2d::Vec2 const &pos, cocos2d::Layer *layer, int tag)
{
	CBonus* pRet = new CBonus(pos, layer, tag);
	if (pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBonus::CBonus(cocos2d::Vec2 const &pos, cocos2d::Layer *layer, int tag)
{
	m_position = pos;
	m_layer = layer;
	m_tag = tag;
}

bool CBonus::init()
{
	if (m_tag == TAG_BONUS_ADD_LIVES)
	{
		m_bonus = GameSprite::gameSpriteWithFile("Game/Bonus/bonus_life.png");
	}
	else if (m_tag == TAG_BONUS_EXPLOSION_ENEMYS)
	{
		m_bonus = GameSprite::gameSpriteWithFile("Game/Bonus/bonus_bomb.png");
	}
	auto bonusBody = PhysicsBody::createBox(m_bonus->getContentSize());
	bonusBody->setGravityEnable(false);
	bonusBody->setDynamic(false);
	bonusBody->setRotationEnable(false);
	bonusBody->setCollisionBitmask(MASK_BONUS);
	bonusBody->setContactTestBitmask(true);

	m_bonus->setPhysicsBody(bonusBody);
	m_bonus->setPosition(CCPoint(m_position));
	m_bonus->setTag(m_tag);
	m_layer->addChild(m_bonus);

	return true;
}

