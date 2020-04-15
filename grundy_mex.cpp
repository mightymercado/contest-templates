pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <cstdio>
#include <numeric>
#include <cmath>
#include <assert.h>
#include <deque>
#include <iostream>
#include <string.h>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <bitset>
#include <array>
#define loop(i, n) for (int i = 0; i < n; i++)
#define testcase int _t; cin >> _t; while (_t--)
#define all(x) (x).begin(), (x).end()
using i64 = long long;
using namespace std;
 
void yes(bool y) {
  cout << (y ? "YES\n" : "NO\n");
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
 
const int mod = 998244353;
// dp[0] = can use any attack
// dp[1] = cant use infantry
// dp[2] = cant use cavalry
const int maxn = 3e5;
int dp[3][maxn + 1], p; // p is the cycle
 
int mex(vector<int> a) {
  sort(all(a));
  a.resize(unique(all(a)) - a.begin());
  for (int i = 0; i < a.size(); ++i) {
    if (i != a[i]) return i;
  }
  return a.back() + 1;  
}
 
int get(int dp[maxn], i64 n) {
  // trivial
  if (n <= 200) 
    return dp[n];
  
  // p is cycle size
  return dp[(n - 200) % p + 200];
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  testcase {
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    vector<i64> a(n);
    cin >> a;
    // grundy numbers for one pile
    // length of cycle should be small
    // use a table of 200 as seed values
    p = -1;
    for (int i = 1; i <= 300; i++) {
      dp[0][i] = mex({dp[0][max(i - x, 0)], dp[1][max(i - y, 0)], dp[2][max(i - z, 0)]});
      dp[1][i] = mex({dp[0][max(i - x, 0)], dp[2][max(i - z, 0)]});
      dp[2][i] = mex({dp[0][max(i - x, 0)], dp[1][max(i - y, 0)]});
      // pre compute first 200 values
      if (i <= 200) continue;
      // are the value a repitition of the last 5 of the 200 values
      bool ok = true;
      for (int j = 0; j < 5; j++) {
        ok &= dp[0][200 - j] == dp[0][i - j];
        ok &= dp[1][200 - j] == dp[1][i - j];
        ok &= dp[2][200 - j] == dp[2][i - j];
      }
      // if so p - 200 will represent cycle from that 200
      if (ok) {
        p = i;
        break;
      }
    }
 
    p -= 200;
    
    int xo = 0;
    for (int i = 0; i < n; i++) {
      xo ^= get(dp[0], a[i]);
    }
 
    // try all first moves
    // castles are independent
    int ans = 0;
    for (int i = 0; i < n; i++) {
      xo ^= get(dp[0], a[i]); // unapply grundy number at index i
      // use cavalry first
      // if non zero then its a winning position
      ans += (xo ^ get(dp[0], a[i] - x)) == 0; // use mixed
      ans += (xo ^ get(dp[1], a[i] - y)) == 0; // use infantry
      ans += (xo ^ get(dp[2], a[i] - z)) == 0; // use cavalry
      xo ^= get(dp[0], a[i]); // reapply
    }
    cout << ans << '\n';
  }
}
