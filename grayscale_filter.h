#pragma once
#include "filter.h"
class GrayscaleFilter : public Filter {
public:
    Image Apply(const Image& imag) const override;
};
