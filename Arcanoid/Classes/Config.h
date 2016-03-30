#pragma once
#include "cocos2d.h"


static const int MAX_NUMBER_BLOCKS = 63;
static const int SIZE_LABEL = 25;
static const int TAG_PLAYER_SCORE_LABEL = 13;
static const int TAG_SCORE_LABEL = 14;
static const int TAG_BALL = 50;
static const int TAG_START_BLOCK = 100;
static const int NUMBER_LIFE = 3;

static const auto MASK_BALL = 0x02;
static const auto MASK_RACKET = 0x01;
static const auto MASK_BLOCK = 0x03;
static const auto BORDER_CONTACT_BITMASK = 0xffff;

static const float ACCELERATION = 0.05f;
static const cocos2d::Color3B COLOR_LABEL = { 23, 244, 244 };


template <class T, class ...TArgs>
T *make_cc(TArgs&&... args)
{
	T *ret = new (std::nothrow) T;
	if (ret && ret->init(std::forward<TArgs>(args)...)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}