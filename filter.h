#pragma once
#include "Image.h"
class Filter {
public:
    virtual Image Apply(const Image& image) const = 0;
};
