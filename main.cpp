#include "TXLib.h"
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

/*void drawBackArrow()
{
    txSetColor (TX_BLACK, 2);
    if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20)
        txSetColor (TX_LIGHTRED, 2);
    txLine(10, 10, 30, 10);
    txLine(10, 10, 15, 5);
    txLine(10, 10, 15, 15);
    txSetColor (TX_BLACK, 4);
}*/

int main()
{
    txCreateWindow (1000, 800);

    string PAGE = "��������";

    ///bool openSubsect = false;


    //�������
    BUTTON buttons[5];
    buttons[0] = {"������",     {{"������"      }, {"�����"       }, {"�������"   }, {"������"    }, {"�����"}}};
    buttons[1] = {"�������",    {{"����. ������"}, {"������������"}, {"����������"}, {"����������"}, {" "}}};
    buttons[2] = {"���",        {{"������"      }, {"�����"       }, {""          }, {""          }, {" "}}};
    buttons[3] = {"������",     {{"������"      }, {"�������"     }, {"�����"     }, {""          }, {" "}}};
    buttons[4] = {"����������", {{"�����"       }, {"����"        }, {"�����"     }, {""          }, {" "}}};
    //���������� ������ ���� �� �������� ���������
    for(int i = 0; i < 4 + 1; i++)
    {
        buttons[i].x = i * 200;
        buttons[i].y = 0;
    }

    int mx = -500;
    int x4 = 0;
    int y4 = 0;
    int x5 = 0;
    int y5 = 0;
    //�������� ������ ������
    Picture variants[100];
    int nVariants = fillVariants(variants, buttons);

    //�������� � ������
    int nPictures = 0;
    Picture activeObj[1000];
    int activePic = -10;

    //�����, �������
    int nRooms = 0;
    room ActRoom[100];
    int activeRoom = -10;


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
            txSetColor(TX_BLACK, 4);
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&  txMouseY() >= 700 &&
                txMouseX() <= 150 && txMouseY() <= 800)
                txSetColor (TX_LIGHTBLUE, 4);

            txDrawText(0, 700, 150, 800, "������� �������");
            txSetColor(TX_BLACK, 4);
            txTextOut(450, 50, "��� �������.");
            txTextOut(250, 100, "��� �������� ���� � ������� �� ������ ������� �� ��� ������.");
            txTextOut(300, 150, "�������� ����� ������� ���������� �� �����.");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&  txMouseY() >= 700 &&
                txMouseX() <= 150 && txMouseY() <= 800)
            {
                PAGE = "��������";
                txSleep(200);
            }
        }
        else
        {
            for(int i = 0; i < nRooms + 1; i++)
                txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);
            drawPics(activeObj, nPictures);

            txRectangle (0, 0, 1000, 100);

            //��������� �� ������

            //������ ������
            for (int i = 0; i < 5; i++)
            {
                buttons[i].draw();
                if(txMouseX() >= buttons[i].x          && txMouseY() >= buttons[i].y &&
                   txMouseX() <= buttons[i].x + 200    && txMouseY() <= buttons[i].y + 100)
                    txSetColor (TX_LIGHTBLUE, 4);
                txDrawText(buttons[i].x, buttons[i].y, buttons[i].x + 200, buttons[i].y + 100 , buttons[i].text);
                txSetColor (TX_BLACK, 4);
            }

            //����� ��������� ������?
            for (int i = 0; i < 5; i++)
            {
                if (txMouseY() >= 0            && txMouseY() <= 100 &&
                    txMouseX() >= buttons[i].x && txMouseX() <= buttons[i].x + 200 &&
                    txMouseButtons() == 1)
                {
                    choosenSection = i;
                    chSection = buttons[i].text;
                }
            }

            mx = buttons[choosenSection].x ;

            int my = 100;
            if(choosenSection > -1)
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
                    //openSubsect = true;
                    chSection = buttons[choosenSection].text;
                    chSubSection = buttons[choosenSection].subButtons[i].text;
                }
                txSetColor (TX_BLACK, 4);
            }
            //������� �������
            txDrawText(0, 700, 150, 800, "������� �������");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseY() >= 700 &&
                txMouseX() <= 150)
            {
                PAGE = "�������";
                txSleep(200);
            }

            //������ ������ ����������
            if (txMouseY() >= 300 && txMouseButtons() == 1 && chSubSection != "�����")
            {
                //openSubsect = false;
                //txSleep(20);
                choosenSection = -1;
                //chSection = "";
                //chSubSection = "";
            }

            //����� ���������
            for(int i = 0; i < nVariants; i++)
            {
                variants[i].drawObject = false;

                //������ �������� ���� ������� �����-�� ���� "������-���������"
                if (chSubSection == variants[i].subSection && chSection == variants[i].section)
                {
                    variants[i].drawObject = true;
                }
            }

            //��������� ����
            if (chSection == "����������" && chSubSection == "�����")
            {
                txTextOut(850, 245, "*�������*");
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
                if (variants[i].drawObject && chSubSection != "�����")
                {
                    Win32::TransparentBlt (txDC(),variants[i].x,variants[i].y,150,150,variants[i].pic,0,0,variants[i].width,variants[i].height,TX_WHITE);
                }
                if (variants[i].drawObject && chSubSection == "�����")
                {
                    Win32::TransparentBlt (txDC(),variants[i].x,variants[i].y,150,104,variants[i].pic,0,0,variants[i].width,variants[i].height,TX_WHITE);
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
            for(int i = 0; i < nPictures; i++)
            {
                if (activeObj[i].drawObject &&
                    txMouseX() >= activeObj[i].x &&
                    txMouseX() <= activeObj[i].x + 150 &&
                    txMouseY() >= activeObj[i].y &&
                    txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                    activePic < 0)
                {
                    //activeObj[i].yMouse = txMouseY() - activeObj[i];
                    activePic = i;
                    x4 = txMouseX() - activeObj[activePic].x;
                    y4 = txMouseY() - activeObj[activePic].y;
                }

                if (activeObj[i].drawObject &&
                    activeObj[i].y <= 100)
                    activeObj[i].drawObject = false;
            }
            //����� � �������� �������� �������
            for(int i = 0; i < nRooms + 1; i++)
            {
                if (txMouseX() >= ActRoom[i].x &&
                    txMouseX() <= ActRoom[i].x2 &&
                    txMouseY() >= ActRoom[i].y &&
                    txMouseY() <= ActRoom[i].y2 && txMouseButtons() == 2 &&
                    activeRoom < 0)
                {
                    activeRoom = i;
                    x5 = txMouseX() - ActRoom[activeRoom].x;
                    y5 = txMouseY() - ActRoom[activeRoom].y;
                }

                if (ActRoom[i].y <= 100)
                    {ActRoom[i].x2 = ActRoom[i].x; ActRoom[i].y2 = ActRoom[i].x;}
            }
            //�������� �������� ��������
            if (activePic >= 0)
            {
                //if(chSubSection == "�����" &&
                //((ActRoom[activeRoom].x == activeObj[activePic].x - 25 or
                //   ActRoom[activeRoom].x == activeObj[activePic].x + 25) )
                //    activeObj[activePic].x = ActRoom[activeRoom].x
                activeObj[activePic].x = txMouseX() - x4;
                activeObj[activePic].y = txMouseY() - y4;
            }
            //�������� �������� �������
            if (activeRoom >= 0)
            {
                int y3 = ActRoom[activeRoom].y2 - ActRoom[activeRoom].y;
                int x3 = ActRoom[activeRoom].x2 - ActRoom[activeRoom].x;
                ActRoom[activeRoom].x = txMouseX() - x5;
                ActRoom[activeRoom].y = txMouseY() - y5;
                ActRoom[activeRoom].x2 = txMouseX() + x3 - x5;
                ActRoom[activeRoom].y2 = txMouseY() + y3 - y5;
            }

            if (txMouseButtons()!= 1)
                activePic = -10;

            if (txMouseButtons()!= 2)
                activeRoom = -10;

            //� �������� ������� ������� ����� ��������� �������
            /*if (chSubSection != "")
            {
                txTextOut(800, 10, chSection.c_str());
                txTextOut(800, 30, chSubSection.c_str());
            }*/

        }

        txSleep(20) ;
    }

    //�������� ��������
    for(int i = 0; i < nVariants; i++)
        txDeleteDC (variants[i].pic);

    return 0;
}
