//---------------------------------------------------------------------------


#pragma hdrstop

#include "Generate_Line.h"
#include "FPC_to_PCB.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

/*float ang (double dx_, double dy_)
        {
        double ANG_s;
        if (dx_ == 0)
                {
                if (dy_ > 0) ANG_s = 90;
                else ANG_s = 270;
                }
        else
                {
                double Dxy = dy_/dx_;
                ANG_s = (atan(Dxy))*573/10;
                if ((dx_ > 0)&&(dy_ < 0)) ANG_s = 360 + ANG_s;
                if (dx_ < 0) ANG_s = 180 + ANG_s;
                }
        return ANG_s;
}

long Generate_Line (double X, double Y, double X2, double Y2,  int type_L , double *OutPut)
{
double D;
double F;
long  lines = 0;
while (lines < max_arc) // ����� ����������� ������� �� ��������� !!!
        {
        *(OutPut + lines) = 0;      //������� ������
        lines++;
        }
lines = 0;
if (type_L == 0)
        { //������ �����
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
        { // ����
        double dx;
        double dy;
        double angL;
        double ang_end;
        double x0;
        double y0;
        double rad;
        double xmid;
        double ymid;
        double len;
        xmid = (X + X2)/(double)2;
        ymid = (Y + Y2)/(double)2;
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
                double H_arc = len/(double)2;
                if (ABS(dx) < ABS(dy)) H_arc = H_arc*(double)dy/(double)dx;
                else H_arc = H_arc*(double)dx/(double)dy;
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
                while (ABS(angL - ang_end) > 10)
                        {
                        if (type_L == 1) Rotate_Vertex (&X, &Y, -10);
                        if (type_L == 2) Rotate_Vertex (&X, &Y, 10);
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
        } // ����

          // X = X2;
          // Y = Y2;
          // } // if (get ("next_corner") == 0)
return lines;
}    */

//---------------------------------------------------------------------------


//#pragma hdrstop

//#include "Generate_Line.h"
//#include "Debug_Areas.h"
//#include "math.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//#pragma package(smart_init)
int GEN_ARC_NUM_CORNERS = 10;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//int Generate_Line (double X, double Y, double X2, double Y2,  int type_L , float *OutPut)
long Generate_Line (double xi, double yi, double xf, double yf,  int type_L , double *OutPut)
{
long  lines = 0;
if (type_L > 2) type_L = 0;
if (type_L == 0 || ( ((xi - xf) < 0.1 && (xi - xf) > -0.1) || ((yi - yf) < 0.1 && (yi - yf) > -0.1) ))
        { //������ �����
        *(OutPut + lines) = xi;
        lines++;
        *(OutPut + lines) = yi;
        lines++;
        *(OutPut + lines) = xf;
        lines++;
        *(OutPut + lines) = yf;
        lines++;
        }
else    { // ����
        float xxi, xxf, yyi, yyf;
        if( type_L == 2/*CPolyLine::ARC_CCW */)
			{
			xxi = xf;
			xxf = xi;
			yyi = yf;
			yyf = yi;
			}
	else
			{
			xxi = xi;
			xxf = xf;
			yyi = yi;
			yyf = yf;
	}
		// find center and radii of ellipse
	float xo, yo, rx, ry;
	if( xxf > xxi && yyf > yyi )
			{
			xo = xxf;
			yo = yyi;
			}
	else if( xxf < xxi && yyf > yyi )
			{
			xo = xxi;
			yo = yyf;
			}
	else if( xxf < xxi && yyf < yyi )
			{
			xo = xxf;
			yo = yyi;
			}
	else if( xxf > xxi && yyf < yyi )
			{
			xo = xxi;
			yo = yyf;
			}
	rx = ABS( (float)(xxi-xxf) );
	ry = ABS( (float)(yyi-yyf) );
	float k = rx/ry;
        *(OutPut + lines) = xi;
        lines++;
        *(OutPut + lines) = yi;
        lines++;
        xi = xi - xo;
        yi = yi - yo;
        xi = xi/k;
        for (int step=0; step<(GEN_ARC_NUM_CORNERS-1); step++)
                {
                if (type_L == 1)
                        Rotate_Vertex (&xi, &yi, -90.0/(float)GEN_ARC_NUM_CORNERS );
                if (type_L == 2)
                        Rotate_Vertex (&xi, &yi, 90.0/(float)GEN_ARC_NUM_CORNERS );
                xi = xi*k + xo;
                yi = yi + yo;
                *(OutPut + lines) = xi;
                lines++;
                *(OutPut + lines) = yi;
                lines++;
                xi = (xi - xo)/k;
                yi = yi - yo;
                }
        *(OutPut + lines) = xf;
        lines++;
        *(OutPut + lines) = yf;
        lines++; 
        }
return lines;
}