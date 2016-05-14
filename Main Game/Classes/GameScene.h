#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "Brick.h"
#include "Player.h"
#include "Button.h"

class CGameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(CGameScene);

private:
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	//bool onContactSeparate(cocos2d::PhysicsContact &contact);
	bool onTouchBegan(Touch* touches, Event* event);
	void onTouchMoved(Touch* touches, Event* event);
	void onTouchEnded(Touch* touches, Event* event);
	void update(float dt);
	void ShootPlayer(cocos2d::Ref *ref);
	void StepPlayer();
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_sceneWorld = world; };
	STATE m_state;
	//void Control() { int x; };
	cocos2d::TMXTiledMap *m_tileMap;
	cocos2d::TMXLayer *m_background;
	std::vector<CBrick*> m_blocksSprite;
	std::vector<CButton*> m_buttons;
	cocos2d::PhysicsWorld *m_sceneWorld;
	//cocos2d::CCSize m_screenSize;
	cocos2d::CCSize m_visibleSize;
	cocos2d::Vec2 m_origin;
	CPlayer *m_player;
};

#endif // __GAME_SCENE_H__