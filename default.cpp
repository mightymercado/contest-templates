#include <cstdio>
#include <iomanip> 
#include <numeric>
#include <cmath>
#include <assert.h>
#include <deque>
#include <iostream>
#include <queue>
#include <string.h>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include <bitset>
#include <array>
#include <iterator>
#define forn(i, n) for (int i = 0; i < n; ++i)
#define ford(i, s, e) for  (int i = s; i <= e; ++i)
#define fordr(i, s, e) for (int i = s; i >= e; --i)
#define fornr(i, n) for (int i = n - 1; i >= 0; --i)
#define testcase int _t; cin >> _t; while (_t--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using i64 = long long;
using namespace std;
 
void YES(bool y) {
  cout << (y ? "YES\n" : "NO\n");
}
 
void Yes(bool y) {
  cout << (y ? "Yes\n" : "No\n");
}
 
template<typename T>
ostream& operator<<(ostream& os, vector<T> const &v) {
  for (T x: v) {
    os << x << ' ';
  }
  os << '\n';
  return os;
} 
 
template<typename T>
istream& operator>>(istream& is, vector<T> &v) {
  for (T &x: v) {
    is >> x;
  }
  return is;
}

template<typename T>
T max(vector<T> a) {
  T mx = a[0];
  for (int e : a) mx = max(mx, e);
  return mx;
}

template<typename T>
T min(vector<T> a) {
  T mn = a[0];
  for (int e : a) mn = min(mn, e);
  return mn;
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
}
