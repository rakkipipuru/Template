struct HLD {
  int tot;
  vector<int> dep, siz, par, top, id, node, son;
  vector<vector<int>> edges;
  HLD() {}
  HLD(int _n) : tot(0), dep(_n + 5), son(_n + 5), siz(_n + 5), par(_n + 5), top(_n + 5), id(_n + 5), node(_n + 5), edges(_n + 5) {}
  void init(int _n) {
    tot = 0;
    dep = vector<int> (_n + 5);
    son = vector<int> (_n + 5);
    siz = vector<int> (_n + 5);
    par = vector<int> (_n + 5);
    top = vector<int> (_n + 5);
    id = vector<int> (_n + 5);
    node = vector<int> (_n + 5);
    edges = vector<vector<int>> (_n + 5);
  }
  void dfsHeavyEdge(int u, int p) {
    dep[u] = dep[p] + 1;
    siz[u] = 1;
    for (int v : edges[u]) {
      if (v != p) {
        par[v] = u;
        dfsHeavyEdge(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) {
          son[u] = v;
        }
      }
    }
  }
  void dfsHeavyPath(int u, int pt) {
    top[u] = pt;
    id[u] = ++tot;
    node[tot] = u;
    if (son[u]) {
      dfsHeavyPath(son[u], pt);
    }
    for (int v : edges[u]) {
      if (v != par[u] && v != son[u]) {
        dfsHeavyPath(v, v);
      }
    }
  }
  void addEdge(int u, int v) {
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
};
