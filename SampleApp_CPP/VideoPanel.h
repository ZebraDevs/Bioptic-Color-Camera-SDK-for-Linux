/*
    Custom wxWidgets controller for displaying video.
*/

#ifndef VIDEOPANEL_H
#define VIDEOPANEL_H

#include "wx/wx.h"
#include "../image_converter/image_converter.h"
#include "camera_bounding_box_factory.h"

class VideoPanel : public wxPanel
{
private:
    // Display width and height.
    int width_;
    int height_;

    // Actual image size.
    uint32_t image_width_ = 0;
    uint32_t image_height_ = 0;
public:
    uint8_t *image_data_ = nullptr;
    size_t image_data_size_ = 0;
    
    bool bounding_box_detection = false;
    bool set_background = true ;
    
    int bmp_image = 0;
    int jpg_image = 1 ;
    
public:
    VideoPanel(
       wxWindow *parent,
       wxWindowID id = wxID_ANY,
       const wxPoint& pos = wxDefaultPosition,
       const wxSize& size = wxDefaultSize,
       long style = wxTAB_TRAVERSAL,
       const wxString& name = wxPanelNameStr
	);
    virtual ~VideoPanel();

    void PaintEvent(wxPaintEvent & evt);
    void PaintNow();

    void AllocateImageBuffer(uint32_t width, uint32_t height);
    void DrawFrame();
    void SetBackground();
    

    void Render(wxDC& dc);

    DECLARE_EVENT_TABLE()
};

#endif // VIDEOPANEL_H
