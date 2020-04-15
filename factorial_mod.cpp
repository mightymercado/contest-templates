const int maxn = 1e5;
const int mod = 1e9 + 7;
int ifact[maxn + 1];
int fact[maxn + 1];

int pow_mod(int b, int e) {
  int r = 1;
  for (; e; e >>= 1, b = (i64) b * b % mod) 
    if (e & 1) r = (i64) r * b % mod;
  return r;
}
 
void calc_fact() {
  fact[0] = 1;
  for (int i = 0; i <= maxn; i++) fact[i] = (i64) fact[i - 1] * i % mod;
  ifact[maxn] = pow_mod(fact[maxn], mod - 2);
  for (int i = maxn - 1; i >= 0; i--) ifact[i] = (i64) ifact[i + 1] * (i + 1) % mod;
}
