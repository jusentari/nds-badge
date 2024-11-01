#include "template.hpp"
#include <pac1.h>
#include <jusent_spritesmall1.h>
#include <jusent_spritesmall3.h>
#include <jusent_spritesmall4.h>
#include <jusent_spritesmall5.h>
#include <jusent_spritesmall2.h>
#include <jusent_spritesmall6.h>
#include <jusent_spritesmall9.h>
#include <jusent_spritesmall8.h>
#include <jusent_spritesmall7.h>
#include <bg1.h>
#include <orb1.h>
#include <orb2.h>
#include <orb3.h>
#include <orb4.h>
#include <pacbust.h>
#include "sprite.hpp"
#include <pacpaw.h>
#include <jusent_spritesmall0.h>
#include <eyes_blink1.h>
#include <eyes_blink2.h>
#include <eyes_blink3.h>

int frameNo = 0;
uint32 oldKeys = 0;
uint32 blinkTime = 300;

u16 paletteColors[8] = {0xfb00, 0xfd60, 0xd92f, 0x2104, 0x7afd, 0xffff, 0xef7d, 0x647f};
//u16 pacColors[8] = 	{0x2997, 0x24E6,0x10AD,0x148E,0x0000,0x0000,0x0000};

void startFileAnim(Sprite* bottomFile, Sprite* topFile){
	//fileFrame = 0;a
	topFile->Move(157, 220);
	Tween* t = new Tween(bottomFile);
	t->LinearMove(bottomFile->x, -16, frameNo, 80);
	topFile->isHidden = false;
	Tween* t2 = new Tween(topFile);
	t2->LinearMove(157, 142, frameNo, 80, 80);
	Tween* t3 = new Tween(topFile);
	t3->LinearMove(272, 142, frameNo, 80, 161);
	tweens.push_back(t);
	tweens.push_back(t2);
	tweens.push_back(t3);
}

/*
Sprite* createCircleSprite(int radius){
	int size = ((radius - 1) * 2) + 1;
	u8* circleSprite = (u8*) calloc(size * size, 1);
	int iterations = 128;
	int degreesPerIteration = DEGREES_IN_CIRCLE / iterations;
	for(int i = 0; i < iterations; i++){
		int x = floorFixed(cosLerp(degreesPerIteration * i) * radius, 12) >> 12;
		int y = floorFixed(sinLerp(degreesPerIteration * i) * radius, 12) >> 12;
		circleSprite[x+(y*size)] = 1;
	}
	Sprite* pac = new Sprite((u8*) circleSprite, size, size, false, true);
	sprites.push_back(pac);
	return pac;
}*/

int main(void)
{
	// set the mode for 2 text layers and two extended background layers
	videoSetMode(MODE_5_2D);

	// set the sub background up for text display (we could just print to one
	// of the main display text backgrounds just as easily
	videoSetModeSub(MODE_5_2D); // sub bg 0 will be used to print text

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_SPRITE);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	fatInitDefault();

	oamInit(&oamMain, SpriteMapping_1D_256, false);
	oamInit(&oamSub, SpriteMapping_1D_256, false);

	//Sprite* sp = new Sprite((u8*) dissolutionTiles, dissolutionWidth, dissolutionHeight, false, false);
	//sprites.push_back(sp);
	//Sprite* pac = new Sprite((u8*) pac1Tiles, pac1Width, pac1Height, false, true);
	//sprites.push_back(pac);
	Sprite* pacbust = new Sprite((u8*) pacbustTiles, pacbustWidth, pacbustHeight, false, true, 1);
	sprites.push_back(pacbust);
	pacbust->priority = 2;
	pacbust->Move(72, 10);
	Sprite* pacpaw = new Sprite((u8*) pacpawTiles, pacpawWidth, pacpawHeight, false, true, 2);
	sprites.push_back(pacpaw);
	pacpaw->priority = 0;
	pacpaw->Move(81, 146);
	Sprite* paceye1 = new Sprite((u8*) eyes_blink1Tiles, eyes_blink1Width, eyes_blink1Height, false, true, 3);
	sprites.push_back(paceye1);
	paceye1->priority = 1;
	paceye1->Move(105, 65);
	Sprite* paceye2 = new Sprite((u8*) eyes_blink2Tiles, eyes_blink2Width, eyes_blink2Height, false, true, 3);
	sprites.push_back(paceye2);
	paceye2->priority = 1;
	paceye2->Move(105, 65);
	Sprite* paceye3 = new Sprite((u8*) eyes_blink3Tiles, eyes_blink3Width, eyes_blink3Height, false, true, 3);
	sprites.push_back(paceye3);
	paceye3->priority = 1;
	paceye3->Move(105, 65);

	//Sprite* slashSprite = new Sprite((u8*) jusent_spritesmall0Tiles, jusent_spritesmall0Width, jusent_spritesmall0Height, false, true);
	//sprites.push_back(slashSprite);
	//slashSprite->Move(4, 159);
	Sprite* jSprite = new Sprite((u8*) jusent_spritesmall1Tiles, jusent_spritesmall1Width, jusent_spritesmall1Height, false, true, 4);
	sprites.push_back(jSprite);
	jSprite->Move(24, 159);
	Sprite* uSprite = new Sprite((u8*) jusent_spritesmall2Tiles, jusent_spritesmall2Width, jusent_spritesmall2Height, false, true, 4);
	sprites.push_back(uSprite);
	uSprite->Move(46, 159);
	Sprite* sSprite = new Sprite((u8*) jusent_spritesmall3Tiles, jusent_spritesmall3Width, jusent_spritesmall3Height, false, true, 4);
	sprites.push_back(sSprite);
	sSprite->Move(72, 159);
	Sprite* eSprite = new Sprite((u8*) jusent_spritesmall4Tiles, jusent_spritesmall4Width, jusent_spritesmall4Height, false, true, 4);
	sprites.push_back(eSprite);
	eSprite->Move(95, 159);
	Sprite* nSprite = new Sprite((u8*) jusent_spritesmall5Tiles, jusent_spritesmall5Width, jusent_spritesmall5Height, false, true, 4);
	sprites.push_back(nSprite);
	nSprite->Move(119, 159);
	Sprite* tSprite = new Sprite((u8*) jusent_spritesmall6Tiles, jusent_spritesmall6Width, jusent_spritesmall6Height, false, true, 4);
	sprites.push_back(tSprite);
	tSprite->Move(143, 159);
	Sprite* aSprite = new Sprite((u8*) jusent_spritesmall7Tiles, jusent_spritesmall7Width, jusent_spritesmall7Height, false, true, 4);
	sprites.push_back(aSprite);
	aSprite->Move(167, 159);
	Sprite* rSprite = new Sprite((u8*) jusent_spritesmall8Tiles, jusent_spritesmall8Width, jusent_spritesmall8Height, false, true, 4);
	sprites.push_back(rSprite);
	rSprite->Move(191, 159);
	Sprite* iSprite = new Sprite((u8*) jusent_spritesmall9Tiles, jusent_spritesmall9Width, jusent_spritesmall9Height, false, true, 4);
	sprites.push_back(iSprite);
	iSprite->Move(215, 159);
	Sprite* orb1Sprite = new Sprite((u8*) orb1Tiles, orb1Width, orb1Height, false, true, 4);
	sprites.push_back(orb1Sprite);
	orb1Sprite->Move(30, 300);
	Sprite* orb2Sprite = new Sprite((u8*) orb2Tiles, orb2Width, orb2Height, false, true, 4);
	sprites.push_back(orb2Sprite);
	orb2Sprite->Move(100, 300);
	Sprite* orb3Sprite = new Sprite((u8*) orb3Tiles, orb3Width, orb3Height, false, true, 4);
	sprites.push_back(orb3Sprite);
	orb3Sprite->Move(190, 300);
	Sprite* orb4Sprite = new Sprite((u8*) orb4Tiles, orb4Width, orb4Height, false, true, 4);
	sprites.push_back(orb4Sprite);
	orb4Sprite->Move(240, 300);
	orb1Sprite->willBubble = true;
	orb1Sprite->priority = 3;
	orb1Sprite->rotId = 1;
	orb2Sprite->willBubble = true;
	orb2Sprite->priority = 3;
	orb1Sprite->rotId = 2;
	orb3Sprite->willBubble = true;
	orb3Sprite->priority = 3;
	orb1Sprite->rotId = 3;
	orb4Sprite->willBubble = true;
	orb4Sprite->priority = 3;
	orb1Sprite->rotId = 4;
	Tween* t = new Tween(orb1Sprite);
	t->LinearMove(orb1Sprite->x, -64, frameNo, 240);
	orb1Sprite->AddTween(t);
	tweens.push_back(t);
	Tween* t2 = new Tween(orb2Sprite);
	t2->LinearMove(orb2Sprite->x, -74, frameNo, 240);
	orb2Sprite->AddTween(t2);
	tweens.push_back(t2);
	Tween* t3 = new Tween(orb3Sprite);
	t3->LinearMove(orb3Sprite->x, -84, frameNo, 240);
	orb3Sprite->AddTween(t3);
	tweens.push_back(t3);
	Tween* t4 = new Tween(orb4Sprite);
	t4->LinearMove(orb4Sprite->x, -94, frameNo, 240);
	orb4Sprite->AddTween(t4);
	tweens.push_back(t4);
	Sprite* fileSprite = new Sprite((u8*) smallfileTiles, smallfileWidth, smallfileHeight, true, false);
	sprites.push_back(fileSprite);
	Sprite* fileTopSprite = new Sprite((u8*) smallfileTiles, smallfileWidth, smallfileHeight, false, false);
	sprites.push_back(fileTopSprite);
	fileTopSprite->Move(157, 200);
	//Sprite* spr = createCircleSprite(10);
	//sprites.push_back(spr);
	//spr->Move(157, 200);
	Menu menu = Menu();
	srand(time(nullptr));

	fileSprite->isHidden = true;
	fileTopSprite->isHidden = true;
	dmaCopy(bg1Pal, BG_PALETTE, 512);
	dmaCopy(paletteColors, SPRITE_PALETTE, 512);
	dmaCopy(pacbustPal, &(SPRITE_PALETTE[16]), pacbustPalLen);
	dmaCopy(pacpawPal, &(SPRITE_PALETTE[32]), pacpawPalLen);
	dmaCopy(eyes_blink1Pal, &(SPRITE_PALETTE[48]), pacbustPalLen);
	dmaCopy(jusent_spritesmall1Pal, &(SPRITE_PALETTE[64]), jusent_spritesmall1PalLen);
	uint32 white = 0xFFFFFFFF;
	dmaCopy(&white, &(SPRITE_PALETTE[80]), 4);
	dmaCopy(&white, &(SPRITE_PALETTE[82]), 4);
	dmaCopy(smallfilePal, SPRITE_PALETTE_SUB, 512);

	// set up our bitmap background
	int topBg = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(bg1Tiles, BG_GFX, bg1TilesLen);
	bgSetPriority(topBg, 3);

	//TODO: Use a pallete and maybe the 4bpp bgsize? Just for memory saving
	int userBg = bgInitSub(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	//decompress(newpacBitmap, BG_GFX, LZ77Vram);
	clearBg();
	showMainAnim = true;

	while (1)
	{
		scanKeys();
		uint32 keys = keysDown();
		uint32 keysJustPressed = (keys ^ oldKeys) & keys;
		touchPosition p;
		touchRead(&p);
		if(!menu.isVisible){
			displayColors(&p);
			displayBrushSizes(&p);
		}
		samples[0] = samples[1];
		samples[1] = samples[2];
		samples[2] = p;
		if(samples[0].px != 0 && samples[1].px != 0 && samples[2].px != 0)
			drawFromSamples();
		if (keys & KEY_SELECT)
		{
			menu.ToggleVisible();
		}
		if (keys & KEY_B)
		{
			showMainAnim = true;
		}
		if (keys & KEY_X)
		{
			
		}
		if (keys & KEY_Y)
		{
			scaleFrame = 0;
		}

		if(scaleFrame > -1){
			showMainAnim = true;
			scaleFrame++;
			if(scaleFrame < 80){
				scale += 64;
			}
			if(scaleFrame == 80){
				fileSprite->Move(157, 154);
				fileSprite->isHidden = false;
				int hours, minutes, seconds, day, month, year;
				time_t unixTime = time(nullptr);
				struct tm* timeStruct = gmtime((const time_t *)&unixTime);

				hours = timeStruct->tm_hour;
				minutes = timeStruct->tm_min;
				seconds = timeStruct->tm_sec;
				day = timeStruct->tm_mday;
				month = timeStruct->tm_mon;
				year = timeStruct->tm_year +1900;

				char* fileName = (char*) calloc(100, 1);
				sprintf(fileName, "%i-%i-%i_%02i-%02i-%02i.bmp", year, month, day, hours, minutes, seconds);

				saveSubBGToFile(fileName);
				free(fileName);
			}
			if(scaleFrame == 110){
				scaleFrame = -1;
				scale = 256;
				startFileAnim(fileSprite, fileTopSprite);
			}
			bgSetScale(userBg, scale, scale);
			bgSetCenter(userBg, (scale - 256) >> 5, (scale - 256) >> 5);
			bgUpdate();
		}
		assert(sprites.size() > 0);
		for(Tween* t : tweens){
			if((t->spr->y % 256 == 200) && t->spr->willBubble){
				t->spr->x = rand() % 240;
				t->fixedPointX = intToFixed(t->spr->x, 6);
				//t->spr->setScale(rand(), rand());
			}
			if(t->startFrame == frameNo){
				t->Start();
			}
			if(t->startFrame <= frameNo && t->endFrame > frameNo){			
				if(t->spr->willBubble == true)
					t->BubbleUpdate();
				else
					t->Update();
			} else if(t->spr->willBubble){
				t->startFrame = 0x0;
				t->endFrame = 0xFFFFFFFF;
			}
		}



		// cheap blink anim
		if(blinkTime > 15){
			paceye1->isHidden = false;
			paceye2->isHidden = true;
			paceye3->isHidden = true;
		} else if (blinkTime > 5){
			paceye1->isHidden = true;
			paceye2->isHidden = false;
			paceye3->isHidden = true;
		} else if (blinkTime > 0){
			paceye1->isHidden = true;
			paceye2->isHidden = true;
			paceye3->isHidden = false;
		} else {
			blinkTime = 120 + (rand() % 240);
		}
		blinkTime--;

		for (Sprite* s : sprites){
			if(!showMainAnim && s->isMainAnim)
				s->isHidden = true;
			s->Update();
		}

		if(menu.isVisible)
			menu.Draw();
		
		menu.handleInput(keysJustPressed);
		if(frameNo % 5 == 0){
		BG_PALETTE[1] = BG_PALETTE[1] + 0x1;
		BG_PALETTE[2] = BG_PALETTE[2] - 0x1;
		}

		swiWaitForVBlank();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		frameNo++;
	}
	return 0;
}
