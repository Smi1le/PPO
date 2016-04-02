#include "Ball.h"
#include "Config.h"

USING_NS_CC;

using namespace cocos2d;

CBall::CBall(cocos2d::Layer * layer, float acceleration, Point pos) {
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_ball = GameSprite::gameSpriteWithFile("ball.png");
	m_width = m_ball->getContentSize().width;
	m_ball->setPosition(pos.x, pos.y + 20.0f);// Point(m_visibleSize.height - 50.0f, 43.0f));
	m_acc = acceleration;
	m_ball->setTag(TAG_BALL);
	layer->addChild(m_ball);
}

void CBall::Start()
{
	auto ballBody = PhysicsBody::createCircle(m_ball->getContentSize().width / 2, PhysicsMaterial(0.f, 2.0f, 0.f));
	ballBody->setGravityEnable(false);
	ballBody->setCollisionBitmask(MASK_BALL);
	ballBody->setContactTestBitmask(true);
	ballBody->setVelocity(Vec2(0 * m_visibleSize.width, m_visibleSize.height * (1 + m_acc)));
	m_ball->setPhysicsBody(ballBody);
}

void CBall::Move(Point pos)
{
	Point nextPosition = pos;
	if (nextPosition.x > m_visibleSize.width - m_width / 2.f) {
		nextPosition.x = m_visibleSize.width - m_width / 2.f;
	}
	if (nextPosition.x < m_width / 2.f) {
		nextPosition.x = m_width / 2.f;
	}

	m_ball->setPositionX(nextPosition.x);
}