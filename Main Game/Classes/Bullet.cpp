#include "Bullet.h"




CBullet* CBullet::create(cocos2d::Vec2 const &pos, STATE const &state, cocos2d::Layer *layer)
{
	CBullet* pRet = new CBullet(pos, state, layer);
	if (pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CBullet::CBullet(cocos2d::Vec2 const &pos, STATE const &state, cocos2d::Layer *layer)
{
	m_screenSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_position = pos;
	m_state = state;
	m_layer = layer;
	//m_bulletSprite = GameSprite::gameSpriteWithFile("Game//bullet.png");
}

bool CBullet::init()
{
	m_bulletSprite = GameSprite::gameSpriteWithFile("Game//bullet.png");
	

	auto bulletBody = PhysicsBody::createBox(m_bulletSprite->getContentSize());
	bulletBody->setGravityEnable(false);
	bulletBody->setDynamic(true);
	bulletBody->setRotationEnable(false);
	bulletBody->setCollisionBitmask(MASK_BULLET);
	bulletBody->setContactTestBitmask(true);
	
	if (m_state == STATE::UP)
	{
		bulletBody->setVelocity(cocos2d::Vec2(0.f, SPEED_BULLET));
	}
	else if (m_state == STATE::DOWN)
	{
		bulletBody->setVelocity(cocos2d::Vec2(0.f, -SPEED_BULLET));
	}
	else if (m_state == STATE::RIGHT)
	{
		bulletBody->setVelocity(cocos2d::Vec2(SPEED_BULLET, 0.f));
	}
	else if (m_state == STATE::LEFT)
	{
		bulletBody->setVelocity(cocos2d::Vec2(-SPEED_BULLET, 0.f));
	}
	m_bulletSprite->setPhysicsBody(bulletBody);
	m_bulletSprite->setPosition(CCPoint(m_position));
	m_bulletSprite->setTag(TAG_BULLET_PLAYER);
	m_layer->addChild(m_bulletSprite);
	//m_coordinatesGunTank = { m_position.x, position.y + 25.f };

	return true;
}

