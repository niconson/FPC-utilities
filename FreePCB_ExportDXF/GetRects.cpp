//---------------------------------------------------------------------------


#pragma hdrstop

#include "GetRects.h"
#include "To_DXF.h"
#include "DXF_library.h"
#include "New.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)



void GetRects (void)
        {
        if (SizeRects)
                delete[] SizeRects;
        try     {
                SizeRects = new(std::nothrow) myRectInt[Form2->StringGrid1->RowCount];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("Error memory of myRectInt[" + AnsiString(Form2->StringGrid1->RowCount) + "]!" );
                exit(0);
                }
        for (int r=0; r<Form2->StringGrid1->RowCount; r++)
                SizeRects[r].ini();
        CanvasAll(-1);
        }