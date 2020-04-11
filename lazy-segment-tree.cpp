#include <iostream>
#include <numeric>
#include <vector>
#include <string.h>
#include <map>
#include <set>
#define loop(i, n) for (int i = 0; i < n; i++)
#define testcase int _t; cin >> _t; while (_t--)
using i64 = long long;
using namespace std;

const int maxn = 5 * 1e5;

i64 node[3 * maxn];
i64 pending[3 * maxn];
template <typename T>
class SegmentTree {
public:
  int n;
  SegmentTree(int n) {
    this->n = n;
  }
  T query(int ql, int qr) {
    // cout << ql << " " << qr << " " << n - 1 << endl;
    return _query(1, 0, n - 1, ql, qr);
  }

  void update(int ql, int qr, T v) {
    _update(1, 0, n - 1, ql, qr, v);
  }
private:

  // void build(int i, int l, int r) {
  //   if (l == r) {
  //     node[i] = -1e18;
  //     return;
  //   }
    
  //   int li = 2 * i;
  //   int ri = li + 1;
  //   int m = (l + r) / 2;

  //   build(li, l, m);
  //   build(ri, m + 1, r);
  // }
  
  T _query(int i, int l, int r, int ql, int qr) {
    if (l == ql && r == qr) {
      return node[i];
    }

    int li = 2 * i;
    int ri = li + 1;
    int m = (l + r) / 2;

    propagate(i, l, r);

    if (ql > m) return _query(ri, m + 1, r, ql, qr);
    if (qr <= m) return _query(li, l, m, ql, qr);

    T l_res = _query(li, l, m, ql, m);
    T r_res = _query(ri, m + 1, r, m + 1, qr);
    return merge(l_res, r_res);
  }

  void _update(int i, int l, int r, int ql, int qr, T v) {
    if (l == ql && r == qr) {
      lazy_apply(i, l, r, v);
      return;
    }

    int li = 2 * i;
    int ri = li + 1;
    int m = (l + r) / 2;

    propagate(i, l, r);

    if (ql > m) {
      _update(ri, m + 1, r, ql, qr, v);
    } else if (qr <= m) {
      _update(li, l, m, ql, qr, v);
    } else {
      _update(li, l, m, ql, m, v);
      _update(ri, m + 1, r, m + 1, qr, v);
    }

    node[i] = merge(node[li], node[ri]);
  }

  T merge(T x, T y) {
    return min(x, y);
  }

  void lazy_apply(int i, int l, int r, T v) {
    node[i] += v;
    pending[i] += v;
  }

  void propagate(int i, int l, int r) {
    if (pending[i] ==0) return;

    int li = 2 * i;
    int ri = li + 1;
    int m = (l + r) / 2;

    lazy_apply(li, l, m, pending[i]);
    lazy_apply(ri, m+1, r, pending[i]);
    pending[i] = 0;
  }
};
