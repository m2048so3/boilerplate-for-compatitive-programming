template <sl prime, sl generator>
struct Fp {
  const static sl p = prime;
  const static sl g = generator;
};

using F_998244353 = Fp<998244353, 3>;

template <class Field>
vector<sl> ntt(const vector<sl>& pol) {
  const sl NN = pol.size();
  if (NN == 1){
    return pol;
  }

  vector<sl> ret;
  vector<sl> f0;
  vector<sl> f1;

  auto zeta = powmod(Field::g, (Field::p - 1) / NN, Field::p);
  // check point: (Field::p % NN) == 0?
  auto cur = 1;

  FOR0(i, NN / 2) {
    f0.push_back((pol[i] + pol[i + NN / 2]) % Field::p);
    auto t = (pol[i] + (Field::p - pol[i + NN / 2]) % Field::p) % Field::p;
    t *= cur;
    t %= Field::p;
    f1.push_back(t);
    cur = (cur * zeta) % Field::p;
  }

  auto F0 = ntt<Field>(f0);
  auto F1 = ntt<Field>(f1);

  FOR0(i, NN / 2) {
    ret.push_back(F0[i]);
    ret.push_back(F1[i]);
  }
  return ret;
}

template <class Field>
vector<sl> intt(const vector<sl>& pol) {
  const sl NN = pol.size();
  auto fpol = ntt<Field>(pol);
  vector<sl> ret;

  auto NNinv = modinv(NN, Field::p);

  FOR0(i, NN) {
    ret.push_back((fpol[(NN - i) % NN] * NNinv) % Field::p);
  }
  return ret;
}

template <class Field>
vector<sl> convolution_ntt(const vector<sl>& _a, const vector<sl>& _b) {
  sl K = 1;
  vector<sl> a = _a;
  vector<sl> b = _b;

  while (K < a.size() + b.size()) {
    K <<= 1;
  }

  FORi(i, a.size(), K) {
    a.push_back(0);
  }

  FORi(i, b.size(), K) {
    b.push_back(0);
  }

  auto f1 = ntt<Field>(a);
  auto f2 = ntt<Field>(b);

  vector<sl> f3;

  FOR0(i, K) {
    f3.push_back((f1[i] * f2[i]) % Field::p);
  }

  return intt<Field>(f3);
}
