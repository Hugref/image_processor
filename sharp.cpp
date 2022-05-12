#include "sharp.h"
FilterSharp::FilterSharp() : MatrixFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}) {
}