struct PrefixSum {
  vector<long long> s;
  PrefixSum(vector<int> &a) {
    s.resize(a.size() + 1, 0);
    for (int i = 0; i < a.size(); i++) {
      s[i + 1] = s[i] + a[i];
    }
  }
  long long query(int L, int R) {
    return s[min(++R, int(s.size()) - 1)] - (L > 0 ? s[L] : 0);
  }
};
