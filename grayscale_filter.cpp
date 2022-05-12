#include <cmath>
#include "grayscale_filter.h"
Image GrayscaleFilter::Apply(const Image& imag) const {
    Image image(imag.GetHeight(), imag.GetWidth());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pixel = imag.GetPixel(x, y);
            uint8_t grey = 0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue;
            Pixel pixel2 = {grey, grey, grey};
            image.SetPixel(pixel2, x, y);
        }
    }
    return image;
}