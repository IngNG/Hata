#include "TXLib.h"

struct BUTTON
{

};

const int MENU_OPEN = 1;

//����
void fon(int mx, int my)
{
    txSetColor (TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 800, 100);

    txDrawText(0, 0, 200, 100 ,"������");
    txDrawText(200, 0, 400, 100 ,"�����");
    txDrawText(400, 0, 600, 100 ,"���");
    txDrawText(600, 0, 800, 100 ,"����");

    txRectangle(900,100,1080,900);

    txRectangle (mx, my, mx + 150, my + 140);
}

int main()
    {
    txCreateWindow (1080, 900);


    HDC Kreslo = txLoadImage ("������.bmp");

    HDC Stol = txLoadImage ("����.bmp");

    HDC Kreslo2 = txLoadImage("������2.bmp");

    bool drawKreslo = false;
    bool drawstol = false;
    bool drawKreslo2 = false;
    bool drawKresloB2=false;

    int window = 0;
    int mx = -500;
    int my = -500;
    char section [3][6][13];
    sprintf(section [0][0], "0���������0") ;
    sprintf(section [0][1], "0���������1") ;
    sprintf(section [0][2], "0���������2") ;
    sprintf(section [0][3], "0���������3") ;
    sprintf(section [0][4], "0���������4") ;
    sprintf(section [0][5], "0���������5") ;
    sprintf(section [0][6], "0���������6") ;


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txSetColor (TX_WHITE, 4);
        txClear();
        txSetColor (TX_BLACK, 4);


        window = 0;

        fon(mx, my);


    if(txMouseX() >= mx && txMouseX() <= mx + 200 && txMouseY() >= my && txMouseY() <= my + 150 )
        window = MENU_OPEN;

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

    //����� ���������
    if(txMouseX() >= 200 && txMouseX() <= 400 &&
       txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
    {
        drawKreslo = true;
        drawKreslo2 = true;
        //drawstol = true;
    }
    if (drawKreslo2)
    {
        Win32::TransparentBlt (txDC(), 930,250,100,100,Kreslo2,0,0,1200,1200,TX_BLACK);
    }
    if (drawKreslo)
    {
        Win32::TransparentBlt (txDC(), 930, 120, 100, 100, Kreslo, 0, 0, 686, 700, TX_BLACK);
    }



    //����� ��������
    if(txMouseX()>= 930 && txMouseX() <=1030 &&
        txMouseY()>=120 && txMouseY() <= 220 && txMouseButtons() == 1)
    {
        drawKresloB2 = true;
    }


//������

    if(txMouseX() >= 0 && txMouseX() <= 200 &&
       txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
    {

    }
    if (drawKresloB2)
    {
      Win32::TransparentBlt (txDC(),200,200,150,150,Kreslo2,0,0,1200,1200,TX_BLACK);
    }
    if (drawstol)
    {
        Win32::TransparentBlt (txDC(), 400, 400, 400, 400, Stol, 0, 0, 686, 700, TX_BLACK);
    }



    if (window == MENU_OPEN)
        Win32::TransparentBlt (txDC(), mx, 0, 50, 50, Kreslo, 0, 0, 686, 700, TX_BLACK); // 10x zoom


    if (GetAsyncKeyState(VK_SPACE))
    {
        drawKresloB2=false;
        drawstol=false;
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

