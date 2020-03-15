#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <fstream>
#include <functional>
#include <string>

#include "vec2d.h"

void output(uint32_t t, vec2d point);

class FileOutput {
  public:
    FileOutput(const std::string &filename);

    ~FileOutput();

    std::function<void(uint32_t, vec2d)> GetCallback();

  private:
    std::ofstream file;
};

#endif  // OUTPUT_H_
