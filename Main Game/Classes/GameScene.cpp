#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Brick.h"
//#include "Player.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

Scene* CGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//g_gameState = gameState;
	auto layer = CGameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool CGameScene::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	if (!Layer::init())
	{
		return false;
	}

	

	m_tileMap = new CCTMXTiledMap();
	m_tileMap->initWithTMXFile("level.tmx");
	m_background = m_tileMap->layerNamed("Objects");
	CCTMXObjectGroup *objectGroup = m_tileMap->objectGroupNamed("Objects");
	CCTMXObjectGroup *noDestroySolids = m_tileMap->objectGroupNamed("NoDestroyObjects");
	m_tileMap->setPosition(Vec2(64, 0));

	int i = 100;
	for (Value solid1 : objectGroup->getObjects())
	{
		ValueMap props = solid1.asValueMap();
		CBrick *_block = new (std::nothrow) CBrick();
		if (!_block->init(this, Vec2(props.at("x").asFloat() + 77.f, props.at("y").asFloat() + 11.f), i))
		{
			return false;
		}
		m_blocksSprite.push_back(_block);
		++i;
	}

	

	CCLOG("**********************");
	for (Value solid : noDestroySolids->getObjects())
	{
		ValueMap props = solid.asValueMap();
		auto gateBody = PhysicsBody::createBox(Size(props.at("width").asFloat(), props.at("height").asFloat()));
		gateBody->setDynamic(false);
		gateBody->setContactTestBitmask(true);
		gateBody->setCollisionBitmask(BORDER_CONTACT_BITMASK);
		//gateBody->setContactTestBitmask(true);
		CCLOG(std::to_string(props.at("x").asFloat() + 77.f).c_str());
		CCLOG(std::to_string(props.at("y").asFloat() + 11.f).c_str());
		auto gateNode = make_cc<Node>();
		gateNode->setPosition(Point(props.at("x").asFloat() + (props.at("width").asFloat() / 2.f) + 64.f,
			(props.at("y").asFloat() + (props.at("height").asFloat() / 2.f))));
		gateNode->setPhysicsBody(gateBody);
		this->addChild(gateNode);
	}
	CCLOG("++++++++++++++++++++++++++++++++++");
	CCTMXObjectGroup *object = m_tileMap->objectGroupNamed("Player");
	m_player = new (std::nothrow) CPlayer;
	ValueMap props = object->getObject("player");
	CCLOG(std::to_string(props.at("x").asFloat()).c_str());
	CCLOG(std::to_string(props.at("y").asFloat()).c_str());
	m_player->init(this, Vec2(props.at("x").asFloat() + 77.f, props.at("y").asFloat() + 11.f));
	this->addChild(m_tileMap);


	CButton *butUp = new CButton(); // 100 100
	butUp->init(this, Vec2(50.f, 275.f), 1000, TypeButton::UP, "Up.png", "Up-bg.png");
	m_buttons.push_back(butUp);

	CButton *butLeft = new CButton();// 50 50
	butLeft->init(this, Vec2(50.f, 125.f), 1001, TypeButton::LEFT, "Left.png", "Left-bg.png");
	m_buttons.push_back(butLeft);

	CButton *butDown = new CButton(); // 100 50
	butDown->init(this, Vec2(50.f, 200.f), 1002, TypeButton::DOWN, "Down.png", "Down-bg.png");
	m_buttons.push_back(butDown);

	CButton *butRight = new CButton(); // 150 50
	butRight->init(this, Vec2(50.f, 50.f), 1003, TypeButton::RIGHT, "Right.png", "Right-bg.png");
	m_buttons.push_back(butRight);
	
	auto fire = MenuItemImage::create("psd_2_.png", "psd_back.png", CC_CALLBACK_1(CGameScene::ShootPlayer, this));
	fire->setPosition(Point(400.f, 500.f));

	auto buttonFire = Menu::create(fire, NULL);
	buttonFire->setPosition(Point::ZERO);

	this->addChild(buttonFire);

	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CGameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CGameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CGameScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->setTouchEnabled(true);

	this->scheduleUpdate();
	return true;
}

bool CGameScene::onTouchBegan(Touch* touches, Event* event) {
	if (touches)
	{
		auto point = touches->getLocation();
		for (auto button : m_buttons)
		{
			if (button->IsContainsPoint(point))
			{
				button->IsTouch = true;
				m_player->isMove = true;
				return true;
			}
		}
	}
	return false;
}

void CGameScene::onTouchMoved(Touch* touches, Event* event) 
{
	
}

void CGameScene::onTouchEnded(Touch* touches, Event* event)
{
	for (auto button : m_buttons)
	{
		if (button->IsTouch)
		{
			button->IsTouch = false;
			m_player->isMove = false;
			m_player->Control(STATE::STAY);
		}
	}
}

void CGameScene::StepPlayer()
{
	for (auto button : m_buttons)
	{
		if (button->IsTouch)
		{
			if (button->GetTypeButton() == TypeButton::DOWN)
			{
				m_player->Control(STATE::DOWN);
			}
			if (button->GetTypeButton() == TypeButton::LEFT)
			{
				m_player->Control(STATE::LEFT);
			}
			if (button->GetTypeButton() == TypeButton::RIGHT)
			{
				m_player->Control(STATE::RIGHT);
			}
			if (button->GetTypeButton() == TypeButton::UP)
			{
				m_player->Control(STATE::UP);
			}
		}
	}
}

void CGameScene::update(float dt)
{
	if (m_player->isMove)
	{
		StepPlayer();
	}
	
}

bool CGameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	if (((MASK_PLAYER == a->getCollisionBitmask()) &&
		(BORDER_CONTACT_BITMASK == b->getCollisionBitmask())) ||
		((MASK_PLAYER == b->getCollisionBitmask()) &&
		(BORDER_CONTACT_BITMASK == a->getCollisionBitmask())))
	{
		m_player->isMove = false;
		return true;
	}
	else if (((MASK_PLAYER == a->getCollisionBitmask()) &&
		(MASK_BRICK == b->getCollisionBitmask())) ||
		((MASK_PLAYER == b->getCollisionBitmask()) &&
		(MASK_BRICK == a->getCollisionBitmask())))
	{
		m_player->isMove = false;
		return true;
	}
	else if (((BORDER_CONTACT_BITMASK == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask())) ||
		((BORDER_CONTACT_BITMASK == b->getCollisionBitmask()) &&
		(MASK_BULLET == a->getCollisionBitmask())))
	{
		removeChildByTag(TAG_BULLET_PLAYER);
		return true;
	}
	else if (((MASK_BRICK == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask())) ||
		((MASK_BRICK == b->getCollisionBitmask()) &&
		(MASK_BULLET == a->getCollisionBitmask())))
	{
		CCLOG(std::to_string(a->getTag()).c_str());
		CCLOG(std::to_string(b->getTag()).c_str());
		if (a->getNode() != NULL)
		{
			removeChildByTag(a->getNode()->getTag());
		}
		if (b->getNode() != NULL)
		{
			removeChildByTag(b->getNode()->getTag());
		}
		return true;
	}
	m_player->isMove = true;
	return false;
}

void CGameScene::ShootPlayer(cocos2d::Ref *ref)
{
	m_player->Shoot(this);
}