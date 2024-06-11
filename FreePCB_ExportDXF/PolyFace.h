//---------------------------------------------------------------------------

#ifndef PolyFaceH
#define PolyFaceH
#define INT_DEF 999999999

struct cLINE
        {
        float x1;
        float y1;
        float z1;
        float x2;
        float y2;
        float z2;
        float Width;
        cLINE * prev;
        cLINE * next;
        };
class CContour
        {
        cLINE * First;
        cLINE * Last;
        CContour * prev;
        CContour * next;
        int nLines;
        void AddLine(float x1, float y1, float z1, float x2, float y2, float z2);
        void DelLine(int i);
        void Clear();
        int TestPointInsideContour(float x, float y, float z);
        int TestLineIntersection(cLINE * Line);
        };
class CContourList
        {
        CContour * First;
        CContour * Last;
        int nContours;
        void CreateContour();
        void DeleteContour(int i);
        void RemoveAll();
        int TestPointInside(float x, float y, float z);
        int TestLineIntersection(cLINE * Line);
        CContourList()
                {
                nContours = 0;
                RemoveAll();
                }
        };
class PolyFace
        {
private:
        CContourList HOLES;
public:
        CContourList * PolygonTriangulation (CContour * Contour, CContourList * Holes);
        int DRAW_FACETS( CContourList * FACETS );
        void AddVertex(float X, float Y, float Z);
        void CloseContour();
        };
//---------------------------------------------------------------------------
#endif
