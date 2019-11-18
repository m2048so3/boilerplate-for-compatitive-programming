bool isprime(const ul& n) {
  if (n < 2 || n % 2 == 0) {
    return false;
  }
  for (ul i = 1; i * i < n; i += 2) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

std::set<ul> divisors(const ul& n) {
  std::set<ul> div;
  for (ul i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      div.insert(i);
      if (n / i != i) {
        div.insert(n / i);
      }
    }
  }
  if (n == 1) {
    div.insert(1);
  }
  return div;
}

template <class T>
T gcd(T a, T b) {
  while (b) {
    T t = a % b;
    a = b;
    b = t;
  }
  return a;
}

template <class T>
tuple<T, T, T> xgcd(const T& a0, const T& b0) {
  T a = a0, b = b0;
  T x = 0, y = 1, u = 1, v = 0;
  while (a != 0) {
    auto q = b / a;
    auto r = b % a;
    auto m = x - u * q;
    auto n = y - v * q;
    b = a;
    a = r;
    x = u;
    y = v;
    u = m;
    v = n;
  }
  return make_tuple(b, x, y);
}

sl modinv(const sl& a, const sl& m) {
  auto t = xgcd(a, m);
  // assert(std::get<0>(t) == 1)
  auto res = std::get<1>(t) % m;
  if (res < 0) {
    res += m;
  }
  res %= m;
  return res;
}

template <class T>
T powmod(T x, ul y, ul z) {
  T cur = x;
  T res = 1;
  while (y != 0) {
    if ((y & 1) == 1) {
      res = (res * cur) % z;
    }
    cur = (cur * cur) % z;
    y >>= 1;
  }
  return res;
}

template <class T>
T factorial(const T& n) {
  T res = 1;
  FOR0(i, n) {
    res *= i + 1;
  }
  return res;
}

template <class T>
T permutation(const T& n, const T& m) {
  return factorial(n) / factorial(n - m);
}

template <class T>
T combination(const T& n, const T& m) {
  return permutation(n, m) / factorial(m);
}