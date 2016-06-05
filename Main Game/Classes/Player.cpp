#include "Player.h"
#include "Bullet.h"

using namespace cocos2d;


bool CPlayer::init(cocos2d::Vec2 const &pos, cocos2d::Layer *layer)
{
	cocos2d::CCSize m_pScreenSize = CCDirector::sharedDirector()->getWinSize();
	auto m_visibleSize = Director::getInstance()->getVisibleSize();
	auto m_origin = Director::getInstance()->getVisibleOrigin();
	m_playerSprite = GameSprite::gameSpriteWithFile("Player//player_up_1.png");
	latestTrend = STATE::UP;
	initAnimation();
	m_position = pos;
	auto m_body = PhysicsBody::createBox(m_playerSprite->getContentSize());
	m_body->setGravityEnable(false);
	m_body->setDynamic(true);
	m_body->setRotationEnable(false);
	m_body->setCollisionBitmask(MASK_PLAYER);
	m_body->setContactTestBitmask(true);
	m_playerSprite->setPhysicsBody(m_body);

	m_playerSprite->setPosition(CCPoint(m_position));
	m_playerSprite->setTag(TAG_PLAYER);
	m_coordinatesGunTank = { m_position.x, m_position.y + 25.f };
	layer->addChild(m_playerSprite);
	m_tag = TAG_PLAYER;
	return true;
}

void CPlayer::SetPosition(cocos2d::Vec2 const &pos)
{
	m_playerSprite->setPosition(pos);
}

void CPlayer::Control(STATE const &state)
{
	if (state == STATE::UP)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0.f, SPEED_ENEMY_AND_PLAYER));
		latestTrend = state;
		m_playerSprite->runAction(cocos2d::RepeatForever::create(animVector.at(0)));
	}
	else if (state == STATE::RIGHT)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(SPEED_ENEMY_AND_PLAYER, 0.f));
		latestTrend = state;
		m_playerSprite->runAction(cocos2d::RepeatForever::create(animVector.at(3)));
	}
	else if (state == STATE::LEFT)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(-SPEED_ENEMY_AND_PLAYER, 0.f));
		latestTrend = state;
		m_playerSprite->runAction(cocos2d::RepeatForever::create(animVector.at(2)));
	}
	else if (state == STATE::DOWN)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0.f, -SPEED_ENEMY_AND_PLAYER));
		latestTrend = state;
		m_playerSprite->runAction(cocos2d::RepeatForever::create(animVector.at(1)));
	}
	else if (state == STATE::STAY)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0.f, 0.f));
		m_playerSprite->stopAllActions();
	}
	
}

void CPlayer::Shoot(cocos2d::Layer *layer)
{
	if (m_playerSprite != NULL)
	{
		cocos2d::Vec2 gunPosition;
		if (latestTrend == STATE::UP)
		{
			gunPosition = cocos2d::Vec2(m_playerSprite->getPosition().x,
				m_playerSprite->getPosition().y + m_playerSprite->getContentSize().height / 2.f);

		}
		else if (latestTrend == STATE::DOWN)
		{
			gunPosition = cocos2d::Vec2(m_playerSprite->getPosition().x,
				m_playerSprite->getPosition().y - m_playerSprite->getContentSize().height / 2.f);
		}
		else if (latestTrend == STATE::RIGHT)
		{
			gunPosition = cocos2d::Vec2(m_playerSprite->getPosition().x + m_playerSprite->getContentSize().width / 2.f,
				m_playerSprite->getPosition().y);

		}
		else if (latestTrend == STATE::LEFT)
		{
			gunPosition = cocos2d::Vec2(m_playerSprite->getPosition().x - m_playerSprite->getContentSize().width / 2.f,
				m_playerSprite->getPosition().y);
		}
		auto bullet = CBullet::create(gunPosition, latestTrend, layer, TAG_BULLET_PLAYER);
		ChangeResolution();
	}
}

void CPlayer::ChangeResolution()
{
	m_bulletReleased = !m_bulletReleased;
}

void CPlayer::ReleasedBullet()
{
	m_bulletReleased = false;
}

bool CPlayer::IsShot()const
{
	return m_bulletReleased;
}

int CPlayer::GetTag() const
{
	return m_tag;
}

cocos2d::Vec2 CPlayer::GetPosition() const
{
	return m_playerSprite->getPosition();
}

void CPlayer::ReturnToStart(cocos2d::Layer * layer)
{
	m_playerSprite->setPosition(Point(m_position));
//	m_playerSprite->setPhysicsBody(m_body);
	--m_health;
	m_bulletReleased = false;
	layer->addChild(m_playerSprite);
}

void CPlayer::initAnimation()
{
	Vector<SpriteFrame*> animFramesUp(2);
	animFramesUp.pushBack(SpriteFrame::create("Player//player_up_1.png", Rect(0, 0, 39, 39)));
	animFramesUp.pushBack(SpriteFrame::create("Player//player_up_2.png", Rect(0, 0, 39, 39)));
	auto animationUp = Animation::createWithSpriteFrames(animFramesUp, ACTION_TIME);
	auto animateUp = Animate::create(animationUp);
	animVector.pushBack(animateUp);

	Vector<SpriteFrame*> animFramesDown(2);
	animFramesDown.pushBack(SpriteFrame::create("Player//player_down_1.png", Rect(0, 0, 39, 39)));
	animFramesDown.pushBack(SpriteFrame::create("Player//player_down_2.png", Rect(0, 0, 39, 39)));
	auto animationDown = Animation::createWithSpriteFrames(animFramesDown, ACTION_TIME);
	auto animateDown = Animate::create(animationDown);
	animVector.pushBack(animateDown);

	Vector<SpriteFrame*> animFramesLeft(2);
	animFramesLeft.pushBack(SpriteFrame::create("Player//player_left_1.png", Rect(0, 0, 39, 39)));
	animFramesLeft.pushBack(SpriteFrame::create("Player//player_left_2.png", Rect(0, 0, 39, 39)));
	auto animationLeft = Animation::createWithSpriteFrames(animFramesLeft, ACTION_TIME);
	auto animateLeft = Animate::create(animationLeft);
	animVector.pushBack(animateLeft);

	Vector<SpriteFrame*> animFramesRight(2);
	animFramesRight.pushBack(SpriteFrame::create("Player//player_right_1.png", Rect(0, 0, 39, 39)));
	animFramesRight.pushBack(SpriteFrame::create("Player//player_right_2.png", Rect(0, 0, 39, 39)));
	auto animationRight = Animation::createWithSpriteFrames(animFramesRight, ACTION_TIME);
	auto animateRight = Animate::create(animationRight);
	animVector.pushBack(animateRight);
}