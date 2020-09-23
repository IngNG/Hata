#include "TXLib.h"

//����� ��� ��������� ��� ������� � ����������

struct subBUTTON
{
    //int x;
    //int y;
    const char* text;
};

struct BUTTON
{
    //int x;
    //int y;
    const char* text;
    subBUTTON subButtons[10];
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
    HDC pic;
    bool drawObject;
    int width;
    int height;
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
    txSetColor (TX_WHITE, 4);
    txClear();
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


    bool openSubsect = false;

    strObject object[100];
    object[0] = {50, 0, txLoadImage ("Pictures/������.bmp"), false, 686, 700};
    object[1] = {150, 0, txLoadImage ("Pictures/����.bmp"), false, 910, 746};
    object[2] = {250, 0, txLoadImage ("Pictures/������2.bmp"), false, 822, 836};

    subBUTTON btn[10];
    btn[0] = {"�������"};
    btn[1] = {"����"};
    btn[2] = {"������"};
    btn[3] = {"������"};
    btn[4] = {"������"};
    BUTTON buttons[5];
    buttons[0] = {"������",        btn    };

    bool drawKresloB2=false;
    //HDC Sofa2 = txLoadImage("Pictures/�����.bmp");
    //HDC Stolpc = txLoadImage("Pictures/��������.bmp");
    //HDC room = txLoadImage("Pictures/������.bmp");


    int window = 0;
    int mx = -500;
    int my = -500;
    char section [3][6][12];
    sprintf(section [0][0], "�������") ;
    sprintf(section [0][1], "����") ;
    sprintf(section [0][2], "������") ;
    sprintf(section [0][3], "������") ;
    sprintf(section [0][4], "���� + ����") ;
    sprintf(section [0][5], "0���������5") ;
    sprintf(section [0][6], "0���������6") ;

    txBegin();
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txSetColor (TX_WHITE, 4);
        txClear();
        txSetColor (TX_BLACK, 4);
        fon(mx, my);
        if(!openSubsect)
        {
            fon(mx, my);
            txRectangle (mx, my, mx + 150, my + 140);
            for(int i = 0; i < 4; i++)
            {
                if(txMouseX() >= mx + 5 && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 20 + i * 20)
                    txSetColor (TX_LIGHTBLUE, 4);
                txDrawText(mx, my + i * 20, mx + 150, my + 20 + i * 20 , buttons[0].subButtons[i]);
                if(txMouseX() >= mx + 5 && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 20 + i * 20 && txMouseButtons() == 1)
                    openSubsect = true;
                txSetColor (TX_BLACK, 4);
            }
            txSleep(20);
        }

        else
            openSubsection();

        if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1 && openSubsect)
            {openSubsect = false; mx = -500; txSleep(200);}


        for(int i = 0; i < 1000; i = i + 200)
        {
            if(txMouseX() >= 0 + i && txMouseX() <= 200 + i && txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
            {
                my = txMouseY() ;
                mx = txMouseX() ;
                if(mx + 150 >= 1000)
                   mx = 850;
            }
        }


        //����� ���������
        for(int i = 0; i < 3; i++)
            if (txMouseX() >= object[i].x &&
                txMouseX() <= object[i].x + object[i].width &&
                txMouseY() >= 0 && txMouseY() <= 100 &&
                txMouseButtons() == 1 && openSubsect)
            {
                object[i].drawObject = true;
            }

        //��������� ��������� � ������ ���������
        for(int i = 0; i < 3; i++)
            if (openSubsect)
            {
                Win32::TransparentBlt (txDC(), object[i].x, object[i].y, 100, 100,object[i].pic, 0, 0, object[i].width, object[i].height, TX_BLACK);
            }


        //�������� �� ������
        for(int i = 0; i < 3; i++)
            if (object[i].drawObject)
            {
                Win32::TransparentBlt (txDC(),object[i].x,object[i].y,150,150,object[i].pic,0,0,object[i].width,object[i].height,TX_BLACK);
            }

            //if (drawstol)
            {
                //Win32::TransparentBlt (txDC(), 400, 400, 400, 400, Stol, 0, 0, 686, 700, TX_BLACK);
            }
            //if (drawSofa2)
            {
                //Win32::TransparentBlt (txDC(), 400, 400, 400, 400, Sofa2, 0, 0, 686, 700, TX_BLACK);
            }
            //if (drawstolpc)
            {
                //Win32::TransparentBlt (txDC(), 400, 400, 400, 400, Stolpc, 0, 0, 686, 700, TX_BLACK);
            }
            //if (drawroom)
            {
                //Win32::TransparentBlt (txDC(), 400, 400, 400, 400, room, 0, 0, 686, 700, TX_BLACK);
            }



        if (window == MENU_OPEN)
            Win32::TransparentBlt (txDC(), mx, 0, 50, 50, object[0].pic, 0, 0, 686, 700, TX_BLACK); // 10x zoom

        for(int i = 0; i < 3; i++)
            if (GetAsyncKeyState(VK_SPACE))
            {
                //drawKresloB2=false;
                object[i].drawObject=false;
            }


        if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
        {
            mx = -500;
            my = -500;
        }

        txSleep(20) ;

    }

    for(int i = 0; i < 3; i++)
        txDeleteDC (object[i].pic);

    return 0;
}

