template <ul prime, ul generator>
struct Fp {
  const static ul p = prime;
  const static ul g = generator;
};

using F_167772161 = Fp<167772161, 3>;
using F_469762049 = Fp<469762049, 3>;
using F_1224736769 = Fp<1224736769, 3>;
using F_1004535809 = Fp<1004535809, 3>;
using F_998244353 = Fp<998244353, 3>;
using F_985661441 = Fp<985661441, 3>;

template <class Field>
struct NTT {
  unordered_map<ul, ul> nth_unit;

  NTT() {
    for (ul i = 2; (Field::p - 1) / i > 1; i <<= 1) {
      nth_unit[i >> 1] = powmod(Field::g, (Field::p - 1) / i, Field::p);
    }
  }

  vector<sl> ntt(const vector<sl>& pol) {
    const ul NN = pol.size();

    vector<sl> ret = pol;
    FOR0(i, NN) {
      ui j = i, k = 0, l = NN - 1;
      while (l != 0) {
        k <<= 1;
        k |= (j & 1);
        j >>= 1;
        l >>= 1;
      }
      ret[i] = pol[k];
    }

    for (ul i = 1; i < NN; i <<= 1) {
      auto zeta = nth_unit[i];
      for (ul j = 0; j < NN; j += 2 * i) {
        sl cur = 1;
        FOR0(k, i) {
          auto x = ret[j + k];
          auto y = (cur * ret[j + k + i]) % Field::p;
          ret[j + k] = (x + y) % Field::p;
          ret[j + k + i] = (x + (Field::p - y)) % Field::p;
          if (ret[j + k + i] < 0) {
            ret[j + k + i] += Field::p;
          }
          cur = (cur * zeta) % Field::p;
        }
      }
    }

    return ret;
  }

  vector<sl> intt(const vector<sl>& pol) {
    const ul NN = pol.size();
    auto fpol = ntt(pol);
    vector<sl> ret(NN);

    auto NNinv = modinv(NN, Field::p);

    FOR0(i, NN) {
      ret[i] = (fpol[(NN - i) % NN] * NNinv) % Field::p;
    }
    return ret;
  }

  vector<sl> convolution_ntt(const vector<sl>& _a, const vector<sl>& _b) {
    ui K = 1;
    vector<sl> a = _a;
    vector<sl> b = _b;

    while (K < a.size() + b.size()) {
      K <<= 1;
    }

    a.resize(K, 0);
    b.resize(K, 0);

    vector<sl> f1 = ntt(a);
    vector<sl> f2 = ntt(b);

    vector<sl> f3;
    f3.resize(K);

    FOR0(i, K) {
      f3[i] = (f1[i] * f2[i]) % Field::p;
    }

    return intt(f3);
  }
};
