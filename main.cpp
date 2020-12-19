#include "TXLib.h"
#include "Picture.cpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
inline int GetFilePointer(HANDLE FileHandle){
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}
bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height){
    bool Success=0;
    HBITMAP OffscrBmp=NULL;
    HDC OffscrDC=NULL;
    LPBITMAPINFO lpbi=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFileA(filename,
                        GENERIC_WRITE,
                        0, NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                      (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if(lpbi->bmiHeader.biClrUsed)
    PalEntries = lpbi->bmiHeader.biClrUsed;
    if(PalEntries){
    if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
        return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;


    CloseHandle (BmpFile);

    delete [] (char*)lpvBits;
    delete [] lpbi;

    DeleteDC (OffscrDC);
    DeleteObject (OffscrBmp);


    return 1;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename, HWND hwnd){


    HDC hDC= GetDC(hwnd);
    HDC hDc = CreateCompatibleDC(hDC);


    HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);


    HGDIOBJ old= SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);


    SelectObject(hDc, old);

    DeleteObject(hBmp);

    DeleteDC (hDc);
    ReleaseDC (hwnd, hDC);

    return ret;
}

///��������� "�������"
struct room
{
    int x ;
    int y ;
    int x2;
    int y2;
    bool window;
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
    txCreateWindow (1200, 800);

    txTextCursor (false);

    string PAGE = "��������";

    //�������
    BUTTON buttons[5];
    buttons[0] = {"������",     {{"������"      }, {"�����"       }, {"�������"   }, {"������"    }, {""}}};
    buttons[1] = {"�������",    {{"��� �����"   }, {"����������"  }, {"����������"}, {""          }, {""}}};
    buttons[2] = {"���",        {{"������"      }, {"�����"       }, {""          }, {""          }, {""}}};
    buttons[3] = {"������",     {{"������"      }, {"�������"     }, {"�����"     }, {""          }, {""}}};
    buttons[4] = {"����������", {{"�����"       }, {"����"        }, {"�����"     }, {""          }, {""}}};

    //���������� ������ ���� �� �������� ���������
    for(int i = 0; i < 5; i++)
    {
        buttons[i].x = i * 200;
        buttons[i].y = 0;
    }

    int mx = -500;
    int x4 = 0;
    int y4 = 0;
    int x5 = 0;
    int y5 = 0;
    int x6 = 0;
    int y6 = 0;
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

        if (PAGE == "�������")
        {
            txSetColor(TX_BLACK, 4);
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&  txMouseY() >= 700 &&
                txMouseX() <= 150 && txMouseY() <= 800)
                txSetColor (TX_LIGHTBLUE, 4);

            txDrawText(0, 700, 150, 800, "������� �������");
            txSetColor(TX_BLACK, 6);
            txTextOut(450, 50, "��� �������.");
            txDrawText(380, 100, 800, 500,
                                "� ��������� ���������� �� ������\n"
                                "����� ��������� �������, ���������\n"
                                "������, ������ �������.\n "
                                "� ����� �������� ��������� 23 �������.\n"
                                "�������� ����� ������� ���������� �� �����.\n"
                                "����� �������� �����, ��� ����� ��� ����� ������ �� ���������� > �����.\n"
                                "� ��� ����� ��������.\n"
                                "����� ����� ������� ������ ����� � ������ ��������.");
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
            {
                if(ActRoom[i].window)
                    txSetColor(TX_LIGHTBLUE, 4);
                txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);
                txSetColor(TX_BLACK, 4);
            }
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
            {
                int a = 120;
                for(int i = 0; i < 6; i++)
                {
                    if(buttons[choosenSection].subButtons[i].text == "")
                        a = a - 25;
                }
                txRectangle (mx, my, mx + 200, my + a);
            }


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
                    chSection = buttons[choosenSection].text;
                    chSubSection = buttons[choosenSection].subButtons[i].text;
                }
                txSetColor (TX_BLACK, 4);
            }

            //������� �������
            txDrawText(0, 700, 150, 800, "������� �������");
            if (txMouseButtons() == 1 &&txMouseX() >= 0 &&
                txMouseY() >= 700 && txMouseX() <= 150)
            {
                PAGE = "�������";
                txSleep(200);
            }

            //������ ������ ����������
            if (txMouseY() >= 200 && txMouseButtons() == 1)
            {
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

            //��������� ���� � ����
            if (chSection == "����������" && (chSubSection == "�����" or chSubSection == "����"))
            {
                txTextOut(850, 175, "*�������*");
                if (txMouseButtons() == 2)
                {
                    nRooms++;
                    if(chSubSection == "����")
                        ActRoom[nRooms] = {txMouseX(), txMouseY(), txMouseX(), txMouseY(), true};
                    else
                        ActRoom[nRooms] = {txMouseX(), txMouseY(), txMouseX(), txMouseY(), false};
                    txRectangle(ActRoom[nRooms].x, ActRoom[nRooms].y, ActRoom[nRooms].x2, ActRoom[nRooms].y2);
                    txSleep(10);
                    while(txMouseButtons() == 2)
                    {
                        if(ActRoom[nRooms].window)
                        {
                            if(txMouseX() - ActRoom[nRooms].x > txMouseY() - ActRoom[nRooms].y)
                            {
                                ActRoom[nRooms].y2 = ActRoom[nRooms].y + 1;
                                ActRoom[nRooms].x2 = txMouseX();
                            }
                            else if(txMouseX() - ActRoom[nRooms].x < txMouseY() - ActRoom[nRooms].y)
                            {
                                ActRoom[nRooms].x2 = ActRoom[nRooms].x + 1;
                                ActRoom[nRooms].y2 = txMouseY();
                            }

                        }
                        else
                        {
                            ActRoom[nRooms].x2 = txMouseX();
                            ActRoom[nRooms].y2 = txMouseY();
                        }
                        if(txMouseX() < ActRoom[nRooms].x)
                            ActRoom[nRooms].x2 = ActRoom[nRooms].x + 1;
                        if(txMouseY() < ActRoom[nRooms].y)
                            ActRoom[nRooms].y2 = ActRoom[nRooms].y + 1;
                        for(int i = 0; i < nRooms + 1; i++)
                        {
                            txSetColor(TX_BLACK, 4);
                            if(ActRoom[i].window)
                                txSetColor(TX_LIGHTBLUE, 4);
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
              /*if (variants[i].drawObject && chSubSection != "�����")
                {
                    Win32::TransparentBlt (txDC(),variants[i].x,variants[i].y,150,150,variants[i].pic,0,0,variants[i].width,variants[i].height,TX_WHITE);
                }
                if (variants[i].drawObject && chSubSection == "�����")
                {
                    Win32::TransparentBlt (txDC(),variants[i].x,variants[i].y,variants[i].width,variants[i].height,variants[i].pic,0,0,variants[i].width,variants[i].height,TX_WHITE);
                }  */

                if(variants[i].width > variants[i].height && variants[i].drawObject)
                    Win32::TransparentBlt  (txDC(), variants[i].x, variants[i].y, 150, 150 * variants[i].height/variants[i].width, variants[i].pic, 0, 0, variants[i].width, variants[i].height, TX_WHITE);
                else if (variants[i].drawObject)
                    Win32::TransparentBlt  (txDC(), variants[i].x, variants[i].y, 150 * variants[i].width/variants[i].height, 150, variants[i].pic, 0, 0, variants[i].width, variants[i].height, TX_WHITE);

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
            for(int i = nPictures; i > -1; i--)
            {
                if (activeObj[i].drawObject &&
                    txMouseX() >= activeObj[i].x &&
                    txMouseX() <= activeObj[i].x + 150 &&
                    txMouseY() >= activeObj[i].y &&
                    txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                    activePic < 0 && activeRoom < 0)
                {
                    //activeObj[i].yMouse = txMouseY() - activeObj[i];
                    activePic = i;
                    x4 = txMouseX() - activeObj[activePic].x;
                    y4 = txMouseY() - activeObj[activePic].y;
                }

                if (activeObj[i].drawObject && activeObj[i].y <= 100 && activePic == i)
                    activeObj[i].drawObject = false;
            }

            //����� � �������� �������� �������
            for(int i = nRooms + 1; i > -1; i--)
            {
                if (txMouseX() >= ActRoom[i].x &&
                    txMouseX() <= ActRoom[i].x2 &&
                    txMouseY() >= ActRoom[i].y &&
                    txMouseY() <= ActRoom[i].y2 && txMouseButtons() == 1 &&
                    activeRoom < 0 && activePic < 0)
                {
                    activeRoom = i;
                    x5 = txMouseX() - ActRoom[activeRoom].x;
                    y5 = txMouseY() - ActRoom[activeRoom].y;
                }

                if (ActRoom[i].y <= 100 && activeRoom == i)
                    {ActRoom[i].x2 = ActRoom[i].x; ActRoom[i].y2 = ActRoom[i].x;}
            }

            //�������� �������� ��������
            if (activePic >= 0)
            {
                //activeRoom = -10;
                activeObj[activePic].x = txMouseX() - x4;
                activeObj[activePic].y = txMouseY() - y4;
            }

            //�������� �������� �������
            if (activeRoom >= 0)
            {
                //activePic = -10;
                int y3 = ActRoom[activeRoom].y2 - ActRoom[activeRoom].y;
                int x3 = ActRoom[activeRoom].x2 - ActRoom[activeRoom].x;
                ActRoom[activeRoom].x = txMouseX() - x5;
                ActRoom[activeRoom].y = txMouseY() - y5;
                ActRoom[activeRoom].x2 = txMouseX() + x3 - x5;
                ActRoom[activeRoom].y2 = txMouseY() + y3 - y5;
            }

            //�������� �� �����
            if (txMouseButtons() == 3)
            {
                x6 = txMouseX();
                y6 = txMouseY();
                int x7[nPictures];
                int y7[nPictures];
                int x8[nRooms];
                int y8[nRooms];
                int x8_2[nRooms];
                int y8_2[nRooms];
                for (int i = 0; i < nPictures; i++)
                {
                    x7[i] = activeObj[i].x;
                    y7[i] = activeObj[i].y;
                }
                for (int i = 0; i < nRooms + 1; i++)
                {
                    x8[i] = ActRoom[i].x;
                    y8[i] = ActRoom[i].y;
                }
                for (int i = 0; i < nRooms + 1; i++)
                {
                    x8_2[i] = ActRoom[i].x2;
                    y8_2[i] = ActRoom[i].y2;
                }
                txSleep(100);
                while (txMouseButtons() == 3)
                {
                    txBegin();
                    txClear();
                    txSetColor(TX_BLACK, 4);
                    txSetFillColor (TX_WHITE);

                    for(int i = 0; i < nRooms + 1; i++)
                    {
                        if(ActRoom[i].window)
                            txSetColor(TX_LIGHTBLUE, 4);
                        txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);
                        txSetColor(TX_BLACK, 4);
                    }
                    drawPics(activeObj, nPictures);

                    txRectangle (0, 0, 1000, 100);

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

                    //�������� ������ ������
                    for(int i = 0; i < nVariants; i++)
                    {

                        if(variants[i].width > variants[i].height && variants[i].drawObject)
                            Win32::TransparentBlt  (txDC(), variants[i].x, variants[i].y, 150, 150 * variants[i].height/variants[i].width, variants[i].pic, 0, 0, variants[i].width, variants[i].height, TX_WHITE);
                        else if (variants[i].drawObject)
                            Win32::TransparentBlt  (txDC(), variants[i].x, variants[i].y, 150 * variants[i].width/variants[i].height, 150, variants[i].pic, 0, 0, variants[i].width, variants[i].height, TX_WHITE);

                    }

                    txDrawText(0, 700, 150, 800, "������� �������");

                    //� �������� ������� ������� ����� ��������� �������
                    if (chSubSection != "")
                    {
                        txTextOut(800, 10, chSection.c_str());
                        txTextOut(800, 30, chSubSection.c_str());
                    }

                    int x9 = txMouseX() - x6;
                    int y9 = txMouseY() - y6;

                    for (int i = 0; i < nPictures; i++)
                    {
                        activeObj[i].x = x7[i] + x9;
                        activeObj[i].y = y7[i] + y9;
                    }

                    for (int i = 0; i < nRooms + 1; i++)
                    {
                        ActRoom[i].x = x8[i] + x9;
                        ActRoom[i].y = y8[i] + y9;
                        ActRoom[i].x2 = x8_2[i] + x9;
                        ActRoom[i].y2 = y8_2[i] + y9;
                    }
                    txSleep(5);

                }
            }

            if(GetAsyncKeyState(VK_SNAPSHOT))
            {
                ScreenCapture(0, 110, 1000, 620, "screen.bmp", txWindow());
                txMessageBox ("�� ������ ��������");
            }

            if (txMouseButtons()!= 1)
                activePic = -10;

            if (txMouseButtons()!= 1)
                activeRoom = -10;

            //� �������� ������� ������� ����� ��������� �������
            /*if (chSubSection != "")
            {
                txTextOut(800, 10, chSection.c_str());
                txTextOut(800, 30, chSubSection.c_str());
            }
            */
        }

        txSleep(20);
    }

    //�������� ��������
    for(int i = 0; i < nVariants; i++)
        txDeleteDC (variants[i].pic);

    return 0;
}
