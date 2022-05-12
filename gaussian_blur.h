#pragma once
#include "filter.h"
class GaussianBlur : public Filter {

public:
    GaussianBlur(double sigma);
    Image Apply(const Image &image) const override;

private:
    double sigma_;
};
