#ifndef ENTRY_T
#define ENTRY_T
// some people use inheritance, i dont
enum ENTRY_TYPE {
    CLEAR,
    IMAGE,
    CHANGE_PALETTE
};
class MenuEntry {
    public:
        ENTRY_TYPE type;
        char* fileName;
};
#endif