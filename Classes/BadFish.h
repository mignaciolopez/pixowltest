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

private:
	void setRandomPosition();
	void runAxnToCenter();

	float m_badFishScale;

	unsigned int m_badFishMinVel, m_badFishMaxVel;

};

#endif // !BAD_FISH_H