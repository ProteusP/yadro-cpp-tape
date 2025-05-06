#include "TapeSorter.hpp"
#include "FileTape.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

void TapeSorter::sort(const std::string &inputPath,
                      const std::string &outputPath, const Config &config,
                      size_t memoryLimitBytes) {

  const size_t intSize = sizeof(int);
  size_t chunkSize = memoryLimitBytes / intSize;

  std::vector<std::string> tempFiles;
  std::filesystem::create_directories("tmp");

  {
    FileTape input(inputPath, config.delayRead, config.delayWrite,
                   config.delayMove, config.delayRewind);
    input.rewind();

    while (true) {
      std::vector<int> buffer;
      int value;

      for (size_t i = 0; i < chunkSize && input.read(value); ++i) {
        buffer.push_back(value);
        input.moveForward();
      }

      if (buffer.empty())
        break;

      std::sort(buffer.begin(), buffer.end());

      std::ostringstream tmpName;
      tmpName << "tmp/chunk_" << tempFiles.size() << ".bin";
      std::string tmpPath = tmpName.str();
      tempFiles.push_back(tmpPath);

      std::ofstream out(tmpPath, std::ios::binary);
      for (int val : buffer) {
        out.write(reinterpret_cast<char *>(&val), intSize);
      }
    }
  }

  {
    FileTape output(outputPath, config.delayRead, config.delayWrite,
                    config.delayMove, config.delayRewind);
    output.rewind();

    std::vector<std::ifstream> inputs;
    std::vector<int> curValues;
    std::vector<bool> hasValue;

    for (const auto &path : tempFiles) {
      inputs.emplace_back(path, std::ios::binary);
      int val;

      if (inputs.back().read(reinterpret_cast<char *>(&val), intSize)) {
        curValues.push_back(val);
        hasValue.push_back(true);
      } else {
        curValues.push_back(0);
        hasValue.push_back(false);
      }
    }
    while (true) {
      int minIndex = -1;

      for (size_t i = 0; i < curValues.size(); ++i) {
        if (hasValue[i]) {
          if (minIndex == -1 || curValues[i] < curValues[minIndex]) {
            minIndex = static_cast<int>(i);
          }
        }
      }

      if (minIndex == -1)
        break;
      output.write(curValues[minIndex]);
      output.moveForward();

      int val;
      if (inputs[minIndex].read(reinterpret_cast<char *>(&val), intSize)) {
        curValues[minIndex] = val;
      } else {
        hasValue[minIndex] = false;
      }
    }
  }

  for (const auto &path : tempFiles) {
    std::filesystem::remove(path);
  }
}