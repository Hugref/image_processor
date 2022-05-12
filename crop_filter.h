#pragma once
#include "filter.h"
class CropFilter : public Filter {
public:
    CropFilter(const uint32_t& width, const uint32_t& height);
    Image Apply(const Image& imag) const override;

private:
    int32_t width_;
    int32_t height_;
};
