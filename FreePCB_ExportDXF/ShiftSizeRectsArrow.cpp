//---------------------------------------------------------------------------


#pragma hdrstop

#include "ShiftSizeRectsArrow.h"
#include "DXF_library.h"
#include "To_DXF.h"
#include "New.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void ShiftSizeRectsArrow (int i, int shift)
        {
        int SizeRectsLength = Form2->StringGrid1->RowCount - shift;
        myRectInt * CSizeRects;
        try     {
                CSizeRects = new(std::nothrow) myRectInt[SizeRectsLength];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("Error memory of myRectInt[" + AnsiString(SizeRectsLength) + "]!" );
                exit(0);
                }
        for (int t=0; t<SizeRectsLength; t++)
                CSizeRects[t] = SizeRects[t];
        delete[] SizeRects;
        try     {
                SizeRects = new(std::nothrow) myRectInt[Form2->StringGrid1->RowCount];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("Error memory of myRectInt[" + AnsiString(Form2->StringGrid1->RowCount) + "]!" );
                exit(0);
                }
        for (int t=0; t<Form2->StringGrid1->RowCount; t++)
                SizeRects[t].ini();
        for (int t=0; t<i; t++)
                SizeRects[t] = CSizeRects[t];
        for (int t=i; t<SizeRectsLength; t++)
                SizeRects[t+shift] = CSizeRects[t];
        delete[] CSizeRects;
        }
