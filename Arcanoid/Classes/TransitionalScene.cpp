#include "TransitionalScene.h"
#include "MenuScene.h"
#include "Config.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>

USING_NS_CC;

/*static int g_score;
static int g_level;
static int g_life;*/
static std::shared_ptr<CGameState> g_gameState;

Scene* CTransitionalScene::createScene(std::shared_ptr<CGameState> gameState)
{
	auto scene = Scene::create();
	auto layer = CTransitionalScene::create();
	g_gameState = gameState;
	scene->addChild(layer);
	return scene;
}

bool CTransitionalScene::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}

	m_screenSize = CCDirector::sharedDirector()->getWinSize();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::Sprite* sprite = GameSprite::create("bg_tranc_scene.png");
	sprite->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(sprite);

	auto playItem = MenuItemImage::create("menu.png", "menu_bg.png", CC_CALLBACK_1(CTransitionalScene::gotoMenuScene, this));
	playItem->setPosition(Point(visibleSize.width / 4.0f, visibleSize.height / 4.0f));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	auto gotoGame = MenuItemImage::create("next.png", "next_bg.png", CC_CALLBACK_1(CTransitionalScene::gotoGameScene, this));
	gotoGame->setPosition(Point(visibleSize.width / 1.3f, visibleSize.height / 4.0f));

	auto game = Menu::create(gotoGame, NULL);
	game->setPosition(Point::ZERO);

	this->addChild(game);

	return true;
}

void CTransitionalScene::gotoMenuScene(cocos2d::Ref *sender)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void CTransitionalScene::gotoGameScene(cocos2d::Ref *sender)
{
	auto scene = CGameLayer::createScene(g_gameState);
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}