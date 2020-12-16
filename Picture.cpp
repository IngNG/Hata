///\file Picture.cpp

#include "TXLib.h"
#include "Button.cpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <dirent.h>

using namespace std;

///Структура картинка
struct Picture
{
    string address;
    ///Раздел
    string section;
    ///подраздел
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
        Win32::TransparentBlt (txDC(), x, y, width, height, pic, 0, 0, width, height,TX_WHITE);
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
    nVariants = fillVariants("Pictures/Мебель/стулья/", object, nVariants);
    nVariants = fillVariants("Pictures/Мебель/столы/", object, nVariants);
    nVariants = fillVariants("Pictures/Мебель/кровати/", object, nVariants);
    nVariants = fillVariants("Pictures/Техника/телевизоры/", object, nVariants);
    nVariants = fillVariants("Pictures/Техника/для кухни/", object, nVariants);
    nVariants = fillVariants("Pictures/Пол/ковры/", object, nVariants);
    nVariants = fillVariants("Pictures/Пол/паркет/", object, nVariants);
    nVariants = fillVariants("Pictures/Мебель/диваны/", object, nVariants);
    nVariants = fillVariants("Pictures/Планировка/двери/", object, nVariants);
    nVariants = fillVariants("Pictures/Разное/декор/", object, nVariants);
    nVariants = fillVariants("Pictures/Разное/ванные/", object, nVariants);


    for(int i = 0; i < nVariants; i++)
    {
        //string d = "Pictures/";
        string str = object[i].address;
        int pos1 = str.find("/", 0);
        int pos2 = str.find("/", pos1 + 1);
        int pos3 = str.find("/", pos2 + 1);
        object[i].section = str.substr(pos1 + 1, pos2 - pos1 - 1);
        object[i].subSection = str.substr(pos2 + 1, pos3 - pos2 - 1);

        //5 кнопок
        for (int j = 0; j < 5; j++)
            //5 подразделов
            for (int k = 0; k < 5; k++)
                if (btn[j].text == object[i].section &&
                    btn[j].subButtons[k].text == object[i].subSection)
                    {
                        object[i].y = 10 + 150 * btn[j].subButtons[k].N;
                        btn[j].subButtons[k].N++;
                    }

        object[i].x = 1025;
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
