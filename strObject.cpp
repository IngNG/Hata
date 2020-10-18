#include "TXLib.h"


//Картинка
struct strObject
{
    int x;
    int y;
    HDC pic;
    //Раздел и подраздел
    string section;
    string subSection;
    bool drawObject;
    int width;
    int height;

    void drawIcon()
    {
        Win32::TransparentBlt (txDC(), x, y, 120, 120, pic, 0, 0, width, height,TX_BLACK);
    }
};

void drawPics(strObject* activeObj, int nActObj)
{
    for(int i = 0; i < nActObj; i++)
        if (activeObj[i].drawObject)
        {
            activeObj[i].drawIcon();
            //Win32::TransparentBlt (txDC(),activeObj[i].x,activeObj[i].y,150,150,activeObj[i].pic,0,0,activeObj[i].width,activeObj[i].height,TX_BLACK);
        }
}
