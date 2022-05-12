#include <cmath>

#include "gaussian_blur.h"
GaussianBlur::GaussianBlur(double sigma) {
    sigma_ = sigma;
}

Image GaussianBlur::Apply(const Image& image) const {
    Image ans_image(image.GetHeight(), image.GetWidth());
    Image tmp_image(image.GetHeight(), image.GetWidth());
    const int32_t offset = 3 * sigma_ + 2;
    std::vector<double> e(std::max(image.GetHeight(), image.GetWidth()));

    for (int32_t i = 0; i < static_cast<int32_t>(std::max(image.GetHeight(), image.GetWidth())); ++i) {
        e[i] = expf(-i * i / (2.f * sigma_ * sigma_)) / sqrtf(2.f * M_PI) / sigma_;
    }

    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;
            for (int32_t k = x >= offset ? x - offset : 0; k <= std::min(x + offset, image.GetWidth() - 1); ++k) {
                float ex = e[abs(static_cast<int>(x) - static_cast<int>(k))];
                Pixel pixel = image.GetPixel(k, y);
                red += ex * pixel.red;
                green += ex * pixel.green;
                blue += ex * pixel.blue;
            }

            tmp_image.SetPixel(
                {static_cast<uint8_t>(std::min(255.0, blue)), static_cast<uint8_t>(std::min(255.0, green)),
                 static_cast<uint8_t>(std::min(255.0, red))},
                x, y);
        }
    }

    for (int32_t x = 0; x < image.GetWidth(); ++x) {
        for (int32_t y = 0; y < image.GetHeight(); ++y) {
            double red = 0;
            double green = 0;
            double blue = 0;
            for (int32_t k = y >= offset ? y - offset : 0; k <= std::min(y + offset, image.GetHeight() - 1); ++k) {
                float ex = e[std::abs(static_cast<int>(y) - static_cast<int>(k))];
                Pixel pixel = tmp_image.GetPixel(x, k);
                red += ex * pixel.red;
                green += ex * pixel.green;
                blue += ex * pixel.blue;
            }

            ans_image.SetPixel(
                {static_cast<uint8_t>(std::min(255.0, blue)), static_cast<uint8_t>(std::min(255.0, green)),
                 static_cast<uint8_t>(std::min(255.0, red))},
                x, y);
        }
    }

    return ans_image;
}