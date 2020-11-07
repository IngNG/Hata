#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct room
{
    int x ;
    int y ;
    int x2;
    int y2;
};

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

    string PAGE = "��������";

    bool openSubsect = false;

    //�������� ������ ������
    Picture variants[100];
    int nVariants = fillVariants(variants);

    //�������� � ������
    int nPictures = 0;
    Picture activeObj[1000];
    int activePic = -10;

    //�����, �������
    int nRooms = 0;
    room ActRoom[100];
    int activeRoom = -10;

    //�������
    BUTTON buttons[5];
    buttons[0] =   {0, 0, "������",     {{"������"      }, {"�����"       }, {"�������"   }, {"������"    }, {"�����"}}};
    buttons[1] = {200, 0, "�������",    {{"����. ������"}, {"������������"}, {"����������"}, {"����������"}, {" "}}};
    buttons[2] = {400, 0, "���",        {{"������"      }, {"�����"       }, {""          }, {""          }, {" "}}};
    buttons[3] = {600, 0, "������",     {{"������"      }, {"�������"     }, {"�����"     }, {""          }, {" "}}};
    buttons[4] = {800, 0, "����������", {{"�����"       }, {"����"        }, {"�����"     }, {""          }, {" "}}};
    //���������� ������ ���� �� �������� ���������

    int mx = -500;

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
            txDrawText(850, 700, 1000, 800, "������� �������");
            txTextOut(450, 50, "��� �������.");
            txTextOut(250, 100, "��� �������� ���� � ������� �� ������ ������� �� ��� ������.");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 850 &&  txMouseY() >= 700 &&
                txMouseX() <= 1000 && txMouseY() <= 800)
            {
                PAGE = "��������";
                txSleep(200);
            }
        }
        else
        {
            drawPics(activeObj, nPictures);
            for(int i = 0; i < nRooms + 1; i++)
                txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);

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
                }

                int my = 100;
                txRectangle (mx, my, mx + 200, my + 140);

                //����� ��� � ��������� ��������
                for (int i = 0; i < 5; i++)
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
                        txMouseButtons() == 1 && activePic <= 0)
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

            txDrawText(850, 700, 1000, 800, "������� �������");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 850 &&
                txMouseY() >= 700 &&
                txMouseX() <= 1000)
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
            for(int i = 0; i < nVariants; i++)
            {
                variants[i].drawObject = false;

                //������ �������� ���� ������� �����-�� ���� "������-���������"
                if (openSubsect && chSubSection == variants[i].subSection && chSection == variants[i].section)
                {
                    variants[i].drawObject = true;
                }
            }

            //��������� ����
            if (chSection == "����������" && chSubSection == "�����")
            {
                if (txMouseButtons() == 1)
                {
                    nRooms++;
                    ActRoom[nRooms] = {txMouseX(), txMouseY(), txMouseX(), txMouseY()};
                    txRectangle(ActRoom[nRooms].x, ActRoom[nRooms].y, ActRoom[nRooms].x2, ActRoom[nRooms].y2);
                    txSleep(10);
                    while(txMouseButtons() == 1)
                    {
                        ActRoom[nRooms].x2 = txMouseX();
                        ActRoom[nRooms].y2 = txMouseY();
                        for(int i = 0; i < nRooms + 1; i++)
                        {
                            txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);
                            drawPics(activeObj, nPictures);
                        }
                        txSleep(50);
                    }
                }
            }

            //�������� ������ ������
            for(int i = 0; i < nVariants; i++)
            {
                if (variants[i].drawObject)
                {
                    Win32::TransparentBlt (txDC(),variants[i].x,variants[i].y,150,150,variants[i].pic,0,0,variants[i].width,variants[i].height,TX_BLACK);
                }

                //���� �� ������� (������)
                if (variants[i].drawObject &&
                    txMouseX() >= variants[i].x &&
                    txMouseX() <= variants[i].x + 150 &&
                    txMouseY() >= variants[i].y &&
                    txMouseY() <= variants[i].y + 150 && txMouseButtons() == 1)
                {
                    activeObj[nPictures] = {variants[i].address, variants[i].section, variants[i].subSection, 300, 300, true, variants[i].width, variants[i].height, variants[i].pic};
                    nPictures++;
                    while(txMouseButtons() == 1)
                    {}
                }
            }

            //����� � �������� �������� ��������
            for(int i = 0; i < nRooms; i++)
            {
                if (activeObj[i].drawObject &&
                    txMouseX() >= activeObj[i].x &&
                    txMouseX() <= activeObj[i].x + 150 &&
                    txMouseY() >= activeObj[i].y &&
                    txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                    activePic < 0)
                {
                    activePic = i;
                }

                if (activeObj[i].drawObject &&
                    activeObj[i].y + 75 <= 100)
                    activeObj[i].drawObject = false;
            }

            for(int i = 0; i < nRooms + 1; i++)
            {
                if (txMouseX() >= ActRoom[i].x &&
                    txMouseX() <= ActRoom[i].x2 &&
                    txMouseY() >= ActRoom[i].y &&
                    txMouseY() <= ActRoom[i].y2 && txMouseButtons() == 2 &&
                    activeRoom < 0)
                {
                    activeRoom = i;
                }

                if (ActRoom[i].y <= 100)
                    {ActRoom[i].x2 = ActRoom[i].x; ActRoom[i].y2 = ActRoom[i].x;}
            }
            //�������� �������� ��������
            if (activePic >= 0)
            {
                activeObj[activePic].x = txMouseX() - 75;
                activeObj[activePic].y = txMouseY() - 75;
            }

            if (activeRoom >= 0)
            {
                int y3 = ActRoom[activeRoom].y2 - ActRoom[activeRoom].y;
                int x3 = ActRoom[activeRoom].x2 - ActRoom[activeRoom].x;
                ActRoom[activeRoom].x = txMouseX();
                ActRoom[activeRoom].y = txMouseY();
                ActRoom[activeRoom].x2 = txMouseX() + x3;
                ActRoom[activeRoom].y2 = txMouseY() + y3;
            }

            if (txMouseButtons()!= 1)
                activePic = -10;

            if (txMouseButtons()!= 2)
                activeRoom = -10;

            //�� ������� �������� ��� ������
           // for(int i = 0; i < nVariants; i++)
           //     if (GetAsyncKeyState(VK_SPACE))
           //     {
           //         variants[i].drawObject=false;
           //     }

            //� �������� ������� ������� ����� ��������� �������
            if (chSubSection != "")
            {
                txTextOut(800, 10, chSection.c_str());
                txTextOut(800, 30, chSubSection.c_str());
            }

        }

        txSleep(20) ;
    }

    //�������� ��������
    for(int i = 0; i < nVariants; i++)
        txDeleteDC (variants[i].pic);

    return 0;
}
