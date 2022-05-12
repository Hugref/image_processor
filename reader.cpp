#include "reader.h"
#include "exceptions.h"
template <typename T>
void ReadFile(std::ifstream &file, T &numb) {
    file.read(reinterpret_cast<char *>(&numb), sizeof(numb));
}

Image Reader::Read(const char *read_file) {
    uint32_t header = 0;
    std::ifstream input(read_file, std::ios::in | std::ios::binary);
    uint32_t size = 0;
    uint32_t offset = 0;
    uint32_t width = 0;
    int32_t height = 0;
    if (input.is_open()) {
        input.seekg(2, std::ios::cur);
        ReadFile(input, size);

        input.seekg(4, std::ios::cur);
        ReadFile(input, offset);
        ReadFile(input, header);
        ReadFile(input, width);
        ReadFile(input, height);
        input.seekg(offset, std::ios::beg);

        Image image(abs(height), width);

        for (int32_t y = 0; y < abs(height); ++y) {

            for (uint32_t x = 0; x < width; ++x) {
                Pixel pixel = {0, 0, 0};
                ReadFile(input, pixel.blue);
                ReadFile(input, pixel.green);
                ReadFile(input, pixel.red);
                if (height > 0) {

                    image.SetPixel(pixel, x, y);
                } else {
                    image.SetPixel(pixel, x, abs(height) - 1 - y);
                }
            }
            input.seekg(image.GetLenPadd(), std::ios::cur);
        }
        return image;
    } else {
        throw FileOpenFailedException(read_file);
    }
}
