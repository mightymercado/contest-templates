const int maxm = 2 * 1e7;
int phi[maxm+1];
int lp[maxm+1];
vector<int> pr;

inline void calc_sieve() {
  phi[1] = 1;
  for (int i = 2; i <= maxm; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      phi[i] = i - 1;
      pr.push_back(i);
    } else {
      if (lp[i] == lp[i / lp[i]])
        phi[i] = phi[i / lp[i]] * lp[i];
      else
        phi[i] = phi[i / lp[i]] * (lp[i] - 1);
    }
    for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && (u64) i * pr[j] <= maxm; ++j)
      lp[i * pr[j]] = pr[j];
  }
}
