//---------------------------------------------------------------------------


#pragma hdrstop

#include "W_SOLID_BLK.h"
#include "To_DXF.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void W_SOLID_BLK (  float x1,
                float y1,
                float z1,
                float x2,
                float y2,
                float z2,
                float x3,
                float y3,
                float z3,
                float x4,
                float y4,
                float z4,
                int Color,
                AnsiString Layer
                )
        {
        switch (Color)
                {
                case CL_BOARD:          if (!Form1->CheckBox1->Checked)return;
                                        break;
                case CL_TOPPADS:        if (!Form1->CheckBox2->Checked)return;
                                        break;
                case CL_TOPLINES:       if (!Form1->CheckBox3->Checked)return;
                                        break;
                case CL_TOPAREAS:       if (!Form1->CheckBox4->Checked)return;
                                        break;
                case CL_TOPMASK:        if (!Form1->CheckBox5->Checked)return;
                                        break;
                case CL_TOPPASTE:       if (!Form1->CheckBox6->Checked)return;
                                        break;
                case CL_TOPSILK:        if (!Form1->CheckBox7->Checked)return;
                                        break;
                case CL_BOTPADS:        if (!Form1->CheckBox8->Checked)return;
                                        break;
                case CL_BOTLINES:       if (!Form1->CheckBox9->Checked)return;
                                        break;
                case CL_BOTAREAS:       if (!Form1->CheckBox10->Checked)return;
                                        break;
                case CL_BOTMASK:        if (!Form1->CheckBox11->Checked)return;
                                        break;
                case CL_BOTPASTE:       if (!Form1->CheckBox12->Checked)return;
                                        break;
                case CL_BOTSILK:        if (!Form1->CheckBox13->Checked)return;
                                        break;
                //case CL_3DTOP:          if (!Form1->CheckBox14->Checked)return;
                //                        break;
                //case CL_3DBOTTOM:       if (!Form1->CheckBox15->Checked)return;
                //                        break;
                case CL_VIAS:           if (!Form1->CheckBox16->Checked)return;
                                        break;
                case CL_VIA_HOLES:      if (!Form1->CheckBox18->Checked)return;
                                        break;
                case CL_HOLES:          if (!Form1->CheckBox17->Checked)return;
                                        break;
                default:                if (Layer.LowerCase().SubString(1,Layer.Length()) == LT)
                                                {
                                                if (!Form1->CheckBox14->Checked)return;
                                                break;
                                                }
                                        if (Layer.LowerCase().SubString(1,Layer.Length()) == LB)
                                                {
                                                if (!Form1->CheckBox15->Checked)return;
                                                break;
                                                }
                }
        Form1->Blocks->Items->Add("0");         // experimental
        Form1->Blocks->Items->Add("3DSOLID");   // experimental
        Form1->Blocks->Items->Add("0");
        Form1->Blocks->Items->Add("3DFACE");
        Form1->Blocks->Items->Add("8");
        Form1->Blocks->Items->Add(Layer);
        Form1->Blocks->Items->Add("62");
        Form1->Blocks->Items->Add(AnsiString(Color));
        //
        Form1->Blocks->Items->Add("10");
        Form1->Blocks->Items->Add(F_str(x1));
        Form1->Blocks->Items->Add("20");
        Form1->Blocks->Items->Add(F_str(y1));
        Form1->Blocks->Items->Add("30");
        Form1->Blocks->Items->Add(F_str(z1));
        //
        Form1->Blocks->Items->Add("11");
        Form1->Blocks->Items->Add(F_str(x2));
        Form1->Blocks->Items->Add("21");
        Form1->Blocks->Items->Add(F_str(y2));
        Form1->Blocks->Items->Add("31");
        Form1->Blocks->Items->Add(F_str(z2));
        //
        Form1->Blocks->Items->Add("12");
        Form1->Blocks->Items->Add(F_str(x4));
        Form1->Blocks->Items->Add("22");
        Form1->Blocks->Items->Add(F_str(y4));
        Form1->Blocks->Items->Add("32");
        Form1->Blocks->Items->Add(F_str(z4));
        //
        Form1->Blocks->Items->Add("13");
        Form1->Blocks->Items->Add(F_str(x3));
        Form1->Blocks->Items->Add("23");
        Form1->Blocks->Items->Add(F_str(y3));
        Form1->Blocks->Items->Add("33");
        Form1->Blocks->Items->Add(F_str(z3));
        }