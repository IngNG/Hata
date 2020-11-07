#include "TXLib.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

//Картинка
struct Picture
{
    const char* address;
    //Раздел и подраздел
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
    object[0] = {"Pictures/Мебель/стулья/кресло.bmp"};
    object[1] = {"Pictures/Мебель/стулья/кресло2.bmp"};
    object[2] = {"Pictures/Мебель/стулья/Stul1.bmp"};
    object[3] = {"Pictures/Мебель/стулья/Stul2.bmp"};
    object[4] = {"Pictures/Мебель/стулья/Stul3.bmp"};
    object[5] = {"Pictures/Мебель/стулья/Stul4.bmp"};
    object[6] = {"Pictures/пол/ковры/Sofa.bmp"};

    object[7] = {"Pictures/Мебель/столы/Стол.bmp"};
    object[8] = {"Pictures/Мебель/кровати/Bed.bmp"};
    object[9] = {"Pictures/Мебель/кровати/Bed3.bmp"};
    object[10] = {"Pictures/техника/телевизоры/Изогнутый.bmp"};
    object[11] = {"Pictures/Мебель/диваны/Изогнутый.bmp"};
    object[16] = {"Pictures/Мебель/диваны/Divan1.bmp"};
    object[12] = {"Pictures/пол/ковры/Cover1.bmp"};
    object[13] = {"Pictures/пол/ковры/Cover2.bmp"};
    object[14] = {"Pictures/пол/ковры/Cover3.bmp"};
    object[15] = {"Pictures/пол/ковры/Cover4.bmp"};
    object[16] = {"Pictures/пол/ковры/Sofa.bmp"};

    //Прикинь, диваны не рисуются
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
