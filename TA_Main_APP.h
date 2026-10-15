#include <wx/wx.h>
#include <wx/display.h>
#include <wx/glcanvas.h>
//Incon Insertion 
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bitmap.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>

class TA_APP;
class TA_Canvas : public wxGLCanvas
{
public:
    float m_fZoom;
    float m_fPanX;
    float m_fPanY;
    float m_fRoationAngle;
    bool m_bPanning;
    bool m_bRotating;

    wxGLContext m_objContext;
    wxPoint m_ObjLastPnt;
    wxPoint m_ObjLastRotatePnt;

    TA_Canvas(wxWindow* pWindow, const wxGLAttributes& art, const wxSize& size);

    void Move(wxMouseEvent& evt);
    void OnRightUP(wxMouseEvent& evt);
    void OnRightDown(wxMouseEvent& evt);
    void OnLeftUP(wxMouseEvent& evt);
    void OnLefttDown(wxMouseEvent& evt);
    void OnMouseWheel(wxMouseEvent& evt);

    void OnPaint(wxPaintEvent& evt);
};

class TA_APP : public wxApp
{
public:
    bool OnInit();
};


