template <class T>
bool isprime(const T& n, const sl& k = 20) {
  static random_device seed;
  static mt19937_64 mt(seed());
  uniform_int_distribution<T> rand(1, n - 1);
  if (n < 100000) {
    // trial division
    if (n < 2 || n % 2 == 0) {
      return false;
    }
    for (T i = 3; i * i <= n; i += 2) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;
  }
  if (n % 2 == 0) {
    return false;
  }
  // miller-rabin
  T d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;
  }
  FOR0(i, k) {
    T a = rand(mt);
    T t = d;
    T y = powmod(a, t, n);
    while ((t != n - 1) && (y != 1) && (y != n - 1)) {
      y = (y * y) % n;
      t <<= 1;
    }
    if ((y != n - 1) && (t & 1) == 0) {
      return false;
    }
  }
  return true;
}

template <class T>
T pollard_rho_brent(const T& n) {
  static random_device seed;
  static mt19937_64 mt(seed());
  uniform_int_distribution<T> rand(1, n);
  if (isprime(n)) {
    return n;
  }
  T g = n;
  while (g == n) {
    T y = rand(mt);
    T c = rand(mt);
    T m = rand(mt);
    T r = 1;
    T x = 1;
    T ys = 1;
    g = 1;

    while (g == 1) {
      x = y;
      T k = 0;
      FOR0(_i, r) {
        y = (y * y + c) % n;
      }
      while (k < r && g == 1) {
        ys = y;
        T q = 1;
        FOR0(_i, min(m, r - k)) {
          y = (y * y + c) % n;
          q = (q * ((x - y + n) % n)) % n;
        }
        g = gcd(q, n);
        k += m;
      }
      r *= 2;
    }

    if (g == n) {
      while (1) {
        ys = (ys * ys + c) % n;
        g = gcd(x - ys + n, n);
        if (g > 1) {
          break;
        }
      }
    }
  }
  return g;
}

template <class T>
multiset<T> prime_factor(const T& n) {
  if (n == 1) {
    return { };
  } else if (n == 2) {
    return { 2 };
  }
  if (isprime(n)) {
    return { n };
  }
  T g = pollard_rho_brent(n);
  multiset<T> res = prime_factor(g);
  multiset<T> res2 = prime_factor(n / g);
  FORITER(res2, it) {
    res.emplace(*it);
  }
  return res;
}


std::set<sl> divisors(const sl& n) {
  MASSERT(0 < n);
  std::set<sl> div;
  for (sl i = 1; i * i <= n; i++) {
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

// support positive power only
template <class T>
T powmod(T x, sl y, sl z) {
  MASSERT(0 < y);
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
T powint(T x, sl y) {
  MASSERT(0 < y);
  T cur = x;
  T res = 1;
  while (y != 0) {
    if ((y & 1) == 1) {
      res = res * cur;
    }
    cur = cur * cur;
    y >>= 1;
  }
  return res;
}

sl garner(const vector<sl>& ai, const vector<sl>& ni, const sl mod) {
  sl N = ai.size();
  vector<sl> ki(N);
  ki[0] = ai[0];
  FORi(i, 1, N) {
    sl a = 0;
    sl b = ai[i];
    sl m = 1;
    sl n = ni[i];

    FOR0(j, i) {
      a += m * ki[j];
      a %= n;
      m = (m * ni[j]) % n;
    }

    ki[i] = ((b - a) * modinv(m, n)) % n;
    if (ki[i] < 0) {
      ki[i] += n;
    }
  }
  sl M = 1;
  sl res = 0;
  FOR0(i, N) {
    res += (M * ki[i]) % mod;
    res %= mod;
    M = (M * ni[i]) % mod;
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
  T res = 1;
  FORi(i, n - m, n) {
    res *= i + 1;
  }
  return res;
}

template <class T>
T combination(const T& n, const T& m) {
  T res = permutation(n, m);
  FORi(i, 0, m) {
    res /= i + 1;
  }
  return res;
}
