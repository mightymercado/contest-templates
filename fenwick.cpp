template <typename T>
class Fenwick {
public:
  T t[maxn + 1] = {0};
  int n;

  Fenwick(int n) : n(n) {}

  T get(int i) {
    T s = 0;
    while (i > 0) {
      s = merge(s, t[i]);
      i -= i & -i;
    }
    return s;
  }

  void update(int i, T v) {
    while (i <= n) {
      t[i] = merge(t[i], v);
      i += i & -i;
    }
  }

  virtual T merge(T a, T b) {
    return a + b;
  }
};

template <typename T>
class MaxFenwick : public Fenwick<T> {
public:
  using Fenwick<T>::Fenwick;
  T merge(T a, T b) override {
    return max(a, b);
  }
};
