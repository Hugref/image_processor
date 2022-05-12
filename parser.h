#pragma once
#include "Image.h"
#include "unordered_map"
#include <string>
#include <functional>
#include <memory>
#include "filter.h"
class Parser {
public:
    Parser(int argc, const char* argv[]);
    const char* GetFileToRead() const;
    const char* GetFileToWrite() const;
    const std::vector<std::unique_ptr<Filter>>& GetFilters();

private:
    void DoCrop();
    void DoGrayscale();
    void DoNegative();
    void DoSharp();
    void DoEdge();
    void DoGauss();
    std::unordered_map<std::string, std::function<void()>> filters_;
    int argnow_;
    const char** argv_;
    int argc_;
    const char* file_to_read_;
    const char* file_to_write_;
    std::vector<std::unique_ptr<Filter>> doing_filters_ = {};
};
