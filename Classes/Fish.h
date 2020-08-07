#ifndef FISH_H
#define FISH_H

#include "cocos2d.h"
#include "graphics/TP_graphics.hpp"

class Fish : public cocos2d::Sprite
{
public:
	static Fish* createFish();

	virtual bool init() override;

	CREATE_FUNC(Fish);

	void rotate(cocos2d::Vec2 touchLocation);

private:
	cocos2d::Animation m_fishAnimation;
};

#endif // !FISH_H