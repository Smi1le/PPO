#include "Racket.h"
#include "Config.h"


USING_NS_CC;

using namespace cocos2d;

CRacket* CRacket::init(cocos2d::Layer * layer) {
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_racket = GameSprite::gameSpriteWithFile("_bmp.png");
	m_width = m_racket->getContentSize().width;
	auto racketBody = PhysicsBody::createBox(m_racket->getContentSize());
	racketBody->setGravityEnable(false);
	racketBody->setDynamic(false);
	racketBody->setCollisionBitmask(MASK_RACKET);
	racketBody->setContactTestBitmask(true);
	m_racket->setPhysicsBody(racketBody);
	//m_racket->setPosition(Vec2(m_visibleSize.height - 50.0f, 25.0f));
	layer->addChild(m_racket);
	return this;
}

void CRacket::SetPosition(Point pos)
{
	m_racket->setPosition(pos);
	
}

float CRacket::GetPosition()
{
	return m_racket->getPositionX();
}

void CRacket::Move(Point pos)
{
	Point nextPosition = pos;
	if (nextPosition.x > m_visibleSize.width - m_width / 2.f) {
		nextPosition.x = m_visibleSize.width - m_width / 2.f;
	}
	if (nextPosition.x < m_width / 2.f) {
		nextPosition.x = m_width / 2.f;
	}

	m_racket->setPositionX(nextPosition.x);
}