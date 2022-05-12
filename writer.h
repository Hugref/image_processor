#pragma once
#include "Image.h"
#include <string>

class Writer {
public:
    static void Write(const Image, const std::string &write_file);
};
