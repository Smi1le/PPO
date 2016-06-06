#include "../Classes/Enemy.h"
#include "Bullet.h"


using namespace cocos2d;

bool CEnemy::init(cocos2d::Vec2 const &pos, STATE const &state, int tag, cocos2d::Layer *layer)
{
	//int en = cocos2d::random(1, 2);
	initAnimation();
	m_speed = SPEED_ENEMY_AND_PLAYER;
	animVector = easyAnimVector;
	/*else
	{
		m_speed = SPEED_ENEMY_AND_PLAYER + 20.f;
		animVector = fastAnimVector;
	}*/
	m_position = pos;
	m_state = state;
	m_tag = tag + TAG_ENEMY;
	m_enemySprite = GameSprite::gameSpriteWithFile("Enemy/easyEnemy_down_1.png");
	auto body = PhysicsBody::createBox(m_enemySprite->getContentSize());
	body->setGravityEnable(false);
	body->setDynamic(true);
	body->setRotationEnable(false);
	body->setCollisionBitmask(MASK_ENEMY);
	body->setContactTestBitmask(true);
	m_enemySprite->setPhysicsBody(body);
	
	Control(m_state);
	m_enemySprite->setPosition(CCPoint(m_position));
	m_enemySprite->setTag(m_tag);
	layer->addChild(m_enemySprite);

	return true;
}


void CEnemy::Control(STATE const &state)
{
	auto body = m_enemySprite->getPhysicsBody();
	if (state == STATE::UP)
	{
		body->setVelocity(cocos2d::Vec2(0.f, m_speed));
		m_enemySprite->stopAllActions();
		m_enemySprite->runAction(cocos2d::RepeatForever::create(animVector.at(0)));
	}
	else if (state == STATE::DOWN)
	{
		body->setVelocity(cocos2d::Vec2(0.f, -m_speed));
		m_enemySprite->stopAllActions();
		m_enemySprite->runAction(cocos2d::RepeatForever::create(animVector.at(1)));
	}
	else if (state == STATE::RIGHT)
	{
		body->setVelocity(cocos2d::Vec2(m_speed, 0.f));
		m_enemySprite->stopAllActions();
		m_enemySprite->runAction(cocos2d::RepeatForever::create(animVector.at(3)));
		
	}
	else if (state == STATE::LEFT)
	{
		body->setVelocity(cocos2d::Vec2(-m_speed, 0.f));
		m_enemySprite->stopAllActions();
		m_enemySprite->runAction(cocos2d::RepeatForever::create(animVector.at(2)));
	}
	m_state = state;
	m_enemySprite->setPhysicsBody(body);
}

int CEnemy::GetTag() const
{
	return m_tag;
}

void CEnemy::ChangeDirection()
{
	for (;;)
	{
		int dir = cocos2d::random(0, 3);
		if (dir == 0 && m_state != STATE::LEFT)
		{
			Control(STATE::LEFT);
			break;
		}
		else if (dir == 1 && m_state != STATE::RIGHT)
		{
			Control(STATE::RIGHT);
			break;
		}
		else if (dir == 2 && m_state != STATE::UP)
		{
			Control(STATE::UP);
			break;
		}
		else if (dir == 3 && m_state != STATE::DOWN)
		{
			Control(STATE::DOWN);
			break;
		}
	}
}

void CEnemy::Update(cocos2d::Layer *layer)
{
	
	if ((abs(m_enemySprite->getPhysicsBody()->getVelocity().y) < SPEED_ENEMY_AND_PLAYER / 2.f)
		|| (abs(m_enemySprite->getPhysicsBody()->getVelocity().x) < SPEED_ENEMY_AND_PLAYER / 2.f))
	{
		Control(m_state);
	}
}

void CEnemy::Shoot(cocos2d::Layer *layer)
{
	cocos2d::Vec2 gunPosition;
	if (m_state == STATE::UP)
	{
		gunPosition = cocos2d::Vec2(m_enemySprite->getPosition().x,
			m_enemySprite->getPosition().y + m_enemySprite->getContentSize().height / 2.f);

	}
	else if (m_state == STATE::DOWN)
	{
		gunPosition = cocos2d::Vec2(m_enemySprite->getPosition().x,
			m_enemySprite->getPosition().y - m_enemySprite->getContentSize().height / 2.f);
	}
	else if (m_state == STATE::RIGHT)
	{
		gunPosition = cocos2d::Vec2(m_enemySprite->getPosition().x + m_enemySprite->getContentSize().width / 2.f,
			m_enemySprite->getPosition().y);

	}
	else if (m_state == STATE::LEFT)
	{
		gunPosition = cocos2d::Vec2(m_enemySprite->getPosition().x - m_enemySprite->getContentSize().width / 2.f,
			m_enemySprite->getPosition().y);
	}
	m_bulletTag = m_tag + TAG_BULLET_ENEMY;
	CBullet::create(gunPosition, m_state, layer, m_bulletTag);
	ChangeResolution();
}

void CEnemy::ChangeResolution()
{
	m_bulletReleased = !m_bulletReleased;
}

bool CEnemy::IsShot()const
{
	return m_bulletReleased;
}

int CEnemy::GetBulletTag() const
{
	return m_bulletTag;
}

cocos2d::Vec2 CEnemy::GetPosition() const
{
	return m_enemySprite->getPosition();
}

void CEnemy::initAnimation()
{
	Vector<SpriteFrame*> animFramesUp(2);
	animFramesUp.pushBack(SpriteFrame::create("Enemy/easyEnemy_up_1.png", Rect(0, 0, 39, 39)));
	animFramesUp.pushBack(SpriteFrame::create("Enemy/easyEnemy_up_2.png", Rect(0, 0, 39, 39)));
	auto animationUp = Animation::createWithSpriteFrames(animFramesUp, ACTION_TIME);
	auto animateUp = Animate::create(animationUp);
	easyAnimVector.pushBack(animateUp);

	Vector<SpriteFrame*> animFramesDown(2);
	animFramesDown.pushBack(SpriteFrame::create("Enemy/easyEnemy_down_1.png", Rect(0, 0, 39, 39)));
	animFramesDown.pushBack(SpriteFrame::create("Enemy/easyEnemy_down_2.png", Rect(0, 0, 39, 39)));
	auto animationDown = Animation::createWithSpriteFrames(animFramesDown, ACTION_TIME);
	auto animateDown = Animate::create(animationDown);
	easyAnimVector.pushBack(animateDown);

	Vector<SpriteFrame*> animFramesLeft(2);
	animFramesLeft.pushBack(SpriteFrame::create("Enemy/easyEnemy_left_1.png", Rect(0, 0, 39, 39)));
	animFramesLeft.pushBack(SpriteFrame::create("Enemy/easyEnemy_left_2.png", Rect(0, 0, 39, 39)));
	auto animationLeft = Animation::createWithSpriteFrames(animFramesLeft, ACTION_TIME);
	auto animateLeft = Animate::create(animationLeft);
	easyAnimVector.pushBack(animateLeft);

	Vector<SpriteFrame*> animFramesRight(2);
	animFramesRight.pushBack(SpriteFrame::create("Enemy/easyEnemy_right_1.png", Rect(0, 0, 39, 39)));
	animFramesRight.pushBack(SpriteFrame::create("Enemy/easyEnemy_right_2.png", Rect(0, 0, 39, 39)));
	auto animationRight = Animation::createWithSpriteFrames(animFramesRight, ACTION_TIME);
	auto animateRight = Animate::create(animationRight);
	easyAnimVector.pushBack(animateRight);

	/*Vector<SpriteFrame*> framesUp(2);
	framesUp.pushBack(SpriteFrame::create("Enemy/fastEnemy_up_1.png", Rect(0, 0, 39, 45)));
	framesUp.pushBack(SpriteFrame::create("Enemy/fastEnemy_up_2.png", Rect(0, 0, 39, 45)));
	auto animUp = Animation::createWithSpriteFrames(framesUp, ACTION_TIME);
	auto anUp = Animate::create(animUp);
	fastAnimVector.pushBack(anUp);

	Vector<SpriteFrame*> framesDown(2);
	framesDown.pushBack(SpriteFrame::create("Enemy/fastEnemy_down_1.png", Rect(0, 0, 39, 45)));
	framesDown.pushBack(SpriteFrame::create("Enemy/fastEnemy_down_2.png", Rect(0, 0, 39, 45)));
	auto animDown = Animation::createWithSpriteFrames(framesDown, ACTION_TIME);
	auto anDown = Animate::create(animDown);
	fastAnimVector.pushBack(anDown);

	Vector<SpriteFrame*> framesLeft(2);
	framesLeft.pushBack(SpriteFrame::create("Enemy/fastEnemy_left_1.png", Rect(0, 0, 45, 39)));
	framesLeft.pushBack(SpriteFrame::create("Enemy/fastEnemy_left_2.png", Rect(0, 0, 45, 39)));
	auto animLeft = Animation::createWithSpriteFrames(framesLeft, ACTION_TIME);
	auto anLeft = Animate::create(animLeft);
	fastAnimVector.pushBack(anLeft);

	Vector<SpriteFrame*> framesRight(2);
	framesRight.pushBack(SpriteFrame::create("Enemy/fastEnemy_right_1.png", Rect(0, 0, 45, 39)));
	framesRight.pushBack(SpriteFrame::create("Enemy/fastEnemy_right_2.png", Rect(0, 0, 45, 39)));
	auto animRight = Animation::createWithSpriteFrames(framesRight, ACTION_TIME);
	auto anRight = Animate::create(animRight);
	fastAnimVector.pushBack(anRight);*/
}