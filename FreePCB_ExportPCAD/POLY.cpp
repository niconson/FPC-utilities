//---------------------------------------------------------------------------


#pragma hdrstop

#include "POLY.h"
#include "FPC_to_PCB.h"
#include "fstream.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void CUTOUT (int CASE, int LaYeR)
{
 /*ofstream CUTOUTs;
 CUTOUTs.open((Path + "CUTOUTS_AREA.TXT").c_str(), std::ios_base::app );
 if (CASE == 1)
    {
     CUTOUTs << LaYeR;
     CUTOUTs << "    (polyCutOut ";
     CUTOUTs << endl;
     CUTOUTs << LaYeR;
     CUTOUTs << "      (pcbPoly ";
     CUTOUTs << endl;
    } // if (CASE == 1)
 else if (CASE == 2)
    {
     CUTOUTs << LaYeR;
     CUTOUTs << "          (pt ";
     CUTOUTs << F_str(X).c_str();
     CUTOUTs << " ";
     CUTOUTs << F_str(Y).c_str();
     CUTOUTs << ")";
     CUTOUTs << endl;
    } // else if (CASE == 2)
 else if (CASE == 3)
    {
     CUTOUTs << LaYeR;
     CUTOUTs << "      )";
     CUTOUTs << endl;
     CUTOUTs << LaYeR;
     CUTOUTs << "    )";
     CUTOUTs << endl;
    } // else if (CASE == 3)
 else if (CASE == 4)
    {

    } // else if (CASE == 4)
 CUTOUTs.close(); */
}