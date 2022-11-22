struct Merge {
  int operator () (const int& x, const int& y) const {
    return x ^ y;
  }
};

template<class T, class Merge = std::plus<T>>
struct SegmentTree {
  int n;
  Merge merge;
  vector<T> a;
  SegmentTree() : merge(Merge()) {}
  SegmentTree(int _n) : n(_n + 5), merge(Merge()), a(4 * n + 5) {}
  SegmentTree(int _n, const vector<T>& init) : SegmentTree(_n) {
    function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        a[p] = init[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
    };
    build(1, 1, _n + 1);
  }
  void init(int _n) {
    n = _n + 5;
    a = vector<T> (4 * n + 5);
  }
  void pull(int p) {
    a[p] = merge(a[2 * p], a[2 * p + 1]);
  }
  void modify(int p, int l, int r, int x, T v) {
    if (r - l == 1) {
      a[p] = v;
      return;
    }
    int m = (l + r) / 2;
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }
  void modify(int x, T v) {
    modify(1, 1, n - 4, x, v);
  }
  T rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return 0;
    }
    if (x <= l && r <= y) {
      return a[p];
    }
    int m = (l + r) / 2;
    return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
  }
  T rangeQuery(int l, int r) {
    return rangeQuery(1, 1, n - 4, l, r);
  }
};
