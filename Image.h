#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
};
class Image {
public:
    int GetLenPadd() const;
    Image(const int32_t& height, const int32_t& width);
    Image();
    void SetPixel(const Pixel& pix, const int32_t& x, const int32_t& y);
    Pixel GetPixel(const int32_t& x, const int32_t& y) const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;

private:
    std::vector<std::vector<Pixel>> pixels_;
    int32_t height_;
    int32_t width_;
};
