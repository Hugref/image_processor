#include "matrix_filter.h"
MatrixFilter::MatrixFilter(const std::vector<std::vector<int>>& v) {
    matrix_ = v;
}
Image MatrixFilter::Apply(const Image& image) const {
    Image imag(image.GetHeight(), image.GetWidth());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pixel = {0, 0, 0};
            int red = 0;
            int blue = 0;
            int green = 0;
            for (size_t l1 = 0; l1 < matrix_.size(); ++l1) {
                for (size_t l2 = 0; l2 < matrix_[0].size(); ++l2) {
                    Pixel pixel2 = image.GetPixel(x - (matrix_[0].size() / 2 - l2), y - (matrix_.size() / 2 - l1));
                    red += matrix_[l1][l2] * pixel2.red;
                    blue += matrix_[l1][l2] * pixel2.blue;
                    green += matrix_[l1][l2] * pixel2.green;
                }
            }

            pixel.red = std::max(0, std::min(255, red));
            pixel.green = std::max(0, std::min(255, green));
            pixel.blue = std::max(0, std::min(255, blue));
            imag.SetPixel(pixel, x, y);
        }
    }

    return imag;
}
