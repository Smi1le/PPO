#include "Ball.h"
#include "Config.h"

USING_NS_CC;

using namespace cocos2d;

/*bool CBall::initBall(float acc)
{
	
}*/

/*void CBall::SetPosition(Point pos)
{
	m_ball->setPosition(pos);
}*/

CBall* CBall::init(cocos2d::Layer * layer, float acceleration, float pos) {
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_ball = GameSprite::gameSpriteWithFile("ball.png");
	m_width = m_ball->getContentSize().width;
	
	m_acc = acceleration;
	m_ball->setTag(TAG_BALL);
	auto ballBody = PhysicsBody::createCircle(m_ball->getContentSize().width / 2, PhysicsMaterial(0.f, 2.0f, 0.f));

	ballBody->setLinearDamping(0);
	ballBody->setGravityEnable(false);
	ballBody->setCollisionBitmask(MASK_BALL);
	ballBody->setContactTestBitmask(true);
	m_ball->setPhysicsBody(ballBody);
	m_ball->setPosition(Point(pos,  120.0f));
	layer->addChild(m_ball);
	return this;
}

void CBall::Start()
{
	m_ball->getPhysicsBody()->setVelocity(Vec2(0 * m_visibleSize.width, m_visibleSize.height * (1 + m_acc)));
}

void CBall::Move(Point pos)
{
	CCLOG("++++++++++++++++++");
	Point nextPosition = pos;
	if (nextPosition.x > m_visibleSize.width - m_width / 2.f) {
		nextPosition.x = m_visibleSize.width - m_width / 2.f;
	}
	if (nextPosition.x < m_width / 2.f) {
		nextPosition.x = m_width / 2.f;
	}
	m_ball->setPositionX(nextPosition.x);
	m_ball->setPositionY(120.0f);
}