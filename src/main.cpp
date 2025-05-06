#include "Config.hpp"
#include "TapeSorter.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: sorter <input_file>" << std::endl;
    return 1;
  }

  std::string inputPath = argv[1];
  // Выходной файл
  std::string outputPath = "output.bin";
  // Файл конфигурации
  std::string configPath = "config.json";

  try {

    Config config = Config::load(configPath);

    // Ограничение по памяти - Кб
    size_t memoryLimit = 1 * 1024;

    TapeSorter sorter;
    sorter.sort(inputPath, outputPath, config, memoryLimit);

    std::cout << "Sorting complete." << std::endl;
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
    return 1;
  }

  return 0;
}
