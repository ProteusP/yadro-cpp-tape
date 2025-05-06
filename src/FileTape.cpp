#include "FileTape.hpp"
#include <chrono>
#include <iostream>

FileTape::FileTape(const std::string &path, int readMs, int writeMs, int moveMs,
                   int rewindMs)
    : filename(path), delayRead(readMs), delayWrite(writeMs), delayMove(moveMs),
      delayRewind(rewindMs), pos(0) {

  file.open(path, std::ios::in | std::ios::out | std::ios::binary);

  if (!file) {
    file.clear();
    file.open(path, std::ios::out | std::ios::binary);
    file.close();
    file.open(path, std::ios::in | std::ios::out | std::ios::binary);
  }
}

FileTape::~FileTape() { file.close(); }

void FileTape::delay(int ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool FileTape::moveBackward() {
  if (pos == 0) {
    return false;
  }

  delay(delayMove);
  --pos;
  return true;
}

bool FileTape::moveForward() {
  delay(delayMove);
  ++pos;
  return true;
}

bool FileTape::read(int &val) {
  delay(delayRead);

  file.seekg(pos * sizeof(int), std::ios::beg);
  file.read(reinterpret_cast<char *>(&val), sizeof(int));

  return file.good();
}

bool FileTape::write(int val) {
  delay(delayMove);

  file.seekg(pos * sizeof(int), std::ios::beg);
  file.write(reinterpret_cast<const char *>(&val), sizeof(int));

  return file.good();
}

bool FileTape::rewind() {
  delay(delayRewind);
  pos = 0;
  return true;
}