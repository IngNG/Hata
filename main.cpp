#include "TXLib.h"

#include "strObject.cpp"

//���������
struct subBUTTON
{
    bool subBtnOpened;
    const char* text;
};

//������
struct BUTTON
{
    int x;
    int y;
    bool btnOpened;
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


const int MENU_OPEN = 1;

//����
void fon(int mx, int my)
{
    txClear();
    txSetColor (TX_BLACK, 4);
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
    txSetColor (TX_BLACK, 4);
}

int main()
{
    txCreateWindow (1000, 800);

    string PAGE = "�������";

    bool openSubsect = false;

    //�������� ������ ������
    int nObj = 7;
    int nActObj = 0;
    int nActRoom = 0;
    strObject object[100];
    object[0] = {750, 100, txLoadImage ("Pictures/������/������.bmp"),
        "������", "������", false, 324, 306};
    object[1] = {750, 250, txLoadImage ("Pictures/������/������2.bmp"),
        "������", "������", false, 382, 400};
    object[2] = {750, 400, txLoadImage ("Pictures/������/couchplanesofa.bmp"),
        "������", "������", false, 750, 563};

    object[3] = {750, 550, txLoadImage ("Pictures/������/Sofa.bmp"),
        "������", "������", false, 768, 332};
    object[4] = {750, 100, txLoadImage ("Pictures/������/����.bmp"),
        "������", "�����", false, 300, 177};
    object[5] = {750, 250, txLoadImage ("Pictures/������/Bed.bmp"),
        "������", "�������", false, 415, 310};

    object[6] = {750, 100, txLoadImage ("Pictures/�������/���������.bmp"),
        "�������", "����������", false, 150, 29};

    strObject activeObj[1000];
    int active = -10;

    room ActRoom[100];

    //�������
    BUTTON buttons[5];
    buttons[0] =   {0, 0, false, "������",     {{false, "������"      }, {false, "�����"       }, {false, "�������"   }, {false, "�����"     }, {false, " "}}};
    buttons[1] = {200, 0, false, "�������",    {{false, "����. ������"}, {false, "������������"}, {false, "����������"}, {false, "����������"}, {false, " "}}};
    buttons[2] = {400, 0, false, "���",        {{false, "������"      }, {false, "�����"       }, {false, ""          }, {false, ""          }, {false, " "}}};
    buttons[3] = {600, 0, false, "������",     {{false, "������"      }, {false, "�������"     }, {false, "�����"     }, {false, ""          }, {false, " "}}};
    buttons[4] = {800, 0, false, "����������", {{false, "�����"       }, {false, "����"        }, {false, "�����"     }, {false, ""          }, {false, " "}}};

    int window = 0;
    int mx = -500;
    int my = -500;

    //��������� ������ / ���������
    int choosenSection = -1;
    int choosenSubSection = -1;
    string chSection = "";
    string chSubSection = "";

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();

        txDrawText(0, 0, 100, 100, "������ �����");

        if (PAGE == "�������")
        {
            txTextOut(450, 50, "��� �������.");
            txTextOut(250, 100, "��� �������� ���� � ������� �� ������ ������� �� ��� ������.");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseX() <= 100)
            {
                PAGE = "��������";
                txSleep(2000);
            }

        }
        else
        {
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseX() <= 100)
            {
                PAGE = "�������";
                txSleep(2000);
            }

            if(!openSubsect)
            {
                fon(mx, my);
                for (int i = 0; i < 5; i++)
                {
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
                            buttons[i].btnOpened = true;
                            choosenSection = i;
                            chSection = buttons[i].text;
                        }
                        else
                            buttons[i].btnOpened = false;
                    }

                    for (int i = 0; i < 4; i++)
                            buttons[i].btnOpened = false;
                    mx = buttons[choosenSection].x ;
                    my = 100 ;
                }
                txRectangle (mx, my, mx + 200, my + 140);

                for (int i = 0; i < 4; i++)
                {
                    //���� ����������
                    if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20)
                        txSetColor (TX_LIGHTBLUE, 4);
                    if(!(choosenSection == -1))
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
                        buttons[choosenSection].subButtons[i].subBtnOpened = true;
                        chSubSection = buttons[choosenSection].subButtons[i].text;

                        //� ����� ��������� ������ ���-�� ��������?
                    }
                    txSetColor (TX_BLACK, 4);
                }
                //txSleep(20);
            }

            else
                openSubsection();

            //������ ������ ����������
            if (txMouseX() >= 0 && txMouseX() <= 35 &&
                txMouseY() >= 0 && txMouseY() <= 20 &&
                txMouseButtons() == 1 && openSubsect)
            {
                openSubsect = false; /*mx = -500;*/ txSleep(200);
                chSection = "";
                chSubSection = "";
                for (int i = 0; i < 4; i++)
                    buttons[choosenSection].subButtons[i].subBtnOpened = false;
            }

            //�� ��� ����� mx, my? ������ �� �������� ���� ������������� ��� �������? ��� � �������� ��� ��

            //����� ���������
            for(int i = 0; i < nObj; i++)
                object[i].drawObject = false;

            //������ �������� ���� ������� �����-�� ���� "������-���������"
            for(int i = 0; i < nObj; i++)
                if (openSubsect && chSubSection == object[i].subSection && chSection == object[i].section)
                {
                    object[i].drawObject = true;
                }


            //��� ������� ��������. ���?
            //if (openSubsect && buttons[4].subButtons[2].subBtnOpened && buttons[4].btnOpened)
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
                            txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);
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
                    activeObj[nActObj] = {300, 300, object[i].pic, object[i].section, object[i].subSection, true, object[i].width, object[i].height};
                    nActObj++;
                    while(txMouseButtons() == 1)
                    {}
                }
            }

            drawPics(activeObj, nActObj);

            for(int i = 0; i < nActObj; i++)
            {
            if (activeObj[i].drawObject &&
                    txMouseX() >= activeObj[i].x &&
                    txMouseX() <= activeObj[i].x + 150 &&
                    txMouseY() >= activeObj[i].y &&
                    txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                    active < 0
                    )
                {
                    active = i;
                }
                if (activeObj[i].drawObject &&
                    activeObj[i].y + 75 <= 100)
                    activeObj[i].drawObject = false;
            }


                if (active >= 0)
                {
                    activeObj[active].x = txMouseX() - 75;
                    activeObj[active].y = txMouseY() - 75;
                }

                if (txMouseButtons()!= 1)
                    active = -10;

            //��� ���?
            if (window == MENU_OPEN)
                Win32::TransparentBlt (txDC(), mx, 0, 50, 50, object[0].pic, 0, 0, 686, 700, TX_BLACK); // 10x zoom

            //�� ������� �������� ��� ������
            for(int i = 0; i < nObj; i++)
                if (GetAsyncKeyState(VK_SPACE))
                {
                    object[i].drawObject=false;
                }


            if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
            {
                mx = -500;
                my = -500;
            }

            //� �������� ������� ������� ����� ��������� �������
            for(int i = 0; i < 5; i++)
            {
                if (buttons[i].btnOpened)  txTextOut(800, 10, buttons[i].text);
                    for(int j = 0; j < 4; j++)
                        if (buttons[i].subButtons[j].subBtnOpened)  txTextOut(800, 30, buttons[i].subButtons[j].text);
            }
        }

        txSleep(20) ;
    }

    //�������� ��������
    for(int i = 0; i < nObj; i++)
        txDeleteDC (object[i].pic);

    return 0;
}
