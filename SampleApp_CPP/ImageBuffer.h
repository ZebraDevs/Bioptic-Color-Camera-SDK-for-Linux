#ifndef CAMERA_VIDEO_H_
#define CAMERA_VIDEO_H_

#include <wx/wx.h>

#include <mutex>

/*
    Image buffer class to manage the image frames.
*/
class ImageBuffer
{
public:
    ImageBuffer();
    ~ImageBuffer();

    void AllocateBuffer(uint32_t width, uint32_t height);
    void CopyToBuffer(const uint8_t *data, size_t size);
    void CopyFromBuffer(uint8_t *data, size_t& size);
    void SaveAsJpeg(std::string filename);
    void SaveAsBmp(std::string filename);
private:
    std::mutex mutex_;

    size_t utilized_size_ = 0;  // This is the amount we currently use.
    size_t image_size_ = 0; // Capacity.
    uint8_t *image_frame_data_ = nullptr;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};

#endif // CAMERA_VIDEO_H_
