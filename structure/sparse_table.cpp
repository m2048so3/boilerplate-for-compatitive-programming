// verified: https://judge.yosupo.jp/submission/1967
template <class T>
struct SparseTable {
  function<T(T, T)> op;
  sl N;
  vector<vector<T>> table;

  template <class Container>
  void build(const Container& arr, function<T(T, T)> _op) {
    build(arr, _op, arr.size());
  }

  template <sl _N>
  void build(const T (&arr)[_N], function<T(T, T)> _op) {
    build(arr, _op, _N);
  }

  template <class Container>
  void build(const Container& arr, function<T(T, T)> _op, const sl& _N) {
    op = _op;
    N = _N;
    sl M = 0;
    while ((1 << M) < N) {
      table.emplace_back(N);
      M++;
    }
    table.emplace_back(N);
    FOR0(i, N) {
      table[0][i] = arr[i];
    }
    for (sl j = 1; j <= M; j++) {
      for (sl i = 0; i < N - (1 << j) + 1; i++) {
        table[j][i] = op(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  /* [a, b) */
  T query(const sl& a, const sl& b) {
    MASSERT(a < b);
    sl j = floor(log2(b - a));
    return op(table[j][a], table[j][b - (1 << j)]);
  }
};
