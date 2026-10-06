/*
    Image frame handling and listener implementation.
*/

#include "ImageBuffer.h"

#include <cstring>
#include <thread>
#include <sstream>      // For std::stringstream
#include <fstream>

#include "ZebraCameraDemoMain.h"
#include "image_converter.h"

ImageBuffer::ImageBuffer()
{
}

ImageBuffer::~ImageBuffer()
{
    if (image_frame_data_)
    {
        delete [] image_frame_data_;
    }
}

void ImageBuffer::AllocateBuffer(uint32_t width, uint32_t height)
{
    std::lock_guard<std::mutex> lock(mutex_);

    width_ = width;
    height_ = height;

    size_t required_size = width * height * 3;

    if (image_size_ < required_size)
    {
        // (Re)Allocate if current buffer is not enough.
        if (image_frame_data_)
        {
            delete [] image_frame_data_;
        }

        image_frame_data_ = new uint8_t[required_size];
    }
    image_size_ = required_size;

    utilized_size_ = 0;
}

void ImageBuffer::CopyToBuffer(const uint8_t *data, size_t size)
{
    std::lock_guard<std::mutex> lock(mutex_);

    //wxLogMessage("%s: our size = %d, required = %d", __func__, image_size_, size);

    if (image_size_ >= size && 0 != size)
    {
        std::memcpy(image_frame_data_, data, size);
        utilized_size_ = size;

        //wxLogMessage("%s: copied: %lu bytes", __func__, utilized_size_);
    }
    else
    {
        wxLogMessage("%s: No room for this image data!", __func__);
    }

}

void ImageBuffer::CopyFromBuffer(uint8_t *data, size_t& size)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (image_size_ <= size && 0 != utilized_size_)
    {
        std::memcpy(data, image_frame_data_, utilized_size_);
        size = utilized_size_;

        //wxLogMessage("%s: copied: %lu bytes", __func__, utilized_size_);
    }
    else
    {
        wxLogMessage("%s: No room for this image data! image_size_=%lu, size=%lu",
                     __func__, image_size_, size);
    }
}

void ImageBuffer::SaveAsJpeg(std::string filename)
{
    std::lock_guard<std::mutex> lock(mutex_);

    zebra::camera_sdk::ImageData image = {
        width_,
        height_,
        width_ * 3,
        image_size_,
        image_frame_data_
    };
    std::vector<uint8_t> data = Encode(zebra::image::FileConverter::RGB_TO_JPEG, image);

    std::ofstream ofs(filename, std::ios_base::binary);
	ofs.write((const char*) &data[0], data.size());
	ofs.close();
}

void ImageBuffer::SaveAsBmp(std::string filename)
{
    std::lock_guard<std::mutex> lock(mutex_);

    zebra::camera_sdk::ImageData image = {
        width_,
        height_,
        width_ * 3,
        image_size_,
        image_frame_data_
    };
    std::vector<uint8_t> data = Encode(zebra::image::FileConverter::RGB_TO_BMP, image);

    std::ofstream ofs(filename, std::ios_base::binary);
	ofs.write((const char*) &data[0], data.size());
	ofs.close();
}
