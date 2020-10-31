#include "TXLib.h"
#include "strObject.cpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

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
        //if(txMouseX() >= x          && txMouseY() >= y &&
        //   txMouseX() <= x + 200    && txMouseY() <= y + 100);
        //    txSetColor (TX_LIGHTBLUE, 4);
        txDrawText(x, y, x + 200, y + 100 ,text);
        txSetColor (TX_BLACK, 4);
    }

};

struct room
{
    int x ;
    int y ;
    int x2;
    int y2;
};
    /*bool click()
    {
        if(txMouseX() >= � && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1);
    } */

int getWidth(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);
    bmp.read(header, 54);
    int width;
    memcpy(&width, &header[18], sizeof(width));
    return width;
}

int getHeight(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);
    bmp.read(header, 54);
    int height;
    memcpy(&height, &header[22], sizeof(height));
    return height;
}

void drawBackArrow()
{
    txSetColor (TX_BLACK, 2);
    if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20)
        txSetColor (TX_LIGHTRED, 2);
    txLine(10, 10, 30, 10);
    txLine(10, 10, 15, 5);
    txLine(10, 10, 15, 15);
    txSetColor (TX_BLACK, 4);
}

int main()
{
    txCreateWindow (1000, 800);

    string PAGE = "�������";

    bool openSubsect = false;

    //�������� ������ ������
    int nObj = 10;
    int nActObj = 0;
    int nActRoom = 0;
    strObject object[100];
    object[0] = {"Pictures/������/������/������.bmp", "������", "������"};
    object[1] = {"Pictures/������/������/������2.bmp", "������", "������"};
    object[2] = {"Pictures/������/������/Stul1.bmp","������", "������"};
    object[3] = {"Pictures/������/������/Stul2.bmp", "������", "������"};
    object[4] = {"Pictures/������/������/Stul3.bmp", "������", "������"};
    object[5] = {"Pictures/������/������/Stul4.bmp", "������", "������"};
    object[6] = {"Pictures/������/������/Divan1.bmp", "������", "������", 100};
    object[7] = {"Pictures/������/�����/����.bmp", "������", "�����", 100};
    object[8] = {"Pictures/������/�������/Bed.bmp", "������", "�������", 100};
    object[9] = {"Pictures/�������/����������/���������.bmp", "�������", "����������", 100};

    //�������, ������ �� ��������
    int yStul = 100;
    for(int i = 0; i < nObj; i++)
    {
        if (object[i].subSection == "������")
        {
            object[i].y = yStul;
            yStul = yStul + 150;
        }


        object[i].x = 750;
        object[i].drawObject = false;
        object[i].pic = txLoadImage (object[i].address);
        object[i].width  = getWidth (object[i].address);
        object[i].height = getHeight(object[i].address);
    }

    strObject activeObj[1000];
    int active = -10;

    room ActRoom[100];

    //�������
    BUTTON buttons[5];
    buttons[0] =   {0, 0, "������",     {{"������"      }, {"�����"       }, {"�������"   }, {"�����"     }, {"������"}}};
    buttons[1] = {200, 0, "�������",    {{"����. ������"}, {"������������"}, {"����������"}, {"����������"}, {" "}}};
    buttons[2] = {400, 0, "���",        {{"������"      }, {"�����"       }, {""          }, {""          }, {" "}}};
    buttons[3] = {600, 0, "������",     {{"������"      }, {"�������"     }, {"�����"     }, {""          }, {" "}}};
    buttons[4] = {800, 0, "����������", {{"�����"       }, {"����"        }, {"�����"     }, {""          }, {" "}}};
    //���������� ������ ���� �� �������� ���������

    int mx = -500;
    int my = -500;

    //��������� ������ / ���������
    int choosenSection = -1;
    string chSection = "";
    string chSubSection = "";

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_BLACK, 4);
        txSetFillColor (TX_WHITE);
        txClear();

        //�� ���� ��� �� ��������� ������� ��������?
        if (PAGE == "�������")
        {
            txDrawText(0, 200, 150, 300, "������ �����");
            txTextOut(450, 50, "��� �������.");
            txTextOut(250, 100, "��� �������� ���� � ������� �� ������ ������� �� ��� ������.");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseX() <= 100)
            {
                PAGE = "��������";
                txSleep(200);
            }

        }
        else
        {
            txRectangle (0, 0, 1000, 100);

            //��������� �� ������
            if(!openSubsect)
            {
                //������ ������
                for (int i = 0; i < 5; i++)
                {
                    txSetColor (TX_BLACK, 4);
                    if(txMouseX() >= buttons[i].x          && txMouseY() >= buttons[i].y &&
                       txMouseX() <= buttons[i].x + 200    && txMouseY() <= buttons[i].y + 100)
                        txSetColor (TX_LIGHTBLUE, 4);
                    buttons[i].draw();
                    txSetColor (TX_BLACK, 4);
                }

                if (txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
                {
                    //����� ��������� ������?
                    for (int i = 0; i < 5; i++)
                    {
                        if (txMouseX() >= buttons[i].x && txMouseX() <= buttons[i].x + 200)
                        {
                            choosenSection = i;
                            chSection = buttons[i].text;
                        }
                    }

                    mx = buttons[choosenSection].x ;
                    my = 100 ;
                }
                txRectangle (mx, my, mx + 200, my + 140);

                //����� ��� � ��������� ��������
                for (int i = 0; i < 4; i++)
                {
                    //���� ����������
                    if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20)
                        txSetColor (TX_LIGHTBLUE, 4);
                    if(choosenSection >= 0)
                        txDrawText (mx,         my + 5 + i * 20,
                                    mx + 200,   my + 25 + i * 20 , buttons[choosenSection].subButtons[i].text);

                    //����� ����������
                    if (txMouseX() >= mx &&
                        txMouseX() <= mx + 150 &&
                        txMouseY() >= my + 5 + i * 20 &&
                        txMouseY() <= my + 25 + i * 20 &&
                        txMouseButtons() == 1)
                    {
                        openSubsect = true;
                        chSection = buttons[choosenSection].text;
                        chSubSection = buttons[choosenSection].subButtons[i].text;
                    }
                    txSetColor (TX_BLACK, 4);
                }
            }

            else
                drawBackArrow();



            txDrawText(0, 200, 150, 300, "������ �����");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseY() >= 200 &&
                txMouseX() <= 100)
            {
                PAGE = "�������";
                txSleep(200);
            }

            //������ ������ ����������
            if (txMouseX() >= 0 && txMouseX() <= 35 &&
                txMouseY() >= 0 && txMouseY() <= 20 &&
                txMouseButtons() == 1 && openSubsect)
            {
                openSubsect = false;
                txSleep(200);
                chSection = "";
                chSubSection = "";
            }

            //�� ��� ����� mx, my? ������ �� �������� ���� ������������� ��� �������? ��� � �������� ��� ��

            //����� ���������
            for(int i = 0; i < nObj; i++)
            {
                object[i].drawObject = false;

                //������ �������� ���� ������� �����-�� ���� "������-���������"
                if (openSubsect && chSubSection == object[i].subSection && chSection == object[i].section)
                {
                    object[i].drawObject = true;
                }
            }

            //��������� ����
            if (chSection == "����������" && chSubSection == "�����")
            {
                if (txMouseButtons() == 1)
                {
                    nActRoom++;
                    ActRoom[nActRoom] = {txMouseX(), txMouseY(), txMouseX(), txMouseY()};
                    txRectangle(ActRoom[nActRoom].x, ActRoom[nActRoom].y, ActRoom[nActRoom].x2, ActRoom[nActRoom].y2);
                    txSleep(10);
                    while(txMouseButtons() == 1)
                    {
                        ActRoom[nActRoom].x2 = txMouseX();
                        ActRoom[nActRoom].y2 = txMouseY();
                        for(int i = 0; i < nActRoom + 1; i++)
                        {
                            txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);
                            drawPics(activeObj, nActObj);
                        }
                        txSleep(50);
                    }
                }
            }

            for(int i = 0; i < nActRoom + 1; i++)
                txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);

            //�������� ������ ������
            for(int i = 0; i < nObj; i++)
            {
                if (object[i].drawObject)
                {
                    Win32::TransparentBlt (txDC(),object[i].x,object[i].y,150,150,object[i].pic,0,0,object[i].width,object[i].height,TX_BLACK);
                }

                //���� �� ������� (������)
                if (object[i].drawObject &&
                    txMouseX() >= object[i].x &&
                    txMouseX() <= object[i].x + 150 &&
                    txMouseY() >= object[i].y &&
                    txMouseY() <= object[i].y + 150 && txMouseButtons() == 1)
                {
                    activeObj[nActObj] = {object[i].address, object[i].section, object[i].subSection, 300, 300, true, object[i].width, object[i].height, object[i].pic};
                    nActObj++;
                    while(txMouseButtons() == 1)
                    {}
                }
            }

            drawPics(activeObj, nActObj);

            //����� � �������� �������� ��������
            for(int i = 0; i < nActObj; i++)
            {
                if (activeObj[i].drawObject &&
                    txMouseX() >= activeObj[i].x &&
                    txMouseX() <= activeObj[i].x + 150 &&
                    txMouseY() >= activeObj[i].y &&
                    txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                    active < 0)
                {
                    active = i;
                }

                if (activeObj[i].drawObject &&
                    activeObj[i].y + 75 <= 100)
                    activeObj[i].drawObject = false;
            }

            //�������� �������� ��������
            if (active >= 0)
            {
                activeObj[active].x = txMouseX() - 75;
                activeObj[active].y = txMouseY() - 75;
            }

            if (txMouseButtons()!= 1)
                active = -10;


            //�� ������� �������� ��� ������
            for(int i = 0; i < nObj; i++)
                if (GetAsyncKeyState(VK_SPACE))
                {
                    object[i].drawObject=false;
                }



            //� �������� ������� ������� ����� ��������� �������
            //if (chSubSection != "")
            {
                txTextOut(800, 10, chSection.c_str());
                txTextOut(800, 30, chSubSection.c_str());
            }
        }

        txSleep(20) ;
    }

    //�������� ��������
    for(int i = 0; i < nObj; i++)
        txDeleteDC (object[i].pic);

    return 0;
}
