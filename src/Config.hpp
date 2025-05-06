#pragma once

#include <string>

struct Config {
  int delayRead;
  int delayWrite;
  int delayMove;
  int delayRewind;

  static Config load(const std::string &configPath);
};