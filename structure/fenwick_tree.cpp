template <class T>
struct AbelianGroup {
  const T identity;
  const function<T(T, T)> add;
  const function<T(T)> inverse;

  AbelianGroup (const T& ident, const function<T(T, T)>& operation, const function<T(T)>& inv)
    : identity(ident),
      add(operation),
      inverse(inv) {}

  T sub(const T& a, const T& b) const {
    return add(a, inverse(b));
  }
};

template <class T, int N>
class FenwickTree {
  T tree[N];
  const AbelianGroup<T> group;

  public:
  FenwickTree(const AbelianGroup<T>& _group) : group(_group) {}

  template <class Container>
  void build(const Container container) {
    FOR0(i, N) {
      add(i, container[i]);
    }
  }

  void add(int i, const T& w) {
    for (int j = i; j < N; j |= j + 1) {
      tree[j] = group.add(tree[j], w);
    }
  }

  /* sum of [0, i) */
  T sum(int i) {
    if (i == 0) {
      return group.identity;
    }
    T ret = group.identity;
    for (int j = i - 1; LELE(0, j, N); j = (j & (j + 1)) - 1) {
      ret = group.add(ret, tree[j]);
    }
    return ret;
  }

  /* [a, b) */
  T range_sum(int a, int b) {
    return group.sub(sum(b), sum(a));
  }

  T point(int a) {
    return range_sum(a, a + 1);
  }
};