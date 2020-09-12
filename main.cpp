#include "TXLib.h"
void(fon(int mx, int my))
{
    txSetColor (TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 800, 100);

    txDrawText(0, 0, 200, 100 ,"название раздела");
    txDrawText(200, 0, 400, 100 ,"название раздела");
    txDrawText(400, 0, 600, 100 ,"название раздела");
    txDrawText(600, 0, 800, 100 ,"название раздела");

    txRectangle (mx, my, mx + 150, my + 140);
}

int main()
    {
    txCreateWindow (800, 800);

    int window = 0;
    int mx = -500;
    int my = -500;
    char section [3][6][13];
    sprintf(section [0][0], "0подраздел0") ;
    sprintf(section [0][1], "0подраздел1") ;
    sprintf(section [0][2], "0подраздел2") ;
    sprintf(section [0][3], "0подраздел3") ;
    sprintf(section [0][4], "0подраздел4") ;
    sprintf(section [0][5], "0подраздел5") ;
    sprintf(section [0][6], "0подраздел6") ;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
    txSetColor (TX_WHITE, 4);
    txClear();
    txSetColor (TX_BLACK, 4);

    window = 0;

    fon(mx, my);

    if(txMouseX() >= mx && txMouseX() <= mx + 200 && txMouseY() >= my && txMouseY() <= my + 150 )
        window = 1;

    for(int i = -1; i < 7; i++)
    {
        txDrawText(mx, my + i * 20, mx + 150, my + 20 + i * 20 , section [0][i]);
    }

    for(int i = 0; i < 800; i = i + 200)
    {
        if(txMouseX() >= 0 + i && txMouseX() <= 200 + i && txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1 && window == 0)
        {
            my = txMouseY() ;
            mx = txMouseX() ;
            if(mx + 200 >= 800)
               mx = 650;
        }
    }

    txSleep(10) ;

    if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
    {
        mx = -500;
        my = -500;
    }

    txSleep(20) ;

    }

    return 0;
    }

