//---------------------------------------------------------------------------


#pragma hdrstop

#include "Print_Part.h"
#include "To_DXF.h"
#include "Options.h"
#include "DXF_library.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)








//---------------------------------------------------------------------------
long Set_cursor ( AnsiString StrinG, int start_index, int break_index )
{
        AnsiString CUR;
        if (StrinG.SubString((StrinG.Length()-2),3) == "...")
                {
                StrinG = StrinG.SubString(1,(StrinG.Length()-3));
                AnsiString CUR = Form1->File->Items->operator [](start_index);
                CUR = CUR.Trim();
                int shift = 0;
                int Length1 = StrinG.Length();
                int Length2 = MIN(StrinG.Length(),CUR.Length());
                while (CUR.SubString(1,Length2) != StrinG.SubString(1,Length1))
                        {
                        shift++;
                        if ((shift+start_index) >= Form1->File->Items->Count)
                                return 0;
                        if (break_index)
                                if ((shift+start_index) > break_index)
                                        return 0;
                        CUR = Form1->File->Items->operator [](start_index + shift);
                        CUR = CUR.Trim();
                        Length2 = MIN(StrinG.Length(),CUR.Length());
                        }
                return (start_index + shift);
                }
        else    {
                int Length1 = StrinG.Length();
                int Length2;
                for( int i=0; LABELS[i]>0; i++ )
                        {
                        if( LABELS[i] < start_index )
                                continue;
                        if( LABELS[i] > break_index )
                                return 0;
                        CUR = Form1->File->Items->operator [](LABELS[i]);
                        CUR = CUR.Trim();
                        Length2 = CUR.Length();
                        if (CUR.SubString(1,Length2) == StrinG.SubString(1,Length1) )
                                return LABELS[i];
                        }
                return 0;
                }

}
//---------------------------------------------------------------------------










//---------------------------------------------------------------------------
TPoint Print_Part (AnsiString Part, bool GetPos)
{
  AnsiString S;
  long n_str;
  long i;
  long HOLE;
  float X_pos;
  float Y_pos;
  float Vertex_Of_Lines[99];
  float X__1;
  float Y__1;
  float X__2;
  float Y__2;
  float X_P;
  float Y_P;
  long A_P;
  long A_Prt;
  long side;
  float First_X;
  float First_Y;
  long type_L;
  float W_Line;
  float SM = (float)default_mask_clearance;      // SM cutouts
  float PM = (float)default_paste_clearance;     // paste
  AnsiString Num_pin;
  AnsiString WR_foot;
  //
  //
  //
  n_str = Set_cursor (("part: " + Part), IndexParts, IndexNets);
  TPoint Position(0,0);
  if (n_str <= 0)
        return Position;
  int StrPart = n_str;
  int i_next_part = Set_cursor ("part:...", StrPart+1, IndexNets);
  n_str = Set_cursor ("pos...", StrPart, IndexNets);
  if (n_str > i_next_part && i_next_part > 0)
        return Position;
  S = Form1->File->Items->operator [](n_str);
  i = prob (S, 1 );
  X_pos = ex_float (S, &i )/(float)_106;
  Y_pos = ex_float (S, &i )/(float)_106;
  Position.x = X_pos;
  Position.y = Y_pos;
  if (GetPos)
        return Position;
  side = ex_float (S, &i );
  A_Prt = ex_float (S, &i );
  //
  n_str = Set_cursor ("shape...", StrPart, IndexNets);
  if (n_str <= 0)
        return Position;
  if (n_str > i_next_part && i_next_part > 0)
        return Position;
  S = Form1->File->Items->operator [](n_str);
  i = prob (S, 1 );
  S = ex_str (S, &i );
  AnsiString Sh = S;
  S = AnsiString("name: \"") + S + "\"";
  n_str = Set_cursor (S, IndexFoot, IndexBoard );
  if (n_str <= 0)
        return Position;
  int i_pack = Set_cursor ("package:...", n_str, IndexBoard );
  int i_next_name = Set_cursor ("name:...", n_str+1, IndexBoard );
  AnsiString NameBlk="";
  if (i_pack > n_str)
        if (i_pack < i_next_name || !i_next_name)
                {
                S = Form1->File->Items->operator [](i_pack);
                i = prob (S, 1 );
                S = ex_str (S, &i );
                NameBlk = S;
                // MOD_NameBlk ( delete .,_- )
                MOD(&NameBlk);
                }
  if(NameBlk.Length())
        {
         // draw model (3dFaces)
        AnsiString Blk = NameBlk;
        if (!side) Blk += "_top";
        else       Blk += "_bot";
        myRect sr;
        int Rotate = 0;
        int Clr_3D = Form1->NamesOfBlocks->Items->IndexOf(Blk);
        if (Clr_3D == -1 &&
           ((Form1->CheckBox14->Checked && !side) || (Form1->CheckBox15->Checked && side)) )
              {
              Form1->Blocks->Items->Add("0");
              Form1->Blocks->Items->Add("BLOCK");
              Form1->Blocks->Items->Add("2");
              Form1->Blocks->Items->Add(Blk);
              Form1->Blocks->Items->Add("10");
              Form1->Blocks->Items->Add("0");
              Form1->Blocks->Items->Add("20");
              Form1->Blocks->Items->Add("0");
              Form1->Blocks->Items->Add("30");
              Form1->Blocks->Items->Add("0");
              int Ptr;
              int i_branch =  Form2->StringGrid1->Cols[PACKAGES]->IndexOf(NameBlk);
              if (i_branch == -1)
                      {
                      if( NO_PACKAGE.Pos(Sh) < 1 )
                              NO_PACKAGE += ("\n     " + Sh);
                      }
              else    {
                      int i_head = i_branch;
                      int MIN_GRID_INDEX = i_branch;
                      int MAX_GRID_INDEX = i_branch;
                      S =  Form2->StringGrid1->Cells[PACKAGES][i_branch];
                      while (S.LowerCase().SubString(1,S.Length()) == NameBlk.LowerCase().SubString(1,NameBlk.Length()))
                              {
                              MAX_GRID_INDEX++;
                              S = Form2->StringGrid1->Cells[PACKAGES][MAX_GRID_INDEX];
                              }
                      MAX_GRID_INDEX--;
                      JumpData_struct JumpData[NUMBER_OF_TJumps];
                      for (int q=0; q<NUMBER_OF_TJumps; q++)
                              {
                              JumpData[q].J =   JUMP_NOT_FOUND;
                              JumpData[q].min = JUMP_NOT_FOUND;
                              JumpData[q].max = JUMP_NOT_FOUND;
                              }
                      InsertBlock (0, 0, 0, &sr, RESET, 0, 0, 0);
                      int fB = n_str;
                      do      {
                              while ((Ptr = InsertBlock (fB, Rotate, side, &sr, i_head, i_branch, MIN_GRID_INDEX, MAX_GRID_INDEX)) == WARNING_OF_MEMORY)
                                      {
                                      MAX_FACES_AND_LINES = SwellMem()-99;
                                      }
                              if (Ptr == JUMP_NOT_FOUND)
                                      {
                                      i_branch = JumpData[0].J+1;
                                      i_head =   JumpData[0].J;
                                      for (int t=1; JumpData[t].J>0; t++)
                                              i_head = JumpData[t].J;
                                      MIN_GRID_INDEX = JumpData[0].min;
                                      MAX_GRID_INDEX = JumpData[0].max;
                                      for (int d=0; d<(NUMBER_OF_TJumps-1); d++)
                                              {    //removing
                                              JumpData[d].J = JumpData[d+1].J;
                                              JumpData[d].min = JumpData[d+1].min;
                                              JumpData[d].max = JumpData[d+1].max;
                                              }
                                      JumpData[NUMBER_OF_TJumps-1].J = JUMP_NOT_FOUND;
                                      }
                              else    {
                                      for (int d=(NUMBER_OF_TJumps-1); d>0; d--)
                                              {    //writing
                                              JumpData[d].J = JumpData[d-1].J;
                                              JumpData[d].min = JumpData[d-1].min;
                                              JumpData[d].max = JumpData[d-1].max;
                                              }
                                      JumpData[0].J = Ptr;
                                      JumpData[0].min = MIN_GRID_INDEX;
                                      JumpData[0].max = MAX_GRID_INDEX;
                                      S = Form2->StringGrid1->Cells[SHAPE][JumpData[0].J];
                                      NameBlk = S;
                                      i_branch = Form2->StringGrid1->Cols[PACKAGES]->IndexOf(S);
                                      MIN_GRID_INDEX = i_branch;
                                      MAX_GRID_INDEX = i_branch;
                                      while (S.LowerCase().SubString(1,S.Length()) == NameBlk.LowerCase().SubString(1,NameBlk.Length()))
                                              {
                                              MAX_GRID_INDEX++;
                                              S = Form2->StringGrid1->Cells[PACKAGES][MAX_GRID_INDEX];
                                              }
                                      MAX_GRID_INDEX--;
                                      i_head =   JumpData[0].J;
                                      for (int t=1; JumpData[t].J>0; t++)
                                              i_head = JumpData[t].J;
                                      fB = Form2->GetFootBeg( NameBlk );
                                      if( fB == -1 )
                                                fB = n_str;
                                      }
                              }while (i_branch > 0 && NameBlk.Length());
                      Clr_3D = CLR;
                      Form1->Blocks->Items->Add("0");
                      Form1->Blocks->Items->Add("ENDBLK");
                      }
              }
        else  if ((Form1->CheckBox14->Checked && !side) || (Form1->CheckBox15->Checked && side))
              Clr_3D = StrToInt(Form1->NamesOfBlocks->Items->operator [](Clr_3D+1));
        // insert model
        if ((Form1->CheckBox14->Checked && !side) || (Form1->CheckBox15->Checked && side))
              {
              //INSERT BLK : NameBlk
              int Ang = A_Prt + Rotate;
              Form1->OutputBox->Items->Add("0");
              Form1->OutputBox->Items->Add("INSERT");
              Form1->OutputBox->Items->Add("2");
              Form1->OutputBox->Items->Add(Blk);
              Form1->OutputBox->Items->Add("8");
              if (side)
                      Form1->OutputBox->Items->Add(LB);
              else    Form1->OutputBox->Items->Add(LT);
              Form1->OutputBox->Items->Add("62");
              Form1->OutputBox->Items->Add(AnsiString(Clr_3D));
              Ang = 360-Ang;
              Form1->OutputBox->Items->Add("10");
              Form1->OutputBox->Items->Add(F_str(X_pos));
              Form1->OutputBox->Items->Add("20");
              Form1->OutputBox->Items->Add(F_str(Y_pos));
              Form1->OutputBox->Items->Add("50");
              Form1->OutputBox->Items->Add(F_str(Ang));
              }
        }
  // draw footprint
  if(n_str > 0)
        {
        bool bLINE_EN = 0;
        int Units_MM = 0;
        int InPin = 0;
        int llay = 0;
        n_str++;
        S = Form1->File->Items->operator [](n_str);
        while (1)
              {
              if (S.SubString(1,6) == "units:")
                      {
                      i = prob(S,1);
                      if (S.UpperCase().SubString(i,2) == "NM")      Units_MM = 0;
                      else if (S.UpperCase().SubString(i,2) == "MI") Units_MM = 1;
                      else                                           Units_MM = 2;
                      }
              else if (S.SubString(1,7) == "outline")
                      {
                      i = prob(S,1);
                      W_Line  = ex_float(S, &i);              //W
                      X__1 = ex_float(S, &i);                 //X
                      Y__1 = ex_float(S, &i);                 //Y
                      int vis = ex_float(S, &i);              //vis
                      if(!vis)
                        bLINE_EN = 0;
                      else
                        bLINE_EN = 1;
                      int hatch = ex_float(S, &i);            //hatch
                      llay = ex_float(S, &i);             //llay
                      if (Units_MM == 1)
                              {
                              W_Line = W_Line*INV_PER_MIL;
                              X__1 =     X__1*INV_PER_MIL;
                              Y__1 =     Y__1*INV_PER_MIL;
                              }
                      else if (Units_MM == 0)
                              {
                              W_Line = W_Line/_106;
                              X__1 =     X__1/_106;
                              Y__1 =     Y__1/_106;
                              }
                      First_X = X__1;
                      First_Y = Y__1;
                      }
              else if ( bLINE_EN && (S.SubString(1,5) == "next_" || S.SubString(1,6) == "close_")  )
                      {
                      if (S.SubString(1,5) == "next_")
                              {
                              i = prob(S,1);
                              X__2 = ex_float(S, &i);                 //X
                              Y__2 = ex_float(S, &i);                 //Y
                              type_L = ex_float(S, &i);               //type_L
                              if (Units_MM == 1)
                                      {
                                      X__2 =     X__2*INV_PER_MIL;
                                      Y__2 =     Y__2*INV_PER_MIL;
                                      }
                              else if (Units_MM == 0)
                                      {
                                      X__2 =     X__2/_106;
                                      Y__2 =     Y__2/_106;
                                      }
                              }
                      else    {
                              X__2 = First_X;                         //X
                              Y__2 = First_Y;                         //Y
                              i = prob(S, 1);
                              type_L = ex_float(S, &i);               //type_L
                              }
                      float X__1S = X__1;
                      float Y__1S = Y__1;
                      float X__2S = X__2;
                      float Y__2S = Y__2;
                      mirror_angle (A_Prt, side, &X__1S, &Y__1S);
                      mirror_angle (A_Prt, side, &X__2S, &Y__2S);
                      X__1S += X_pos;
                      Y__1S += Y_pos;
                      X__2S += X_pos;
                      Y__2S += Y_pos;
                      int type_LS = type_L;
                      if      (side && type_L == 1)   type_LS = 2;
                      else if (side && type_L == 2)   type_LS = 1;
                      long  L = Generate_Line (X__1S, Y__1S, X__2S, Y__2S, type_LS, &Vertex_Of_Lines[0]);
                      for (int h=0; h <= (L-4); h = h+2)
                              {
                              AnsiString s_l;
                              int c_l;
                              if (llay == FP_TOP_COPPER || llay == FP_BOT_COPPER)
                                        {
                                        if (!side)
                                                {
                                                c_l = CL_TOPPADS;
                                                s_l = "top_pads";
                                                }
                                        else    {
                                                c_l = CL_BOTPADS;
                                                s_l = "bottom_pads";
                                                }
                                        }
                              else      {
                                        if (!side)
                                                {
                                                c_l = CL_TOPSILK;
                                                s_l = "top_silk";
                                                }
                                        else    {
                                                c_l = CL_BOTSILK;
                                                s_l = "bottom_silk";
                                                }
                                        }
                              W_LWPOLYLINE( Vertex_Of_Lines[h], Vertex_Of_Lines[h+1],
                                                      Vertex_Of_Lines[h+2], Vertex_Of_Lines[h+3],
                                                      W_Line, 0, BoardThick, 0, c_l, s_l );
                              }
                      X__1 = X__2;
                      Y__1 = Y__2;
                      }
              else if (S.SubString(1,3) == "pin")
                      {
                      i = prob (S, 1 );
                      Num_pin =       ex_str (S, &i );
                      HOLE =          ex_float (S, &i );
                      X_P =           ex_float (S, &i );
                      Y_P =           ex_float (S, &i );
                      A_P =           ex_float (S, &i );
                      if (HOLE > BY_ZERO)
                              {
                              float PHOLE = HOLE;
                              float PX_P = X_P;
                              float PY_P = Y_P;
                              if (Units_MM == 1)
                                      {
                                      PX_P =  PX_P*INV_PER_MIL;
                                      PY_P =  PY_P*INV_PER_MIL;
                                      PHOLE = PHOLE*INV_PER_MIL;
                                      }
                              else if (Units_MM == 0)
                                      {
                                      PX_P =  PX_P/_106;
                                      PY_P =  PY_P/_106;
                                      PHOLE = PHOLE/_106;
                                      }
                              mirror_angle(A_Prt, side, &PX_P, &PY_P);
                              PX_P += X_pos;
                              PY_P += Y_pos;
                              ///W_LWPOLYLINE(PX_P,PY_P,PX_P,PY_P,PHOLE,0,0,BoardThick,CL_HOLES,0,"pad_holes");
                              ///W_LWPOLYLINE(PX_P,PY_P,PX_P,PY_P,PHOLE,0,BoardThick,0,CL_HOLES,0,"pad_holes");
                              float currX;
                              float currY;
                              float nextX;
                              float nextY;
                              for (int An = 0; An < 360; An = An + 30)
                                      {
                                      currX = PX_P + PHOLE/(float)2*cos((float)An*M_PI/180.0);
                                      currY = PY_P + PHOLE/(float)2*sin((float)An*M_PI/180.0);
                                      nextX = PX_P + PHOLE/(float)2*cos((float)(An + 30)*M_PI/180.0);
                                      nextY = PY_P + PHOLE/(float)2*sin((float)(An + 30)*M_PI/180.0);
                                      W_SOLID(        currX,currY,0,
                                                      nextX,nextY,0,
                                                      currX,currY,BoardThick,
                                                      nextX,nextY,BoardThick,CL_HOLES,"pad_holes");
                                      }
                              W_LINE(PX_P, PY_P, 0, PX_P, PY_P, BoardThick, CL_HOLES,"pad_holes");
                              }
                      }
              else if (S.SubString(1,7) == "top_pad")
                      {
                      i = prob (S, 1 );
                      int Type_top = ex_float (S, &i );       //
                      float W_top = ex_float (S, &i );       // W
                      float L_top = ex_float (S, &i );       // L
                      L_top = ex_float (S, &i );              // L
                      L_top = L_top*2;
                      if (!L_top) L_top = W_top;
                      float R_top = ex_float (S, &i );       // Rad
                      if (Type_top == 6)
                              {
                              W_top = W_top*cos(22.5*M_PI/(float)180);
                              R_top = W_top/(2 + sqrt(2));
                              L_top = W_top;
                              }
                      //
                      float PARAM_TOP[N_PARAM];
                      PARAM_TOP[0] = Type_top;
                      PARAM_TOP[1] = W_top;
                      PARAM_TOP[2] = L_top;
                      PARAM_TOP[3] = R_top;
                      PARAM_TOP[4] = A_Prt;
                      PARAM_TOP[5] = A_P;
                      PARAM_TOP[6] = 0;
                      PARAM_TOP[7] = X_P;
                      PARAM_TOP[8] = Y_P;
                      PARAM_TOP[9] = X_pos;
                      PARAM_TOP[10] = Y_pos;
                      if (side) PARAM_TOP[11] = 3;       //bottom
                      else      PARAM_TOP[11] = 0;       //top
                      PARAM_TOP[12] = (float)InPin;
                      PARAM_TOP[13] = HOLE;
                      if (side) Canvas_Pads ( &PARAM_TOP[0] , "bottom_pads", Units_MM, CL_BOTPADS);
                      else      Canvas_Pads ( &PARAM_TOP[0] , "top_pads", Units_MM, CL_TOPPADS);
                      //Generate SM cutout
                      PARAM_TOP[0] = Type_top;
                      float SMT = SM;
                      float PMT = PM;
                      if (Units_MM == 1)
                              {
                              SMT =     SM/PER_MIL;
                              PMT =     PM/PER_MIL;
                              }
                      else if (Units_MM == 2)
                              {
                              SMT =     SM/_106;
                              PMT =     PM/_106;
                              }
                      PARAM_TOP[1] = W_top + SMT*(float)2;
                      PARAM_TOP[2] = L_top + SMT*(float)2;
                      PARAM_TOP[3] = R_top + SMT;
                      if (Type_top == 6)
                              {
                              PARAM_TOP[3] = PARAM_TOP[1]/(2 + sqrt(2));
                              }
                      // SM
                      AnsiString Read_mask;
                      for (int x=0; x<9; x++)
                              {
                              Read_mask = Form1->File->Items->operator [](n_str + x);
                              if (Read_mask.SubString(1,3) == "pin") break;
                              if (Read_mask.SubString(1,8) == "top_mask")
                                      {
                                      i = prob (Read_mask, 1 );
                                      PARAM_TOP[0] = ex_float (Read_mask, &i );       //
                                      PARAM_TOP[1] = ex_float (Read_mask, &i );       // W
                                      PARAM_TOP[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_TOP[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_TOP[2] = PARAM_TOP[2]*2;
                                      PARAM_TOP[3] = ex_float (Read_mask, &i );       // Rad
                                      break;
                                      }
                              }
                      if (side) Canvas_Pads ( &PARAM_TOP[0] , "bottom_mask", Units_MM, CL_BOTMASK);
                      else      Canvas_Pads ( &PARAM_TOP[0] , "top_mask", Units_MM, CL_TOPMASK);
                      //Generate PASTE
                      PARAM_TOP[0] = Type_top;
                      PARAM_TOP[1] = W_top - PMT*(float)2;
                      PARAM_TOP[2] = L_top - PMT*(float)2;
                      PARAM_TOP[3] = R_top - PMT;
                      if (Type_top == 6)
                              {
                              PARAM_TOP[3] = PARAM_TOP[1]/(2 + sqrt(2));
                              }
                      if (HOLE > BY_ZERO) PARAM_TOP[0] = 0;
                      // PASTE
                      for (int x=0; x<9; x++)
                              {
                              Read_mask = Form1->File->Items->operator [](n_str + x);
                              if (Read_mask.SubString(1,3) == "pin") break;
                              if (Read_mask.SubString(1,9) == "top_paste")
                                      {
                                      i = prob (Read_mask, 1 );
                                      PARAM_TOP[0] = ex_float (Read_mask, &i );       //
                                      PARAM_TOP[1] = ex_float (Read_mask, &i );       // W
                                      PARAM_TOP[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_TOP[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_TOP[2] = PARAM_TOP[2]*2;
                                      PARAM_TOP[3] = ex_float (Read_mask, &i );       // Rad
                                      break;
                                      }
                              }
                      if (side) Canvas_Pads ( &PARAM_TOP[0] , "bottom_paste", Units_MM, CL_BOTPASTE);
                      else      Canvas_Pads ( &PARAM_TOP[0] , "top_paste", Units_MM, CL_TOPPASTE);
                      }
              else if (S.SubString(1,10) == "bottom_pad")
                      {
                      i = prob (S, 1 );
                      int Type_bot = ex_float (S, &i );       //
                      float W_bot = ex_float (S, &i );       // W
                      float L_bot = ex_float (S, &i );       // L
                      L_bot = ex_float (S, &i );              // L
                      L_bot = L_bot*2;
                      if (!L_bot) L_bot = W_bot;
                      float R_bot = ex_float (S, &i );       // Rad
                      if (Type_bot == 6)
                              {
                              W_bot = W_bot*cos(22.5*M_PI/(float)180);
                              R_bot = W_bot/(2 + sqrt(2));
                              L_bot = W_bot;
                              }
                      //-------
                      float PARAM_BOT[N_PARAM];
                      PARAM_BOT[0] = Type_bot;
                      PARAM_BOT[1] = W_bot;
                      PARAM_BOT[2] = L_bot;
                      PARAM_BOT[3] = R_bot;
                      PARAM_BOT[4] = A_Prt;
                      PARAM_BOT[5] = A_P;
                      PARAM_BOT[6] = 0;
                      PARAM_BOT[7] = X_P;
                      PARAM_BOT[8] = Y_P;
                      PARAM_BOT[9] = X_pos;
                      PARAM_BOT[10] = Y_pos;
                      if (side) PARAM_BOT[11] = 2;       //top
                      else      PARAM_BOT[11] = 1;       //bottom
                      PARAM_BOT[12] = (float)InPin;
                      PARAM_BOT[13] = HOLE;
                      if (side) Canvas_Pads ( &PARAM_BOT[0] , "top_pads", Units_MM, CL_TOPPADS);
                      else      Canvas_Pads ( &PARAM_BOT[0] , "bottom_pads", Units_MM, CL_BOTPADS);
                      //Generate SM cutout
                      PARAM_BOT[0] = Type_bot;
                      float SMB = SM;
                      float PMB = PM;
                      if (Units_MM == 1)
                              {
                              SMB =     SM/PER_MIL;
                              PMB =     PM/PER_MIL;
                              }
                      else if (Units_MM == 2)
                              {
                              SMB =     SM/_106;
                              PMB =     PM/_106;
                              }
                      PARAM_BOT[1] = W_bot + SMB*(float)2;
                      PARAM_BOT[2] = L_bot + SMB*(float)2;
                      PARAM_BOT[3] = R_bot + SMB;
                      if (Type_bot == 6)
                              {
                              PARAM_BOT[3] = PARAM_BOT[1]/(2 + sqrt(2));
                              }
                      // SM
                      AnsiString Read_mask;
                      for (int x=0; x<9; x++)
                              {
                              Read_mask = Form1->File->Items->operator [](n_str + x);
                              if (Read_mask.SubString(1,3) == "pin") break;
                              if (Read_mask.SubString(1,11) == "bottom_mask")
                                      {
                                      i = prob (Read_mask, 1 );
                                      PARAM_BOT[0] = ex_float (Read_mask, &i );       //
                                      PARAM_BOT[1] = ex_float (Read_mask, &i );       // W
                                      PARAM_BOT[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_BOT[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_BOT[2] = PARAM_BOT[2]*2;
                                      PARAM_BOT[3] = ex_float (Read_mask, &i );       // Rad
                                      break;
                                      }
                              }
                      if (side) Canvas_Pads ( &PARAM_BOT[0] , "top_mask", Units_MM, CL_TOPMASK);
                      else      Canvas_Pads ( &PARAM_BOT[0] , "bottom_mask", Units_MM, CL_BOTMASK);
                      //Generate PASTE
                      PARAM_BOT[0] = Type_bot;
                      PARAM_BOT[1] = W_bot - PMB*(float)2;
                      PARAM_BOT[2] = L_bot - PMB*(float)2;
                      PARAM_BOT[3] = R_bot - PMB;
                      if (Type_bot == 6)
                              {
                              PARAM_BOT[3] = PARAM_BOT[1]/(2 + sqrt(2));
                              }
                      if (HOLE > BY_ZERO) PARAM_BOT[0] = 0;
                      // PASTE
                      for (int x=0; x<9; x++)
                              {
                              Read_mask = Form1->File->Items->operator [](n_str + x);
                              if (Read_mask.SubString(1,3) == "pin") break;
                              if (Read_mask.SubString(1,12) == "bottom_paste")
                                      {
                                      i = prob (Read_mask, 1 );
                                      PARAM_BOT[0] = ex_float (Read_mask, &i );       //
                                      PARAM_BOT[1] = ex_float (Read_mask, &i );       // W
                                      PARAM_BOT[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_BOT[2] = ex_float (Read_mask, &i );       // L
                                      PARAM_BOT[2] = PARAM_BOT[2]*2;
                                      PARAM_BOT[3] = ex_float (Read_mask, &i );       // Rad
                                      break;
                                      }
                              }
                      if (side) Canvas_Pads ( &PARAM_BOT[0] , "top_paste", Units_MM, CL_TOPPASTE);
                      else      Canvas_Pads ( &PARAM_BOT[0] , "bottom_paste", Units_MM, CL_BOTPASTE);
                      }
              else if (S.SubString(1,9) == "inner_pad")       {;}
              else if (S.SubString(1,8) == "top_mask")        {;}
              else if (S.SubString(1,9) == "top_paste")       {;}
              else if (S.SubString(1,11) == "bottom_mask")    {;}
              else if (S.SubString(1,12) == "bottom_paste")   {;}
              n_str++;
              S = Form1->File->Items->operator [](n_str);
              if (S.Length() == 0 )                   break;
              if (S.SubString(1,4) == "name" )        break;
              if (S.SubString(1,7) == "[board]" )     break;
              }
        }
 return Position;
}