#pragma once

class TapeInterface {
public:
  virtual bool moveForward() = 0;
  virtual bool moveBackward() = 0;
  virtual bool read(int &val) = 0;
  virtual bool write(int val) = 0;
  virtual bool rewind() = 0;

  virtual ~TapeInterface() = default;
};