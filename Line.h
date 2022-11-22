template<typename T>
struct Line {
  using P = Point<T>;
  P a, b;
  Line() {}
  Line(P a, P b) : a(a), b(b) {}
  bool online(const P& p) const {
    return abs(ccw(a, b, p)) != 1;
  }
  friend bool parallel(const Line& p, const Line& q) {
    return cross(p.a - p.b, q.a - q.b) == 0 && abs(ccw(p.a, p.b, q.a)) == 1;
  }
  friend bool intersect(const Line& p, const Line& q) {
    return !parallel(p, q);
  }
  friend P intersection(const Line& p, const Line& q) {
    assert(intersect(p, q));
    return p.a + (p.b - p.a) * cross(q.b - q.a, q.a - p.a) / cross(q.b - q.a, p.b - p.a);
  }
};
