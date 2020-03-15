
#include <functional>
#include <iostream>
#include <string>

#include "output.h"
#include "vec2d.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;

void output(uint32_t time, vec2d point) {
  cout << time << ' ' << point.x() << ' ' << point.y() << endl;
}

FileOutput::FileOutput(const string &filename) {
  file.open(filename, ofstream::out);
}

FileOutput::~FileOutput() {
  file.close();
}

std::function<void(uint32_t, vec2d)> FileOutput::GetCallback() {
  return [this](uint32_t time, vec2d point) {
    this->file << time << ' ' << point.x() << ' ' << point.y() << '\n';
  };
}
