#pragma once
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include <sstream>
//#include <cstdlib>
//#include <stdlib.h>
//#include <random>
#include <vector>
//#include <list>
//#include <ctime>
//#include <crtdbg.h>
#include "GameSprite.h"
//#include "level.h"
#include "Config.h"
//#include "vld.h"
//#include <memory>
//#include "music.h"




//#include "levelObject.h"

class CPlayer {
public:
	//std::vector<Object> obj;
	float speed;
	float currentFrame;
	float delay;
	float frame;
	int w;
	int h;
	int health;
	int individualNumber;
	int individualNumberBonus;
	int numberEnemyTank;
	//enum { LEFT, RIGHT, UP, DOWN, STAY } state;
	cocos2d::Vec2 coordinatesGunTank;
	bool alive;
	
	bool onGround;
	bool bulletReleased = false;
	bool isBlock;
	
	
	//Texture *texture;
	//Sprite *sprite;
	//String name;

	std::vector<int> permittedMovementOptions;
	//CPlayer* create(cocos2d::Layer * layer, cocos2d::Vec2 position);
	bool isMove = true;
	void Shoot(cocos2d::Layer *layer);
	bool init(cocos2d::Layer * layer, cocos2d::Vec2 position);
	void SetPosition(cocos2d::Vec2 const &pos);
	void Control(STATE const &state);

	//CREATE_FUNC(CPlayer);
private:
	
	STATE latestTrend;
	cocos2d::Vec2 coordinates;
	cocos2d::Vec2 diraction;
	cocos2d::Vec2 speedBulles;
	cocos2d::Vec2 m_position;
	cocos2d::Vec2 m_lastPosition;
	cocos2d::Vec2 m_coordinatesGunTank;
	GameSprite* m_playerSprite;
	int m_tag;
	//FloatRect getRect();
	
	//virtual void update(float time, vector<Object> &obj, music *sound) = 0;
};