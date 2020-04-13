#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <cstdio>
#include <numeric>
#include <cmath>
#include <deque>
#include <iostream>
#include <string.h>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <array>
#define loop(i, n) for (int i = 0; i < n; i++)
#define testcase int _t; cin >> _t; while (_t--)
using i64 = long long;
using namespace std;

string yes(bool y) {
  return y ? "YES" : "NO";
}
 
template<typename T>
ostream& operator<<(ostream& os, vector<T> const &v) {
  for (T x: v) {
    os << x << ' ';
  }
  cout << '\n';
  return os;
}
 
template<typename T>
istream& operator>>(istream& is, vector<T> &v) {
  for (T &x: v) {
    is >> x;
  }
  return is;
}

const int maxn = 2 * 1e5;
const int maxlogn = 19;
int par[maxn][19];
vector<int> adj[maxn];
int depth[maxn];
bitset<maxn> vis;
int n;

void dfs(int x, int d) {
  depth[x] = d;
  vis[x] = 1;

  for (int y : adj[x]) {
    if (!vis[y]) {
      par[y][0] = x;
      dfs(y, d + 1);
    }
  }
}

void gawin() {
  par[0][0] = 0;
  dfs(0, 0);
  
  for (int i = 1; i < 19; i++) {
    for (int j = 0; j < n; j++) {
      par[j][i] = par[par[j][i - 1]][i - 1];
    }
  }
}

int walk(int i, int k) {
  for (int d = 0; d < 19; d++) {
    if (((1 << d) & k) > 0) {
      i = par[i][d];
    }
  }
  return i;
}

int lca(int i, int j) {
  if (depth[i] > depth[j]) 
    i = walk(i, depth[i] - depth[j]);
  else if (depth[i] < depth[j])
    j = walk(j, depth[j] - depth[i]);
  if (i == j)
    return i;

  for (int d = 18; d >= 0; d--) {
    if (par[i][d] != par[j][d]) {
      i = par[i][d];
      j = par[j][d];
    }
  }
  return par[i][0];   
}

int dista(int i, int j) {
  return depth[i] + depth[j] - 2 * depth[lca(i, j)];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 0, u, v; i < n - 1; i++) {
    cin >> u >> v;
    --u; --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  gawin();
  i64 d = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 2 * i; j <= n; j += i) {
      d += dista(i - 1, j - 1) + 1;
    }
  }
  cout << d << '\n';
}
