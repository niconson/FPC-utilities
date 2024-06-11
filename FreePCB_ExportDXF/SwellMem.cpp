//---------------------------------------------------------------------------


#pragma hdrstop

#include "SwellMem.h"
#include "To_DXF.h"
#include "new.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)







int SwellMem (void)
        {
        static int SWELL_M=1;
        SWELL_M = SWELL_M*2;
        float * NewFArray;
        int * NewIArray;
        try     {
                NewFArray = new(std::nothrow) float[_103*(SWELL_M/2)];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("float[" + AnsiString(_103*(SWELL_M/2)) + "]!" );
                exit(0);
                }
        try     {
                NewIArray = new(std::nothrow) int[_103*(SWELL_M/2)];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("float[" + AnsiString(_103*(SWELL_M/2)) + "]!" );
                exit(0);
                }
        for (int i=0; i<_103*(SWELL_M/2); i++)
                {
                NewFArray[i] = FACES[i];
                NewIArray[i] = LINES[i];
                }
        delete[] FACES;
        delete[] LINES;
        try     {
                FACES = new(std::nothrow) float[_103*SWELL_M];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("float[" + AnsiString(_103*SWELL_M) + "]!" );
                exit(0);
                }
        try     {
                LINES = new(std::nothrow) int[_103*SWELL_M];
                }
        catch(std::bad_alloc)
                {
                ShowMessage("float[" + AnsiString(_103*SWELL_M) + "]!" );
                exit(0);
                }
        for (int i=0; i<_103*(SWELL_M/2); i++)
                {
                FACES[i] = NewFArray[i];
                LINES[i] = NewIArray[i];
                }
        delete[] NewFArray;
        delete[] NewIArray;
        return _103*SWELL_M;
        }