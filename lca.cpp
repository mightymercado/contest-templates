
vector<vector<int>> adj;
vector<array<int, 19>> par;
vector<int> dep;
int n;

void dfs(int x, int d, int p) {
  dep[x] = d;
  for (int y : adj[x]) if (y != p)
    par[y][0] = x, dfs(y, d + 1, x);
}

void gawin() {
  par[0][0] = 0;
  dfs(0, 0, -1);
  for (int i = 1; i < 19; i++)
    for (int j = 0; j < n; j++) 
      par[j][i] = par[par[j][i - 1]][i - 1];
}

int walk(int i, int k) {
  for (int d = 0; d < 19; d++)
    if (((1 << d) & k) > 0)
      i = par[i][d];
  return i;
}

int lca(int i, int j) {
  if (dep[i] > dep[j]) swap(i, j);
  j = walk(j, abs(dep[j] - dep[i]));
  if (i == j) return i;
  for (int d = 18; d >= 0; d--) 
    if (par[i][d] != par[j][d]) 
      i = par[i][d], j = par[j][d];
  return par[i][0];   
}

int dista(int i, int j) {
  return dep[i] + dep[j] - 2 * dep[lca(i, j)];
}
