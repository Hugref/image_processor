#pragma once
#include "filter.h"
class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold);
    Image Apply(const Image& imag) const override;

private:
    uint8_t threshold_ = 0;
};
