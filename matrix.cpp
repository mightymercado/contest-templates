#include <cstdio>
#include <numeric>
#include <cmath>
#include <iostream>
#include <set>
#include <array>
using i64 = long long;
using namespace std;

template<class T, int N>
using A = array<T, N>;

template<class T, int N, int M>
struct mat : A<A<T, N>, M> {
    using A<A<T, N>, M>::A;
    using A<A<T, N>, M>::size;
    template<class U> mat(vector<vector <U>>& a){
      for (int i = 0; i < a.size(); i++) 
        for (int j = 0; j < a[0].size(); j++)
          (*this)[i][j] = a[i][j];
    }
    void unit(int v) {
      for (int i = 0; i < min(height(), width()); i++)
        (*this)[i][i] = v;
    }
    void zero() { 
      for (int i = 0; i < height(); i++)
        for (int j = 0; j < width(); j++) 
          (*this)[i][j] = 0;
    }
    mat(int v = 0) { 
      if (v > 0) unit(v);
    }
    int height() const {
      return size();
    }
    int width() const { 
      return (*this)[0].size();
    }
    T sum() const {
      T tot = 0;
      for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
          tot += (*this)[i][j];
        }
      }
      return tot;
    }
    mat operator+(const mat &r) const {
      assert(height() == r.height() && width() == r.width());
      mat res = mat();
      res.zero();
      for (int i = 0; i < height(); i++) 
        for (int j = 0; j < width(); j++)
          res[i][j] = (this)[i][j] + r[i][j];
      return res;
    }
    mat operator-(const mat &r) const {
      assert(height() == r.height() && width() == r.width());
      mat res = mat();
      res.zero();        
      for (int i = 0; i < height(); i++) 
        for (int j = 0; j < width(); j++)
          res[i][j] = (this)[i][j] - r[i][j];
      return res;
    }
    mat operator*(const mat &r) const {
      assert(width() == r.height());
      mat res = mat();
      res.zero();
      for (int i = 0; i < height(); i++)
        for (int j = 0; j < r.width(); j++)
          for (int k = 0; k < width(); k++)
            res[i][j] += (*this)[i][k] * r[k][j];
      return res;
    }
    mat &operator+=( mat &r) { 
      return *this = *this + r;
    }
    mat &operator-=( mat &r) {
      return *this = *this - r;
    }
    mat &operator*=( mat &r) {
      return *this = *this * r;
    }
    mat operator^(i64 n) const {
      assert(height() == width());
      mat x = *this;
      mat r(1);
      while (n) {
          if (n & 1) r *= x;
          x *= x;
          n >>= 1;
      }
      return r;
    }
};

template<typename T, int H, int W> ostream &operator<<(ostream &os, mat<T, H, W> vec) { 
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) { 
      os << vec[i][j];
    }
    os << endl;
  }
  return os;
}
