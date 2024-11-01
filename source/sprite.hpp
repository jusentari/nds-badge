#include <nds.h>
#include <vector>
#include <nds/arm9/sprite.h>
// should use a bitmap at some point but whatever
#ifndef SPRITE_H
#define SPRITE_H
class Tween;
class Sprite 
{
	public:
		int x;
		int y;
		int width = 64;
		int height = 64;
		bool isMainAnim = false;
		const int spritesWide();
		const int spritesTall();
		u8*  spriteGfxLoc = 0;
		bool willBubble = false;
		// Max of 12 because that is how many 64x64 sprites fit on screen
		// TODO: Increase this if I want sprites bigger than size of screen?
		u16* vramLocations[12] = {0};
		int spriteStartId = 0;
		void Move(int newX, int newY);
		void DebugMovement();
		void Update();
		void BubbleUpdate();
		bool LinearMove(int destX, int destY, int frames);
		void AddTween(Tween* t);

		int state;
		int paletteNo;
		int priority = 0;
		uint32 frame = 0;
		int subSprites;
		bool isHidden = false;
		bool isSub = false;
		SpriteSize spriteSize = SpriteSize_64x64;
		int velocityX = 0;
		int velocityY = 0;
		//std::vector<Tween> tweens;
		Tween* tween = nullptr;
		void setScale(int hdx, int hdy);
		int rotId = 0;
		Sprite(u8* gfx, int width, int height, bool newIsSub, bool newIsMainAnim, int palette = 0);
};
static std::vector<Sprite*> sprites;
// for some reason static methods were not working in Sprite so i gave up lol
class SpriteSpawner {
	public:
		SpriteSpawner();
		Sprite* Create(u8* gfx, int width, int height, bool newIsSub);
};
#endif