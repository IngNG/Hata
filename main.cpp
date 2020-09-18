#include "TXLib.h"

//����� ��� ��������� ��� ������� � ����������
struct BUTTON
{
    int x;
    int y;
    char text[];
};

void drawButton(int x, int y, char text[] )
{
    txSetColor (TX_BLACK, 4);
    if(txMouseX() >= x          && txMouseX() <= y &&
       txMouseY() >= x + 200    && txMouseY() <= y + 100)
        txSetColor (TX_LIGHTBLUE, 4);

    txDrawText(x, y, x + 200, y + 100 ,text);
}

struct strObject
{
    int x;
    int y;
    int oSize;
};

const int MENU_OPEN = 1;

//����
void fon(int mx, int my)
{
    //������ 1000 ����� ����� SCREEN_WIDTH �����-������ ��� txGetExtentX()
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 1000, 100);

    //������� ��������, ��������� �� �������
    drawButton(0, 0, "������");
    drawButton(200, 0, "�������");
    drawButton(400, 0, "���");
    drawButton(600, 0, "�����");
    drawButton(800, 0, "������� ");

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
    txCreateWindow (1080, 900);

    HDC Kreslo = txLoadImage ("Pictures/������.bmp");
    HDC Stol = txLoadImage ("Pictures/����.bmp");
    HDC Kreslo2 = txLoadImage("Pictures/������2.bmp");

    bool drawKreslo = false;
    bool drawstol = false;
    bool drawKreslo2 = false;
    bool drawKresloB2=false;

    bool openSubsect = false;

    strObject object[100];
    object[0] = {-500, -500, 10};


    int window = 0;
    int mx = -500;
    int my = -500;
    char section [3][6][13];
    sprintf(section [0][0], "�������") ;
    sprintf(section [0][1], "����") ;
    sprintf(section [0][2], "������") ;
    sprintf(section [0][3], "������") ;
    sprintf(section [0][4], "���� + ����") ;
    sprintf(section [0][5], "0���������5") ;
    sprintf(section [0][6], "0���������6") ;



    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txSetColor (TX_WHITE, 4);
        txClear();
        txSetColor (TX_BLACK, 4);
        window = 0;
        fon(mx, my);
        if(!openSubsect)
        {
            fon(mx, my);
            txRectangle (mx, my, mx + 150, my + 140);
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
            {openSubsect = false; mx = -500; txSleep(200);}


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


        //����� ���������
        if(txMouseX() >= 200 && txMouseX() <= 400 &&
           txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
        {
            drawKreslo = true;
            drawKreslo2 = true;
        }

        //��������� ��������� � ������ ���������
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

        //�������� �� ������
        if (drawKresloB2)
        {
          Win32::TransparentBlt (txDC(),200,200,150,150,Kreslo2,0,0,800,800,TX_BLACK);
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


        if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
        {
            mx = -500;
            my = -500;
        }


        txSleep(20) ;

    }

    return 0;
    }

