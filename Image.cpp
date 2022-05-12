
#include "Image.h"

Image::Image(const int32_t& height, const int32_t& width) {
    height_ = height;
    width_ = width;
    pixels_.resize(height);
    for (int32_t i = 0; i < height; ++i) {
        pixels_[i].resize(width);
    }
}
void Image::SetPixel(const Pixel& pix, const int32_t& x, const int32_t& y) {
    pixels_[y][x] = pix;
}

Pixel Image::GetPixel(const int32_t& x, const int32_t& y) const {
    int32_t closest_y = height_ - 1;
    int32_t closest_x = width_ - 1;
    if (y < 0) {
        closest_y = 0;
    } else if (y < height_) {
        closest_y = y;
    }
    if (x < 0) {
        closest_x = 0;
    } else if (x < width_) {
        closest_x = x;
    }
    return pixels_[closest_y][closest_x];
}

int32_t Image::GetWidth() const {
    return width_;
}
int32_t Image::GetHeight() const {
    return height_;
}
int Image::GetLenPadd() const {
    return (GetWidth() % 4);
}
Image::Image() {
    height_ = 0;
    width_ = 0;
}
