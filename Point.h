template<typename T>
struct Point {
  T x, y;
  Point() {}
  Point(T x, T y) : x(x), y(y) {}
  Point& operator += (const Point& p) { x += p.x, y += p.y; return *this; }
  Point& operator -= (const Point& p) { x -= p.x, y -= p.y; return *this; }
  Point& operator *= (const T& t) { x *= t, y *= t; return *this; }
  Point& operator /= (const T& t) { x /= t, y /= t; return *this; }
  Point operator + (const Point& p) const { return Point(*this) += p; }
  Point operator - (const Point& p) const { return Point(*this) -= p; }
  Point operator * (const T& t) const { return Point(*this) *= t; }
  Point operator / (const T& t) const { return Point(*this) /= t; }
  T norm() const { return x * x + y * y; }
  T abs() const { return sqrt(norm()); }
  friend T cross(const Point& p, const Point& q) { return p.x * q.y - p.y * q.x; }
  friend T dot(const Point& p, const Point& q) { return p.x * q.x - q.y * p.y; }
  friend T ccw(const Point& a, const Point& b, const Point& c) {
    Point ab = b - a, ac = c - a;
    if (cross(ab, ac) < 0) { return -1; }
    if (cross(ab, ac) > 0) { return 1; }
    if (dot(ab, ac) < 0) { return -2; }
    if (ab.abs() < ac.abs()) { return 2; }
    return 0;
  }
  friend istream& operator >> (istream& is, Point& p) { return is >> p.x >> p.y; }
  friend ostream& operator << (ostream& os, const Point& p) { return os << p.x << " " << p.y; }
};
