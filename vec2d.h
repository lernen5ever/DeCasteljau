#ifndef VEC2D_H_
#define VEC2D_H_

class vec2d {
  public:
    vec2d(double x, double y) : m_x(x), m_y(y) {}

    friend inline vec2d operator*(double t, const vec2d& v);

    vec2d operator+(const vec2d& v) {
      return vec2d(m_x + v.m_x, m_y + v.m_y);
    }

    double x() const {
      return m_x;
    }

    double y() const {
      return m_y;
    }

  private:
    double m_x;
    double m_y;
};

inline vec2d operator*(double t, const vec2d& v) {
  return vec2d(t * v.m_x, t * v.m_y);
}

#endif  // VEC2D_H_
