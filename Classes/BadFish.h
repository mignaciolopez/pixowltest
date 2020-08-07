#ifndef BAD_FISH_H
#define BAD_FISH_H

#include "cocos2d.h"
#include "graphics/TP_graphics.hpp"

class BadFish : public cocos2d::Sprite
{
public:
	static BadFish* createBadFish();

	virtual bool init() override;

	CREATE_FUNC(BadFish);

	bool didReachCenter();

private:
	void setRandomPosition();
	void runAxnToCenter();
	void gameOver();

	bool m_reachCenter = false;
};

#endif // !BAD_FISH_H