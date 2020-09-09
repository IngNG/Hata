#include "TXLib.h"
void(fon())
{
    txSetColor (TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 800, 100);

    txDrawText(0, 0, 200, 100 ,"название раздела");
    txDrawText(200, 0, 400, 100 ,"название раздела");
    txDrawText(400, 0, 600, 100 ,"название раздела");
    txDrawText(600, 0, 800, 100 ,"название раздела");
}

int main()
    {
    txCreateWindow (800, 800);
    txSetColor (TX_WHITE, 4);
    txClear();

    fon();

    //while()


    return 0;
    }

