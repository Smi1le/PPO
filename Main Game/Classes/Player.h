#pragma once
#include <vector>
#include "GameSprite.h"
#include "Config.h"

using animateVector = cocos2d::Vector<cocos2d::Animate*>;


//#include "levelObject.h"

class CPlayer : public cocos2d::Layer 
{
public:

	std::vector<int> permittedMovementOptions;
	bool isMove = true;
	void Shoot(cocos2d::Layer *layer);
	void ChangeResolution();
	void ReleasedBullet();
	bool IsShot()const;
	int GetTag() const;
	bool init(cocos2d::Vec2 const &pos, cocos2d::Layer *layer);
	void SetPosition(cocos2d::Vec2 const &pos);
	cocos2d::Vec2 GetPosition() const;
	void Control(STATE const &state);
	void ReturnToStart(cocos2d::Layer * layer);
private:
	void initAnimation();
	
	STATE latestTrend;
	cocos2d::Vec2 coordinates;
	cocos2d::Vec2 diraction;
	cocos2d::Vec2 speedBulles;
	cocos2d::Vec2 m_position;
	cocos2d::Vec2 m_lastPosition;
	cocos2d::Vec2 m_coordinatesGunTank;
	cocos2d::Layer *m_layer;
	GameSprite* m_playerSprite;
	animateVector animVector;
	int m_tag;
	int m_health;
	bool m_bulletReleased = false;
};