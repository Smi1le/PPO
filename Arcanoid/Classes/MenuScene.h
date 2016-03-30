#pragma once
#include "GameLayer.h"

class MenuScene : public cocos2d::Layer
{
public:
	MenuScene() = default;
	~MenuScene() = default;
	CREATE_FUNC(MenuScene);
	static cocos2d::Scene* createScene();
private:
	bool init() override;
	void gotoGameScene(cocos2d::Ref *sender);
};