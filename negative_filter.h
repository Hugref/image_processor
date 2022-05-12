#pragma once
#include "Image.h"
#include "filter.h"
class NegativeFilter : public Filter {
public:
    Image Apply(const Image& imag) const override;
};
