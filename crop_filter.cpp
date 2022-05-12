#include "crop_filter.h"
CropFilter::CropFilter(const uint32_t& width, const uint32_t& height) {
    width_ = width;
    height_ = height;
}
Image CropFilter::Apply(const Image& imag) const {
    Image image(height_, width_);
    for (int32_t y = 0; y < height_; ++y) {
        for (int32_t x = 0; x < width_; ++x) {
            image.SetPixel(imag.GetPixel(x, imag.GetHeight() - height_ + y), x, y);
        }
    }
    return image;
}
