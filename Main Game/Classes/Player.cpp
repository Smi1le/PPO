#include "Player.h"
#include "Bullet.h"

using namespace cocos2d;

bool CPlayer::init(cocos2d::Layer * layer, cocos2d::Vec2 position) {
	cocos2d::CCSize m_pScreenSize = CCDirector::sharedDirector()->getWinSize();
	auto m_visibleSize = Director::getInstance()->getVisibleSize();
	auto m_origin = Director::getInstance()->getVisibleOrigin();
	m_playerSprite = GameSprite::gameSpriteWithFile("11.png");
	
	m_position = position;
	latestTrend = STATE::UP;
	/*Vector<SpriteFrame*> animFrames;
	animFrames.reserve(2);
	animFrames.pushBack(SpriteFrame::create("player.png", Rect(100, 0, 138, 39)));
	animFrames.pushBack(SpriteFrame::create("player.png", Rect(100, 52, 138, 91)));
	auto animation = Animation::createWithSpriteFrames(animFrames, 1.f);
	auto animate = Animate::create(animation);
	m_playerSprite->runAction(cocos2d::RepeatForever::create(animate));*/
	auto blockBody = PhysicsBody::createBox(m_playerSprite->getContentSize());
	blockBody->setGravityEnable(false);
	blockBody->setDynamic(true);
	blockBody->setRotationEnable(false);
	blockBody->setCollisionBitmask(MASK_PLAYER);
	blockBody->setContactTestBitmask(true);
	m_playerSprite->setPhysicsBody(blockBody);
	//CCLOG(std::to_string(coordinates.x).c_str());
	//CCLOG(std::to_string(coordinates.y).c_str());
	m_playerSprite->setPosition(CCPoint(position));
	m_playerSprite->setTag(TAG_PLAYER);
	m_coordinatesGunTank = { position.x, position.y + 25.f };
	//m_block->setColor(cocos2d::Color3B(random(0, 255), random(0, 255), random(0, 255)));
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
	}
	else if (state == STATE::RIGHT)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(SPEED_ENEMY_AND_PLAYER, 0.f));
		latestTrend = state;
	}
	else if (state == STATE::LEFT)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(-SPEED_ENEMY_AND_PLAYER, 0.f));
		latestTrend = state;
	}
	else if (state == STATE::DOWN)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0.f, -SPEED_ENEMY_AND_PLAYER));
		latestTrend = state;
	}
	else if (state == STATE::STAY)
	{
		m_playerSprite->getPhysicsBody()->setVelocity(cocos2d::Vec2(0.f, 0.f));
	}
	
}

void CPlayer::Shoot(cocos2d::Layer *layer)
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
	auto bullet = CBullet::create(gunPosition, latestTrend, layer);
}