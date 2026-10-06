#include "VideoPanel.h"

#include <cstring>

CameraBoundingBoxDetectorInterface* frameProc;
vector<BoundingBoxPoint> bounding_rect;


BEGIN_EVENT_TABLE(VideoPanel, wxPanel)

// catch paint events
EVT_PAINT(VideoPanel::PaintEvent)

END_EVENT_TABLE()

VideoPanel::VideoPanel(
   wxWindow *parent,
   wxWindowID id,
   const wxPoint& pos,
   const wxSize& size,
   long style,
   const wxString& name
): wxPanel(parent, id, pos, size, style, name)
{
frameProc = CameraImageProcessingFactory::CreateBoundingBoxDetector(BackgroundFilterType::kStatic);
}

VideoPanel::~VideoPanel()
{
    if (image_data_)
    {
        delete [] image_data_;
    }
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void VideoPanel::PaintEvent(wxPaintEvent & evt)
{
    (void)evt;
    wxPaintDC dc(this);
    DrawFrame();
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void VideoPanel::PaintNow()
{
    wxClientDC dc(this);
}

void VideoPanel::AllocateImageBuffer(uint32_t width, uint32_t height)
{
    if (image_data_)
    {
        delete [] image_data_;
    }
    image_width_ = width;
    image_height_ = height;
    image_data_size_ = width * height * 3;
    image_data_ = new uint8_t[image_data_size_]; // Assume an RGB image.
}

void VideoPanel::DrawFrame() {
    wxClientDC dc(this);
    if (image_data_) {
        wxSize size = GetSize();
        wxImage pWxImg = wxImage(image_width_, image_height_, image_data_, TRUE);
        wxBitmap bmp = wxBitmap(pWxImg.Scale(size.GetWidth(), size.GetHeight()));
        dc.DrawBitmap(bmp, wxPoint(0, 0));

        zebra::camera_sdk::ImageData image = {
            image_width_,
            image_height_,
            image_width_ * 3,
            image_data_size_,
            image_data_
        };

        std::vector<uint8_t> data = Encode(zebra::image::FileConverter::RGB_TO_BMP, image);
        if (set_background) {
            frameProc->SetBackgroundFrame(&data[0], data.size(), image_width_, image_height_, bmp_image);
            set_background = false;
        } else {
            if (bounding_box_detection) {
                bool rect_found = frameProc->DetectBoundingBox(&data[0], data.size(), image_width_, image_height_, bmp_image, bounding_rect);
                if (rect_found) {

                    float x_pos = (float) bounding_rect[0].x;
                    float y_pos = (float) bounding_rect[0].y;

                    float x_cordinate = ((float) bmp.GetWidth() / (float) image_width_) * x_pos;
                    float y_cordinate = ((float) bmp.GetHeight() / (float) image_height_) * y_pos;

                    int new_x_pos = (int) x_cordinate;
                    int new_y_pos = (int) y_cordinate;


                    float rect_width = ((float) bmp.GetWidth() / (float) image_width_)*(float) bounding_rect[3].x - ((float) bmp.GetWidth() / (float) image_width_)*(float) bounding_rect[0].x;
                    float rect_height = ((float) bmp.GetHeight() / (float) image_height_)*(float) bounding_rect[3].y - ((float) bmp.GetHeight() / (float) image_height_)*(float) bounding_rect[0].y;

                    int box_width = (int) rect_width;
                    int box_height = (int) rect_height;

                    wxClientDC dc(this);
                    dc.SetBrush(*wxTRANSPARENT_BRUSH);
                    wxColour colour(233, 249, 120);
                    wxPen pen(colour, 3);
                    dc.SetPen(pen);
                    dc.DrawRectangle(new_x_pos, new_y_pos, box_width, box_height);
                }
            }
        }
    }
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void VideoPanel::Render(wxDC&  dc)
{
    (void)dc;
}
void VideoPanel::SetBackground()
{  
    set_background = true;
}