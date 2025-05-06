#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: validate_output <output_file>" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::ifstream in(filename, std::ios::binary);

  if (!in) {
    std::cerr << "Error: Cannot open file: " << filename << std::endl;
    return 1;
  }

  int prev, curr;
  size_t index = 0;
  
  if (!in.read(reinterpret_cast<char *>(&prev), sizeof(int))) {
    std::cerr << "File is empty or unreadable." << std::endl;
    return 1;
  }

  while (in.read(reinterpret_cast<char *>(&curr), sizeof(int))) {
    ++index;
    if (curr < prev) {
      std::cerr << "Validation failed at index " << index << ": " << prev
                << " > " << curr << std::endl;
      return 1;
    }
    prev = curr;
  }

  std::cout << "Validation successful: data is sorted in ascending order."
            << std::endl;
  return 0;
}
