#include "tween.hpp"
#include "sprite.hpp"
#include <nds/ndstypes.h>
#include <nds/arm9/trig_lut.h>

Tween::Tween(Sprite* s){
    spr = s;
}

// max range of -512 to 511
void Tween::LinearMove(s16 destX, s16 destY, int currentFrame, int frames, int delay){
    fixedPointX = destX << 6;
    fixedPointY = destY << 6;
    startFrame = currentFrame + delay;
    endFrame = currentFrame + frames + delay;
}

void Tween::Start(){
    fixedPointX += -(spr->x << 6);
    fixedPointY += -(spr->y << 6);
    int frames = endFrame - startFrame;
    velocityX = fixedPointX / frames;
    velocityY = fixedPointY / frames;
    fixedPointX = spr->x << 6;
    fixedPointY = spr->y << 6;
}

// going to use 10.6 fixed point numbers? to represent -512 - 511
void Tween::Update(){
    fixedPointX += velocityX;
    fixedPointY += velocityY;
    int intPointX = fixedPointX >> 6;
    int intPointY = fixedPointY >> 6;
    spr->x = intPointX;
    spr->y = intPointY;
}

void Tween::BubbleUpdate(){
    Update();
    spr->x += cosLerp(fixedPointY * 7 + fixedPointX) >> 10;
}