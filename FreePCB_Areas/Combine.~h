//---------------------------------------------------------------------------

#ifndef CombineH
#define CombineH
#define MIN_LEN_SIDE _104


class MLine
        {
        public:
        double X1;
        double Y1;
        double X2;
        double Y2;
        double Bounds;
        int First;
        int n_board;
        int n_thermal;
        bool FlagBegPoint;
        bool FlagDelete;
        bool FlagWrite;
        bool Arc;
        void RST(void)
                {
                X1=0;Y1=0;X2=0;Y2=0;
                Bounds=0;
                First=-1;
                n_board=-1;
                n_thermal=-1;
                FlagBegPoint=0;
                FlagDelete=0;
                FlagWrite=0;
                Arc=0;
                }
        };
class MPolyLine
        {
        public:
        double X;
        double Y;
        bool Flag;
        bool Label;
        void RST(void)
                {
                X=0;
                Y=0;
                Flag=0;
                Label=0;
                }
        };

class LinesContainer {
#define DEF_MAX_LINES 20
#define L_LIMIT 9999
private://====================================================
        int cnt;
        int def;
        int * mem1_i;
        int * mem2_i;
        int * mem1_v1;
        int * mem2_v1;
        int * mem1_v2;
        int * mem2_v2;
        int * i;
        int * v1;
        int * v2;
public: //====================================================
        int MAX_LINES;
        LinesContainer();
        bool setMaxLines( int nl );
        bool set ( int ii, int vv1, int vv2, int n_str=-1 );
        void reset ( int value );
        int iof ( int ii, int vv1, int vv2 );
        int iof ( int vv1, int vv2 );
        int iof ( int ii );
        int push ( int ii, int vv1, int vv2 );
        int del ( int num=0 );
        bool get ( int num, int * ii, int * vv1, int * vv2 );
        bool get_first ( int * ii, int * vv1, int * vv2 );
        bool get_last ( int * ii, int * vv1, int * vv2 );
        int get_count (){return cnt;}
        int get_max (){return MAX_LINES;}
        //====================================================
};

class CCombine
{
public:
        MLine * Lines;
        int n_Lines;
        MPolyLine * Corners;
        int i_Corner;
        int n_Corners;
        int IndexStartContour;
        int IndexEndContour;
        int Th_w;
        LinesContainer LC;
        double BEGIN_POINT_HORIZ;
        double BEGIN_POINT_VERT;
        bool scanDir;
        //
        CCombine();
        void Ini(       MLine * lines,
                        MPolyLine * corners,
                        int nlines,
                        int ncorners,
                        int begX,
                        int begY,
                        int th_w,
                        bool scanD);
        void ClearFlagsWrite(void);
        void ClearFlagsDelete(void);
        void ClearFlagsBegPoint(void);
        int NextLine (int INDEX);
        int FindLine (double x,
                      double y,
                      double x2,
                      double y2,
                      double *outX,
                      double *outY,
                      int IndexLine,
                      int StartC,
                      bool *EndContour );
        bool PointContourInside (double X, double Y, int st, int end);
        void DeleteLines (bool INSIDE_OUTSIDE, int st, int end);
        bool TestPoint (double Xp, double Yp, int iEXLUDE);
        int MinV (double * outx, double * outy);
        int MinH (double * outx, double * outy);
        int BeginPoint (double * Xb, double * Yb);
        int IndexMinXY(int MODE, double * Xstart, double * Ystart);
        int Combine ();
};
//---------------------------------------------------------------------------
#endif
