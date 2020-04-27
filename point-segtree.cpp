
const int maxn = 5 * 1e5;

array<int, 2> node[3 * maxn];
template <typename T>
class SegmentTree {
public:
  int n;
  SegmentTree() {}
  SegmentTree(vector<int> &a) {
    this->n = a.size();
    build(1, 0, n - 1, a);

  }
  T query(int ql, int qr) {
    return _query(1, 0, n - 1, ql, qr);
  }

  void update(int q, T v) {
    _update(1, 0, n - 1, q, v);
  }
private:
  void build(int i, int l, int r, vector<int> &a) {
    if (l == r) {
      node[i] = {a[l], l};
      return;
    }
    
    int li = 2 * i;
    int ri = li + 1;
    int m = (l + r) / 2;

    build(li, l, m, a);
    build(ri, m + 1, r, a);

    node[i] = merge(node[li], node[ri]);
  }
  
  T _query(int i, int l, int r, int ql, int qr) {
    if (l == ql && r == qr) {
      return node[i];
    }

    int li = 2 * i;
    int ri = li + 1;
    int m = (l + r) / 2;

    if (ql > m) return _query(ri, m + 1, r, ql, qr);
    if (qr <= m) return _query(li, l, m, ql, qr);

    T l_res = _query(li, l, m, ql, m);
    T r_res = _query(ri, m + 1, r, m + 1, qr);
    return merge(l_res, r_res);
  }

  void _update(int i, int l, int r, int q, T v) {
    if (l == r) {
      node[i] = merge(node[i], v);
      return;
    }

    int li = 2 * i;
    int ri = li + 1;
    int m = (l + r) / 2;

    if (q > m) {
      _update(ri, m + 1, r, q, v);
    } else if (q <= m) {
      _update(li, l, m, q, v);
    }

    node[i] = merge(node[li], node[ri]);
  }

  T merge(T x, T y) {
    return min(x, y);
  }
};
