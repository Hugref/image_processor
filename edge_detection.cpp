//
// Created by iglin on 22.03.2022.
//

#include "edge_detection.h"
#include "grayscale_filter.h"
#include "matrix_filter.h"
const GrayscaleFilter F;
const MatrixFilter M({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
const Pixel WHITE = {255, 255, 255};
const Pixel BLACK = {0, 0, 0};
EdgeDetection::EdgeDetection(double threshold) {
    threshold_ = 255 * threshold;
}
Image EdgeDetection::Apply(const Image& imag) const {

    Image image2 = F.Apply(imag);
    image2 = M.Apply(image2);
    for (int32_t y = 0; y < image2.GetHeight(); ++y) {
        for (int32_t x = 0; x < image2.GetWidth(); ++x) {
            if (image2.GetPixel(x, y).blue > threshold_) {
                image2.SetPixel(WHITE, x, y);
            } else {
                image2.SetPixel(BLACK, x, y);
            }
        }
    }
    return image2;
}
