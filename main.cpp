#include "TXLib.h"

#include "strObject.cpp"

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

struct room
{
    int x = 0;
    int y = 0;
    int x2 = 0;
    int y2 = 0;
};
    /*bool click()
    {
        if(txMouseX() >= Х && txMouseX() <= 35 && txMouseY() >= 0 && txMouseY() <= 20 && txMouseButtons() == 1);
    } */


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
    int nObj = 6;
    int nActObj = 0;
    strObject object[100];
    object[0] = {750, 100, txLoadImage ("Pictures/Стул/кресло.bmp"), "Мебель", "стулья", false, 324, 306};
    object[1] = {750, 200, txLoadImage ("Pictures/Стол.bmp"), "Мебель", "столы", false, 910, 746};
    object[2] = {750, 300, txLoadImage ("Pictures/Стул/кресло2.bmp"), "Мебель", "стулья", false, 382, 400};
    object[3] = {750, 400, txLoadImage ("Pictures/Bed.bmp"), "Мебель", "кровати", false, 310, 415};
    object[4] = {750, 500, txLoadImage ("Pictures/couchplanesofa.bmp"), "Мебель", "стулья", false, 750, 563};
    object[5] = {750, 600, txLoadImage ("Pictures/Sofa.bmp"), "Мебель", "стулья", false, 768, 332};
    object[6] = {750, 700, txLoadImage ("Pictures/izognytUE.bmp"), "Техника", "телевизоры", false, 150, 29};

    strObject activeObj[1000];
    int active = -10;

    room AcrtRoom[100];

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
    string chSection = "";
    string chSubSection = "";

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

            txRectangle (mx, my, mx + 200, my + 140);

            //for (int i = 0; i < 4; i++)
            //    buttons[0].subButtons[i].subBtnOpened = false;

            for (int i = 0; i < 4; i++)
            {
                //Цвет подраздела
                if(txMouseX() >= mx && txMouseX() <= mx + 150 && txMouseY() >= my + 5 + i * 20 && txMouseY() <= my + 25 + i * 20)
                    txSetColor (TX_LIGHTBLUE, 4);
                if(!(choosenSection == -1))
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
                    buttons[choosenSection].subButtons[i].subBtnOpened = true;
                    chSubSection = buttons[choosenSection].subButtons[i].text;

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
        if (txMouseY() >= 0 && txMouseY() <= 100 && txMouseButtons() == 1 && !openSubsect)
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
                mx = buttons[choosenSection].x ;
                my = 100 ;
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
                    chSection = buttons[i].text;
                }
                else
                    buttons[i].btnOpened = false;
            }

        }

        //Выбор категории
        for(int i = 0; i < nObj; i++)
            object[i].drawObject = false;

        //Рисуем картинки если выбрана такая-то пара "раздел-подраздел"   С фига ли такой цикл, Никитос?!
        /*for(int i = 0; i < 4; i++)
            if (openSubsect && buttons[i].subButtons[i].subBtnOpened && buttons[i].btnOpened)
                object[i].drawObject = true;   */
        for(int i = 0; i < nObj; i++)
            if (openSubsect && chSubSection == object[i].subSection && chSection == object[i].section)
            {
                object[i].drawObject = true;
            }

        /*
        if (openSubsect && chSubSection == object[1].subSection && chSection == object[1].section)
        {
            object[1].drawObject = true;
        }
        if (openSubsect && chSubSection == object[2].subSection && buttons[2].btnOpened)
        {
            object[2].drawObject = true;
        }
        if (openSubsect && chSubSection == object[2].subSection && buttons[2].btnOpened)
        {
            object[3].drawObject = true;
        }
        if (openSubsect && chSubSection == object[2].subSection && buttons[2].btnOpened)
        {
            object[4].drawObject = true;
        }
        if (openSubsect && buttons[1].subButtons[2].subBtnOpened && buttons[1].btnOpened)
        {
            object[5].drawObject = true;
        }
        if (openSubsect && buttons[1].subButtons[2].subBtnOpened && buttons[1].btnOpened)
        {
            object[6].drawObject = true;
        }

        if (openSubsect && buttons[1].subButtons[3].subBtnOpened && buttons[1].btnOpened)
        {
            object[7].drawObject = true;
        }*/
        if (openSubsect && buttons[4].subButtons[2].subBtnOpened && buttons[4].btnOpened)
        {
            if(txMouseButtons() == 1)
            {
                int x = txMouseX();
                int y = txMouseY();
                txRectangle(x, y, x, y);
                txSleep(100);
                    while(txMouseButtons() == 1)
                    {
                        int x2 = txMouseX();
                        int y2 = txMouseY();
                        txRectangle(x, y, x2, y2);
                        txSleep(50);
                    }
            }
        }

        //txRectangle(x, y, x2, y2);

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
                activeObj[nActObj] = {300, 300, object[i].pic, object[i].section, object[i].subSection, true, object[i].width, object[i].height};
                nActObj++;
                Sleep(200);
            }
        }

        drawPics(activeObj, nActObj);

        for(int i = 0; i < nActObj; i++)
        {
        if (activeObj[i].drawObject &&
                txMouseX() >= activeObj[i].x &&
                txMouseX() <= activeObj[i].x + 150 &&
                txMouseY() >= activeObj[i].y &&
                txMouseY() <= activeObj[i].y + 150 && txMouseButtons() == 1 &&
                active < 0
                )
            {
                active = i;
            }
            if (activeObj[i].drawObject &&
                activeObj[i].y + 75 <= 100)
                activeObj[i].drawObject = false;
        }


            if (active >= 0)
            {
                activeObj[active].x = txMouseX() - 75;
                activeObj[active].y = txMouseY() - 75;
            }

            if (txMouseButtons()!= 1)
                active = -10;

        //Что это?
        if (window == MENU_OPEN)
            Win32::TransparentBlt (txDC(), mx, 0, 50, 50, object[0].pic, 0, 0, 686, 700, TX_BLACK); // 10x zoom

        //По пробелу скрываем всю мебель
        for(int i = 0; i < nObj; i++)
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
        for(int i = 0; i < 5; i++)
        {
            if (buttons[i].btnOpened)  txTextOut(800, 10, buttons[i].text);
                for(int j = 0; j < 4; j++)
                    if (buttons[i].subButtons[j].subBtnOpened)  txTextOut(800, 30, buttons[i].subButtons[j].text);
        }

        txSleep(20) ;
    }

    //Удаление картинок
    for(int i = 0; i < nObj; i++)
        txDeleteDC (object[i].pic);

    return 0;
}
