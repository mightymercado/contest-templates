vector<array<vector<int>,2>> bipartite(int n, vector<vector<int>> adj) {
  vector<int> color(n, 0);
  vector<int> occ[2];

  auto dfs = [&](auto dfs, int u, int c) -> bool {
    color[u] = c;
    for (int v : adj[u]) {
      if (color[v] == 0) {
        if (!dfs(dfs, v, c ^ 3)) return false;
      } else if (color[v] == c) {
        return false;
      }
    }
    occ[color[u] - 1].push_back(u);
    return true;
  };

  bool ok = true;
  vector<array<vector<int>,2>> ret;
  for (int i = 0; i < n; i++) {
    if (color[i] == 0) {
      for (int j = 0; j < 2; j++) occ[j].clear();
      if (!dfs(dfs, i, 1)) {
        ok = false; break;
      }
      ret.push_back({occ[0], occ[1]});
    }
  }

  if (!ok) return {};
  return ret;
}
