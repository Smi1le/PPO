#pragma once
#include <vector>
#include "cocos2d.h"
#include "GameSprite.h"


struct SGameState
{
	int remainingNumberTanks = 20;
	std::vector<cocos2d::ValueMap> respPositions;
	std::vector<cocos2d::ValueMap> bonusesPositions;
	int bonusNumber = 0;
	int numberRespPos = 0;
	int numberEnemys;
	cocos2d::Vec2 posInitPlayer;
	int numberLivesPlayer;
};


class CAnimation
{
public:
	GameSprite* Explosion(cocos2d::Vec2 const &pos);
	void initPlayerAnimation();
	cocos2d::Vector<cocos2d::Animate*> m_animations;
private:
	
};