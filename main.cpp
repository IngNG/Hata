#include "TXLib.h"
#include "strObject.cpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

//Подраздел
struct subBUTTON
{
    const char* text;
};

//Раздел
struct BUTTON
{
    int x;
    int y;
    const char* text;
    subBUTTON subButtons[10];

    void draw()
    {
        txSetColor (TX_BLACK, 4);
        //if(txMouseX() >= x          && txMouseY() >= y &&
        //   txMouseX() <= x + 200    && txMouseY() <= y + 100);
        //    txSetColor (TX_LIGHTBLUE, 4);
        txDrawText(x, y, x + 200, y + 100 ,text);
        txSetColor (TX_BLACK, 4);
    }

};

struct room
{
    int x ;
    int y ;
    int x2;
    int y2;
};
    /*bool click()
    {
        if(txMouseX() >= Х && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1);
    } */

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

void drawBackArrow()
{
    txSetColor (TX_BLACK, 2);
    if(txMouseX() >= 0 && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20)
        txSetColor (TX_LIGHTRED, 2);
    txLine(10, 10, 30, 10);
    txLine(10, 10, 15, 5);
    txLine(10, 10, 15, 15);
    txSetColor (TX_BLACK, 4);
}

int main()
{
    txCreateWindow (1000, 800);

    string PAGE = "Справка";

    bool openSubsect = false;

    //Варианты мебели сверху
    int nObj = 10;
    int nActObj = 0;
    int nActRoom = 0;
    strObject object[100];
    object[0] = {"Pictures/Мебель/стулья/кресло.bmp", "Мебель", "стулья"};
    object[1] = {"Pictures/Мебель/стулья/кресло2.bmp", "Мебель", "стулья"};
    object[2] = {"Pictures/Мебель/стулья/Stul1.bmp","Мебель", "стулья"};
    object[3] = {"Pictures/Мебель/стулья/Stul2.bmp", "Мебель", "стулья"};
    object[4] = {"Pictures/Мебель/стулья/Stul3.bmp", "Мебель", "стулья"};
    object[5] = {"Pictures/Мебель/стулья/Stul4.bmp", "Мебель", "стулья"};
    object[6] = {"Pictures/Мебель/Диваны/Divan1.bmp", "Мебель", "диваны", 100};
    object[7] = {"Pictures/Мебель/столы/Стол.bmp", "Мебель", "столы", 100};
    object[8] = {"Pictures/Мебель/кровати/Bed.bmp", "Мебель", "кровати", 100};
    object[9] = {"Pictures/Техника/телевизоры/Изогнутый.bmp", "Техника", "телевизоры", 100};

    //Прикинь, диваны не рисуются
    int yStul = 100;
    for(int i = 0; i < nObj; i++)
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

    strObject activeObj[1000];
    int active = -10;

    room ActRoom[100];

    //Разделы
    BUTTON buttons[5];
    buttons[0] =   {0, 0, "Мебель",     {{"стулья"      }, {"столы"       }, {"кровати"   }, {"шкафы"     }, {"диваны"}}};
    buttons[1] = {200, 0, "Техника",    {{"стир. машины"}, {"холодильники"}, {"телевизоры"}, {"компьютеры"}, {" "}}};
    buttons[2] = {400, 0, "Пол",        {{"паркет"      }, {"ковры"       }, {""          }, {""          }, {" "}}};
    buttons[3] = {600, 0, "Разное",     {{"ванные"      }, {"туалеты"     }, {"декор"     }, {""          }, {" "}}};
    buttons[4] = {800, 0, "Планировка", {{"двери"       }, {"окна"        }, {"стены"     }, {""          }, {" "}}};
    //Координаты кнопок ваще не проблема посчитать

    int mx = -500;
    int my = -500;

    //Выбранный раздел / Подраздел
    int choosenSection = -1;
    string chSection = "";
    string chSubSection = "";

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_BLACK, 4);
        txSetFillColor (TX_WHITE);
        txClear();

        //На фига мне по умолчанию справку выводить?
        if (PAGE == "Справка")
        {
            txDrawText(0, 200, 150, 300, "Другой режим");
            txTextOut(450, 50, "Это справка.");
            txTextOut(250, 100, "Это редактор хаты в которой ты можещь сделать всё что хочешь.");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseX() <= 100)
            {
                PAGE = "Рудактор";
                txSleep(200);
            }

        }
        else
        {
            txRectangle (0, 0, 1000, 100);

            //Подраздел на выбран
            if(!openSubsect)
            {
                //Рисуем кнопки
                for (int i = 0; i < 5; i++)
                {
                    txSetColor (TX_BLACK, 4);
                    if(txMouseX() >= buttons[i].x          && txMouseY() >= buttons[i].y &&
                       txMouseX() <= buttons[i].x + 200    && txMouseY() <= buttons[i].y + 100)
                        txSetColor (TX_LIGHTBLUE, 4);
                    buttons[i].draw();
                    txSetColor (TX_BLACK, 4);
                }

                if (txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
                {
                    //Какой конкретно раздел?
                    for (int i = 0; i < 5; i++)
                    {
                        if (txMouseX() >= buttons[i].x && txMouseX() <= buttons[i].x + 200)
                        {
                            choosenSection = i;
                            chSection = buttons[i].text;
                        }
                    }

                    mx = buttons[choosenSection].x ;
                    my = 100 ;
                }
                txRectangle (mx, my, mx + 200, my + 140);

                //Ежели что и подраздел выбираем
                for (int i = 0; i < 4; i++)
                {
                    //Цвет подраздела
                    if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20)
                        txSetColor (TX_LIGHTBLUE, 4);
                    if(choosenSection >= 0)
                        txDrawText (mx,         my + 5 + i * 20,
                                    mx + 200,   my + 25 + i * 20 , buttons[choosenSection].subButtons[i].text);

                    //Выбор подраздела
                    if (txMouseX() >= mx &&
                        txMouseX() <= mx + 150 &&
                        txMouseY() >= my + 5 + i * 20 &&
                        txMouseY() <= my + 25 + i * 20 &&
                        txMouseButtons() == 1)
                    {
                        openSubsect = true;
                        chSection = buttons[choosenSection].text;
                        chSubSection = buttons[choosenSection].subButtons[i].text;
                    }
                    txSetColor (TX_BLACK, 4);
                }
            }

            else
                drawBackArrow();



            txDrawText(0, 200, 150, 300, "Другой режим");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseY() >= 200 &&
                txMouseX() <= 100)
            {
                PAGE = "Справка";
                txSleep(200);
            }

            //Отмена выбора подраздела
            if (txMouseX() >= 0 && txMouseX() <= 35 &&
                txMouseY() >= 0 && txMouseY() <= 20 &&
                txMouseButtons() == 1 && openSubsect)
            {
                openSubsect = false;
                txSleep(200);
                chSection = "";
                chSubSection = "";
            }

            //На фиг нужны mx, my? Почему не рисовать тупо прямоугольник под кнопкой? Как в КодБлокс том же

            //Выбор категории
            for(int i = 0; i < nObj; i++)
            {
                object[i].drawObject = false;

                //Рисуем картинки если выбрана такая-то пара "раздел-подраздел"
                if (openSubsect && chSubSection == object[i].subSection && chSection == object[i].section)
                {
                    object[i].drawObject = true;
                }
            }

            //Рисование стен
            if (chSection == "Планировка" && chSubSection == "стены")
            {
                if (txMouseButtons() == 1)
                {
                    nActRoom++;
                    ActRoom[nActRoom] = {txMouseX(), txMouseY(), txMouseX(), txMouseY()};
                    txRectangle(ActRoom[nActRoom].x, ActRoom[nActRoom].y, ActRoom[nActRoom].x2, ActRoom[nActRoom].y2);
                    txSleep(10);
                    while(txMouseButtons() == 1)
                    {
                        ActRoom[nActRoom].x2 = txMouseX();
                        ActRoom[nActRoom].y2 = txMouseY();
                        for(int i = 0; i < nActRoom + 1; i++)
                        {
                            txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);
                            drawPics(activeObj, nActObj);
                        }
                        txSleep(50);
                    }
                }
            }

            for(int i = 0; i < nActRoom + 1; i++)
                txRectangle(ActRoom[i].x, ActRoom[i].y, ActRoom[i].x2, ActRoom[i].y2);

            //Варианты мебели сверху
            for(int i = 0; i < nObj; i++)
            {
                if (object[i].drawObject)
                {
                    Win32::TransparentBlt (txDC(),object[i].x,object[i].y,150,150,object[i].pic,0,0,object[i].width,object[i].height,TX_BLACK);
                }

                //Клик на вариант (раздел)
                if (object[i].drawObject &&
                    txMouseX() >= object[i].x &&
                    txMouseX() <= object[i].x + 150 &&
                    txMouseY() >= object[i].y &&
                    txMouseY() <= object[i].y + 150 && txMouseButtons() == 1)
                {
                    activeObj[nActObj] = {object[i].address, object[i].section, object[i].subSection, 300, 300, true, object[i].width, object[i].height, object[i].pic};
                    nActObj++;
                    while(txMouseButtons() == 1)
                    {}
                }
            }

            drawPics(activeObj, nActObj);

            //Выбор и удаление активной картинки
            for(int i = 0; i < nActObj; i++)
            {
                if (activeObj[i].drawObject &&
                    txMouseX() >= activeObj[i].x &&
                    txMouseX() <= activeObj[i].x + 150 &&
                    txMouseY() >= activeObj[i].y &&
                    txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                    active < 0)
                {
                    active = i;
                }

                if (activeObj[i].drawObject &&
                    activeObj[i].y + 75 <= 100)
                    activeObj[i].drawObject = false;
            }

            //Движение активной картинки
            if (active >= 0)
            {
                activeObj[active].x = txMouseX() - 75;
                activeObj[active].y = txMouseY() - 75;
            }

            if (txMouseButtons()!= 1)
                active = -10;


            //По пробелу скрываем всю мебель
            for(int i = 0; i < nObj; i++)
                if (GetAsyncKeyState(VK_SPACE))
                {
                    object[i].drawObject=false;
                }



            //В качестве отладки выводим номер открытого раздела
            //if (chSubSection != "")
            {
                txTextOut(800, 10, chSection.c_str());
                txTextOut(800, 30, chSubSection.c_str());
            }
        }

        txSleep(20) ;
    }

    //Удаление картинок
    for(int i = 0; i < nObj; i++)
        txDeleteDC (object[i].pic);

    return 0;
}
