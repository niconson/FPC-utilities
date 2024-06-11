//---------------------------------------------------------------------------


#pragma hdrstop

#include "viaStyle.h"
#include "FPC_to_PCB.h"
#include "fstream.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString viaStyle (void)
{
AnsiString MEM_v_s = A;
AnsiString Name_via_style_ = F_str(F);
Name_via_style_ = Name_via_style_ + "vs";
Name_via_style_ = Name_via_style_ + F_str(H);

ifstream ViaS((Path + "VIASTYLE.TXT").c_str());;
ViaS.getline(str,2500);
A = str;
A = A.Trim();
bool FLa = true;
           while (get_end ())
                 {
                  if (go (1,Name_via_style_)) FLa = false;
                  ViaS.getline(str,2500);
                 }
ViaS.close();
if (FLa == true)
{
ofstream VS;
VS.open((Path + "VIASTYLE.TXT").c_str(), std::ios_base::app );
//
VS << "  (viaStyleDef \"";
VS << Name_via_style_.c_str();
VS << "\"";
VS << endl;
VS << "    (holeDiam ";
VS << F_str(H).c_str();
VS << ")";
VS << endl;
VS << "    (StartRange 1)" << endl;
VS << "    (EndRange 2)" << endl;
VS << "    (viaShape (layerNumRef 1) (viaShapeType Ellipse) (shapeWidth ";
VS << F_str(F).c_str();
VS << ") (shapeHeight ";
VS << F_str(F).c_str();
VS << ") )";
VS << endl;
VS << "    (viaShape (layerNumRef 2) (viaShapeType Ellipse) (shapeWidth ";
VS << F_str(F).c_str();
VS << ") (shapeHeight ";
VS << F_str(F).c_str();
VS << ") )";
VS << endl;
VS << "    (viaShape (layerType Signal) (viaShapeType Ellipse) (shapeWidth ";
VS << F_str(F).c_str();
VS << ") (shapeHeight ";
VS << F_str(F).c_str();
VS << ") )";
VS << endl;
VS << "    (viaShape (layerType Plane) (viaShapeType Direct) (shapeWidth 0.0) (shapeHeight 0.0) )";
VS << endl;
VS << "    (viaShape (layerType NonSignal) (viaShapeType Ellipse) (shapeWidth 0.0) (shapeHeight 0.0) )";
VS << endl;
VS << "  )";
VS << endl;
//
VS.close();
}//if (FLa == true)
A = MEM_v_s;
return Name_via_style_;
}
