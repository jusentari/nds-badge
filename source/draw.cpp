#include "draw.hpp"
#include <nds/arm9/math.h>
#include <stdlib.h>
#include <complex>
#include <nds/arm9/trig_lut.h>
u8 color = 0;
s32 scale = 256;
s32 scaleFrame = -1;
touchPosition samples[3] = {{0}};
u16 bottomBuffer[pixels];
u16 colors[8] = {0x2104, 0xfb00, 0xd92f, 0xfd60, 0x7afd, 0x647f, 0xef7d, 0xffff};
bool brushPressed = false;

u16 c565Toa555(u16 color){
 return (color >> 11 & 0x1F) | (color >> 6 & 0x1F) << 5 | (color & 0x1F) << 10 | 0x8000;
}
int brushSize = 3;
void setColor(int _color){
    color = _color;
}

void clearBg(){
	for (int i = 0; i < pixels; i++)
	{
		BG_GFX_SUB[i] = 0xFFFF;
		bottomBuffer[i] = 0xFFFF;
	}
}

bool detectRect(int x, int y, int w, int h, touchPosition* tp){
	return tp->px > x && 
		tp->px < x+w && 
		tp->py > y && 
		tp->py < y+h;
}

void displayRect(int x, int y, int w, int h, u16 color){
	int startRow = y * 256;
	int startCol = x;
	for(int i = 0; i < w * h; i++){
		int col = (i % w);
		int row = (i / w) * 256;
		BG_GFX_SUB[startRow + row + startCol + col] = color;
	}
}

void drawChar(char character, int x, int y){
	u32 charBitmap = glyphs[character];
	for(int i = 0; i < 32; i++){
		int row = i / 4;
		int col = i % 4;
		bool isWhite = ((charBitmap >> (31 - i)) & 1) == 0;
		BG_GFX_SUB[x + col + ((y + row) * 256)] = isWhite ? 0xFFFF : 0x8000;
	}
}

void drawString(char* string, int x, int y){
	int i = 0;
	int col = 0;
	int row = 0;
	// move these another time
	// is actually 4x8, but added pixel for padding
	int fontWidth = 5;
	int fontHeight = 9;
	while(string[i] != '\0'){
		drawChar(string[i] - 32, x + (col * fontWidth), y + (row * fontHeight));
		i++;
		if(string[i] == '\n'){
			row++;
			col = 0;
		} else {
			col++;
		}
	}
}

void displayColors(touchPosition* tp){
	for(int i = 0; i < 8; i++){
		displayRect(i * 16, 176, 16, 16, c565Toa555(colors[i]));
		if(detectRect(i * 16, 176, 16, 16, tp)){
			color = i;
		}
		displayRect(7 * 16, 176, 16, 16, c565Toa555(0x0000));
		displayRect((7 * 16) + 2, 178, 12, 12, c565Toa555(0xffff));
	}
}

void displayBrushSizes(touchPosition* tp){
	for(int i = 1; i <= 3; i++){
		displayRect((i+8) * 16, 176, 16, 16, 0x8000);
		displayRect(((i+8) * 16) + 2, 178, 12, 12, 0xFFFF);
	}
	displayRect((9 * 16) + 4, 184, 8, 2, 0x8000);
	displayRect((10 * 16) + 4, 180, brushSize, brushSize, 0x8000);
	displayRect((11 * 16) + 4, 183, 8, 2, 0x8000);
	displayRect((11 * 16) + 7, 180, 2, 8, 0x8000);
	if(detectRect(9 * 16, 176, 16, 16, tp)){
		if(!brushPressed){
			brushSize = std::max(brushSize - 1, 1);
			brushPressed = true;
		}
	} else if(detectRect(11 * 16, 176, 16, 16, tp)){
		if(!brushPressed){
			brushSize = std::min(brushSize + 1, 24);
			brushPressed = true;
		}
	} else {
		brushPressed = false;
	}
}

u16 coordToIndex(u16 x, u16 y){
	return (y * 256) + x;
}

// simple linear draw
void drawFromSamples(){
	for(int i = 0; i < 8; i++){
		int test = c565Toa555(colors[i]);
		iprintf("%d", test);
	}
	if(scaleFrame > -1){
		return;
	}
	//TODO: Disallow painting from continuing over edge of screen
	int32 diffX = samples[1].px - samples[2].px;
	int32 diffY = samples[1].py - samples[2].py;
	int32 curX = samples[2].px;
	int32 curY = samples[2].py;
	int32 iterations = std::max(std::abs(diffX), std::abs(diffY));
	bool isXLarger = std::abs(diffX) > std::abs(diffY);
	// 20.12 signed fixed points
	diffX = intToFixed(diffX, 12);
	diffY = intToFixed(diffY, 12);
	int32 slope = isXLarger ? divf32(diffY, diffX) : divf32(diffX, diffY);
	int directionX = (diffX < 0) ? -1 : 1;
	int directionY = (diffY < 0) ? -1 : 1;
	if((isXLarger && (diffX < 0)) || (!isXLarger && (diffY < 0))){
		slope = -slope;
	}
	curX = intToFixed(curX, 12);
	curY = intToFixed(curY, 12);

	for(int k = 0; k < iterations; k++){
		if(isXLarger){
			curX += intToFixed(directionX, 12);
			curY += slope;
		} else {
			curY += intToFixed(directionY, 12);
			curX += slope;
		}
		int32 pixelX = curX >> 12;
		// rounding like a chump
		if(curX & (1 << 11))
			pixelX++;
		int32 pixelY = curY >> 12;
		if(curY & (1 << 11))
			pixelY++;
		for(int i = 0; i < brushSize; i++){
			for(int j = 0; j < brushSize; j++){
				int index = coordToIndex(pixelX + i, pixelY + j);
				if((pixelX + i) < 256 && (pixelY + j) < 192 && (index < pixels)){
					BG_GFX_SUB[index] = c565Toa555(colors[color]);
					bottomBuffer[index] = BG_GFX_SUB[index];
				}
			}
		}
	}
}

void clearBottomScreen(){
	for (int i = 0; i < pixels; i++){
		BG_GFX_SUB[i] = 0xFFFF;
		bottomBuffer[i] = 0xFFFF;
	}
}