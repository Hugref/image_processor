#include "parser.h"
#include "crop_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharp.h"
#include "edge_detection.h"
#include "gaussian_blur.h"
#include "exceptions.h"
#include "reader.h"
Parser::Parser(int argc, const char** argv) {
    if (argc == 1) {
        std::cout << "Usage:\timage_processor INPUT_FILE OUTPUT_FILE [-FILTER1 PARAM1 ...] [-FILTER2 PARAM1 ...]"
                  << std::endl;
        std::cout << std::endl;

        std::cout << "Apply several filters to bpm image" << std::endl;
        std::cout << std::endl;

        std::cout << "Filters:" << std::endl;
        std::cout << "  -crop WIDTH HEIGHT    Crop image" << std::endl;
        std::cout << "  -gs                   Apply grayscale" << std::endl;
        std::cout << "  -neg                  Apply negative" << std::endl;
        std::cout << "  -sharp                Apply sharpening" << std::endl;
        std::cout << "  -edge THRESHOLD       Apply edge detection" << std::endl;
        std::cout << "  -blur SIGMA           Apply gaussian blur" << std::endl;
    }

    if (argc < 3) {
        throw NotEnoughArgumentsException(argc);
    }

    argv_ = argv;
    argnow_ = 3;
    argc_ = argc;
    filters_["-crop"] = [&]() { DoCrop(); };
    filters_["-gs"] = [&]() { DoGrayscale(); };
    filters_["-neg"] = [&]() { DoNegative(); };
    filters_["-sharp"] = [&]() { DoSharp(); };
    filters_["-edge"] = [&]() { DoEdge(); };
    filters_["-blur"] = [&]() { DoGauss(); };
    file_to_read_ = argv_[1];
    file_to_write_ = argv_[2];
    while (argnow_ < argc) {
        auto it = filters_.find(argv[argnow_]);
        if (it == filters_.end()) {
            throw FilterNotExistsException(argv_[argnow_]);

        } else {
            it->second();
        }
    }
}
void Parser::DoCrop() {
    if (argnow_ + 2 > argc_) {
        throw std::out_of_range("usage: -crop <width> <height>");
    }
    int32_t width = 0;
    int32_t height = 0;
    argnow_ += 3;
    try {
        width = std::stoi(argv_[argnow_ - 2]);
        height = std::stoi(argv_[argnow_ - 1]);
        if (width < 0 || height < 0) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("Crop filter should get positive numbers");
    }

    doing_filters_.push_back(std::make_unique<CropFilter>(width, height));
}

void Parser::DoGrayscale() {
    doing_filters_.push_back(std::make_unique<GrayscaleFilter>());
    ++argnow_;
}
void Parser::DoNegative() {
    doing_filters_.push_back(std::make_unique<NegativeFilter>());
    ++argnow_;
}

void Parser::DoSharp() {
    doing_filters_.push_back(std::make_unique<FilterSharp>());
    ++argnow_;
}
void Parser::DoEdge() {
    if (argnow_ + 1 > argc_) {
        throw std::out_of_range("usage: -edge <threshold>");
    }
    double threshold = 0;
    argnow_ += 2;
    try {
        threshold = std::stod(argv_[argnow_ - 1]);
        if (threshold < 0 || threshold > 1) {
            throw std::exception();
        }

    } catch (const std::exception& e) {
        throw std::invalid_argument("argument should be from 0 to 1, got " + std::string(argv_[argnow_ + 1]));
    }
    doing_filters_.push_back(std::make_unique<EdgeDetection>(threshold));
}
void Parser::DoGauss() {
    if (argnow_ + 1 > argc_) {
        throw std::out_of_range("usage: -blur <sigma>");
    }
    double sigma = 0;
    argnow_ += 2;
    try {
        sigma = std::stod(argv_[argnow_ + 1]);
        if (sigma < 0) {
            throw std::exception();
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("argument should be positive " + std::string(argv_[argnow_ + 1]));
    }
    doing_filters_.push_back(std::make_unique<GaussianBlur>(sigma));
}
const char* Parser::GetFileToRead() const {
    return file_to_read_;
}
const char* Parser::GetFileToWrite() const {
    return file_to_write_;
}
const std::vector<std::unique_ptr<Filter>>& Parser::GetFilters() {
    return doing_filters_;
}
