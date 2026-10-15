#include "TA_Main_APP.h"
#include <wx/image.h>
#include <wx/log.h>
//*****************************************************************
TA_Canvas::TA_Canvas(wxWindow* pWindow, const wxGLAttributes& art, const wxSize& size): wxGLCanvas(pWindow, art, wxID_ANY, wxDefaultPosition, size),m_objContext(this)
{
    Bind(wxEVT_PAINT, &TA_Canvas::OnPaint, this);
    Bind(wxEVT_MOUSEWHEEL, &TA_Canvas::OnMouseWheel, this);
    Bind(wxEVT_RIGHT_UP, &TA_Canvas::OnRightUP, this);
    Bind(wxEVT_RIGHT_DOWN, &TA_Canvas::OnRightDown, this);
    Bind(wxEVT_MOTION, &TA_Canvas::Move, this);
    Bind(wxEVT_LEFT_DOWN, &TA_Canvas::OnLefttDown, this);
    Bind(wxEVT_LEFT_UP, &TA_Canvas::OnLeftUP, this);

    m_fZoom = 1.0f;
    m_fPanX = 0.0f;
    m_fPanY = 0.0f;
    m_fRoationAngle = 0;
    m_bPanning = false;
    m_bRotating = false;
}
//*****************************************************************
void TA_Canvas::Move(wxMouseEvent& evt)
{
    if (m_bPanning && evt.RightIsDown())
    {
        double x = evt.GetPosition().x - m_ObjLastPnt.x;
        double y = evt.GetPosition().y - m_ObjLastPnt.y;

        wxSize frameSize = GetClientSize();

        if (frameSize.x <= 0 || frameSize.y <= 0)
            return;

        m_ObjLastPnt = evt.GetPosition();

        m_fPanX += x / frameSize.x;
        m_fPanY -= y / frameSize.y;
    }
    else if (m_bRotating && evt.LeftIsDown())
    {
        wxPoint currentPnt = evt.GetPosition();

        int dx = currentPnt.x - m_ObjLastRotatePnt.x;

        m_fRoationAngle += dx * 0.5f;

        m_ObjLastRotatePnt = currentPnt;

    }

    Refresh();
}
//*****************************************************************
void TA_Canvas::OnRightUP(wxMouseEvent& evt)
{
    m_bPanning = false;

    if (HasCapture())
        ReleaseMouse();
}
//*****************************************************************
void TA_Canvas::OnRightDown(wxMouseEvent& evt)
{
    if (evt.ControlDown())
    {
        m_bPanning = true;
        m_ObjLastPnt = evt.GetPosition();

        if (!HasCapture())
            CaptureMouse();
    }
}
//*****************************************************************
void TA_Canvas::OnLeftUP(wxMouseEvent& evt)
{
    m_bRotating = false;

    if (HasCapture())
        ReleaseMouse();
}
void TA_Canvas::OnLefttDown(wxMouseEvent& evt)
{
    if (evt.ControlDown())
    {
        m_bRotating = true;
        m_ObjLastRotatePnt = evt.GetPosition();

        if (!HasCapture())
            CaptureMouse();
    }
}
//*****************************************************************
void TA_Canvas::OnMouseWheel(wxMouseEvent& evt)
{
    double dRotation = evt.GetWheelRotation();
    double dDelte = evt.GetWheelDelta();

    double dStep = dRotation / dDelte;

    float fLoc = m_fZoom;
    fLoc = m_fZoom + (m_fZoom * dStep * 0.1);

    if (fLoc <= 0.1f || fLoc >= 2.5f)
        return;

    m_fZoom = fLoc;

    Refresh();
}
//*****************************************************************
void TA_Canvas::OnPaint(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    if (!SetCurrent(m_objContext))
        return;

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(m_fPanX, m_fPanY, 0.0f);
    glScalef(m_fZoom, m_fZoom, 1.0f);
    glRotatef(m_fRoationAngle, 0, 0, 1);

    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.3f, 0.7f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.f, 0.5f);
    glEnd();

    SwapBuffers();
}
//*****************************************************************
bool TA_APP::OnInit()
{
    // Ensure image handlers (PNG, ICO, etc.) are initialized so wxImage
    // can load image files. Without this, attempting to load images may
    // trigger errors or fail to recognize formats.
    wxInitAllImageHandlers();

    wxDisplay dpy;
    wxRect area = dpy.GetClientArea();
    int w = area.GetWidth();
    int h = area.GetHeight();

    wxPoint pos(area.GetX(), area.GetY());
    wxSize objSize(w, h);

    // 1. Create the main frame
    wxFrame* pFrame = new wxFrame(nullptr, wxID_ANY, "Tri Axi", pos, objSize);

    wxSize frameSize = pFrame->GetClientSize();

    int canvasWidth = static_cast<int>(frameSize.GetWidth() * 0.8);
    int canvasHeight = static_cast<int>(frameSize.GetHeight() * 0.8);

    wxGLAttributes a;
    a.PlatformDefaults().DoubleBuffer().Depth(20).FrameBuffersRGB().EndList();

    // 2. To prevent the single-child auto-stretch rule, create a root panel first
    wxPanel* rootPanel = new wxPanel(pFrame);

    wxSize objCanvasSize(canvasWidth, canvasHeight);

    // 3. Parent the canvas to the rootPanel instead of pFrame directly
    TA_Canvas* pTA_Canvas = new TA_Canvas(rootPanel, a, objCanvasSize);

    // Position at top-center inside the panel
    int x = (frameSize.GetWidth() - canvasWidth) / 2;
    int y = 20; // some top margin

    pTA_Canvas->SetSize(x, y, canvasWidth, canvasHeight);

    pFrame->Show(true);

    //Prefix add used for file formating like platform spesified (for window it change \ to \\)
    wxString iconPath = R"(D:\WS\TRI_AXI_26\Dependecy\Image\logo_256.png)";
    wxIcon ico(iconPath, wxBITMAP_TYPE_PNG);
    if (ico.IsOk())
    {
        pFrame->SetIcon(ico);
    }

    return true;
}
wxIMPLEMENT_APP(TA_APP);
