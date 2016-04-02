#include "GameOverScene.h"
#include "Config.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>

USING_NS_CC;

static std::shared_ptr<CGameState> g_gameState;

Scene* CGameOverScene::createScene(std::shared_ptr<CGameState> gameState)
{
	auto scene = Scene::create();
	auto layer = CGameOverScene::create();
	g_gameState = gameState;
	scene->addChild(layer);
	return scene;
}

bool CGameOverScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_screenSize = CCDirector::sharedDirector()->getWinSize();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::Sprite* sprite = Sprite::create("game_over_bg.png");
	sprite->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(sprite);

	auto playItem = MenuItemImage::create("menu.png", "menu_bg.png", CC_CALLBACK_1(CGameOverScene::gotoMenuScene, this));
	playItem->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 4.0f));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	m_winner = CCLabelTTF::create("Game Over", "Arial", SIZE_LABEL);
	m_winner->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	m_winner->setColor(COLOR_LABEL);
	m_winner->setTag(TAG_SCORE_LABEL);
	this->addChild(m_winner);

	return true;
}

void CGameOverScene::gotoMenuScene(cocos2d::Ref *sender)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}