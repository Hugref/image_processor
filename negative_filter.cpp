#include "negative_filter.h"
Image NegativeFilter::Apply(const Image& imag) const {
    Image image(imag.GetHeight(), imag.GetWidth());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pix = imag.GetPixel(x, y);
            Pixel pixel = {static_cast<uint8_t>(255 - pix.blue), static_cast<uint8_t>(255 - pix.green),
                           static_cast<uint8_t>(255 - pix.red)};
            image.SetPixel(pixel, x, y);
        }
    }
    return image;
}
