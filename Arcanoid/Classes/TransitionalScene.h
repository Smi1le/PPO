#pragma once
#include "GameLayer.h"

class CTransitionalScene : public cocos2d::LayerColor
{
public:
	CTransitionalScene() = default;
	~CTransitionalScene() = default;
	
	static cocos2d::Scene* createScene(std::shared_ptr<CGameState> gameState);

	CREATE_FUNC(CTransitionalScene);
private:
	bool init() override;
	void gotoMenuScene(cocos2d::Ref *sender);
	void gotoGameScene(cocos2d::Ref *sender);

	CCSize m_screenSize;
	cocos2d::LabelTTF * m_winner;
	int m_playerScore;
};