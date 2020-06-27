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
#include <sstream>
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
 
int N, gap;
vector<int> S, sa, pos, tmp;
 
bool suf_cmp(int i, int j) {
  if (pos[i] != pos[j])
    return pos[i] < pos[j];
  i += gap;
  j += gap;
  return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}
 
void buildSA() {
  N = S.size();
  for (int i = 0; i < N; i++) {
    sa[i] = i;
    pos[i] = S[i];
  }
  for (gap = 1;; gap *= 2) {
    sort(all(sa), suf_cmp);
    for(int i = 0; i < N - 1; i++) 
      tmp[i + 1] = tmp[i] + suf_cmp(sa[i], sa[i + 1]);
    for (int i = 0; i < N; i++) pos[sa[i]] = tmp[i];
    if (tmp[N - 1] == N - 1) break;
  }
}
 
auto find_all_matches(vector<int> &query) {
  N = S.size();
  auto bin_search = [&](int lo, int hi, auto &&func) {
    int m = query.size();
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      int suffix = sa[mid];
      if (func(suffix, suffix + m))
        lo = mid + 1;
      else
        hi = mid;
    };
    return lo;
  };
 
  auto lt = [&](int start, int end) {
    int j = 0, i = start;
    for (; i < end && j < query.size(); i++, j++) {
      if (S[i] < query[j]) {
        return true;
      } else if (S[i] > query[j]) {
        return false;
      } 
    }
    return (end - start) < query.size();
  };
 
  auto gt = [&](int start, int end) {
    int j = 0, i = start;
    for (; i < end && j < query.size(); i++, j++) {
      if (S[i] < query[j]) {
        return false;
      } else if (S[i] > query[j]) {
        return false;
      } 
    }
    return (end - start) == query.size();
  };
 
  int start = bin_search(0, N, lt);
  int end = bin_search(start, N, gt);
 
  return make_pair(start, end);
};
 
map<string, int> id;
int cur_id;
 
int get_id(string word) {
  if (!id.count(word))
    id[word] = cur_id++;
  return id[word];
}
 
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt = 0;
  testcase {
    cout << "Case " << ++tt << ":\n";
    cur_id = 0;
    id.clear();
    int n, q;
    cin >> n >> q;
    string line;
 
    getline(cin, line);
 
    S.clear();
    S.push_back(-1);
    for (int i = 0; i < n; i++) {
      getline(cin, line);
      stringstream stream(line);
      
      while (stream) {
        string word;
        stream >> word;
        if (word.size() == 0) break;
        // cout << word << ' ';
        S.push_back(get_id(word));
      }
      S.push_back(-1);
    }
    tmp.resize(S.size());
    pos.resize(S.size());
    sa.resize(S.size());
 
    buildSA();
 
    // for (int i = 0; i < S.size(); i++) {
    //   cout << S[i] << ' ';
    // }
    // cout << '\n';
 
    vector<int> pts;
    for (int i = 0; i < S.size(); i++) {
      if (S[i] == -1) pts.push_back(i);
    }
 
    for (int i = 0; i < q; i++) {
      string line;
      getline(cin, line);
      stringstream stream(line);
      
      vector<int> query;
 
      while (stream) {
        string word;
        stream >> word;
        if (word.size() == 0) break;
        query.push_back(get_id(word));
      }
 
      auto p = find_all_matches(query);
      int start = p.first;
      int end = p.second;
      vector<int> ans;
      for (int i = start; i < end; i++) {
        ans.push_back(sa[i]);
      }
 
      sort(all(ans));
 
      int j = 0;
      int cnt = 0;
      for (int i = 1; i < pts.size(); i++) {
        int start = pts[i - 1];
        int end = pts[i];
 
        bool good = false;
        while (j < ans.size()) {
          if (start < ans[j] and ans[j] < end) {
            good = true; 
            j += 1;
          } else {
            break;
          }
        }
 
        if (good) cnt++;
        if (j >= ans.size()) break;
      }
 
      cout << cnt << '\n';
    }
 
  }
}
