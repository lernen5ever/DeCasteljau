#include <cstring>  
#include <cstdlib>  
#include <iostream>
#include <string>

#include "bezier.h"
#include "output.h"
#include "vec2d.h"

using std::cerr;
using std::endl;
using std::exit;
using std::strncmp;
using std::string;

static double GetDouble(const string &str) {
  if (str.empty()) {
    cerr << "Number must not be empty" << endl;
    exit(1);
  }
  size_t len = 0;
  double result = stod(str, &len);
  if (len != str.size()) {
    cerr << "Not a number: '" << str << '\'' << endl;
    exit(1);
  }
  return result;
}

static double GetMillisecs(const string &str) {
  if (str.empty()) {
    cerr << "Number must not be empty" << endl;
    exit(1);
  }
  size_t len = 0;
  long long result = stoll(str, &len);
  if (len != str.size()) {
    cerr << "Not an integer: '" << str << '\'' << endl;
    exit(1);
  }
  if (result <= 0) {
    cerr << "Integer not positive: '" << str << '\'' << endl;
    exit(1);
  } else if (result > 0xFFFFFFFFL) {
    cerr << "Integer too large: '" << str << '\'' << endl;
    exit(1);
  }
  return result;
}

int main(int argc, const char *argv[]) {
  int start = 1;
  if ((argc > 2) && (strncmp(argv[1], "-o", 2) == 0)) {
    start = (argv[1][2] == '\0') ? 3 : 2;
  }
  bool file = (start != 1);
  if (argc < start + 2) {
    cerr << "Usage: " << argv[0]
      << " [-o file] MillisecsWhole MillisecsInterval x1 y1 x2 y2 ..." << endl;
    return 1;
  }
  if ((argc - start) % 2 != 0) {
    cerr << "Control points must occur in pairs" << endl;
    return 1;
  }
  uint32_t MillisecsWhole = GetMillisecs(argv[start]);
  uint32_t MillisecsInterval = GetMillisecs(argv[start + 1]);
  Bezier curve;
  for (int i = start + 2; i < argc; i += 2) {
    curve.AddControlPoint(vec2d(GetDouble(argv[i]), GetDouble(argv[i + 1])));
  }
  if (file) {
    string Filename(start == 2 ? (argv[1] + 2) : argv[2]);
    curve.Simulate(MillisecsWhole, MillisecsInterval,
                   FileOutput(Filename).GetCallback());
  } else {
    curve.Simulate(MillisecsWhole, MillisecsInterval, output);
  }
  return 0;
}
