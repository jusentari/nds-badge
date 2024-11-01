#include "sprite.hpp"
#include "tween.hpp"
#include <nds/arm9/sprite.h>
#include <nds/arm9/trig_lut.h>

static u8 lastSpriteNo = 0;

Sprite::Sprite(u8* gfx, int newWidth, int newHeight, bool newIsSub, bool newIsMainAnim, int palette){
	spriteGfxLoc = gfx;
	width = newWidth;
	height = newHeight;
	// TODO: Def change this based on color/size of sprite
    u32 bytes = (64*64) >> 1;
	if(newHeight <= 16 && newWidth <= 16){
		spriteSize = SpriteSize_16x16;
		bytes = (16*16) >> 1;
	}
	u8 subSpriteNo = 0;
	subSprites = spritesWide() * spritesTall();
	isSub = newIsSub;
	isMainAnim = newIsMainAnim;
    
	while(subSpriteNo < subSprites){
		vramLocations[subSpriteNo] = oamAllocateGfx(isSub ? &oamSub : &oamMain, spriteSize, SpriteColorFormat_16Color);
		dmaCopy(gfx + (bytes * subSpriteNo), vramLocations[subSpriteNo], bytes);
		subSpriteNo++;
	}
	spriteStartId = lastSpriteNo;
	lastSpriteNo += subSpriteNo;
	paletteNo = palette;
	Move(0, 0);
};

bool Sprite::LinearMove(int destX, int destY, int frames){
	return false;
}

void Sprite::Move(int newX, int newY){
	this->x = newX;
	this->y = newY;
}

void Sprite::DebugMovement(){
	frame++;
	int subSpriteNo = spriteStartId;
	while(subSpriteNo < subSprites){
		int DEBUG_spritePosX = (subSpriteNo % spritesWide()) * 64 + (sinLerp((frame + (subSpriteNo << 3)) << 5) >> 7);
		int DEBUG_spritePosY = (subSpriteNo / spritesWide())*64 + (cosLerp((frame + (subSpriteNo << 2)) << 7) >> 7);
		//int DEBUG_spritePosX = (subSpriteNo % spritesWide()) * 64;
		//int DEBUG_spritePosY = (subSpriteNo / spritesWide()) * 64;
		Move(DEBUG_spritePosX, DEBUG_spritePosY);
		subSpriteNo++;
	}
}

void Sprite::Update(){
	frame++;
	int subSpriteNo = 0;
	while(subSpriteNo < subSprites){
		int adjustedX = ((subSpriteNo % spritesWide()) * 64) + x;
		int adjustedY = ((subSpriteNo / spritesWide()) * 64) + y;
		//int DEBUG_spritePosX = (subSpriteNo % spritesWide()) * 64;
		//int DEBUG_spritePosY = (subSpriteNo / spritesWide()) * 64;
		oamSet(isSub ? &oamSub : &oamMain, subSpriteNo + spriteStartId, adjustedX, adjustedY, priority, paletteNo, spriteSize, SpriteColorFormat_16Color, 
		vramLocations[subSpriteNo], -1, false, isHidden, false, false, false);
		subSpriteNo++;
	}
}

void Sprite::AddTween(Tween* t){
	// dont work, revisit this
	//tweens.push_back(t);
	tween = t;
}

const int Sprite::spritesWide(){
	return (width + 63) / 64;
}

const int Sprite::spritesTall(){
	return (height + 63) / 64;
}

SpriteSpawner::SpriteSpawner(){}

Sprite* SpriteSpawner::Create(u8* gfx, int width, int height, bool newIsSub){
	Sprite* retSprite = new Sprite(gfx, width, height, newIsSub, false);
	sprites.push_back(retSprite);
	return retSprite;
}

void Sprite::setScale(int hdx, int hdy){
	oamSetAffineIndex (&oamMain, spriteStartId, rotId, false);
	oamRotateScale(&oamMain, rotId, 0, hdx, hdy);
}