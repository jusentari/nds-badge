#include "draw.hpp"
#include "menuEntry.hpp"
#include <vector>
#ifndef FILES_H
#define FILES_H
void saveSubBGToFile(char* fileName);
void populateFileNames();
void readFileToBG(char* fileName, bool topBG);
MenuEntry getEntry(int entryNo);
#endif