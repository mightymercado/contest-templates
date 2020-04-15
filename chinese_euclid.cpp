int inverse(u64 a, u64 m) {
  int o = m;
  u64 u = 0, v = 1;
  while (a != 0) {
      int t = m / a;
      m -= (u64) t * a; swap(a, m);
      u -= (u64) t * v; swap(u, v);
  }
  assert(m == 1);
  if (u < 0) u = o - (-u) % o;
  u %= o;
  return u;
}

int chinese(vector<int> &rem, vector<int> &mod) {
  int n = mod.size();
  int p = 1;
  for (int i = 0; i < n; i++) {
      p *= mod[i];
  }
  u64 x = 0;
  for (int i = 0; i < n; i++) {
      int y = p / mod[i];
      int inv = inverse(y, mod[i]);
      x += ((u64) y * inv % p) * (u64) rem[i] % p;
      x %= p;
  }
  for (int i = 0; i < mod.size(); i++) {
    assert (x % mod[i] == rem[i]);
  }
  return x;
}
