#include "TXLib.h"

//#include "Struct"

//Подраздел
struct subBUTTON
{
    bool subBtnOpened;
    const char* text;
};

//Раздел
struct BUTTON
{
    int x;
    int y;
    bool btnOpened;
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

    /*bool click()
    {
        if(txMouseX() >= Х && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1);
    } */

//Картинка
struct strObject
{
    int x;
    int y;
    HDC pic;
    bool drawObject;
    int width;
    int height;
};

const int MENU_OPEN = 1;

//Меню
void fon(int mx, int my)
{
    txClear();
    txSetColor (TX_BLACK, 4);
    //Вместо 1000 везде лучше SCREEN_WIDTH какой-нибудь или txGetExtentX()
    txSetColor(TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 1000, 100);

    //Сделать функцией, зависящей от раздела
    /*drawButton(0, 0, "Мебель");
    drawButton(200, 0, "техника");
    drawButton(400, 0, "пол");
    drawButton(600, 0, "стены");
    drawButton(800, 0, "комната ");    */

    txRectangle (mx, my, mx + 150, my + 140);
}

void openSubsection()
{
    txClear();
    txSetColor (TX_BLACK, 4);
    txSetFillColor (TX_WHITE);
    txRectangle (0, 0, 1000, 100);
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

    bool openSubsect = false;

    //Варианты мебели сверху
    int numObj = 3;
    strObject object[100];
    object[0] = {50, 0, txLoadImage ("Pictures/кресло.bmp"), false, 686, 700};
    object[1] = {150, 0, txLoadImage ("Pictures/Стол.bmp"), false, 910, 746};
    object[2] = {250, 0, txLoadImage ("Pictures/кресло2.bmp"), false, 822, 836};

    //Разделы
    BUTTON buttons[5];
    buttons[0] =   {0, 0, false, "Мебель",     {{false, "стулья"      }, {false, "столы"       }, {false, "кровати"   }, {false, "шкафы"     }, {false, " "}}};
    buttons[1] = {200, 0, false, "Техника",    {{false, "стир. машины"}, {false, "холодильники"}, {false, "телевизоры"}, {false, "компьютеры"}, {false, " "}}};
    buttons[2] = {400, 0, false, "Пол",        {{false, "паркет"      }, {false, "ковры"       }, {false, ""          }, {false, ""          }, {false, " "}}};
    buttons[3] = {600, 0, false, "Разное",     {{false, "ванные"      }, {false, "туалеты"     }, {false, "декор"     }, {false, ""          }, {false, " "}}};
    buttons[4] = {800, 0, false, "Планировка", {{false, "двери"       }, {false, "окна"        }, {false, "стены"     }, {false, ""          }, {false, " "}}};

    int window = 0;
    int mx = -500;
    int my = -500;

    //Выбранный раздел / Подраздел
    int choosenSection = -1;
    int choosenSubSection = -1;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        if(!openSubsect)
        {
            fon(mx, my);
            for (int i = 0; i < 5; i++)
            {
                if(txMouseX() >= buttons[i].x          && txMouseY() >= buttons[i].y &&
                   txMouseX() <= buttons[i].x + 200    && txMouseY() <= buttons[i].y + 100)
                    txSetColor (TX_LIGHTBLUE, 4);
                buttons[i].draw();
                txSetColor (TX_BLACK, 4);
            }


            /*if (click(subButton[2]))
            {
                category = subbUtton[2].category;//Столы кухонные
            } */

            txRectangle (mx, my, mx + 150, my + 140);

            //for (int i = 0; i < 4; i++)
            //    buttons[0].subButtons[i].subBtnOpened = false;

            for (int i = 0; i < 4; i++)
            {
                //Цвет подраздела
                if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20)
                    txSetColor (TX_LIGHTBLUE, 4);
                txDrawText (mx,         my + 5 + i * 20,
                            mx + 150,   my + 25 + i * 20 , buttons[0].subButtons[i].text);

                //Выбор подраздела
                if (txMouseX() >= mx &&
                    txMouseX() <= mx + 150 &&
                    txMouseY() >= my + 5 + i * 20 &&
                    txMouseY() <= my + 25 + i * 20 &&
                    txMouseButtons() == 1)
                {
                    openSubsect = true;
                    buttons[choosenSection].subButtons[i].subBtnOpened = true;

                    //А номер выбранной кнопки где-то хранится?
                }
                txSetColor (TX_BLACK, 4);
            }
            txSleep(20);
        }

        else
            openSubsection();

        //Отмена выбора подраздела
        if (txMouseX() >= 0 && txMouseX() <= 35 &&
            txMouseY() >= 0 && txMouseY() <= 20 &&
            txMouseButtons() == 1 && openSubsect)
        {
            openSubsect = false; /*mx = -500;*/ txSleep(200);

            for (int i = 0; i < 4; i++)
                buttons[choosenSection].subButtons[i].subBtnOpened = false;
        }

        //На фиг нужны mx, my? Почему не рисовать тупо прямоугольник под кнопкой? Как в КодБлокс том же

        //Клик на раздел
        if (txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
        {
            //Второй раз не открываем (можно красивее написать)
            for (int i = 0; i < 4; i++)
                if (buttons[i].btnOpened && txMouseX() >= buttons[i].x && txMouseX() <= buttons[i].x + 200){}
            //else if (buttons[1].btnOpened && txMouseX() >= buttons[1].x && txMouseX() <= buttons[1].x + 200){}
            else
            {
                for (int i = 0; i < 4; i++)
                    buttons[i].btnOpened = false;
                //buttons[1].btnOpened = false;
                my = txMouseY() ;
                mx = txMouseX() ;
                if(mx + 150 >= 1000)
                   mx = 850;
            }

            //Какой конкретно раздел?
            for (int i = 0; i < 5; i++)
            {
                if (txMouseX() >= buttons[i].x && txMouseX() <= buttons[i].x + 200)
                {
                    buttons[i].btnOpened = true;
                    choosenSection = i;
                }
                else
                    buttons[i].btnOpened = false;
            }

        }
        //На фига тут фор по и?
        /*for(int i = 0; i < 1000; i = i + 200)
        {
            if(txMouseX() >= 0 + i && txMouseX() <= 200 + i && txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1)
            {
                my = txMouseY() ;
                mx = txMouseX() ;
                if(mx + 150 >= 1000)
                   mx = 850;
            }
        } */


        //Выбор категории
        for(int i = 0; i < numObj; i++)
            object[i].drawObject = false;

        //Рисуем картинки если выбрана такая-то пара "раздел-подраздел"
        for(int i = 0; i < 4; i++)
            if (openSubsect && buttons[i].subButtons[i].subBtnOpened && buttons[i].btnOpened)
                object[i].drawObject = true;
        //if (openSubsect && buttons[1].subButtons[1].subBtnOpened && buttons[1].btnOpened)
        //{
        //    object[1].drawObject = true;
        //}


        //Варианты мебели сверху
        for(int i = 0; i < numObj; i++)
        {
            if (object[i].drawObject)
            {
                Win32::TransparentBlt (txDC(),object[i].x,object[i].y,150,150,object[i].pic,0,0,object[i].width,object[i].height,TX_BLACK);
            }
            if (object[i].drawObject && txMouseX() >= object[i].x && txMouseX() <= object[i].width && txMouseY() >= object[i].y && txMouseY() <= object[i].y && txMouseButtons() == 1)
            {
                Win32::TransparentBlt (txDC(),object[i].x - 300,object[i].y - 300,150,150,object[i].pic,0,0,object[i].width,object[i].height,TX_BLACK);
            }
        }


        //Что это?
        if (window == MENU_OPEN)
            Win32::TransparentBlt (txDC(), mx, 0, 50, 50, object[0].pic, 0, 0, 686, 700, TX_BLACK); // 10x zoom

        //По пробелу скрываем всю мебель
        for(int i = 0; i < numObj; i++)
            if (GetAsyncKeyState(VK_SPACE))
            {
                object[i].drawObject=false;
            }


        if(!(txMouseX() >= mx, txMouseY() >= my, txMouseX() <= mx + 200,txMouseY() <= my + 140) && txMouseButtons() == 1)
        {
            mx = -500;
            my = -500;
        }

        //В качестве отладки выводим номер открытого раздела
        {
        for(int i = 0; i < 5; i++)
        {
            if (buttons[i].btnOpened)  txTextOut(800, 10, buttons[i].text);
                for(int j = 0; j < 4; j++)
                    if (buttons[i].subButtons[j].subBtnOpened)  txTextOut(800, 30, buttons[i].subButtons[j].text);
        }


        //if (buttons[1].btnOpened)  txTextOut(100, 250, "1");
        //if (buttons[2].btnOpened)  txTextOut(100, 300, "2");
        //if (buttons[3].btnOpened)  txTextOut(100, 350, "3");
        //if (buttons[4].btnOpened)  txTextOut(100, 400, "4");

        //if (buttons[0].subButtons[0].subBtnOpened)  txTextOut(200, 200, "0");
        //if (buttons[0].subButtons[1].subBtnOpened)  txTextOut(200, 250, "1");
        }
        txSleep(20) ;
    }

    //Удаление картинок
    for(int i = 0; i < numObj; i++)
        txDeleteDC (object[i].pic);

    return 0;
}
