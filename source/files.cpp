#define ARM9 1
#include <nds.h>
#include <fat.h>
#include <stdio.h>
#include <filesystem.h>
#include <fat.h>
#include <vector>
#include "/opt/devkitpro/devkitARM/arm-none-eabi/include/sys/dirent.h"
#include "files.hpp"

static std::vector<MenuEntry> savedFileNames;
void populateFileNames(){
	savedFileNames.clear();
	DIR *pdir;
	struct dirent *pent;
	pdir=opendir("/images/");
	int index = 0;

	if (pdir){
		while ((pent=readdir(pdir))!=nullptr) {
			if(strcmp(".", pent->d_name) == 0 || strcmp("..", pent->d_name) == 0)
				continue;
			char* fileName = (char*) calloc(256, 1);
			strcpy(fileName, pent->d_name);
			MenuEntry entry;
			entry.fileName = fileName;
			entry.type = IMAGE;
			savedFileNames.push_back(entry);
		}
		closedir(pdir);
	} else {
		iprintf ("opendir() failure; terminating\n");
	}
}

MenuEntry getEntry(int entryNo){
	if(savedFileNames.size() > entryNo){
		return savedFileNames.at(entryNo);
	} else {
		char* fileName = (char*) malloc(8);
		strcpy(fileName, "no file");
		MenuEntry entry;
		entry.fileName = fileName;
		entry.type = IMAGE;
		return entry;
	}
}

bool doesFileNameExist(char* fileName){
	DIR *pdir;
	struct dirent *pent;

	pdir=opendir("/");

	if (pdir){
		while ((pent=readdir(pdir))!=nullptr) {
			if(strcmp(fileName, pent->d_name) == 0)
				return true;
		}
		closedir(pdir);
		return false;
	} else {
		iprintf ("opendir() failure; terminating\n");
		return true;
	}
}

bool doesBMPExist(int frameNo){
	char fileName[256];
	sprintf(fileName, "image_%d.bmp", frameNo);
	return doesFileNameExist(fileName);
}


void saveSubBGToFile(char* fileName){
	// save image
	char filePath[256] = "/images/image_";
	strcat(filePath, fileName);
	FILE *fpImage = fopen(filePath, "w+");
	if(fpImage == 0){
		iprintf("fp is null");
	} else {
		fwrite(bottomBuffer, sizeof(u16), pixels, fpImage);
		fclose(fpImage);
		// blank screen
		clearBottomScreen();
	}
}

void readFileToBG(char* fileName, bool topBG){
	// save image
	char filePath[256] = "/images/";
	strcat(filePath, fileName);
	FILE *fpImage = fopen(filePath, "r");
	drawString(filePath, 20, 50);
	if(fpImage == 0){
		for (int i = 0; i < pixels; i++)
		{
			BG_GFX[i] = 0x800F;
		}
	} else {
		fread(bottomBuffer, sizeof(u16), pixels, fpImage);
		fclose(fpImage);
		for (int i = 0; i < pixels; i++)
		{
			if(topBG){
				BG_GFX[i] = bottomBuffer[i];
				bottomBuffer[i] = 0xFFFF;
			} else {
				BG_GFX_SUB[i] = bottomBuffer[i];
			}
		}
		/*
		// blank screen
		for (int i = 0; i < pixels; i++)
		{
			BG_GFX_SUB[i] = c565Toa555(0xFFFF);
			bottomBuffer[i] = c565Toa555(0xFFFF);
		}*/
	}
}