#pragma once

#include "Config.hpp"
#include <string>

class TapeSorter {
public:
  void sort(const std::string &inputPath, const std::string &outputPath,
            const Config &config, size_t memoryLimitBytes);
};