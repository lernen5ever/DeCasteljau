#include <cstdlib>  
#include <iostream>

#include "bezier.h"
#include "vec2d.h"

using std::atol;
using std::atof;
using std::cerr;
using std::cout;
using std::endl;

void output(uint32_t t, vec2d point){
  cout << time << ' ' << point.x() << ' ' << point.y() << endl;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0]
      << " MillisecsWhole MillisecsInterval x1 y1 x2 y2 ..." << endl;
    return 1;
  }
  if (argc % 2 != 0) {
    cerr << "Control points must occur in pairs" << endl;
    return 1;
  }
  uint32_t MillisecsWhole = atol(argv[1]);
  uint32_t MillisecsInterval = atol(argv[2]);
  Bezier curve;
  for (int i = 3; i < argc; i += 2) {
    curve.AddControlPoint(vec2d(atof(argv[i]), atof(argv[i + 1])));
  }
  curve.Simulate(MillisecsWhole, MillisecsInterval, output);
  
  return 0;
}
