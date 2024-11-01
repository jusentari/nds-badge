#include "draw.hpp"
#include "files.hpp"
#include "menuEntry.hpp"
#include "sprite.hpp"
#include <stdio.h>

#define MENU_ENTRIES 10

class Menu {
    public:
        u8 optionSelected;
        bool isVisible;
        void ToggleVisible();
        void handleInput(uint32 keys);
        void Draw();
        void Select();
        void AltSelect();
        void RefreshEntries();
        Menu();
        int entryOffset;
        MenuEntry entries[MENU_ENTRIES];
        u8 entryToDraw;
};
