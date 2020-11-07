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
    int nVariants = 17;
    object[0] = {"Pictures/Мебель/стулья/кресло.bmp", "Мебель", "стулья"};
    object[1] = {"Pictures/Мебель/стулья/кресло2.bmp", "Мебель", "стулья"};
    object[2] = {"Pictures/Мебель/стулья/Stul1.bmp","Мебель", "стулья"};
    object[3] = {"Pictures/Мебель/стулья/Stul2.bmp", "Мебель", "стулья"};
    object[4] = {"Pictures/Мебель/стулья/Stul3.bmp", "Мебель", "стулья"};
    object[5] = {"Pictures/Мебель/стулья/Stul4.bmp", "Мебель", "стулья"};

    object[6] = {"Pictures/Мебель/Диваны/Divan1.bmp", "Мебель", "диваны", 100};
    object[7] = {"Pictures/Мебель/столы/Стол.bmp", "Мебель", "столы", 100};
    object[8] = {"Pictures/Мебель/кровати/Bed.bmp", "Мебель", "кровати", 100};
    object[9] = {"Pictures/Мебель/кровати/Bed3.bmp", "Мебель", "кровати", 300};
    object[10] = {"Pictures/Техника/телевизоры/Изогнутый.bmp", "Техника", "телевизоры", 100};
    object[11] = {"Pictures/мебель/диваны/Изогнутый.bmp", "Техника", "телевизоры", 100};
    object[12] = {"Pictures/пол/ковры/Cover1.bmp", "Пол", "ковры", 100};
    object[13] = {"Pictures/пол/ковры/Cover2.bmp", "Пол", "ковры", 300};
    object[14] = {"Pictures/пол/ковры/Cover3.bmp", "Пол", "ковры", 500};
    object[15] = {"Pictures/пол/ковры/Cover4.bmp", "Пол", "ковры", 700};
    object[16] = {"Pictures/пол/ковры/Sofa.bmp", "Мебель", "стулья", 100};

    //Прикинь, диваны не рисуются
    int yStul = 100;
    for(int i = 0; i < nVariants; i++)
    {
        if (object[i].subSection == "стулья")
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
