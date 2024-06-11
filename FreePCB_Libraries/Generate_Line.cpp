//---------------------------------------------------------------------------


#pragma hdrstop

#include "Generate_Line.h"
#include "ABClibrary.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


//------------------------------------------
//        äëèíà ñåãìåíòà
//------------------------------------------
float Length_Line (float X1, float Y1, float X2, float Y2)
        {
        float dx = X2 - X1;
        float dy = Y2 - Y1;
        bool Flag = false;
        if (( ABS(dx) > 30000 )||( ABS(dy) > 30000 ))
                {
                Flag = true;
                dx = dx/(float)100000;
                dy = dy/(float)100000;
                }
        float len = pow(dx, 2) + pow(dy, 2);
        if (len)        len = sqrt(len);
        if (Flag)       len = len*(float)100000;
        return len;
        }

        
float ang (float dx_, float dy_)
        {
        float ANG_s;
        if (dx_ == 0)
                {
                if (dy_ > 0) ANG_s = 90;
                else ANG_s = 270;
                }
        else
                {
                float Dxy = dy_/dx_;
                ANG_s = (atan(Dxy))*180/M_PI;
                if ((dx_ > 0)&&(dy_ < 0)) ANG_s = 360 + ANG_s;
                if (dx_ < 0) ANG_s = 180 + ANG_s;
                }
        return ANG_s;
}





int Generate_Line (double X, double Y, double X2, double Y2,  int type_L , float *OutPut)
{
float D;
float F;
long  lines = 0;
while (lines < 99) // ÄËÈÍÀ ÏÅÐÅÄÀÍÍÎÃÎ ÌÀÑÑÈÂÀ ÏÎ ÓÊÀÇÀÒÅËÞ !!!
        {
        *(OutPut + lines) = 0;      //ñòèðàåì ìàññèâ
        lines++;
        }
lines = 0;
if ((type_L <= 0)||(type_L > 2))
        { //ïðÿìàÿ ëèíèÿ
        *(OutPut + lines) = X;
        lines++;
        *(OutPut + lines) = Y;
        lines++;
        *(OutPut + lines) = X2;
        lines++;
        *(OutPut + lines) = Y2;
        lines++;
        }
else
        { // äóãà
        float dx;
        float dy;
        float angL;
        float ang_end;
        float x0;
        float y0;
        float rad;
        float xmid;
        float ymid;
        float len;
        xmid = (X + X2)/(float)2;
        ymid = (Y + Y2)/(float)2;
        dx = X - X2;
        dy = Y - Y2;
        if ((dx == 0)||(dy == 0))
                {
                *(OutPut + lines) = X;
                lines++;
                *(OutPut + lines) = Y;
                lines++;
                *(OutPut + lines) = X2;
                lines++;
                *(OutPut + lines) = Y2;
                lines++;
                }// if ((dx == 0)||(dy == 0))
        else
                {
                angL = ang (dx,dy);
                if (type_L == 1) angL = angL + 90;
                if (type_L == 2) angL = angL - 90;
                len = Length_Line (0, 0, dx, dy);
                float H_arc = len/(float)2;
                if (ABS(dx) < ABS(dy)) H_arc = H_arc*(float)dy/(float)dx;
                else H_arc = H_arc*(float)dx/(float)dy;
                if (H_arc < 0) H_arc = -H_arc;
                if (angL < 0) angL = angL + 360;
                if (angL > 360) angL = angL - 360;
                x0 = H_arc*cos(angL*10/573) + xmid;
                y0 = H_arc*sin(angL*10/573) + ymid;

                ang_end = ang((X2-x0),(Y2-y0)) ;
                angL = ang((X-x0),(Y-y0)) ;
                D = X;
                F = Y;
                X = X - x0;
                Y = Y - y0;
                *(OutPut + lines) = D;
                lines++;
                *(OutPut + lines) = F;
                lines++;
                while (ABS(angL - ang_end) > 5)
                        {
                        if (type_L == 1) Rotate_Vertex (&X, &Y, -5);
                        if (type_L == 2) Rotate_Vertex (&X, &Y, 5);
                        X = X + x0;
                        Y = Y + y0;
                        *(OutPut + lines) = X;
                        lines++;
                        *(OutPut + lines) = Y;
                        lines++;
                        D = X;
                        F = Y;
                        X = X - x0;
                        Y = Y - y0;
                        angL = ang (X,Y);
                        } // while (ang < ang_end)
                *(OutPut + lines) = X2;
                lines++;
                *(OutPut + lines) = Y2;
                lines++;
                }// else if ((dx == 0)||(dy == 0))
        } // äóãà

          // X = X2;
          // Y = Y2;
          // } // if (get ("next_corner") == 0)
return lines;
}