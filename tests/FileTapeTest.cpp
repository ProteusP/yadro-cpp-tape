#include "../src/FileTape.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

TEST(FileTapeTest, ReadWriteWorksCorrectly) {
  const std::string path = "test_tape.bin";

  std::filesystem::remove(path);

  FileTape tape(path, 0, 0, 0, 0); 

  EXPECT_TRUE(tape.write(42));
  tape.rewind();

  int value = 0;
  EXPECT_TRUE(tape.read(value));
  EXPECT_EQ(value, 42);

  std::filesystem::remove(path);
}

TEST(FileTapeTest, MoveForwardBackward) {
  const std::string path = "test_move.bin";
  std::filesystem::remove(path);

  FileTape tape(path, 0, 0, 0, 0);
  tape.write(1);
  tape.moveForward();
  tape.write(2);
  tape.rewind();

  int val = 0;
  tape.read(val);
  EXPECT_EQ(val, 1);

  tape.moveForward();
  tape.read(val);
  EXPECT_EQ(val, 2);

  std::filesystem::remove(path);
}
