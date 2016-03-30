#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__
#define GOAL_WIDTH 400

#include "cocos2d.h"
#include <vector>

#include "Ball.h"
#include "Racket.h"
#include "Block.h"

class CGameLayer : public cocos2d::Layer
{
public:
	CGameLayer() = default;
	~CGameLayer() = default;

	static cocos2d::Scene* createScene(int score, float acc, int level, int life);
	virtual bool init();
	void playerScore();
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_sceneWorld = world; };
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	bool onTouchBegan(Touch* pTouches, CCEvent* event);
	void onTouchMoved(Touch* pTouches, CCEvent* event);
	void onTouchEnded(Touch* pTouches, CCEvent* event);
	void update(float dt);
    CREATE_FUNC(CGameLayer);
private:
	void gotoMenuScene(cocos2d::Ref *sender);
	void gotoGameOverScene(cocos2d::Ref *sender);

	int m_playerScore;
	CCLabelTTF * m_labelScore;
	CCLabelTTF * m_playerScoreLabel;
	cocos2d::PhysicsWorld *m_sceneWorld;
	cocos2d::CCSize m_screenSize;
	cocos2d::CCSize m_visibleSize;
	cocos2d::Vec2 m_origin;
	std::vector<CBlock *> m_blocks;

	std::vector<CBall*> m_ball;
	CRacket * m_player1;
	
	bool m_flag = false;
	bool m_startBallMovement = false;
};

#endif // __HELLOWORLD_SCENE_H__
