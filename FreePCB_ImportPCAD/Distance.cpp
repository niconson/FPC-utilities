//---------------------------------------------------------------------------


#pragma hdrstop
#include "HEAD.h"
#include "Lines.h"
#include "Distance.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//======================================================
//Кратчайшее расстояние от точки до линии если X4 Y4 == DEFAULT
//Расчет точки пересечения двух линий
//Return кратчайшее расстояние
//единицы нанометры
//===================================
double Distance ( double X1,        //Line1
                double Y1,        //Line1
                double X2,        //Line1
                double Y2,        //Line1
                double X3,        //Line2
                double Y3,        //Line2
                double X4,        //Line2
                double Y4,        //Line2
                double *Xout,     //Точка пересечения
                double *Yout)     //Точка пересечения
{
double DEFAULT = 2000000000;
//ЕСЛИ ПРЯМЫЕ УГЛЫ...
if (X1 == X2) X2 = X2 + (Y1-Y2)/(double)1000;
if (Y1 == Y2) Y2 = Y2 + (X1-X2)/(double)1000;
if (X3 == X4) X4 = X4 + (Y3-Y4)/(double)1000;
if (Y3 == Y4) Y4 = Y4 + (X3-X4)/(double)1000;

///bool FlagParallel = false; //Флаг если линии параллельны
double a1;
a1 = (double)(Y2 - Y1)/(double)(X2 - X1);
double a2;
if ((X4 == DEFAULT)&&(Y4 == DEFAULT))   a2 = (double)-1/(double)a1;
else                                    a2 = (double)(Y4 - Y3)/(double)(X4 - X3);
double b1 = (double)Y1 - (double)a1*(double)X1;
double b2 = (double)Y3 - (double)a2*(double)X3;
double XOut;
if (a1 - a2)    XOut = (b2 - b1)/(a1 - a2);
else            XOut = DEFAULT;
double YOut;
if (XOut < DEFAULT )    YOut = a1*XOut + b1;
else                    YOut = DEFAULT;


if    ( // ЕСЛИ ТОЧКА ПЕРЕСЕЧЕНИЯ ВНУТРИ ОТРЕЗКА X1 Y1 X2 Y2
        ((XOut > X1)&&(XOut < X2))||
        ((XOut > X2)&&(XOut < X1))
      )
        {
        double L = Length_Line(X3, Y3, XOut, YOut);
        *Xout = XOut;
        *Yout = YOut;
        if ((X4 == DEFAULT)&&(Y4 == DEFAULT))   return L;       //ТОЧКА ПЕРЕСЕЧЕНИЯ ВНУТРИ ОТЕЗКА X1Y1X2Y2
        else if
                ( // ЕСЛИ ТОЧКА ПЕРЕСЕЧЕНИЯ ВНУТРИ ОТРЕЗКА X3 Y3 X4 Y4
                ((XOut > X3)&&(XOut < X4))||
                ((XOut > X4)&&(XOut < X3))
                )                               return 0;       //ОТРЕЗКИ ПЕРЕСЕКАЮТСЯ
        }
if ((X4 == DEFAULT)&&(Y4 == DEFAULT))
        {
        double L1 = Length_Line(X3, Y3, X1, Y1);
        double L2 = Length_Line(X3, Y3, X2, Y2);
        if (L1 < L2)
                {
                *Xout = X1;
                *Yout = Y1;
                return L1;                                      //ТОЧКА ПЕРЕСЕЧЕНИЯ ВНЕ ОТЕЗКА X1Y1X2Y2
                }
        else    {
                *Xout = X2;
                *Yout = Y2;
                return L2;                                      //ТОЧКА ПЕРЕСЕЧЕНИЯ ВНЕ ОТЕЗКА X1Y1X2Y2
                }
        }
else    {
        *Xout = XOut;
        *Yout = YOut;
        double MinLen;
        double Dis1 = Length_Line(X3, Y3, X1, Y1);
        double Dis2 = Length_Line(X4, Y4, X1, Y1);
        double Dis3 = Length_Line(X3, Y3, X2, Y2);
        double Dis4 = Length_Line(X4, Y4, X2, Y2);
        if ((Dis1 < Dis2)&&(Dis1 < Dis3)&&(Dis1 < Dis4))
        MinLen = Dis1;                                      //ОТРЕЗКИ НЕ ПЕРЕСЕКАЮТСЯ
        if ((Dis2 < Dis1)&&(Dis2 < Dis3)&&(Dis2 < Dis4))
        MinLen = Dis2;                                      //ОТРЕЗКИ НЕ ПЕРЕСЕКАЮТСЯ
        if ((Dis3 < Dis2)&&(Dis3 < Dis1)&&(Dis3 < Dis4))
        MinLen = Dis3;                                      //ОТРЕЗКИ НЕ ПЕРЕСЕКАЮТСЯ
        if ((Dis4 < Dis2)&&(Dis4 < Dis3)&&(Dis4 < Dis1))
        MinLen = Dis4;                                      //ОТРЕЗКИ НЕ ПЕРЕСЕКАЮТСЯ
        //=====
        double a__1 = (Y2 - Y1)/(X2 - X1);
        double a__2 = -1/a__1;
        double b__1 = Y1 - a__1*(double)X1;
        double b__2 = Y3 - a__2*(double)X3;
        if (a__1 - a__2)        XOut = (b__2 - b__1)/(a__1 - a__2);
        else                    XOut = DEFAULT;
        if (XOut < DEFAULT )    YOut = a__1*XOut + b__1;
        else                    YOut = DEFAULT;
        if      (((XOut > X1)&&(XOut < X2))||
                ((XOut > X2)&&(XOut < X1))||
                ((YOut > Y1)&&(YOut < Y2))||
                ((YOut > Y2)&&(YOut < Y1)))
                {
                double LEN = Length_Line(X3, Y3, XOut, YOut);
                if (LEN < MinLen) MinLen = LEN;
                }
        b__2 = Y4 - a__2*(double)X4;
        if (a__1 - a__2)        XOut = (b__2 - b__1)/(a__1 - a__2);
        else                    XOut = DEFAULT;
        if (XOut < DEFAULT )    YOut = a__1*XOut + b__1;
        else                    YOut = DEFAULT;
        if      (((XOut > X1)&&(XOut < X2))||
                ((XOut > X2)&&(XOut < X1))||
                ((YOut > Y1)&&(YOut < Y2))||
                ((YOut > Y2)&&(YOut < Y1)))
                {
                double LEN = Length_Line(X4, Y4, XOut, YOut);
                if (LEN < MinLen) MinLen = LEN;
                }
        //=======
        a__1 = (Y4 - Y3)/(X4 - X3);
        a__2 = -1/a__1;
        b__1 = Y3 - a__1*(double)X3;
        b__2 = Y1 - a__2*(double)X1;
        if (a__1 - a__2)        XOut = (b__2 - b__1)/(a__1 - a__2);
        else                    XOut = DEFAULT;
        if (XOut < DEFAULT )    YOut = a__1*XOut + b__1;
        else                    YOut = DEFAULT;
        if      (((XOut > X3)&&(XOut < X4))||
                ((XOut > X4)&&(XOut < X3))||
                ((YOut > Y3)&&(YOut < Y4))||
                ((YOut > Y4)&&(YOut < Y3)))
                {
                double LEN = Length_Line(X1, Y1, XOut, YOut);
                if (LEN < MinLen) MinLen = LEN;
                }
        b__2 = Y2 - a__2*(double)X2;
        if (a__1 - a__2)        XOut = (b__2 - b__1)/(a__1 - a__2);
        else                    XOut = DEFAULT;
        if (XOut < DEFAULT )    YOut = a__1*XOut + b__1;
        else                    YOut = DEFAULT;
        if      (((XOut > X3)&&(XOut < X4))||
                ((XOut > X4)&&(XOut < X3))||
                ((YOut > Y3)&&(YOut < Y4))||
                ((YOut > Y4)&&(YOut < Y3)))
                {
                double LEN = Length_Line(X2, Y2, XOut, YOut);
                if (LEN < MinLen) MinLen = LEN;
                }
        //=====
        return MinLen;
        }
}