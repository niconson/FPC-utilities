//---------------------------------------------------------------------------


#pragma hdrstop

#include "Generate_Cutout.h"
#include "Debug_Areas.h"
#include "ProcessMessages.h"
#include "fstream.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//==================
//��������� ��������
//==================
void Generate_Cutout (  float W,
                        float H,
                        float R,
                        float CanvasAng,
                        float IncrementAn,
                        float X,
                        float Y,
                        int n_board,
                        int R_mode)
        {
#define RIGHT_TOP       0
#define LEFT_TOP        1
#define LEFT_BOTTOM     2
#define RIGHT_BOTTOM    3
#define ALL             4
        bool bLine = 0;//ABS(W-H)>_2542;
        if( R_mode == ALL )
                R = MIN3(R,W/2-_2541,H/2-_2541);
        else
                R = MIN3(R,W-_2541,H-_2541);
        if (R < 0)
                R = 0;
        if (IncrementAn <= 0)   IncrementAn = 45;
        W = W/2;
        H = H/2;
        if( W<_104 || H<_104 )
                return;
        float min = DEFAULT;
        float max = -DEFAULT;
        long Back_X = DEFAULT;
        long Back_Y = DEFAULT;
        long First = CountLinesCut;
        float CurrentR;
        float CurrentAn = 0;
        if( R_mode == RIGHT_TOP || R_mode == ALL )
                CurrentR = R;
        else    CurrentR = 0;
        double Pt_X = CurrentR;
        double Pt_Y = 0;
        double px = W-CurrentR;
        double py = H-CurrentR;
        for( ; CurrentAn<(90.0+BY_ZERO); CurrentAn+=IncrementAn )
                {
                Pt_X = CurrentR;
                Pt_Y = 0;
                Rotate_Vertex (&Pt_X, &Pt_Y, CurrentAn);
                Pt_X += px;
                Pt_Y += py;
                Rotate_Vertex (&Pt_X, &Pt_Y, CanvasAng+90);
                Pt_X += X;
                Pt_Y += Y;
                if (Back_X<DEFAULT)
                //if (ABS(Pt_X - Back_X) > _2541 || ABS(Pt_Y - Back_Y) > _2541)
                        {
                        if( CurrentAn<(0.0+BY_ZERO) || bLine )
                                LinesCut[CountLinesCut].Arc = false;
                        else    LinesCut[CountLinesCut].Arc = true;
                        LinesCut[CountLinesCut].FlagDelete = 0;
                        LinesCut[CountLinesCut].FlagWrite = 0;
                        LinesCut[CountLinesCut].n_board = n_board;
                        LinesCut[CountLinesCut].First = First;
                        LinesCut[CountLinesCut].X1 = Back_X;
                        LinesCut[CountLinesCut].Y1 = Back_Y;
                        LinesCut[CountLinesCut].X2 = Pt_X;
                        LinesCut[CountLinesCut].Y2 = Pt_Y;
                        LinesCut[CountLinesCut].n_thermal = -1;
                        CountLinesCut++;
                        }
                Back_X = Pt_X;
                Back_Y = Pt_Y;
                min = MIN(Pt_X,min);
                max = MAX(Pt_X,max);
                }
        CurrentAn = 90;
        if( R_mode == LEFT_TOP || R_mode == ALL )
                CurrentR = R;
        else    CurrentR = 0;
        px = -W+CurrentR;
        py = H-CurrentR;
        for( ; CurrentAn<(180.0+BY_ZERO); CurrentAn+=IncrementAn )
                {
                Pt_X = CurrentR;
                Pt_Y = 0;
                Rotate_Vertex (&Pt_X, &Pt_Y, CurrentAn);
                Pt_X += px;
                Pt_Y += py;
                Rotate_Vertex (&Pt_X, &Pt_Y, CanvasAng+90);
                Pt_X += X;
                Pt_Y += Y;
                if (Back_X<DEFAULT)
                //if (ABS(Pt_X - Back_X) > _2541 || ABS(Pt_Y - Back_Y) > _2541)
                        {
                        if( CurrentAn<(90.0+BY_ZERO) || bLine )
                                LinesCut[CountLinesCut].Arc = false;
                        else    LinesCut[CountLinesCut].Arc = true;
                        LinesCut[CountLinesCut].FlagDelete = 0;
                        LinesCut[CountLinesCut].FlagWrite = 0;
                        LinesCut[CountLinesCut].n_board = n_board;
                        LinesCut[CountLinesCut].First = First;
                        LinesCut[CountLinesCut].X1 = Back_X;
                        LinesCut[CountLinesCut].Y1 = Back_Y;
                        LinesCut[CountLinesCut].X2 = Pt_X;
                        LinesCut[CountLinesCut].Y2 = Pt_Y;
                        LinesCut[CountLinesCut].n_thermal = -1;
                        CountLinesCut++;
                        }
                Back_X = Pt_X;
                Back_Y = Pt_Y;
                min = MIN(Pt_X,min);
                max = MAX(Pt_X,max);
                }
        CurrentAn = 180;
        if( R_mode == LEFT_BOTTOM || R_mode == ALL )
                CurrentR = R;
        else    CurrentR = 0;
        Pt_X = CurrentR;
        Pt_Y = 0;
        px = -W+CurrentR;
        py = -H+CurrentR;
        for( ; CurrentAn<(270.0+BY_ZERO); CurrentAn+=IncrementAn )
                {
                Pt_X = CurrentR;
                Pt_Y = 0;
                Rotate_Vertex (&Pt_X, &Pt_Y, CurrentAn);
                Pt_X += px;
                Pt_Y += py;
                Rotate_Vertex (&Pt_X, &Pt_Y, CanvasAng+90);
                Pt_X += X;
                Pt_Y += Y;
                if (Back_X<DEFAULT)
                //if (ABS(Pt_X - Back_X) > _2541 || ABS(Pt_Y - Back_Y) > _2541)
                        {
                        if( CurrentAn<(180.0+BY_ZERO) || bLine )
                                LinesCut[CountLinesCut].Arc = false;
                        else    LinesCut[CountLinesCut].Arc = true;
                        LinesCut[CountLinesCut].FlagDelete = 0;
                        LinesCut[CountLinesCut].FlagWrite = 0;
                        LinesCut[CountLinesCut].n_board = n_board;
                        LinesCut[CountLinesCut].First = First;
                        LinesCut[CountLinesCut].X1 = Back_X;
                        LinesCut[CountLinesCut].Y1 = Back_Y;
                        LinesCut[CountLinesCut].X2 = Pt_X;
                        LinesCut[CountLinesCut].Y2 = Pt_Y;
                        LinesCut[CountLinesCut].n_thermal = -1;
                        CountLinesCut++;
                        }
                Back_X = Pt_X;
                Back_Y = Pt_Y;
                min = MIN(Pt_X,min);
                max = MAX(Pt_X,max);
                }
        CurrentAn = 270;
        if( R_mode == RIGHT_BOTTOM || R_mode == ALL )
                CurrentR = R;
        else    CurrentR = 0;
        Pt_X = CurrentR;
        Pt_Y = 0;
        px = W-CurrentR;
        py = -H+CurrentR;
        for( ; CurrentAn<(360.0+BY_ZERO); CurrentAn+=IncrementAn )
                {
                Pt_X = CurrentR;
                Pt_Y = 0;
                Rotate_Vertex (&Pt_X, &Pt_Y, CurrentAn);
                Pt_X += px;
                Pt_Y += py;
                Rotate_Vertex (&Pt_X, &Pt_Y, CanvasAng+90);
                Pt_X += X;
                Pt_Y += Y;
                if (Back_X<DEFAULT)
                //if (ABS(Pt_X - Back_X) > _2541 || ABS(Pt_Y - Back_Y) > _2541)
                        {
                        if( CurrentAn<(270.0+BY_ZERO) || bLine )
                                LinesCut[CountLinesCut].Arc = false;
                        else    LinesCut[CountLinesCut].Arc = true;
                        LinesCut[CountLinesCut].FlagDelete = 0;
                        LinesCut[CountLinesCut].FlagWrite = 0;
                        LinesCut[CountLinesCut].n_board = n_board;
                        LinesCut[CountLinesCut].First = First;
                        LinesCut[CountLinesCut].X1 = Back_X;
                        LinesCut[CountLinesCut].Y1 = Back_Y;
                        LinesCut[CountLinesCut].X2 = Pt_X;
                        LinesCut[CountLinesCut].Y2 = Pt_Y;
                        LinesCut[CountLinesCut].n_thermal = -1;
                        CountLinesCut++;
                        }
                Back_X = Pt_X;
                Back_Y = Pt_Y;
                min = MIN(Pt_X,min);
                max = MAX(Pt_X,max);
                }

        // end points
        //if (ABS(Pt_X - LinesCut[First].X1) > _2541 || ABS(Pt_Y - LinesCut[First].Y1) > _2541)
        //        {
                LinesCut[CountLinesCut].Arc = false;
                LinesCut[CountLinesCut].FlagDelete = 0;
                LinesCut[CountLinesCut].FlagWrite = 0;
                LinesCut[CountLinesCut].n_board = n_board;
                LinesCut[CountLinesCut].First = First;
                LinesCut[CountLinesCut].X1 = Pt_X;
                LinesCut[CountLinesCut].Y1 = Pt_Y;
                LinesCut[CountLinesCut].X2 = LinesCut[First].X1;
                LinesCut[CountLinesCut].Y2 = LinesCut[First].Y1;
                LinesCut[CountLinesCut].n_thermal = -1;
                min = MIN(Pt_X,min);
                max = MAX(Pt_X,max);
                CountLinesCut++;
        //        }   
        min = MIN(LinesCut[First].X1,min);
        max = MAX(LinesCut[First].X1,max);
        LinesCut[First].Bounds = min;
        LinesCut[First+1].Bounds = max;
        if( R_mode != ALL )
                {
                LinesCut[First].n_thermal = nTHERMAL;
                nTHERMAL+=1;
                }
        else    LinesCut[First].n_thermal = -1;
        LinesCut[CountLinesCut].First = CountLinesCut;
#undef RIGHT_TOP
#undef LEFT_TOP
#undef LEFT_BOTTOM
#undef RIGHT_BOTTOM
#undef ALL
        }