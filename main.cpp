#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct room
{
    int x0;
    int y0;
    int x1;
    int y1;
};


const int WindowWidth = 1000;
const int WindowHeight = 800;




int main()
{
    txCreateWindow (WindowWidth, WindowHeight);
    txTextCursor(0);
    string PAGE = "Редактор";


    //Разделы
    int buttons_count = 5;
    BUTTON buttons[buttons_count];
    buttons[0] = {"Мебель",     {{"стулья"      }, {"столы"       }, {"кровати"   }, {"диваны"    }, {"шкафы"}}};
    buttons[1] = {"Техника",    {{"стир. машины"}, {"холодильники"}, {"телевизоры"}, {"компьютеры"}, {" "}}};
    buttons[2] = {"Пол",        {{"паркет"      }, {"ковры"       }, {""          }, {""          }, {" "}}};
    buttons[3] = {"Разное",     {{"ванные"      }, {"туалеты"     }, {"декор"     }, {""          }, {" "}}};
    buttons[4] = {"Планировка", {{"двери"       }, {"окна"        }, {"стены"     }, {""          }, {" "}}};
    //Координаты кнопок ваще не проблема посчитать
    for(int i = 0; i < buttons_count; i++)
    {
        buttons[i].x = i * 200;
        buttons[i].y = 0;
    }

    int mx = -500;

    //Варианты мебели сверху
    Picture variants[100];
    int nVariants = fillVariants(variants, buttons);

    //Картинки в центре
    int nPictures = 0;
    Picture activeObj[1000];
    int activePic = -10;

    //Стены, комнаты
    int nRooms = 0;
    room ActRoom[100];
    int activeRoom = -10;


    //Выбранный раздел / Подраздел
    int choosenSection = -1;
    string chSection = "";
    string chSubSection = "";



    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(RGB(0,0,0), 4);
        txSetFillColor (RGB(255,255,255));
        txClear();

        //На фига мне по умолчанию справку выводить?
        if (PAGE == "Справка")
        {
            txSetColor(RGB(0,0,0), 4);
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&  txMouseY() >= 700 &&
                txMouseX() <= 150 && txMouseY() <= 800)
                txSetColor (RGB(0,0,127), 4);

            txDrawText(0, 700, 150, 800, "Закрыть справку");
            txSetColor(RGB(0,0,0), 4);
            txTextOut(450, 50, "Это справка.");
            txTextOut(250, 100, "Это простой редактор квартиры который умеет играться с картинками.");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&  txMouseY() >= 700 &&
                txMouseX() <= 150 && txMouseY() <= 800)
            {
                PAGE = "Редактор";
                txSleep(200);
            }
        }
        else
        {
            for(int i = 0; i < nRooms + 1; i++)
                txRectangle(ActRoom[i].x0, ActRoom[i].y0, ActRoom[i].x1, ActRoom[i].y1);
            drawPics(activeObj, nPictures);

            txRectangle (0, 0, 1000, 100);

            //Если Подраздел на выбран

            //Рисуем кнопки
            for (int i = 0; i < 5; i++)
            {
                buttons[i].draw();
                if(txMouseX() >= buttons[i].x          && txMouseY() >= buttons[i].y &&
                   txMouseX() <= buttons[i].x + 200    && txMouseY() <= buttons[i].y + 100)
                    txSetColor (TX_LIGHTBLUE, 4);
                txDrawText(buttons[i].x, buttons[i].y, buttons[i].x + 200, buttons[i].y + 100 , buttons[i].text);
                txSetColor (TX_BLACK, 4);
            }

            //Какой конкретно раздел?
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
                txRectangle (mx, my, mx + 200, my + 140);

            //Выбираем подраздел
            for (int i = 0; i < 5; i++)
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
                    txMouseButtons() == 1 && activePic <= 0)
                {
                    //openSubsect = true;
                    chSection = buttons[choosenSection].text;
                    chSubSection = buttons[choosenSection].subButtons[i].text;
                }
                txSetColor (TX_BLACK, 4);
            }

            txDrawText(0, 700, 150, 800, "Открыть справку");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 0 &&
                txMouseY() >= 700 &&
                txMouseX() <= 150)
            {
                PAGE = "Справка";
                txSleep(200);
            }

            //Отмена выбора подраздела
            if (txMouseY() >= 300 && txMouseButtons() == 1 && chSubSection != "стены")
            {
                choosenSection = -1;
            }

            //Выбор категории
            for(int i = 0; i < nVariants; i++)
            {
                variants[i].drawObject = 0;

                //Рисуем картинки если выбрана такая-то пара "раздел-подраздел"
                if (chSubSection == variants[i].subSection && chSection == variants[i].section)
                {
                    variants[i].drawObject = 1;
                }
            }

            //Рисование стен
            if (chSection == "Планировка" && chSubSection == "стены")
            {
                if (txMouseButtons() == 1)
                {
                    nRooms++;
                    ActRoom[nRooms] = {txMouseX(), txMouseY(), txMouseX(), txMouseY()};
                    txRectangle(ActRoom[nRooms].x0, ActRoom[nRooms].y0, ActRoom[nRooms].x1, ActRoom[nRooms].y1);
                    txSleep(10);
                    while(txMouseButtons() == 1)
                    {
                        ActRoom[nRooms].x1 = txMouseX();
                        ActRoom[nRooms].y1 = txMouseY();
                        for(int i = 0; i < nRooms + 1; i++)
                        {
                            txRectangle(ActRoom[i].x0, ActRoom[i].y0, ActRoom[i].x1, ActRoom[i].y1);
                            drawPics(activeObj, nPictures);
                        }
                        txSleep(50);
                    }
                }
            }

            //Варианты мебели сверху
            for(int i = 0; i < nVariants; i++)
            {
                if (variants[i].drawObject)
                {
                    Win32::TransparentBlt (txDC(),variants[i].x,variants[i].y,150,150,variants[i].pic,0,0,variants[i].width,variants[i].height,TX_BLACK);
                }

                //Клик на вариант (раздел)
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

            //Выбор и удаление активной картинки
            for(int i = 0; i < nPictures; i++)
            {
                if (activeObj[i].drawObject &&
                    txMouseX() >= activeObj[i].x &&
                    txMouseX() <= activeObj[i].x + 150 &&
                    txMouseY() >= activeObj[i].y &&
                    txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                    activePic < 0)
                {
                    activePic = i;
                }

                if (activeObj[i].drawObject &&
                    activeObj[i].y + 75 <= 100)
                    activeObj[i].drawObject = false;
            }

            for(int i = 0; i < nRooms + 1; i++)
            {
                if (txMouseX() >= ActRoom[i].x0 &&
                    txMouseX() <= ActRoom[i].x1 &&
                    txMouseY() >= ActRoom[i].y0 &&
                    txMouseY() <= ActRoom[i].y1 && txMouseButtons() == 2 &&
                    activeRoom < 0)
                {
                    activeRoom = i;
                }

                if (ActRoom[i].y0 <= 100)
                    {ActRoom[i].x1 = ActRoom[i].x0; ActRoom[i].y1 = ActRoom[i].x0;}
            }
            //Движение активной картинки
            if (activePic >= 0)
            {
                activeObj[activePic].x = txMouseX() - 75;
                activeObj[activePic].y = txMouseY() - 75;
            }

            if (activeRoom >= 0)
            {
                int y2 = ActRoom[activeRoom].y1 - ActRoom[activeRoom].y0;
                int x2 = ActRoom[activeRoom].x1 - ActRoom[activeRoom].x0;
                ActRoom[activeRoom].x0 = txMouseX();
                ActRoom[activeRoom].y0 = txMouseY();
                ActRoom[activeRoom].x1 = txMouseX() + x2;
                ActRoom[activeRoom].y1 = txMouseY() + y2;
            }

            if (txMouseButtons()!= 1)
                activePic = -10;

            if (txMouseButtons()!= 2)
                activeRoom = -10;

            if(GetAsyncKeyState(VK_SPACE))
            {
                for(int i = 0; i < nVariants; i++)
                {
                    variants[i].drawObject=0;
                }
            }

        }

        txSleep(20) ;
    }

    //Удаление картинок
    for(int i = 0; i < nVariants; i++)
        txDeleteDC (variants[i].pic);

    return 0;
}
