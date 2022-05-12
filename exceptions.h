#pragma once
#include <exception>
#include <string>
class FileOpenFailedException : public std::exception {
public:
    FileOpenFailedException(std::string path);
    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class NotEnoughArgumentsException : public std::exception {
public:
    NotEnoughArgumentsException(const int& argc);

    const char* what() const noexcept override;

private:
    std::string message_;
};
class FilterNotExistsException : public std::exception {
public:
    FilterNotExistsException(const std::string& filter);

    const char* what() const noexcept override;

private:
    std::string message_;
};