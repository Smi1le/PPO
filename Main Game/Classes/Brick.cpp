#include "Config.h"
#include "Brick.h"

using namespace cocos2d;

bool CBrick::init(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag)
{
	m_block = GameSprite::gameSpriteWithFile("Game/brick.png");
	auto blockBody = PhysicsBody::createBox(m_block->getContentSize());
	blockBody->setGravityEnable(false);
	blockBody->setDynamic(false);
	blockBody->setCollisionBitmask(MASK_BRICK);
	blockBody->setContactTestBitmask(true);
	m_block->setPhysicsBody(blockBody);
	m_block->setPosition(ccp(coordinates.x, coordinates.y));
	m_block->setTag(tag);
	layer->addChild(m_block);
	m_tag = tag;
	return true;
}

int CBrick::getTag()
{
	return m_tag;
}