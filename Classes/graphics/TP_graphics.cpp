// ---------------------------------------
// Sprite definitions for TP_graphics
// Generated with TexturePacker 5.2.0
//
// https://www.codeandweb.com/texturepacker
// ---------------------------------------

#include "TP_graphics.hpp"

USING_NS_CC;

namespace TP
{

void TP_graphics::addSpriteFramesToCache()
{
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("graphics.plist");
};

void TP_graphics::removeSpriteFramesFromCache()
{
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    cache->removeSpriteFramesFromFile("graphics.plist");
};


// ---------------------
// sprite name constants
// ---------------------
const std::string TP_graphics::background       = "background.png";
const std::string TP_graphics::badFish          = "badFish.png";
const std::string TP_graphics::badFish_rotated  = "badFish_rotated.png";
const std::string TP_graphics::bubble           = "bubble.png";
const std::string TP_graphics::buttonRed        = "buttonRed.png";
const std::string TP_graphics::buttonRedPressed = "buttonRedPressed.png";
const std::string TP_graphics::fish01           = "fish01.png";
const std::string TP_graphics::fish02           = "fish02.png";
const std::string TP_graphics::menuBackground   = "menuBackground.png";

// ---------------------------------------------------------
// convenience functions returing pointers to Sprite objects
// ---------------------------------------------------------
Sprite* TP_graphics::createBackgroundSprite()
{
    return Sprite::createWithSpriteFrameName(background);
}

Sprite* TP_graphics::createBadFishSprite()
{
    return Sprite::createWithSpriteFrameName(badFish);
}

Sprite* TP_graphics::createBadFish_rotatedSprite()
{
    return Sprite::createWithSpriteFrameName(badFish_rotated);
}

Sprite* TP_graphics::createBubbleSprite()
{
    return Sprite::createWithSpriteFrameName(bubble);
}

Sprite* TP_graphics::createButtonRedSprite()
{
    return Sprite::createWithSpriteFrameName(buttonRed);
}

Sprite* TP_graphics::createButtonRedPressedSprite()
{
    return Sprite::createWithSpriteFrameName(buttonRedPressed);
}

Sprite* TP_graphics::createFish01Sprite()
{
    return Sprite::createWithSpriteFrameName(fish01);
}

Sprite* TP_graphics::createFish02Sprite()
{
    return Sprite::createWithSpriteFrameName(fish02);
}

Sprite* TP_graphics::createMenuBackgroundSprite()
{
    return Sprite::createWithSpriteFrameName(menuBackground);
}


// ------------------------------------------------
// convenience functions returning animation frames
// ------------------------------------------------

Vector<SpriteFrame*> TP_graphics::getFISHAnimationFrames()
{
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> frames;
    frames.reserve(2);
    frames.pushBack(frameCache->getSpriteFrameByName(fish02));
	frames.pushBack(frameCache->getSpriteFrameByName(fish01));
    return frames;
}


// ----------
// animations
// ----------

Animate *TP_graphics::createFISHAnimateAction(float delay, unsigned int loops)
{
    return Animate::create(Animation::createWithSpriteFrames(getFISHAnimationFrames(), delay, loops));
}

}; // namespace

