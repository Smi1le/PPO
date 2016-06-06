#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "Brick.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"
#include "gameState.h"



class CGameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int livesPlayer);
	virtual bool init();
	CREATE_FUNC(CGameScene);

private:
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	bool onTouchBegan(cocos2d::Touch* touches, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touches, cocos2d::Event* event);
	void update(float dt);
	void ShootPlayer(cocos2d::Ref *ref);
	void StepPlayer();
	void GoToGameOverScene(cocos2d::Ref *sender);
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_sceneWorld = world; };
	void ChangeDirEnemy(float dt);
	void AddEnemy(float dt);
	void MinusPlayerLives();
	void AddBonus();

private:
	bool initGameObjects(cocos2d::TMXTiledMap *tileMap);
	void CreateButton();
	STATE m_state;
	cocos2d::LabelTTF *m_labelHealthPlayer;
	GameSprite* m_eagleSprite;
	//cocos2d::TMXTiledMap *tileMap;
	//cocos2d::TMXLayer *m_background;
	std::vector<CBrick*> m_blocksSprite;
	std::vector<CButton*> m_buttons;
	std::vector<CEnemy*> m_enemyList;
	std::vector<cocos2d::ValueMap> m_respPositions;
	cocos2d::PhysicsWorld *m_sceneWorld;
	cocos2d::CCSize m_visibleSize;
	float m_timer;
	bool m_needTimer = false;
	bool needBonus = false;
	cocos2d::Vec2 m_origin;
	CPlayer *m_player;
	CAnimation m_animation;
};

#endif // __GAME_SCENE_H__