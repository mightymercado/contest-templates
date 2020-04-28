

int closest(vector<int>::iterator begin, vector<int>::iterator end, int x) {
  int n = end - begin;
  assert(n > 0);
  auto i = lower_bound(begin, end, x) - begin;
  if (i == n) 
    return i - 1;
  if (begin[i] == x || i == 0)
    return i;
  if (abs(x - begin[i]) <= abs(x - begin[i - 1]))
    return i;
  return i - 1;
}

int atleast(vector<int>::iterator begin, vector<int>::iterator end, int x) {
  int n = end - begin;
  return n - (lower_bound(begin, end, x)  - begin);
}

int greater_than(vector<int>::iterator begin, vector<int>::iterator end, int x) {
  int n = end - begin;
  return n - (upper_bound(begin, end, x) - begin);
}

int less_than(vector<int>::iterator begin, vector<int>::iterator end, int x) {
  return upper_bound(begin, end, x) - begin;
}

int count_range(vector<int>::iterator begin, vector<int>::iterator end, int L, int R) {
  return atleast(begin, end, L) - greater_than(begin, end, R);
}
