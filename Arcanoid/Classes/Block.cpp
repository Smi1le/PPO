#include "Config.h"
#include "Block.h"


CBlock::CBlock(cocos2d::Layer * layer, cocos2d::Vec2 const &coordinates, int tag)
{
	cocos2d::CCSize m_pScreenSize = CCDirector::sharedDirector()->getWinSize();
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	m_block = GameSprite::gameSpriteWithFile("block.png");
	auto blockBody = PhysicsBody::createBox(m_block->getContentSize());
	blockBody->setGravityEnable(false);
	blockBody->setDynamic(false);
	blockBody->setCollisionBitmask(MASK_BLOCK);
	blockBody->setContactTestBitmask(true);
	m_block->setPhysicsBody(blockBody);
	m_block->setPosition(ccp(m_pScreenSize.width * coordinates.x, m_pScreenSize.height * coordinates.y));
	m_block->setTag(tag);
	m_block->setColor(cocos2d::Color3B( random(0, 255), random(0, 255), random(0, 255)));
	layer->addChild(m_block);
	m_tag = tag;
}

int CBlock::getTag()
{
	return m_tag;
}

void CBlock::del(cocos2d::Layer * layer)
{
	layer->removeChildByTag(m_tag, true);
}