#include <iostream>
#include "Image.h"
#include "reader.h"
#include "writer.h"
#include "crop_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "matrix_filter.h"
#include "sharp.h"
#include "edge_detection.h"
#include "gaussian_blur.h"
#include "parser.h"
int main(int argc, const char* argv[]) {
    Parser parser(argc, argv);
    Image image = Reader().Read(parser.GetFileToRead());
    for (size_t i = 0; i < parser.GetFilters().size(); ++i) {
        image = parser.GetFilters().at(i)->Apply(image);
    }
    Writer().Write(image, parser.GetFileToWrite());
}