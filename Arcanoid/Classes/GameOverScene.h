#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__


#include "MenuScene.h"

class CGameOverScene : public cocos2d::Layer
{
public:
	CGameOverScene() = default;
	~CGameOverScene() = default;

	static cocos2d::Scene* createScene(std::shared_ptr<CGameState> gameState);
	bool init() override;
	CREATE_FUNC(CGameOverScene);
private:
	
	void gotoMenuScene(cocos2d::Ref *sender);

	cocos2d::CCSize m_screenSize;
	cocos2d::LabelTTF * m_winner;
	int m_playerScore;
};

#endif // __MENUSCENE_H__