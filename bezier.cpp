
#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "bezier.h"
#include "vec2d.h"

using std::function;
using std::numeric_limits;
using std::vector;

vec2d Bezier::Interpolate(double t) const {
  auto b = m_ControlPoints;
  auto n = b.size();
  if (n == 0) {
    return vec2d(numeric_limits<double>::signaling_NaN(),
                 numeric_limits<double>::signaling_NaN());
  }
  while (--n > 0) {
    for (vector<vec2d>::size_type i = 0; i < n; ++i) {
      b[i] = (1 - t) * b[i] + t * b[i + 1];
    }
  }
  return b[0];
}

void Bezier::Simulate(uint32_t MillisecsWhole, uint32_t MillisecsInterval,
                      function<void(uint32_t, vec2d)> callback) const {

  for (uint32_t t = 0; t <= MillisecsWhole; t += MillisecsInterval) {
    callback(t, Interpolate(double(t) / MillisecsWhole));
  }
}
