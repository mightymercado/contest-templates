double t_search(function<double(double)> f, double l, double r) {
  for (int i = 0; i < 100; i++) {
    double m1 = (l * 2 + r) / 3;
    double m2 = (l + 2 * r) / 3;
    f(m1) < f(m2) ? r = m2 : l = m1; // min <, max > 
  }
  return f(l);
}

int t_search(function<long long(int)> f, int l, int r) {
  for (--l; r - l > 1; ) {
    int m = (r + l) >> 1;
    f(m) < f(m + 1) ? r = m : l = m; // min <, max >
  }
  return l + 1; 
}
