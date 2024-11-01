#define ARM9 1
#include <nds.h>
#include <fat.h>
#include <stdio.h>
#include <filesystem.h>
#include <fat.h>

#include <stdio.h>
#include <dirent.h>

// grit outputs a nice header to reference data

#include "files.hpp"
#include "../build/man.h"
#include "../build/bggg.h"
#include "sprite.hpp"
#include "../build/dissolution.h"
#include "../build/smallfile.h"
#include "tween.hpp"
#include "/opt/devkitpro/devkitARM/arm-none-eabi/include/sys/dirent.h"
#include "draw.hpp"
#include "menu.hpp"
Sprite* createCircleSprite(int radius);