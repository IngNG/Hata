#include "TXLib.h"

//Можно две структуры для раздела и подраздела
struct BUTTON
{

};

void fon(int mx, int my)
{
    //Вместо 1000 везде лучше SCREEN_WIDTH какой-нибудь или txGetExtentX()
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 1000, 100);


    //Сделать функцией, зависящей от раздела
    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 0 && txMouseX() <= 200 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(0, 0, 200, 100 ,"Мебель");


    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 200 && txMouseX() <= 400 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(200, 0, 400, 100 ,"техника");
    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 400 && txMouseX() <= 600 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(400, 0, 600, 100 ,"пол");
    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= 600 && txMouseX() <= 800 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(600, 0, 800, 100 ,"комната");
    if(txMouseX() >= 800 && txMouseX() <= 1000 && txMouseY() >= 0 && txMouseY() <= 100)
        txSetColor (TX_LIGHTBLUE, 4);
    txDrawText(800, 0, 1000, 100 ,"стены");

    txRectangle (mx, my, mx + 150, my + 140);
}

void openSubsection()
{
    txSetColor (TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 1000, 100);
    txSetColor (TX_BLACK, 2);
    if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20)
        txSetColor (TX_LIGHTRED, 2);
    txLine(10, 10, 30, 10);
    txLine(10, 10, 15, 5);
    txLine(10, 10, 15, 15);
}

int main()
{
    txCreateWindow (1000, 800);

    HDC Kreslo = txLoadImage ("кресло.bmp");
    HDC Stol = txLoadImage ("Стол.bmp");

    bool drawKreslo = false;
    bool drawstol = false;

    bool openSubsect = false;
    int mx = -500;
    int my = -500;
    char section [3][6][13];
    sprintf(section [0][0], "комната") ;
    sprintf(section [0][1], "стол") ;
    sprintf(section [0][2], "мебель") ;
    sprintf(section [0][3], "стулья") ;
    sprintf(section [0][4], "стол + комп") ;
    sprintf(section [0][5], "0подраздел5") ;
    sprintf(section [0][6], "0подраздел6") ;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txSetFillColor (TX_WHITE);
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


        //кресло
        for(int i = 0; i < 800; i = i + 200)
        {
            if(i == 0 && txMouseX() >= 0 + i && txMouseX() <= 200 + i && txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
            {
                drawKreslo = true;
            }
            if(i == 1 && txMouseX() >= 0 + i && txMouseX() <= 200 + i && txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
            {
                drawKreslo = false;
            }
        }

        //А вот тут можно сообразить, как выглядит структура для картинки
        if (drawKreslo)
        {
            Win32::TransparentBlt (txDC(), 200, 200, 200, 200, Kreslo, 0, 0, 648, 612, TX_BLACK);
        }
        if (drawstol)
        {
            Win32::TransparentBlt (txDC(), 400, 400, 400, 400, Stol, 0, 0, 434, 258, TX_BLACK);
        }



        if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
        {
            mx = -500;
            my = -500;
        }

        txSleep(20) ;

    }

    return 0;
}

