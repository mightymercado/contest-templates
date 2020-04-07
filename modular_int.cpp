#include <cstdio>
#include <numeric>
#include <cmath>
#include <iostream>
#include <set>
#include <array>
using i64 = long long;
using namespace std;

class ModInt {
public:
  int value;
  static const int mod = 1e9 + 7;
  ModInt(int value = 0) {
    this->value = normalize(value);
  }  
  ModInt& operator+=(const ModInt& other) {
      this->value = (*this + other).value;
      return *this;
  }
  ModInt& operator-=(const ModInt& other) {
      this->value = (*this - other).value;
      return *this;
  }
  ModInt& operator*=(const ModInt& other) {
      this->value = (*this * other).value;
      return *this;
  }
  ModInt& operator/=(const ModInt& other) {
      this->value = (*this / other).value;
      return *this;
  }
  int inverse(int a) const {
    int m = mod;
    int u = 0, v = 1;
    while (a != 0) {
        int t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    assert(m == 1);
    return u;
  }
  ModInt operator+(const ModInt &R) const {
    return ModInt(ModInt::normalize(this->value + R.value));
  } 
  ModInt operator-(const ModInt &R) const {
    return ModInt(ModInt::normalize(this->value - R.value));
  } 
  ModInt operator*(const ModInt &R) const {
    return ModInt(ModInt::normalize((i64) this->value * R.value));
  } 
  ModInt operator/(const ModInt &R) const {
    return ModInt(ModInt::normalize((i64) this->value * inverse(R.value)));
  }
  int normalize(i64 value) const {
    while (value < 0) value += mod;
    value %= mod;
    return value;
  }
};

ostream& operator<<(ostream& os, ModInt const &m) {
  os << (m.value);
  return os;
}

istream& operator>>(istream& is, ModInt& r) {
    is >> r.value;
    r.value = r.normalize(r.value);
    return is;
}
