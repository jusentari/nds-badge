#include <nds.h>
#include <nds/arm9/video.h>
#include "glyphs.hpp"
#ifndef DRAW_H
#define DRAW_H
#define pixels 49152
void clearBg();
bool detectRect(int x, int y, int w, int h, touchPosition* tp);
void displayRect(int x, int y, int w, int h, u16 color);
void displayColors(touchPosition* tp);
void displayBrushSizes(touchPosition* tp);
u16 coordToIndex(u16 x, u16 y);
void drawFromSamples();
extern u8 color;
extern s32 scale;
extern s32 scaleFrame;
extern touchPosition samples[3];
extern u16 bottomBuffer[pixels];
static bool showMainAnim;
u16 c565Toa555(u16 color);
void clearBottomScreen();
void drawChar(char character, int x, int y);
void drawString(char* string, int x, int y);
#endif