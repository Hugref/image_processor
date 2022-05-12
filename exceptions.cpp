#include <iostream>
#include "exceptions.h"
FileOpenFailedException::FileOpenFailedException(std::string path)
    : message_(std::string("failed to open file: ") + path) {
}
NotEnoughArgumentsException::NotEnoughArgumentsException(const int& argc)
    : message_("Not enough args: " + std::to_string(argc)) {
}
const char* NotEnoughArgumentsException::what() const noexcept {

    return message_.c_str();
}
FilterNotExistsException::FilterNotExistsException(const std::string& filter)
    : message_("this filter does not exist:" + filter) {
}
const char* FilterNotExistsException::what() const noexcept {
    return message_.c_str();
}
