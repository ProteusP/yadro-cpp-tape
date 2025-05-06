#include "../src/Config.hpp"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

TEST(ConfigTest, LoadParsesCorrectValues) {
  const std::string configFile = "test_config.json";

  std::ofstream out(configFile);
  out << R"({
        "delay_move": 11,
        "delay_write": 22,
        "delay_read": 33,
        "delay_rewind": 44
    })";
  out.close();

  Config config = Config::load(configFile);

  EXPECT_EQ(config.delayMove, 11);
  EXPECT_EQ(config.delayWrite, 22);
  EXPECT_EQ(config.delayRead, 33);
  EXPECT_EQ(config.delayRewind, 44);

  std::remove(configFile.c_str());
}
