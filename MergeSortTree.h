template<typename T>
struct MergeSortTree {
  int n;
  vector<vector<T>> a;
  MergeSortTree() {}
  MergeSortTree(int _n) : n(_n + 5), a(4 * n + 5) {}
  void init(int _n, const vector<T>& init) {
    n = _n + 5;
    a = vector<vector<T>> (4 * n + 5);
    function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        a[p].push_back(init[l]);
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 1, _n + 1);
  }
  void pull(int p) {
    int i = 0, j = 0;
    int L = a[2 * p].size(), R = a[2 * p + 1].size();
    while (i < L && j < R) {
      if (a[2 * p][i] < a[2 * p + 1][j]) {
        a[p].push_back(a[2 * p][i++]);
      }
      if (a[2 * p][i] >= a[2 * p + 1][j]) {
        a[p].push_back(a[2 * p + 1][j++]);
      }
    }
    while (i < L) {
      a[p].push_back(a[2 * p][i++]);
    }
    while (j < R) {
      a[p].push_back(a[2 * p + 1][j++]);
    }
  }
  int query(int p, int l, int r, int x, int y, T v) {
    if (l >= y || r <= x) {
      return 0;
    }
    if (x <= l && r <= y) {
      int l2 = lower_bound(a[p].begin(), a[p].end(), v) - a[p].begin();
      return (l2 < int(a[p].size()) && a[p][l2] == v ? 1 : 0);
    }
    int m = (l + r) / 2;
    return max(query(2 * p, l, m, x, y, v), query(2 * p + 1, m, r, x, y, v));
  }
};
