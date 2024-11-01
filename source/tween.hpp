#include <nds/ndstypes.h>
#include <vector>
class Sprite;
class Tween 
{
	public:
		Tween(Sprite* s);
        Sprite* spr;
        void LinearMove(s16 destX, s16 destY, int currentFrame, int frames, int delay = 0);
        bool Scale(int delta, int frames);
        void Update();
        void Start();
        void BubbleUpdate();
        //int linearDestX;
        //int linearDestY;
        // these four should be in 9.6 signed fixed point
        s16 velocityX = 0;
        s16 velocityY = 0;
        s16 fixedPointX = 0;
        s16 fixedPointY = 0;

        // animation start and end frames
        uint32 startFrame = 0;
        uint32 endFrame = 0;
        int scaleDelta = 0;
};

static std::vector<Tween*> tweens;