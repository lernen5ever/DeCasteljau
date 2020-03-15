#ifndef BEZIER_H_
#define BEZIER_H_

#include <functional>
#include <vector>

#include "vec2d.h"

class Bezier {
  public:
    void AddControlPoint(const vec2d& control_point) {
      m_ControlPoints.push_back(control_point);
    }

    vec2d Interpolate(double t) const;

    void Simulate(uint32_t MillisecsWhole, uint32_t MillisecsInterval,
                  std::function<void(uint32_t, vec2d)> callback) const;

  private:
    std::vector<vec2d> m_ControlPoints;
};

#endif  // BEZIER_H_
