#include "MenuScene.h"
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

	auto sprite = GameSprite::create("bg_menu.png");
	sprite->setPosition(ccp(m_screenSize.width * 0.5, m_screenSize.height* 0.5));
	this->addChild(sprite);

	auto playItem = MenuItemImage::create("_bmp.png", "mallet.png", CC_CALLBACK_1(MenuScene::gotoGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	
	return true;
}

void MenuScene::gotoGameScene(cocos2d::Ref *sender)
{
	auto scene = CGameLayer::createScene(0, ACCELERATION, 0, NUMBER_LIFE);
	CCLOG("goto Game Scene");
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}