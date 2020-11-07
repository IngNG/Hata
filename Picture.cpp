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
    setlocale(LC_ALL, "Russian");

    int nVariants = 17;
    object[0] = {"Pictures/������/������/������.bmp"};
    object[1] = {"Pictures/������/������/������2.bmp"};
    object[2] = {"Pictures/������/������/Stul1.bmp"};
    object[3] = {"Pictures/������/������/Stul2.bmp"};
    object[4] = {"Pictures/������/������/Stul3.bmp"};
    object[5] = {"Pictures/������/������/Stul4.bmp"};
    object[6] = {"Pictures/���/�����/Sofa.bmp"};

    object[7] = {"Pictures/������/�����/����.bmp"};
    object[8] = {"Pictures/������/�������/Bed.bmp"};
    object[9] = {"Pictures/������/�������/Bed3.bmp"};
    object[10] = {"Pictures/�������/����������/���������.bmp"};
    object[11] = {"Pictures/������/������/���������.bmp"};
    object[16] = {"Pictures/������/������/Divan1.bmp"};
    object[12] = {"Pictures/���/�����/Cover1.bmp"};
    object[13] = {"Pictures/���/�����/Cover2.bmp"};
    object[14] = {"Pictures/���/�����/Cover3.bmp"};
    object[15] = {"Pictures/���/�����/Cover4.bmp"};
    object[16] = {"Pictures/���/�����/Sofa.bmp"};

    //�������, ������ �� ��������
    int cord[25];
    int c = 0;
    for(int i = 0; i < 26; i++)
        cord[i] = 100;
    for(int i = 0; i < nVariants; i++)
    {
        string str = object[i].address;
        int pos1 = str.find("/", 0);
        int pos2 = str.find("/", pos1 + 1);
        int pos3 = str.find("/", pos2 + 1);
        object[i].section = str.substr(pos1 + 1, pos2 - pos1 - 1);
        object[i].subSection = str.substr(pos2 + 1, pos3 - pos2 - 1);

        if (object[i].subSection == object[i - 1].subSection && !(i == 0))
        {
            object[i].y = cord[c];
            cord[c + 1] = cord[c] + 200;
        }
        else
        {
            c++;
            object[i].y = cord[c];
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
