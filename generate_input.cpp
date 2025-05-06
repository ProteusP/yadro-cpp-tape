#include <fstream>
#include <iostream>
#include <random>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: generate_input <output_file> <count>" << std::endl;
    return 1;
  }

  std::string outputFile = argv[1];
  int count = std::stoi(argv[2]);

  std::ofstream out(outputFile, std::ios::binary);
  if (!out) {
    std::cerr << "Error: Could not open output file." << std::endl;
    return 1;
  }

  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-100000, 100000);

  for (int i = 0; i < count; ++i) {
    int value = dist(rng);
    std::cout << value << std::endl;
    out.write(reinterpret_cast<char *>(&value), sizeof(int));
  }

  std::cout << "Generated " << count << " integers in file: " << outputFile
            << std::endl;
  return 0;
}
