#include "TXLib.h"


//Картинка
struct strObject
{
    int x;
    int y;
    HDC pic;
    bool drawObject;
    int width;
    int height;
    //Раздел и подраздел
};

void drawPics(strObject* activeObj, int nActObj)
{
    for(int i = 0; i < nActObj; i++)
        if (activeObj[i].drawObject)
        {
            Win32::TransparentBlt (txDC(),activeObj[i].x,activeObj[i].y,150,150,activeObj[i].pic,0,0,activeObj[i].width,activeObj[i].height,TX_BLACK);
        }

}
