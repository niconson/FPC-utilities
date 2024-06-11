//---------------------------------------------------------------------------


#pragma hdrstop

#include "Generate_Line.h"
#include "To_DXF.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int Generate_Line (float xi, float yi, float xf, float yf,  int type_L , float *OutPut)
{
long  lines = 0;
if (type_L > 2) type_L = 0;
if (type_L == 0 || ( ABS(xi - xf) < 0.01 || ABS(yi - yf) < 0.01 ))
        { //прямая линия
        *(OutPut + lines) = xi;
        lines++;
        *(OutPut + lines) = yi;
        lines++;
        *(OutPut + lines) = xf;
        lines++;
        *(OutPut + lines) = yf;
        lines++;
        }
else    { // дуга
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
        for (int step=0; step<6; step++)
                {
                if (type_L == 1)
                        Rotate_Vertex (&xi, &yi, -15);
                if (type_L == 2)
                        Rotate_Vertex (&xi, &yi, 15);
                xi = xi*k + xo;
                yi = yi + yo;
                *(OutPut + lines) = xi;
                lines++;
                *(OutPut + lines) = yi;
                lines++;
                xi = (xi - xo)/k;
                yi = yi - yo;
                } // while (ang < ang_end)
        *(OutPut + lines) = xf;
        lines++;
        *(OutPut + lines) = yf;
        lines++; 
        }
return lines;
}
