#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__
#define GOAL_WIDTH 400

#include "cocos2d.h"
#include <vector>

#include "Ball.h"
#include "Racket.h"
#include "Block.h"
#include "MenuScene.h"

class CGameLayer : public cocos2d::Layer
{
public:
	/*CGameLayer() = default;
	~CGameLayer() = default;
	*/
	static cocos2d::Scene* createScene(std::shared_ptr<CGameState> gameState);
	bool init() override;
    CREATE_FUNC(CGameLayer);
private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_sceneWorld = world; };
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	bool onTouchBegan(Touch* pTouches, Event* event);
	void onTouchMoved(Touch* pTouches, Event* event);
	void onTouchEnded(Touch* pTouches, Event* event);
	void update(float dt);
	void playerScore();
	void gotoMenuScene(cocos2d::Ref *sender);
	void gotoTrancScene(cocos2d::Ref *sender);
	void gotoGameOver(cocos2d::Ref *sender);
	

	CCLabelTTF * m_labelScore;
	CCLabelTTF * m_playerScoreLabel;
	cocos2d::PhysicsWorld *m_sceneWorld;
	cocos2d::CCSize m_screenSize;
	cocos2d::CCSize m_visibleSize;
	cocos2d::Vec2 m_origin;
	std::vector<CBlock *> m_blocks;
	std::vector<CBall*> m_ball;
	//CBall *m_ball;
	CRacket * m_player;
	bool m_flag = false;
	bool m_startBallMovement = false;
};

#endif // __HELLOWORLD_SCENE_H__
