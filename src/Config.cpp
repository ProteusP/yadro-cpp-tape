#include "Config.hpp"
#include "../third_party/nlohmann/json.hpp"
#include <fstream>

Config Config::load(const std::string &configPath) {
  std::ifstream file(configPath);
  nlohmann::json jFile;

  file >> jFile;

  Config config;
  config.delayMove = jFile["delay_move"];
  config.delayWrite = jFile["delay_write"];
  config.delayRead = jFile["delay_read"];
  config.delayRewind = jFile["delay_rewind"];

  return config;
}