#include "TXLib.h"

//#include "Struct"

//���������
struct subBUTTON
{
    const char* text;
};

//������
struct BUTTON
{
    int x;
    int y;
    const char* text;
    subBUTTON subButtons[10];

    void draw()
    {
        txSetColor (TX_BLACK, 4);
        if(txMouseX() >= x          && txMouseY() >= y &&
           txMouseX() <= x + 200    && txMouseY() <= y + 100);
            txSetColor (TX_LIGHTBLUE, 4);

        txDrawText(x, y, x + 200, y + 100 ,text);
    }

};

    /*bool click()
    {
        if(txMouseX() >= � && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1);
    } */

//��������
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
    txSetColor(TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 1000, 100);

    //������� ��������, ��������� �� �������
    /*drawButton(0, 0, "������");
    drawButton(200, 0, "�������");
    drawButton(400, 0, "���");
    drawButton(600, 0, "�����");
    drawButton(800, 0, "������� ");    */

    txRectangle (mx, my, mx + 150, my + 140);
}

void openSubsection()
{
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

    //�������� ������ ������
    strObject object[100];
    object[0] = {50, 0, txLoadImage ("Pictures/������.bmp"), false, 686, 700};
    object[1] = {150, 0, txLoadImage ("Pictures/����.bmp"), false, 910, 746};
    object[2] = {250, 0, txLoadImage ("Pictures/������2.bmp"), false, 822, 836};

    //�������
    BUTTON buttons[5];
    buttons[0] =   {0, 0, "������",     {{"�������1"}, {"����"}, {"������"}, {"������"}, {"������"}}};
    buttons[1] = {200, 0, "�������",    {{"�������2"}, {"����"}, {"������"}, {"������"}, {"������"}}};
    buttons[2] = {400, 0, "���",        {{"�������3"}, {"����"}, {"������"}, {"������"}, {"������"}}};
    buttons[3] = {600, 0, "�����",      {{"�������4"}, {"����"}, {"������"}, {"������"}, {"������"}}};
    buttons[4] = {800, 0, "����������", {{"�������5"}, {"����"}, {"������"}, {"������"}, {"������"}}};

    bool btn0Opened = false;
    bool btn1Opened = false;
    bool btn2Opened = false;
    bool btn3Opened = false;
    bool btn4Opened = false;

    bool subBtn0Opened = false;
    bool subBtn1Opened = false;
    bool subBtn2Opened = false;


    int window = 0;
    int mx = -500;
    int my = -500;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();
        txSetColor (TX_BLACK, 4);
        if(!openSubsect)
        {
            fon(mx, my);
            for (int i = 0; i < 5; i++)
                buttons[i].draw();

            /*if (click(subButton[2]))
            {
                category = subbUtton[2].category;//����� ��������
            } */

            txRectangle (mx, my, mx + 150, my + 140);

            for (int i = 0; i < 4; i++)
            {
                //���� ����������
                if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20)
                    txSetColor (TX_LIGHTBLUE, 4);
                txDrawText(mx, my + 5 + i * 20, mx + 150, my + 25 + i * 20 , buttons[0].subButtons[i].text);

                //����� ����������
                if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20 && txMouseButtons() == 1)
                {
                    openSubsect = true;
                    if (i == 0) {subBtn0Opened = true;  subBtn1Opened = false;}
                    if (i == 1) {subBtn0Opened = false; subBtn1Opened = true;}
                }
                txSetColor (TX_BLACK, 4);
            }
            txSleep(20);
        }

        else
            openSubsection();

        //������ ������ ����������
        if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1 && openSubsect)
        {
            openSubsect = false; /*mx = -500;*/ txSleep(200);

            subBtn0Opened = false;
            subBtn1Opened = false;
        }

        //�� ��� ����� mx, my? ������ �� �������� ���� ������������� ��� �������? ��� � �������� ��� ��

        //���� �� ������
        if (txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
        {
            //������ ��� �� ���������
            if (btn0Opened && txMouseX() >= buttons[0].x && txMouseX() <= buttons[0].x + 200){}
            else if (btn1Opened && txMouseX() >= buttons[1].x && txMouseX() <= buttons[1].x + 200){}
            else
            {
                btn0Opened = false;
                btn1Opened = false;
                my = txMouseY() ;
                mx = txMouseX() ;
                if(mx + 150 >= 1000)
                   mx = 850;
            }
            //����� ��������� ������?
            if (txMouseX() >= buttons[0].x && txMouseX() <= buttons[0].x + 200)
                btn0Opened = true;

            if (txMouseX() >= buttons[1].x && txMouseX() <= buttons[1].x + 200)
                btn1Opened = true;

        }
        //�� ���� ��� ��� �� �?
        /*for(int i = 0; i < 1000; i = i + 200)
        {
            if(txMouseX() >= 0 + i && txMouseX() <= 200 + i && txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
            {
                my = txMouseY() ;
                mx = txMouseX() ;
                if(mx + 150 >= 1000)
                   mx = 850;
            }
        } */


        //����� ���������
        for(int i = 0; i < 3; i++)
            object[i].drawObject = false;

        if (openSubsect && subBtn0Opened && btn1Opened)
        {
            object[0].drawObject = true;
        }
        if (openSubsect && subBtn1Opened && btn1Opened)
        {
            object[1].drawObject = true;
        }

        //��������� ��������� � ������ ���������
        for(int i = 0; i < 3; i++)
            if (openSubsect)
            {
                //Win32::TransparentBlt (txDC(), object[i].x, object[i].y, 100, 100,object[i].pic, 0, 0, object[i].width, object[i].height, TX_BLACK);
            }


        //�������� ������ ������
        for(int i = 0; i < 3; i++)
            if (object[i].drawObject)
            {
                Win32::TransparentBlt (txDC(),object[i].x,object[i].y,150,150,object[i].pic,0,0,object[i].width,object[i].height,TX_BLACK);
            }


        if (window == MENU_OPEN)
            Win32::TransparentBlt (txDC(), mx, 0, 50, 50, object[0].pic, 0, 0, 686, 700, TX_BLACK); // 10x zoom

        //�� ������� �������� ��� ������
        for(int i = 0; i < 3; i++)
            if (GetAsyncKeyState(VK_SPACE))
            {
                object[i].drawObject=false;
            }


        if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
        {
            mx = -500;
            my = -500;
        }

        if (btn0Opened)  txTextOut(100, 200, "0");
        if (btn1Opened)  txTextOut(100, 250, "1");

        if (subBtn0Opened)  txTextOut(200, 200, "0");
        if (subBtn1Opened)  txTextOut(200, 250, "1");

        txSleep(20) ;
    }

    for(int i = 0; i < 3; i++)
        txDeleteDC (object[i].pic);

    return 0;
}

