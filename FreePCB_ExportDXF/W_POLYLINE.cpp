//---------------------------------------------------------------------------


#pragma hdrstop

#include "W_POLYLINE.h"
#include "W_SOLID.h"
#include "To_DXF.h"
#include "Options.h"
#include "math.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void W_LWPOLYLINE (     float x1,
                        float y1,
                        float x2,
                        float y2,
                        float W,
                        float Bulge,
                        float Elevation,
                        float Thickness,
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
        if (Layer.Length() == 0)
                {
                return;
                }
        //
        if (Form3->RadioButton5->Checked) W = W/2;
        float Ang = Angle(x2,y2,x1,y1);
        float px1 = x1 + (W/2)*cos((Ang + 90)*M_PI/180);
        float py1 = y1 + (W/2)*sin((Ang + 90)*M_PI/180);
        float px2 = x2 + (W/2)*cos((Ang + 90)*M_PI/180);
        float py2 = y2 + (W/2)*sin((Ang + 90)*M_PI/180);
        //
        float bwn1 = x2 + (W/2)*cos((Ang + 30)*M_PI/180);
        float bwn2 = y2 + (W/2)*sin((Ang + 30)*M_PI/180);
        float bwn3 = x2 + (W/2)*cos((Ang - 30)*M_PI/180);
        float bwn4 = y2 + (W/2)*sin((Ang - 30)*M_PI/180);
        //
        float px3 = x2 + (W/2)*cos((Ang - 90)*M_PI/180);
        float py3 = y2 + (W/2)*sin((Ang - 90)*M_PI/180);
        float px4 = x1 + (W/2)*cos((Ang - 90)*M_PI/180);
        float py4 = y1 + (W/2)*sin((Ang - 90)*M_PI/180);
        //
        float bwn5 = x1 + (W/2)*cos((Ang - 150)*M_PI/180);
        float bwn6 = y1 + (W/2)*sin((Ang - 150)*M_PI/180);
        float bwn7 = x1 + (W/2)*cos((Ang + 150)*M_PI/180);
        float bwn8 = y1 + (W/2)*sin((Ang + 150)*M_PI/180);
        //
        if (Form3->RadioButton1->Checked)
                {
                W_SOLID(        px1,py1,Elevation,
                                px2,py2,Elevation,
                                px4,py4,Elevation,
                                px3,py3,Elevation,
                                Color,Layer);
                W_SOLID(        px2,py2,Elevation,
                                bwn1,bwn2,Elevation,
                                px3,py3,Elevation,
                                bwn3,bwn4,Elevation,
                                Color,Layer);
                W_SOLID(        px4,py4,Elevation,
                                bwn5,bwn6,Elevation,
                                px1,py1,Elevation,
                                bwn7,bwn8,Elevation,
                                Color,Layer);
                return;
                }
        if (Form3->RadioButton2->Checked) W = 0.01;
        Form1->OutputBox->Items->Add("0");
        Form1->OutputBox->Items->Add("LWPOLYLINE");
        Form1->OutputBox->Items->Add("8");
        Form1->OutputBox->Items->Add(Layer);
        Form1->OutputBox->Items->Add("62");
        Form1->OutputBox->Items->Add(AnsiString(Color));
        Form1->OutputBox->Items->Add("90");
        Form1->OutputBox->Items->Add("4");
        Form1->OutputBox->Items->Add("43");
        Form1->OutputBox->Items->Add(F_str(W));
        Form1->OutputBox->Items->Add("70");
        Form1->OutputBox->Items->Add("1");
        Form1->OutputBox->Items->Add("38");
        Form1->OutputBox->Items->Add(F_str(Elevation));
        Form1->OutputBox->Items->Add("39");
        Form1->OutputBox->Items->Add(F_str(Thickness));
        // 1
        Form1->OutputBox->Items->Add("10");
        Form1->OutputBox->Items->Add(F_str(px1));
        Form1->OutputBox->Items->Add("20");
        Form1->OutputBox->Items->Add(F_str(py1));
        Form1->OutputBox->Items->Add("42");
        Form1->OutputBox->Items->Add(AnsiString(Bulge));
        // 2
        Form1->OutputBox->Items->Add("10");
        Form1->OutputBox->Items->Add(F_str(px2));
        Form1->OutputBox->Items->Add("20");
        Form1->OutputBox->Items->Add(F_str(py2));
        Form1->OutputBox->Items->Add("42");
        Form1->OutputBox->Items->Add(AnsiString(-1));
        // 3
        Form1->OutputBox->Items->Add("10");
        Form1->OutputBox->Items->Add(F_str(px3));
        Form1->OutputBox->Items->Add("20");
        Form1->OutputBox->Items->Add(F_str(py3));
        Form1->OutputBox->Items->Add("42");
        Form1->OutputBox->Items->Add(AnsiString(-Bulge));
        // 4
        Form1->OutputBox->Items->Add("10");
        Form1->OutputBox->Items->Add(F_str(px4));
        Form1->OutputBox->Items->Add("20");
        Form1->OutputBox->Items->Add(F_str(py4));
        Form1->OutputBox->Items->Add("42");
        Form1->OutputBox->Items->Add(AnsiString(-1));
        }