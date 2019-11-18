template <sl Mod>
struct Z_over_nZ{
  sl x;

  Z_over_nZ(const sl& _x) : x(_x % Mod) {
    if (x < 0) {
      x += Mod;
    }
  }

  template <class T>
  Z_over_nZ<Mod> operator+=(const T& y) {
    x += y;
    x %= Mod;
    return *this;
  }

  template <class T>
  Z_over_nZ<Mod> operator-=(const T& y) {
    x -= y;
    x %= Mod;
    return *this;
  }

  template <class T>
  Z_over_nZ<Mod> operator*=(const T& y) {
    x *= y;
    x %= Mod;
    return *this;
  }

  template <class T>
  Z_over_nZ<Mod> operator/=(const T& y) {
    x *= modinv(y, Mod);
    x %= Mod;
    return *this;
  }

  Z_over_nZ<Mod> operator+=(const Z_over_nZ<Mod>& y) {
    return (*this) += y.x;
  }

  Z_over_nZ<Mod> operator-=(const Z_over_nZ<Mod>& y) {
    return (*this) -= y.x;
  }

  Z_over_nZ<Mod> operator*=(const Z_over_nZ<Mod>& y) {
    return (*this) *= y.x;
  }

  Z_over_nZ<Mod> operator/=(const Z_over_nZ<Mod>& y) {
    return (*this) /= y.x;
  }

  template <class T>
  Z_over_nZ<Mod> operator+(const T& y) const {
    return Z_over_nZ(*this) += y;
  }

  template <class T>
  Z_over_nZ<Mod> operator-(const T& y) const {
    return Z_over_nZ(*this) -= y;
  }

  template <class T>
  Z_over_nZ<Mod> operator*(const T& y) const {
    return Z_over_nZ(*this) *= y;
  }

  template <class T>
  Z_over_nZ<Mod> operator/(const T& y) const {
    return Z_over_nZ(*this) /= y;
  }

  Z_over_nZ<Mod> operator-() const {
    return Z_over_nZ(Mod - x);
  }

  template <class T>
  bool operator!=(const T& y) const {
    return !(*this == y);
  }

  template <class T>
  bool operator==(const T& y) const {
    return (x - y) % Mod == 0;
  }

  bool operator==(const Z_over_nZ<Mod>& y) const {
    return (x - y.x) % Mod == 0;
  }

  template <class T>
  Z_over_nZ<Mod> operator=(const T& y) {
    x = y;
    return *this;
  }

  Z_over_nZ<Mod> operator=(const Z_over_nZ& y) {
    x = y.x;
    return *this;
  }

  template <class T>
  bool operator<(const T& other) {
    return x < other;
  }
};

template <sl Mod>
ostream& operator<<(ostream& os, const Z_over_nZ<Mod>& x) {
  os << x.x;
  return os;
}

template <class T, sl Mod>
bool operator<(const T& lhs, const Z_over_nZ<Mod>& rhs) {
  return lhs < rhs.x;
}

using Zmod1000000007 = Z_over_nZ<1000000007>;
