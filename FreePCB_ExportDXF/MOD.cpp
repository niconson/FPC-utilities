//---------------------------------------------------------------------------


#pragma hdrstop

#include "MOD.h"
#include "To_DXF.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


void MOD (AnsiString * mod)
        {
        AnsiString q = *mod;
        q = StringReplace(q,",",".",TReplaceFlags()<<rfReplaceAll);
        q = StringReplace(q,"_","",TReplaceFlags()<<rfReplaceAll);
        q = StringReplace(q,"-","",TReplaceFlags()<<rfReplaceAll);
        *mod = q;
        }