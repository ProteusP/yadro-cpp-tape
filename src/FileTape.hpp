#pragma once

#include "TapeInterface.hpp"
#include <fstream>
#include <string>
#include <thread>

class FileTape : public TapeInterface {
private:
  std::fstream file;
  std::string filename;
  int delayRead;
  int delayWrite;
  int delayMove;
  int delayRewind;
  size_t pos;

  void delay(int ms);

public:
  FileTape(const std::string &path, int readMs, int writeMs, int moveMs, int rewindMs);
  ~FileTape();

  bool moveForward() override;
  bool moveBackward() override;
  bool read(int &val) override;
  bool write(int val) override;
  bool rewind() override;
};