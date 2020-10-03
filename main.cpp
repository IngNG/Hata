#include "TXLib.h"

//#include "Struct"

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
    object[3] = {400, 0, txLoadImage ("Pictures/Bed.bmp"), false, 310, 415};
    object[4] = {550, 0, txLoadImage ("Pictures/couchplanesofa.bmp"), false, 750, 563};
    object[5] = {700, 0, txLoadImage ("Pictures/Sofa.bmp"), false, 768, 332};
    object[6] = {815, 0, txLoadImage ("Pictures/izognyt��.bmp"), false, 150, 29};








    //�������
    BUTTON buttons[5];
    buttons[0] =   {0, 0, false, "������",     {{false, "�������1"}, {false, "����"}, {false, "������"}, {false, "������"}, {false, "������"}}};
    buttons[1] = {200, 0, false, "�������",    {{false, "�������2"}, {false, "����"}, {false, "������"}, {false, "������"}, {false, "������"}}};
    buttons[2] = {400, 0, false, "���",        {{false, "�������3"}, {false, "����"}, {false, "������"}, {false, "������"}, {false, "������"}}};
    buttons[3] = {600, 0, false, "�����",      {{false, "�������4"}, {false, "����"}, {false, "������"}, {false, "������"}, {false, "������"}}};
    buttons[4] = {800, 0, false, "����������", {{false, "�������5"}, {false, "����"}, {false, "������"}, {false, "������"}, {false, "������"}}};

    int window = 0;
    int mx = -500;
    int my = -500;

    //��������� ������ / ���������
    int choosenSection = -1;
    int choosenSubSection = -1;

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

            //for (int i = 0; i < 4; i++)
            //    buttons[0].subButtons[i].subBtnOpened = false;

            for (int i = 0; i < 4; i++)
            {
                //���� ����������
                if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20)
                    txSetColor (TX_LIGHTBLUE, 4);
                txDrawText (mx,         my + 5 + i * 20,
                            mx + 150,   my + 25 + i * 20 , buttons[0].subButtons[i].text);

                //����� ����������
                if (txMouseX() >= mx &&
                    txMouseX() <= mx + 150 &&
                    txMouseY() >= my + 5 + i * 20 &&
                    txMouseY() <= my + 25 + i * 20 &&
                    txMouseButtons() == 1)
                {
                    openSubsect = true;
                    buttons[choosenSection].subButtons[i].subBtnOpened = true;

                    //� ����� ��������� ������ ���-�� ��������?
                }
                txSetColor (TX_BLACK, 4);
            }
            txSleep(20);
        }

        else
            openSubsection();

        //������ ������ ����������
        if (txMouseX() >= 0 && txMouseX() <= 35 &&
            txMouseY() >= 0 && txMouseY() <= 20 &&
            txMouseButtons() == 1 && openSubsect)
        {
            openSubsect = false; /*mx = -500;*/ txSleep(200);

            for (int i = 0; i < 4; i++)
                buttons[choosenSection].subButtons[i].subBtnOpened = false;
        }

        //�� ��� ����� mx, my? ������ �� �������� ���� ������������� ��� �������? ��� � �������� ��� ��

        //���� �� ������
        if (txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
        {
            //������ ��� �� ��������� (����� �������� ��������)
            if (buttons[0].btnOpened && txMouseX() >= buttons[0].x && txMouseX() <= buttons[0].x + 200){}
            else if (buttons[1].btnOpened && txMouseX() >= buttons[1].x && txMouseX() <= buttons[1].x + 200){}
            else
            {
                buttons[0].btnOpened = false;
                buttons[1].btnOpened = false;
                my = txMouseY() ;
                mx = txMouseX() ;
                if(mx + 150 >= 1000)
                   mx = 850;
            }

            //����� ��������� ������?
            for (int i = 0; i < 5; i++)
            {
                if (txMouseX() >= buttons[i].x && txMouseX() <= buttons[i].x + 200)
                {
                    buttons[i].btnOpened = true;
                    choosenSection = i;
                }
                else
                    buttons[i].btnOpened = false;
            }

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

        //������ �������� ���� ������� �����-�� ���� "������-���������"
        if (openSubsect && buttons[0].subButtons[0].subBtnOpened && buttons[0].btnOpened)
        {
            object[0].drawObject = true;
        }
        if (openSubsect && buttons[1].subButtons[1].subBtnOpened && buttons[1].btnOpened)
        {
            object[1].drawObject = true;
        }
        if (openSubsect && buttons[1].subButtons[1].subBtnOpened && buttons[1].btnOpened)
        {
            object[2].drawObject = true;
        }
        if (openSubsect && buttons[1].subButtons[2].subBtnOpened && buttons[1].btnOpened)
        {
            object[3].drawObject = true;
        }

        if (openSubsect && buttons[1].subButtons[2].subBtnOpened && buttons[1].btnOpened)
        {
            object[4].drawObject = true;
        }
        if (openSubsect && buttons[1].subButtons[2].subBtnOpened && buttons[1].btnOpened)
        {
            object[5].drawObject = true;
        }
        if (openSubsect && buttons[1].subButtons[2].subBtnOpened && buttons[1].btnOpened)
        {
            object[6].drawObject = true;
        }

        if (openSubsect && buttons[1].subButtons[3].subBtnOpened && buttons[1].btnOpened)
        {
            object[7].drawObject = true;
        }






        //�������� ������ ������
        for(int i = 0; i < 8; i++)
            if (object[i].drawObject)
            {
                Win32::TransparentBlt (txDC(),object[i].x,object[i].y,150,150,object[i].pic,0,0,object[i].width,object[i].height,TX_BLACK);
            }

        //��� ���?
        if (window == MENU_OPEN)
            Win32::TransparentBlt (txDC(), mx, 0, 50, 50, object[0].pic, 0, 0, 686, 700, TX_BLACK); // 10x zoom

        //�� ������� �������� ��� ������
        for(int i = 0; i < 8; i++)
            if (GetAsyncKeyState(VK_SPACE))
            {
                object[i].drawObject=false;
            }


        if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
        {
            //mx = -500;
            //my = -500;
        }

        //� �������� ������� ������� ����� ��������� �������
        {
        if (buttons[0].btnOpened)  txTextOut(100, 200, "0");
        if (buttons[1].btnOpened)  txTextOut(100, 250, "1");
        if (buttons[2].btnOpened)  txTextOut(100, 300, "2");
        if (buttons[3].btnOpened)  txTextOut(100, 350, "3");
        if (buttons[4].btnOpened)  txTextOut(100, 400, "4");

        if (buttons[0].subButtons[0].subBtnOpened)  txTextOut(200, 200, "0");
        if (buttons[0].subButtons[1].subBtnOpened)  txTextOut(200, 250, "1");
        }
        txSleep(20) ;
    }

    //�������� ��������
    for(int i = 0; i < 3; i++)
        txDeleteDC (object[i].pic);

    return 0;
}
