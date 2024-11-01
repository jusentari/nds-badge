#include "menu.hpp"

Menu::Menu(){
    optionSelected = 0;
    isVisible = false;
    entryToDraw = 0;
    entryOffset = 0;
    RefreshEntries();
}

void Menu::handleInput(uint32 keys){
    if(isVisible){
        if(keys & KEY_UP){
            optionSelected = (optionSelected - 1) % MENU_ENTRIES;
            entryToDraw = 0;
        }
        if(keys & KEY_DOWN){
            optionSelected = (optionSelected + 1) % MENU_ENTRIES;
            entryToDraw = 0;
        }
        if(keys & KEY_A){
            Select();
        }
        if(keys & KEY_X){
            AltSelect();
        }
        if(keys & KEY_LEFT){
            entryOffset = std::max(entryOffset - 9, 0);
            entryToDraw = 0;
            RefreshEntries();
        }
        if(keys & KEY_RIGHT){
            entryOffset += 9;
            entryToDraw = 0;
            RefreshEntries();
        }
    }
}

void Menu::Draw(){
    // draw entries
    if(entryToDraw < MENU_ENTRIES){
        u16 highlight = optionSelected == entryToDraw ? 0xfa00 : 0x8000;
        displayRect(0, entryToDraw*19, 256, 19, highlight);
        displayRect(2, (entryToDraw*19)+2, 252, 15, 0xFFFF);
        drawString(entries[entryToDraw].fileName, 2, (entryToDraw*19)+2);
        entryToDraw++;
    }
}

void Menu::RefreshEntries(){
    populateFileNames();
    MenuEntry clearEntry;
    clearEntry.fileName = "<clear>";
    clearEntry.type = CLEAR;
    entries[0] = clearEntry;
    for(int i = 1; i < MENU_ENTRIES; i++){
        entries[i] = getEntry(i + entryOffset);
    }
}

void Menu::ToggleVisible(){
    isVisible = !isVisible;
    entryToDraw = 0;
    RefreshEntries();
    if(!isVisible){
		for (int i = 0; i < pixels; i++)
		{
			BG_GFX_SUB[i] = bottomBuffer[i];
		}
    }
}

void Menu::Select(){
    // select option
    if(entries[optionSelected].type == ENTRY_TYPE::CLEAR){
        isVisible = false;
        clearBottomScreen();
    }
    if(entries[optionSelected].type == ENTRY_TYPE::CHANGE_PALETTE){

    }
    if(entries[optionSelected].type == ENTRY_TYPE::IMAGE){
        isVisible = false;
        readFileToBG(entries[optionSelected].fileName, false);
    }
}

void Menu::AltSelect(){
    if(entries[optionSelected].type == ENTRY_TYPE::IMAGE){
        isVisible = false;
        readFileToBG(entries[optionSelected].fileName, true);
        showMainAnim = false;
		for (int i = 0; i < pixels; i++)
		{
			BG_GFX_SUB[i] = bottomBuffer[i];
		}
    }
}