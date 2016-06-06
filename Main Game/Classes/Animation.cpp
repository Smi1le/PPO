#include "gameState.h"
#include "cocos2d.h"

using namespace cocos2d;

void CAnimation::initPlayerAnimation()
{
	cocos2d::Vector<SpriteFrame*> animFrames(3);
	animFrames.pushBack(SpriteFrame::create("Boom/BigExplosion_1.png", Rect(0, 0, 11, 10)));
	animFrames.pushBack(SpriteFrame::create("Boom/BigExplosion_2.png", Rect(0, 0, 16, 13)));
	animFrames.pushBack(SpriteFrame::create("Boom/BigExplosion_3.png", Rect(0, 0, 30, 28)));
	m_animations.pushBack(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.15f)));

	cocos2d::Vector<SpriteFrame*> frames(4);
	frames.pushBack(SpriteFrame::create("Enemy/appearance.png", Rect(0, 0, 36, 39)));
	frames.pushBack(SpriteFrame::create("Enemy/appearanc_2.png", Rect(0, 0, 45, 45)));
	frames.pushBack(SpriteFrame::create("Enemy/appearance.png", Rect(0, 0, 36, 39)));
	frames.pushBack(SpriteFrame::create("Enemy/appearance_2.png", Rect(0, 0, 45, 45)));
	m_animations.pushBack(Animate::create(Animation::createWithSpriteFrames(frames, 0.15f)));
}

GameSprite* CAnimation::Explosion(cocos2d::Vec2 const &pos)
{
	
	auto expl = GameSprite::gameSpriteWithFile("Boom/BigExplosion_1.png");
	expl->setPosition(pos);
	expl->runAction(Sequence::create(m_animations.at(0), RemoveSelf::create(true), nullptr));
	return expl;
}