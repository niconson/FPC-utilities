//---------------------------------------------------------------------------


#pragma hdrstop

#include "RND_FUNC.h"
#include "RND.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

int RND_FUNC(   double X1,
                double Y1,
                double X2,
                double Y2,
                double X3,
                double Y3,
                double R,
                float Share,
                int CountNew,
                double MinSeg,
                double Pad1,
                double Pad2,
                int Angmin,
                int Angmax)
{
#define INT_MAX 1073741823
#define R_MAX   99999999.0   //99mm
 double dx12 = X1-X2;
 double dy12 = Y1-Y2;
 double dx23 = X3-X2;
 double dy23 = Y3-Y2;
 double L12 = dx12*dx12 + dy12*dy12;    //����� ������� ��������
 if (L12 > BY_ZERO)
        L12 = sqrt(L12);
 else   return 0;
 double L23 = dx23*dx23 + dy23*dy23;    //����� ������� ��������
 if (L23 > BY_ZERO)
        L23 = sqrt(L23);
 else   return 0;
 double ANGLE12;                                //���� ������� ��������
 double ANGLE23;                                //���� ������� ��������
 double ANGLE_BETWEEN_CORR;                     //���� ����� �����������������
 double ANGLE_BETWEEN;                          //���� �����
 double ANGLE_MIDLE;                            //���� ������� �����
 double ANGLE_R12;                              //���� ����� ������ � ������� ���(������)
 double ANGLE_R23;                              //���� ����� ������ � ������� ���(������)
 double H;                                      //����� ������� ����� ���� �����
 double X_CENT;                                 //����� ����
 double Y_CENT;                                 //����� ����
 double ANGLE_STEP;                             //���� ����
 double START_ANG;                              //��������� ���� ��������� ����
 R = R*_MM_TO_NM; // convert MM to NM
//------------------------������� ������ _NEW[]
 long i = 0;
 while (i < 32)
       { X_NEW[i] = 0;
         Y_NEW[i] = 0;
         i++;
       }
//------------------------ ANGLE12
 /*if ((dx12 == 0)&&(dy12))
    {if (dy12 < 0) ANGLE12 = 270;
     else ANGLE12 = 90;
    }
 else if (ABS(dy12/dx12) > INT_MAX)
    {if (dy12 < 0) ANGLE12 = 270;
     else ANGLE12 = 90;
    }
 else
    {ANGLE12 = atan(dy12/dx12)*(double)180/(double)M_PI;               //����..
     if ((dx12 > 0)&&(dy12 < 0)) ANGLE12 = 360 + ANGLE12;
     if (dx12 < 0) ANGLE12 = 180 + ANGLE12;
    }*/
    ANGLE12 = Angle( dx12,dy12 );
//------------------------ ANGLE23
 /*if ((dx23 == 0)&&(dy23))
    {if (dy23 < 0) ANGLE23 = 270;
     else ANGLE23 = 90;
    }
 else if (ABS(dy23/dx23) > INT_MAX)
    {if (dy23 < 0) ANGLE23 = 270;
     else ANGLE23 = 90;
    }
 else
    {ANGLE23 = atan(dy23/dx23)*(double)180/(double)M_PI;               //����..
     if ((dx23 > 0)&&(dy23 < 0)) ANGLE23 = 360 + ANGLE23;
     if (dx23 < 0) ANGLE23 = 180 + ANGLE23;
    }*/
    ANGLE23 = Angle( dx23,dy23 );
//------------------------ ANGLE_BETWEEN
 ANGLE_BETWEEN = ANGLE23 - ANGLE12;
 if (ANGLE_BETWEEN < 0) ANGLE_BETWEEN = ANGLE_BETWEEN + 360;
 if (ANGLE_BETWEEN > 180) ANGLE_BETWEEN_CORR = 360 - ANGLE_BETWEEN;
 else ANGLE_BETWEEN_CORR = ANGLE_BETWEEN;
//-----------------------------
 if (ANGLE_BETWEEN_CORR > 175)          return 0;
 if (ANGLE_BETWEEN_CORR < Angmin)       return 0;
 if (ANGLE_BETWEEN_CORR > Angmax)       return 0;
 double k = tan(ANGLE_BETWEEN_CORR*M_PI/(double)360);
 if (!k)                return 0;
 if (ABS((int)k) > 30)  return 0;
 MinSeg = MinSeg*_MM_TO_NM;
 if ((L12 < MinSeg)||(L23 < MinSeg)) return 0;
 double Lrnd = R/k;
 if     (L12 < Lrnd*Share || L23 < Lrnd*Share)
        {
        if (L12 < L23) R = L12*k/(double)Share;
        else           R = L23*k/(double)Share;
        }
 Lrnd = R/k;
 if ((CountNew == 2) && (L12 < Lrnd*(double)3.5 || L23 < Lrnd*(double)3.5))
        {
        if (L12 < L23) R = L12*k/(double)3.5;
        else           R = L23*k/(double)3.5;
        }
 else if ((CountNew == 3) && (L12 < Lrnd*(double)2.8 || L23 < Lrnd*(double)2.8))
        {
        if (L12 < L23) R = L12*k/(double)2.8;
        else           R = L23*k/(double)2.8;
        }
 else if ((CountNew == 4) && (L12 < Lrnd*(double)2.45 || L23 < Lrnd*(double)2.45))
        {
        if (L12 < L23) R = L12*k/(double)2.45;
        else           R = L23*k/(double)2.45;
        }
 else if (L12 < Lrnd*(double)2.3 || L23 < Lrnd*(double)2.3)
        {
        if (L12 < L23) R = L12*k/(double)2.3;
        else           R = L23*k/(double)2.3;
        }
 if (R > R_MAX) return 0;
 if ((Pad1) || (Pad2))
    {
    double Lseg1 = L12 - Pad2/1.9;
    double Lseg2 = L23 - Pad1/1.9;
    double Seg = R*tan((180 - ANGLE_BETWEEN_CORR)*M_PI/(double)360);
    if (Pad2)
        {
        if (Lseg1 < 0)return 0;
        if (Lseg1 < Seg) R = Lseg1/tan((180 - ANGLE_BETWEEN_CORR)*M_PI/(double)360);
        }
    else{
        if (Lseg2 < 0)return 0;
        if (Lseg2 < Seg) R = Lseg2/tan((180 - ANGLE_BETWEEN_CORR)*M_PI/(double)360);
        }
    }
 if (ANGLE_BETWEEN > 180)
    {
      ANGLE_MIDLE = ANGLE12 - ANGLE_BETWEEN_CORR/(double)2;
      ANGLE_R12 = ANGLE12 - 90;
      ANGLE_R23 = ANGLE23 + 90;
    }
 else
    {
      ANGLE_MIDLE = ANGLE12 + ANGLE_BETWEEN_CORR/(double)2;
      ANGLE_R12 = ANGLE12 + 90;
      ANGLE_R23 = ANGLE23 - 90;
    }

 if (ANGLE_R12 < 0) ANGLE_R12 = ANGLE_R12 + 360;
 if (ANGLE_R23 < 0) ANGLE_R23 = ANGLE_R23 + 360;
 if (ANGLE_R12 > 360) ANGLE_R12 = ANGLE_R12 - 360;
 if (ANGLE_R23 > 360) ANGLE_R23 = ANGLE_R23 - 360;
 H = R/sin(ANGLE_BETWEEN_CORR*M_PI/(double)360);
 if (H < 0) H = -H;
 X_CENT = H*cos(ANGLE_MIDLE*M_PI/(double)180) + X2;
 Y_CENT = H*sin(ANGLE_MIDLE*M_PI/(double)180) + Y2;
 ANGLE_STEP = 180 - ANGLE_BETWEEN_CORR;
 ANGLE_STEP = ANGLE_STEP/(double)(CountNew-1);
 START_ANG = ANGLE_R23 + 180;
 i = 0;
 while (i < CountNew)
    {X_NEW[i] =  R*cos(START_ANG*M_PI/(double)180) + X_CENT;
     Y_NEW[i] =  R*sin(START_ANG*M_PI/(double)180) + Y_CENT;
     if (ANGLE_BETWEEN > 180) START_ANG = START_ANG - ANGLE_STEP;
     else START_ANG = START_ANG + ANGLE_STEP;
     i++;
     if (i > 15) {ShowMessage ("    Error of RND_FUNC.cpp!"); exit(0);}
    }
 return CountNew;
}