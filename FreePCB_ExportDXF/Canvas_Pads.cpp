//---------------------------------------------------------------------------


#pragma hdrstop

#include "Canvas_Pads.h"
#include "To_DXF.h"
#include "Options.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
int UNITS;







//========================
void Generate_POINT (float *PARAM , long CASE, float *Xout, float *Yout)
{
int Type2 =     *(PARAM + 0);
float W2 =      *(PARAM + 1)/2;
float L2 =      *(PARAM + 2)/2;
float R2 =      *(PARAM + 3);
int A_Part2 =   *(PARAM + 4);
int A_Pi2 =     *(PARAM + 5);
int Ang2 =      *(PARAM + 6);
float X_Pi2 =   *(PARAM + 7);
float Y_Pi2 =   *(PARAM + 8);
float X_Po2 =   *(PARAM + 9);
float Y_Po2 =   *(PARAM + 10);
int LR2 =       *(PARAM + 11);
//-----------------
if (Type2 == 1 || Type2 == 2)
        {
        L2 = W2;
        }
if (Type2 == 5)
        {
        if (W2 < L2)    R2 = W2;
        else            R2 = L2;
        }
float RX = R2;
float RY = R2;
//-----------------
if ((CASE >= 4) && (CASE <= 11))
        {L2 = -L2; RX = -R2;}
if ((CASE >= 8) && (CASE <= 15))
        {W2 = -W2; RY = -R2;}
if ((CASE == 17) || (CASE == 18))
        L2 = -L2;
if ((CASE == 18) || (CASE == 19))
        W2 = -W2;
if (CASE < 16)
        {
        if (CASE > 11) CASE = CASE - 3;
        else if (CASE > 7) CASE = CASE - 2;
        else if (CASE > 3) CASE = CASE - 1;
        *Yout = W2 - RY + ABS(RY)*sin((float)CASE*(float)30*M_PI/(float)180);
        *Xout = L2 - RX + ABS(RX)*cos((float)CASE*(float)30*M_PI/(float)180);
        }
else if (CASE >= 16)
        {
        *Yout = W2;
        *Xout = L2;
        }
if (ABS(A_Pi2) > BY_ZERO)
        Rotate_Vertex (Xout, Yout, -A_Pi2);
*Xout += X_Pi2;
*Yout += Y_Pi2;
if (LR2 > 1)
        {
        Ang2 = -Ang2;
        mirror_angle (A_Part2, 1, Xout, Yout);
        }
else    mirror_angle (A_Part2, 0, Xout, Yout);
if (ABS(Ang2) > BY_ZERO)
        Rotate_Vertex (Xout, Yout, Ang2);
if (UNITS == 1)
        {
        *Xout = (*Xout)*(float)254/(float)10000;
        *Yout = (*Yout)*(float)254/(float)10000;
        }
else if (UNITS == 0)
        {
        *Xout = (*Xout)/(float)PER_MM;
        *Yout = (*Yout)/(float)PER_MM;
        }
*Xout += X_Po2;
*Yout += Y_Po2;
}
















//==================
void Canvas_Pads ( float *PARAM, AnsiString LAYER_NAME, int MM, int COLOR)
{
        int Type = *(PARAM + 0);
        float W = *(PARAM + 1);
        float L = *(PARAM + 2);
        float R = *(PARAM + 3);
   //   float A_Part = *(PARAM + 4);
   //   float A_Pi = *(PARAM + 5);
   //   float Ang = *(PARAM + 6);
   //   float X_Pi = *(PARAM + 7);
   //   float Y_Pi = *(PARAM + 8);
   //   float X_Po = *(PARAM + 9);
   //   float Y_Po = *(PARAM + 10);
        int LR = *(PARAM + 11);
   //   int indexPin = *(PARAM + 12);
        float Hole = *(PARAM + 13);
UNITS = MM;
if (Type == tp_empty)
        return;
if (W < BY_ZERO)
        return;
if (LR > 1) LR = LR - 2;
if (L < BY_ZERO)
        {
        L = W;
        *(PARAM + 2) = W;
        }
if (R < 0)
        {
        R = 0;
        *(PARAM + 3) = 0;
        }
if (Type == tp_round)
        {
        L = W;
        *(PARAM + 2) = W;
        R = W/2;
        *(PARAM + 3) = R;
        }
if ((Type == tp_square)||(Type == tp_rect))
        {
        R = 0;
        *(PARAM + 3) = 0;
        }
if ( Type == tp_oval )
        {
        R = MIN(W,L)/2;
        *(PARAM + 3) = R;
        if (ABS(W - L) < BY_ZERO)
                {
                Type = 1;
                *PARAM = 1;
                }
        }
float Point_X;
float Point_Y;
float save_X;
float save_Y;
float ELEVATION = 0;
//
if (!LR) ELEVATION = BoardThick;
//
if (Type == tp_octagon)       //OCTAGON
        {
        if( Hole > BY_ZERO )
                {
                float paramH[N_PARAM];
                for( int cp=0; cp<N_PARAM; cp++ )
                        paramH[cp] = PARAM[cp];
                paramH[0] = tp_round;
                paramH[1] = Hole;
                paramH[2] = Hole;
                paramH[3] = Hole/2.0;
                paramH[13] = 0.0;
                float X[16],Y[16];
                for (int CS=0; CS<16; CS++)
                        Generate_POINT (paramH , CS, &X[CS], &Y[CS]);
                if( Form3->RadioButton2->Checked )
                        for (int CS=0; CS<16; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 16 )
                                        ncs = 0;
                                W_LINE( X[CS], Y[CS], ELEVATION, X[ncs], Y[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                float RCTX[8],RCTY[8];
                for (int CS=0; CS<16; CS+=4)
                        {
                        int in = CS/2+1;
                        if( in >= 8 )
                                in = 0;
                        Generate_POINT (PARAM , CS, &RCTX[CS/2], &RCTY[CS/2]);
                        Generate_POINT (PARAM , CS+3, &RCTX[in], &RCTY[in]);
                        }
                if( Form3->RadioButton2->Checked )
                        {
                        for (int CS=0; CS<8; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 8 )
                                        ncs = 0;
                                W_LINE( RCTX[CS], RCTY[CS], ELEVATION, RCTX[ncs], RCTY[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                        }
                else    {
                        for (int cs=0; cs<16; cs+=2)
                                {
                                W_SOLID( RCTX[cs/2], RCTY[cs/2], ELEVATION,
                                         X[cs], Y[cs], ELEVATION,
                                         RCTX[cs/2], RCTY[cs/2], ELEVATION,
                                         X[cs+1], Y[cs+1], ELEVATION,
                                         COLOR, LAYER_NAME );
                                int cs2 = cs+2;
                                if( cs2 >= 16 )
                                        cs2 = 0;
                                W_SOLID( RCTX[cs/2], RCTY[cs/2], ELEVATION,
                                         X[cs+1], Y[cs+1], ELEVATION,
                                         RCTX[cs/2], RCTY[cs/2], ELEVATION,
                                         X[cs2], Y[cs2], ELEVATION,
                                         COLOR, LAYER_NAME );
                                int cs3 = cs/2+1;
                                if( cs3 >= 8 )
                                        cs3 = 0;
                                W_SOLID( RCTX[cs/2], RCTY[cs/2], ELEVATION,
                                         RCTX[cs3],  RCTY[cs3], ELEVATION,
                                         RCTX[cs/2], RCTY[cs/2], ELEVATION,
                                         X[cs2], Y[cs2], ELEVATION,
                                         COLOR, LAYER_NAME );
                                }
                        }
                }
        else    {
                float X[8],Y[8];
                for (int CS=0; CS<16; CS+=4)
                        {
                        Generate_POINT (PARAM , CS, &X[CS/2], &Y[CS/2]);
                        Generate_POINT (PARAM , CS+3, &X[CS/2+1], &Y[CS/2+1]);
                        }
                if( Form3->RadioButton2->Checked == 0 )
                        {
                        W_SOLID(         X[0], Y[0], ELEVATION,
                                         X[3], Y[3], ELEVATION,
                                         X[7], Y[7], ELEVATION,
                                         X[4], Y[4], ELEVATION,
                                         COLOR, LAYER_NAME );
                        W_SOLID(         X[0], Y[0], ELEVATION,
                                         X[1], Y[1], ELEVATION,
                                         X[3], Y[3], ELEVATION,
                                         X[2], Y[2], ELEVATION,
                                         COLOR, LAYER_NAME );
                        W_SOLID(         X[7], Y[7], ELEVATION,
                                         X[4], Y[4], ELEVATION,
                                         X[6], Y[6], ELEVATION,
                                         X[5], Y[5], ELEVATION,
                                         COLOR, LAYER_NAME );
                        }
                else    {
                        for (int CS=0; CS<8; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 8 )
                                        ncs = 0;
                                W_LINE( X[CS], Y[CS], ELEVATION, X[ncs], Y[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                        }
                }
        }
else if (Type == tp_rect || (Type == tp_rndrect && R < BY_ZERO) )       //RECT
        {
        if( Hole > BY_ZERO )
                {
                float paramH[N_PARAM];
                for( int cp=0; cp<N_PARAM; cp++ )
                        paramH[cp] = PARAM[cp];
                paramH[0] = tp_round;
                paramH[1] = Hole;
                paramH[2] = Hole;
                paramH[3] = Hole/2.0;
                paramH[13] = 0.0;
                float X[16],Y[16];
                for (int CS=0; CS<16; CS++)
                        Generate_POINT (paramH , CS, &X[CS], &Y[CS]);
                if( Form3->RadioButton2->Checked )
                        for (int CS=0; CS<16; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 16 )
                                        ncs = 0;
                                W_LINE( X[CS], Y[CS], ELEVATION, X[ncs], Y[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                float RCTX[4],RCTY[4];
                for (int CS=0; CS<4; CS++)
                        Generate_POINT (PARAM , CS*4, &RCTX[CS], &RCTY[CS]);
                if( Form3->RadioButton2->Checked )
                        {
                        for (int CS=0; CS<4; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 4 )
                                        ncs = 0;
                                W_LINE( RCTX[CS], RCTY[CS], ELEVATION, RCTX[ncs], RCTY[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                        }
                else    {
                        for (int cs=0; cs<16; cs+=4)
                                {
                                int ib, ib2;
                                ib = cs - 1;
                                if( ib < 0 )
                                        ib = 15;
                                ib2 = cs - 4;
                                if( ib2 < 0 )
                                        ib2 = 12;

                                W_SOLID( X[cs], Y[cs], ELEVATION,
                                         X[ib], Y[ib], ELEVATION,
                                         RCTX[cs/4], RCTY[cs/4], ELEVATION,
                                         RCTX[ib2/4], RCTY[ib2/4], ELEVATION,
                                         COLOR, LAYER_NAME );
                                W_SOLID( X[cs], Y[cs], ELEVATION,
                                         X[cs+1], Y[cs+1], ELEVATION,
                                         RCTX[cs/4], RCTY[cs/4], ELEVATION,
                                         X[cs+2], Y[cs+2], ELEVATION,
                                         COLOR, LAYER_NAME );
                                W_SOLID( RCTX[cs/4], RCTY[cs/4], ELEVATION,
                                         X[cs+3], Y[cs+3], ELEVATION,
                                         RCTX[cs/4], RCTY[cs/4], ELEVATION,
                                         X[cs+2], Y[cs+2], ELEVATION,
                                         COLOR, LAYER_NAME );
                                }
                        }
                }
        else    {
                float X[4],Y[4];
                for (int CS=0; CS<4; CS++)
                        Generate_POINT (PARAM , CS*4, &X[CS], &Y[CS]);
                if( Form3->RadioButton2->Checked == 0 )
                        {
                        W_SOLID( X[0], Y[0], ELEVATION,
                         X[1], Y[1], ELEVATION,
                         X[3], Y[3], ELEVATION,
                         X[2], Y[2], ELEVATION,
                         COLOR, LAYER_NAME );
                        }
                else    {
                        W_LINE( X[0], Y[0], ELEVATION, X[1], Y[1], ELEVATION, COLOR, LAYER_NAME );
                        W_LINE( X[1], Y[1], ELEVATION, X[2], Y[2], ELEVATION, COLOR, LAYER_NAME );
                        W_LINE( X[2], Y[2], ELEVATION, X[3], Y[3], ELEVATION, COLOR, LAYER_NAME );
                        W_LINE( X[3], Y[3], ELEVATION, X[0], Y[0], ELEVATION, COLOR, LAYER_NAME );
                        }
                }
        }
else    //RND RECT AREA
        {
        if( Hole > BY_ZERO )
                {
                float paramH[N_PARAM];
                for( int cp=0; cp<N_PARAM; cp++ )
                        paramH[cp] = PARAM[cp];
                paramH[0] = tp_round;
                paramH[1] = Hole;
                paramH[2] = Hole;
                paramH[3] = Hole/2.0;
                paramH[13] = 0.0;
                float X[16],Y[16];
                for (int CS=0; CS<16; CS++)
                        Generate_POINT (paramH , CS, &X[CS], &Y[CS]);
                if( Form3->RadioButton2->Checked )
                        for (int CS=0; CS<16; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 16 )
                                        ncs = 0;
                                W_LINE( X[CS], Y[CS], ELEVATION, X[ncs], Y[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                float RCTX[16],RCTY[16];
                for (int CS=0; CS<16; CS++)
                        Generate_POINT (PARAM , CS, &RCTX[CS], &RCTY[CS]);
                if( Form3->RadioButton2->Checked )
                        {
                        for (int CS=0; CS<16; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 16 )
                                        ncs = 0;
                                W_LINE( RCTX[CS], RCTY[CS], ELEVATION, RCTX[ncs], RCTY[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                        }
                else    {
                        for (int cs=0; cs<16; cs++)
                                {
                                int ib, ib2;
                                ib = cs - 1;
                                if( ib < 0 )
                                        ib = 15;
                                W_SOLID( X[cs], Y[cs], ELEVATION,
                                         RCTX[cs], RCTY[cs], ELEVATION,
                                         X[ib], Y[ib], ELEVATION,
                                         RCTX[ib], RCTY[ib], ELEVATION,
                                         COLOR, LAYER_NAME );
                                }
                        }
                }
        else    {
                float RCTX[16],RCTY[16];
                for (int CS=0; CS<16; CS++)
                        Generate_POINT (PARAM , CS, &RCTX[CS], &RCTY[CS]);
                float x0 = (RCTX[0]+RCTX[8])/2.0;
                float y0 = (RCTY[4]+RCTY[12])/2.0;
                if( Form3->RadioButton2->Checked == 0 )
                        {
                        for (int cs=0; cs<16; cs+=2)
                                {
                                int n = cs + 2;
                                if( n >= 16 )
                                        n = 0;
                                W_SOLID( RCTX[cs], RCTY[cs], ELEVATION,
                                         RCTX[cs+1], RCTY[cs+1], ELEVATION,
                                         x0, y0, ELEVATION,
                                         RCTX[n], RCTY[n], ELEVATION,
                                         COLOR, LAYER_NAME );
                                }
                        }
                else    {
                        for (int CS=0; CS<16; CS++)
                                {
                                int ncs = CS+1;
                                if( ncs >= 16 )
                                        ncs = 0;
                                W_LINE( RCTX[CS], RCTY[CS], ELEVATION, RCTX[ncs], RCTY[ncs], ELEVATION, COLOR, LAYER_NAME );
                                }
                        }
                }
        }
}