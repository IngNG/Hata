#include "TXLib.h"
void fon(int mx, int my)
{
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 800, 100);

    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 0 && txMouseX() <= 200 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(0, 0, 200, 100 ,"название раздела");
    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 200 && txMouseX() <= 400 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(200, 0, 400, 100 ,"название раздела");
    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 400 && txMouseX() <= 600 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(400, 0, 600, 100 ,"название раздела");
    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 600 && txMouseX() <= 800 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(600, 0, 800, 100 ,"название раздела");

    txRectangle (mx, my, mx + 150, my + 140);
}
void openSubsection()
{
    txSetColor (TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 800, 100);
    txSetColor (TX_BLACK, 2);
    if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20)
        txSetColor (TX_LIGHTRED, 2);
    txLine(10, 10, 30, 10);
    txLine(10, 10, 15, 5);
    txLine(10, 10, 15, 15);
}

int main()
    {
    txCreateWindow (800, 800);

    bool openSubsect = false;
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

    if(!openSubsect)
    {
        fon(mx, my);
        for(int i = 0; i < 7; i++)
        {
            if(txMouseX() >= mx + 5 && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 20 + i * 20)
                txSetColor (TX_LIGHTBLUE, 4);
            txDrawText(mx, my + i * 20, mx + 150, my + 20 + i * 20 , section [0][i]);
            if(txMouseX() >= mx + 5 && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 20 + i * 20 && txMouseButtons() == 1)
                openSubsect = true;
            txSetColor (TX_BLACK, 4);
        }
    }

    else
        openSubsection();

    if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1 && openSubsect)
        {openSubsect = false; mx = -500; txSleep(50);}

    for(int i = 0; i < 800; i = i + 200)
    {
        if(txMouseX() >= 0 + i && txMouseX() <= 200 + i && txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
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

