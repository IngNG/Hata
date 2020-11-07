#include "TXLib.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

//��������
struct Picture
{
    const char* address;
    //������ � ���������
    string section;
    string subSection;
    int y;
    int x;
    bool drawObject;
    int width;
    int height;
    HDC pic;

    void drawIcon()
    {
        Win32::TransparentBlt (txDC(), x, y, 120, 120, pic, 0, 0, width, height,TX_BLACK);
    }
};

void fillVariants();
void drawPics(Picture* activeObj, int nActObj);
int getWidth(const char* address);
int getHeight(const char* address);

void drawPics(Picture* activeObj, int nActObj)
{
    for(int i = 0; i < nActObj; i++)
        if (activeObj[i].drawObject)
        {
            activeObj[i].drawIcon();
            //Win32::TransparentBlt (txDC(),activeObj[i].x,activeObj[i].y,150,150,activeObj[i].pic,0,0,activeObj[i].width,activeObj[i].height,TX_BLACK);
        }
}

int fillVariants(Picture* object)
{
    int nVariants = 17;
    object[0] = {"Pictures/������/������/������.bmp", "������", "������"};
    object[1] = {"Pictures/������/������/������2.bmp", "������", "������"};
    object[2] = {"Pictures/������/������/Stul1.bmp","������", "������"};
    object[3] = {"Pictures/������/������/Stul2.bmp", "������", "������"};
    object[4] = {"Pictures/������/������/Stul3.bmp", "������", "������"};
    object[5] = {"Pictures/������/������/Stul4.bmp", "������", "������"};

    object[6] = {"Pictures/������/������/Divan1.bmp", "������", "������", 100};
    object[7] = {"Pictures/������/�����/����.bmp", "������", "�����", 100};
    object[8] = {"Pictures/������/�������/Bed.bmp", "������", "�������", 100};
    object[9] = {"Pictures/������/�������/Bed3.bmp", "������", "�������", 300};
    object[10] = {"Pictures/�������/����������/���������.bmp", "�������", "����������", 100};
    object[11] = {"Pictures/������/������/���������.bmp", "�������", "����������", 100};
    object[12] = {"Pictures/���/�����/Cover1.bmp", "���", "�����", 100};
    object[13] = {"Pictures/���/�����/Cover2.bmp", "���", "�����", 300};
    object[14] = {"Pictures/���/�����/Cover3.bmp", "���", "�����", 500};
    object[15] = {"Pictures/���/�����/Cover4.bmp", "���", "�����", 700};
    object[16] = {"Pictures/���/�����/Sofa.bmp", "������", "������", 100};

    //�������, ������ �� ��������
    int yStul = 100;
    for(int i = 0; i < nVariants; i++)
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

    return nVariants;
}

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
