#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameSprite.h"
#include "Config.h"

class CEnemy : public cocos2d::Layer
{
public:
	bool init(cocos2d::Vec2 const &pos, STATE const &state, int tag, cocos2d::Layer *layer);
	int GetTag() const;
	int GetBulletTag() const;
	void ChangeResolution();
	bool IsShot()const;
	void ChangeDirection();
	cocos2d::Vec2 GetPosition() const;
	void Update(cocos2d::Layer *layer);
	void Shoot(cocos2d::Layer *layer);
	void Control(STATE const &state);
private:
	void initAnimation();
	GameSprite *m_enemySprite;
	cocos2d::Vector<cocos2d::Animate*> animVector;
	cocos2d::Vector<cocos2d::Animate*> easyAnimVector;
	cocos2d::Vector<cocos2d::Animate*> fastAnimVector;
	cocos2d::Vec2 m_position;
	float m_speed;
	cocos2d::PhysicsBody* m_body;
	int m_tag;
	int m_bulletTag;
	bool m_bulletReleased = false;
	STATE m_state;
};

#endif // __ENEMY_H__