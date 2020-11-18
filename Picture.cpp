#include "TXLib.h"
#include "Button.cpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <dirent.h>

using namespace std;

//��������
struct Picture
{
    string address;
    //������ � ���������
    string section;
    string subSection;
    int y;
    int x;
    bool drawObject;
    int width;
    int height;
    HDC pic;
    int yMouse;
    int xMouse;

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

int fillVariants(string address, Picture* object, int n)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (address.c_str())) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            string s = ent->d_name;
            s = address + s;
            if (s.find(".bmp") != -1)
            {
                //cout << s << endl;
                object[n] = {s};
                n++;
            }
        }
        closedir (dir);
    }
    return n;
}

int fillVariants(Picture* object, BUTTON *btn)
{
    setlocale(LC_ALL, "Russian");

    int nVariants = 0;
    nVariants = fillVariants("Pictures/������/������/", object, nVariants);
    nVariants = fillVariants("Pictures/������/�����/", object, nVariants);
    nVariants = fillVariants("Pictures/������/�������/", object, nVariants);
    nVariants = fillVariants("Pictures/������/����������/", object, nVariants);
    nVariants = fillVariants("Pictures/������/�����/", object, nVariants);
    nVariants = fillVariants("Pictures/������/������/", object, nVariants);
    /*object[0] = {"Pictures/������/������/������.bmp"};
    object[1] = {"Pictures/������/������/������2.bmp"};
    object[2] = {"Pictures/������/������/Stul1.bmp"};
    object[3] = {"Pictures/������/������/Stul2.bmp"};
    object[4] = {"Pictures/������/������/Stul3.bmp"};
    object[5] = {"Pictures/������/������/Stul4.bmp"};

    object[6] = {"Pictures/������/�����/����.bmp"};
    object[7] = {"Pictures/������/�����/���� ��������.bmp"};

    object[8] = {"Pictures/������/�������/Bed.bmp"};
    object[9] = {"Pictures/������/�������/Bed2.bmp"};
    object[10] = {"Pictures/������/�������/Bed3.bmp"};

    object[11] = {"Pictures/�������/����������/���������.bmp"};

    object[12] = {"Pictures/���/�����/Cover1.bmp"};
    object[13] = {"Pictures/���/�����/Cover2.bmp"};
    object[14] = {"Pictures/���/�����/Cover3.bmp"};
    object[15] = {"Pictures/���/�����/Cover4.bmp"};

    object[16] = {"Pictures/������/������/Sofa.bmp"};
    object[17] = {"Pictures/������/������/Divan1.bmp"};
    object[18] = {"Pictures/������/������/Divan2.bmp"};
    object[19] = {"Pictures/������/������/Divan3.bmp"};
    object[20] = {"Pictures/������/������/Divan4.bmp"};*/

    //�������, ������ �� ��������
    for(int i = 0; i < nVariants; i++)
    {
        //string d = "Pictures/";
        string str = object[i].address;
        int pos1 = str.find("/", 0);
        int pos2 = str.find("/", pos1 + 1);
        int pos3 = str.find("/", pos2 + 1);
        object[i].section = str.substr(pos1 + 1, pos2 - pos1 - 1);
        //d = d + object[i].section + "/";
        object[i].subSection = str.substr(pos2 + 1, pos3 - pos2 - 1);
        //d = d + object[i].subSection + "/";
        //object[i].address = fillVariants("Pictures/������/������/", object);

        //5 ������
        for (int j = 0; j < 5; j++)
            //5 �����������
            for (int k = 0; k < 5; k++)
                if (btn[j].text == object[i].section &&
                    btn[j].subButtons[k].text == object[i].subSection)
                    {
                        object[i].y = 100 + 150 * btn[j].subButtons[k].N;
                        btn[j].subButtons[k].N++;
                    }

        object[i].x = 750;
        object[i].drawObject = false;
        object[i].pic = txLoadImage (object[i].address.c_str());
        object[i].width  = getWidth (object[i].address.c_str());
        object[i].height = getHeight(object[i].address.c_str());
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
