#pragma once
#include "filter.h"
#include <vector>
class MatrixFilter : public Filter {
public:
    MatrixFilter(const std::vector<std::vector<int>>& v);
    Image Apply(const Image& image) const override;

protected:
    std::vector<std::vector<int>> matrix_;
};
