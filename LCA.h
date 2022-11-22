struct LCA {
  int LOG;
  vector<int> dep;
  vector<vector<int>> edges, par;
  LCA() {}
  LCA(int _n) : LOG(__lg(_n + 5)), dep(_n + 5), edges(_n + 5), par(LOG + 1, vector<int> (_n + 5)) {}
  void init(int _n) {
    LOG = __lg(_n + 5);
    dep = vector<int> (_n + 5);
    edges = vector<vector<int>> (_n + 5);
    par = vector<vector<int>> (LOG + 1, vector<int> (_n + 5));
  }
  void dfs(int u, int p) {
    for (int v : edges[u]) {
      if (v != p) {
        dep[v] = dep[u] + 1;
        par[0][v] = u;
        for (int i = 0; i < LOG; ++i) {
          par[i + 1][v] = par[i][par[i][v]];
        }
        dfs(v, u);
      }
    }
  }
  int lca(int u, int v) {
    if (dep[u] < dep[v]) {
      swap(u, v);
    }
    int diff = dep[u] - dep[v];
    for (int i = LOG; i >= 0; --i) {
      if (diff >> i & 1) {
        u = par[i][u];
      }
    }
    if (u == v) {
      return u;
    }
    for (int i = LOG; i >= 0; --i) {
      if (par[i][u] != par[i][v]) {
        u = par[i][u];
        v = par[i][v];
      }
    }
    return par[0][u];
  }
  void addEdge(int u, int v) {
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
};
