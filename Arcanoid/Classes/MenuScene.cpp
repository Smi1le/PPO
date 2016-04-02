#include "MenuScene.h"
#include "GameLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Config.h"

USING_NS_CC;



Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	CCSize m_screenSize = CCDirector::sharedDirector()->getWinSize();

	auto playItem = MenuItemImage::create("game.png", "game_bg.png", CC_CALLBACK_1(MenuScene::gotoGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	
	return true;
}

void MenuScene::gotoGameScene(cocos2d::Ref *sender)
{
	auto scene = CGameLayer::createScene(std::make_shared<CGameState>(0, ACCELERATION, 0, NUMBER_LIFE));
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}