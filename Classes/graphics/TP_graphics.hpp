// ---------------------------------------
// Sprite definitions for TP_graphics
// Generated with TexturePacker 5.2.0
//
// https://www.codeandweb.com/texturepacker
// 
// $TexturePacker:SmartUpdate:c114e07078ae326cc921ac2d7232b640:bef47a9664d554f7b50f760e1f68661d:2a5da6da057a8fcb4f7524612837011c$
// ---------------------------------------

#ifndef __TP_GRAPHICS_H__
#define __TP_GRAPHICS_H__

#include "cocos2d.h"

namespace TP
{

class TP_graphics
{
public:
    /**
     * Add sprite frames contained in theTP_graphics sheet to
     * the SpriteFrameCache.
     */
    static void addSpriteFramesToCache();

    /**
     * Remove sprite frames contained in theTP_graphics sheet from
     * the SpriteFrameCache.
     */
    static void removeSpriteFramesFromCache();

    // ---------------------
    // sprite name constants
    // ---------------------
    static const std::string background;
    static const std::string badFish;
    static const std::string badFish_rotated;
    static const std::string bubble;
    static const std::string buttonRed;
    static const std::string buttonRedPressed;
    static const std::string fish01;
    static const std::string fish02;
    static const std::string menuBackground;

    // --------------
    // Sprite objects
    // --------------
    static cocos2d::Sprite *createBackgroundSprite();
    static cocos2d::Sprite *createBadFishSprite();
    static cocos2d::Sprite *createBadFish_rotatedSprite();
    static cocos2d::Sprite *createBubbleSprite();
    static cocos2d::Sprite *createButtonRedSprite();
    static cocos2d::Sprite *createButtonRedPressedSprite();
    static cocos2d::Sprite *createFish01Sprite();
    static cocos2d::Sprite *createFish02Sprite();
    static cocos2d::Sprite *createMenuBackgroundSprite();

    // ----------------
    // animation frames
    // ----------------
    static cocos2d::Vector<cocos2d::SpriteFrame*> getFISHAnimationFrames();

    // ---------------
    // animate actions
    // ---------------
    static cocos2d::Animate *createFISHAnimateAction(float delay, unsigned int loops = 1);

}; // class

}; // namespace

#endif // __TP_GRAPHICS_H__
