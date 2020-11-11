#include "TXLib.h"

//Подраздел
struct subBUTTON
{
    const char* text;
    int N;
};

//Раздел
struct BUTTON
{
    const char* text;
    subBUTTON subButtons[10];
    int x;
    int y;

    void draw()
    {
        txSetColor (TX_BLACK, 4);
        //if(txMouseX() >= x          && txMouseY() >= y &&
        //   txMouseX() <= x + 200    && txMouseY() <= y + 100);
        //    txSetColor (TX_LIGHTBLUE, 4);
        txDrawText(x, y, x + 200, y + 100 ,text);
        txSetColor (TX_BLACK, 4);
    }

};

