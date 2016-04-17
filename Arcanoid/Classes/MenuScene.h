#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "GameState.h"
#include "cocos2d.h"


class MenuScene : public cocos2d::Layer
{
public:
	MenuScene() = default;
	~MenuScene() = default;
	CREATE_FUNC(MenuScene);
	static cocos2d::Scene* createScene();
	bool init() override;
private:
	
	void gotoGameScene(cocos2d::Ref *sender);
};

#endif // __MENU_SCENE_H__