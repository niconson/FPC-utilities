//---------------------------------------------------------------------------


#pragma hdrstop

#include "VIA_FUNC.h"
#include "math.h"
#include "RND.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

bool VIA_FUNC(  double X1,
                double Y1,
                double X2,
                double Y2,
                double X3,
                double Y3,
                double SizeVia,
                double DVia,
                double LenVia,
                double W1,
                double W2,
                bool NewStyle,
                bool RND)
        {
        //—“»–¿≈Ã Ã¿——»¬ _NEW[]
        long i = 0;
        while (i < 32)
                {
                X_NEW[i] = 0;
                Y_NEW[i] = 0;
                i++;
                }
        //-----------------------------------
        bool F1 = true;
        bool F2 = true;
        SizeVia = SizeVia*_MM_TO_NM;
        LenVia = LenVia*_MM_TO_NM;
        if      ( DVia > SizeVia )
                {
                F1 = false;
                F2 = false;
                return 0;
                }
        if (Length_Line(X1,Y1,X2,Y2) < (DVia/2.0)) F1 = false;
        if (Length_Line(X3,Y3,X2,Y2) < (DVia/2.0)) F2 = false;
        double LenVia1 = LenVia;
        double LenVia2 = LenVia;
        if (RND)
                {
                if (Length_Line(X1,Y1,X2,Y2) < (LenVia*2)) LenVia1 = (Length_Line(X1,Y1,X2,Y2))/(double)2;
                if (Length_Line(X3,Y3,X2,Y2) < (LenVia*2)) LenVia2 = (Length_Line(X3,Y3,X2,Y2))/(double)2;
                }
        else    {
                if (Length_Line(X1,Y1,X2,Y2) < LenVia) LenVia1 = Length_Line(X1,Y1,X2,Y2);
                if (Length_Line(X3,Y3,X2,Y2) < LenVia) LenVia2 = Length_Line(X3,Y3,X2,Y2);
                }
        if (LenVia1 < (DVia/(double)2) && NewStyle) F1 = false;
        if (LenVia2 < (DVia/(double)2) && NewStyle) F2 = false;
        if (!NewStyle)
                {   //OLD STYLE
                double DX = X1 - X2;
                double DY = Y1 - Y2;
                double An = Angle(DX, DY);
                if (F1)
                        {
                        DX = LenVia*cos(An*M_PI/180.0);
                        DY = LenVia*sin(An*M_PI/180.0);
                        X_NEW[1] = X2 + DX;
                        Y_NEW[1] = Y2 + DY;
                        }
                DX = X3 - X2;
                DY = Y3 - Y2;
                An = Angle(DX, DY);
                if (F2)
                        {
                        DX = LenVia*cos(An*M_PI/180.0);
                        DY = LenVia*sin(An*M_PI/180.0);
                        X_NEW[0] = X2 + DX;
                        Y_NEW[0] = Y2 + DY;
                        }
                }
        else    {   //NEW STYLE
                double DX = X1 - X2;
                double DY = Y1 - Y2;
                double An = Angle(DX, DY);
                if (F1)
                        {
                        DX = LenVia1*cos(An*M_PI/180.0);
                        DY = LenVia1*sin(An*M_PI/180.0);
                        X_NEW[3] = X2 + DX;
                        Y_NEW[3] = Y2 + DY;
                        double L = (DVia - W1)/(double)2;
                        double AnCorr = atan(L/LenVia1);
                        AnCorr = AnCorr*(double)180/(double)M_PI;
                        An = An + 90 - AnCorr;
                        DX = L*cos(An*(double)M_PI/(double)180);
                        DY = L*sin(An*(double)M_PI/(double)180);
                        X_NEW[4] = X2 + DX;
                        Y_NEW[4] = Y2 + DY;
                        An = An - 180 + AnCorr*(double)2;
                        DX = L*cos(An*(double)M_PI/(double)180);
                        DY = L*sin(An*(double)M_PI/(double)180);
                        X_NEW[5] = X2 + DX;
                        Y_NEW[5] = Y2 + DY;
                        }
                DX = X3 - X2;
                DY = Y3 - Y2;
                An = Angle(DX, DY);
                if (F2)
                        {
                        DX = LenVia2*cos(An*(double)M_PI/(double)180);
                        DY = LenVia2*sin(An*(double)M_PI/(double)180);
                        X_NEW[0] = X2 + DX;
                        Y_NEW[0] = Y2 + DY;
                        double L = (DVia - W2)/(double)2;
                        double AnCorr = atan(L/LenVia2);
                        AnCorr = AnCorr*(double)180/(double)M_PI;
                        An = An + 90 - AnCorr;
                        DX = L*cos(An*(double)M_PI/(double)180);
                        DY = L*sin(An*(double)M_PI/(double)180);
                        X_NEW[1] = X2 + DX;
                        Y_NEW[1] = Y2 + DY;
                        An = An - 180 + AnCorr*(double)2;
                        DX = L*cos(An*(double)M_PI/(double)180);
                        DY = L*sin(An*(double)M_PI/(double)180);
                        X_NEW[2] = X2 + DX;
                        Y_NEW[2] = Y2 + DY;
                        }
                }
        return true;
        }
