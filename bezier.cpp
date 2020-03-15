
#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "bezier.h"
#include "vec2d.h"

#define TIME_SYNC

#ifdef TIME_SYNC
  using std::chrono::steady_clock;
  using std::chrono::milliseconds;
  using std::this_thread::sleep_for;
#endif
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
#ifdef TIME_SYNC
  auto EntryTime = steady_clock::now();
#endif
  for (uint32_t t = 0; t <= MillisecsWhole; t += MillisecsInterval) {
#ifdef TIME_SYNC
    auto SleepTo = EntryTime + milliseconds(t);
    auto Current = steady_clock::now();
    if (SleepTo > Current) {
      sleep_for(SleepTo - Current);
    }
#endif
    callback(t, Interpolate(double(t) / MillisecsWhole));
  }
}
