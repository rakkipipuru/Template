template<typename T>
struct Segment {
  using P = Point<T>;
  using L = Line<T>;
  P a, b;
  Segment() {}
  Segment(P a, P b) : a(a), b(b) {}
  bool online(const P& p) const {
    return ccw(a, b, p) == 0;
  }
  friend bool parallel(const Segment& p, const Segment& q) {
    return cross(p.a - p.b, q.a - q.b) == 0 && abs(ccw(p.a, p.b, q.a)) == 1;
  }
  friend bool intersect(const L& p, const Segment& q) {
    return ccw(p.a, p.b, q.a) * ccw(p.a, p.b, q.b) < 0;
  }
  friend bool intersect(const Segment& p, const Segment& q) {
    return ccw(p.a, p.b, q.a) * ccw(p.a, p.b, q.b) <= 0 && ccw(q.a, q.b, p.a) * ccw(q.a, q.b, p.b) <= 0;
  }
  friend P intersection(const L& p, const Segment& q) {
    assert(intersect(p, q));
    return p.a + (p.b - p.a) * cross(q.b - q.a, q.a - p.a) / cross(q.b - q.a, p.b - p.a);
  }
  friend P intersection(const Segment& p, const Segment& q) {
    assert(intersect(p, q));
    return p.a + (p.b - p.a) * cross(q.b - q.a, q.a - p.a) / cross(q.b - q.a, p.b - p.a);
  }
};
