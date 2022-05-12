#include "writer.h"
#include <cmath>
#include <string>
#include "exceptions.h"
template <typename T>
void WriteFile(std::ofstream &file, const T &numb) {
    file.write(reinterpret_cast<const char *>(&numb), sizeof(numb));
}

const int16_t NUMBER_OF_BITS_PER_PIXEL = 24;
const int16_t COLOR_PLANE = 1;
const int32_t RESOLUTION = 2835;
const int32_t OFFSET = 54;
const int32_t HEADER = 40;
const int8_t PAD = 0;
const int32_t ZERO = 0;

void Writer::Write(const Image imag, const std::string &write_file) {
    std::ofstream output(write_file, std::ios::out | std::ios::binary);
    const int32_t size = imag.GetHeight() * (3 * imag.GetWidth() + imag.GetWidth() % 4) + OFFSET;
    const int32_t size_of_bitmap = size - OFFSET;
    const int32_t height = imag.GetHeight();
    const int32_t width = imag.GetWidth();
    if (output.is_open()) {
        output.write("BM", 2);
        WriteFile(output, size);
        WriteFile(output, ZERO);
        WriteFile(output, OFFSET);
        WriteFile(output, HEADER);
        WriteFile(output, width);
        WriteFile(output, height);
        WriteFile(output, COLOR_PLANE);
        WriteFile(output, NUMBER_OF_BITS_PER_PIXEL);
        WriteFile(output, ZERO);
        WriteFile(output, size_of_bitmap);
        WriteFile(output, RESOLUTION);
        WriteFile(output, RESOLUTION);
        WriteFile(output, ZERO);
        WriteFile(output, ZERO);

        for (int32_t y = 0; y < imag.GetHeight(); ++y) {

            for (int32_t x = 0; x < imag.GetWidth(); ++x) {
                Pixel pixel = imag.GetPixel(x, y);
                WriteFile(output, pixel.blue);
                WriteFile(output, pixel.green);
                WriteFile(output, pixel.red);
            }
            for (int k = 0; k < imag.GetLenPadd(); ++k) {
                WriteFile(output, PAD);
            }
        }
        output.close();
    } else {
        throw FileOpenFailedException(write_file);
    }
}
