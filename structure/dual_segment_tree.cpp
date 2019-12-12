/* (identity element, operation) */
template <class T>
struct Monoid {
  const T identity;
  const function<T(T, T)> op;
  Monoid (const T& _ident, const function<T(T, T)>& _op)
    : identity(_ident), op(_op) {};
};

template <class T, sl K>
class DualSegmentTree {
  const Monoid<T> monoid;
  const sl N = (1 << K);
  T tree[2 * (1 << K) - 1];

  inline si parent(si i) {
    MASSERT(LELT(0, i, 2 * N - 1));
    MASSERT(i != 0);
    return (i - 1) / 2;
  }

  inline si left(si i) {
    MASSERT(LELT(0, i, 2 * N - 1));
    return i * 2 + 1;
  }

  inline si right(si i) {
    MASSERT(LELT(0, i, 2 * N - 1));
    return i * 2 + 2;
  }

  inline si leaf(si i) {
    MASSERT(LELT(0, i, N));
    return i + N - 1;
  }

  inline bool is_leaf(si i) {
    MASSERT(LELT(0, i, 2 * N - 1));
    return (N - 1 <= i);
  }

  inline void propagate(si idx) {
    MASSERT(LELT(0, idx, 2 * N - 1));
    if (tree[idx] == monoid.identity) {
      return;
    }
    if (!is_leaf(idx)) {
      tree[left(idx)] = monoid.op(tree[left(idx)], tree[idx]);
      tree[right(idx)] = monoid.op(tree[right(idx)], tree[idx]);
      tree[idx] = monoid.identity;
    }
  }

  void propagate_to(si idx) {
    MASSERT(LELT(0, idx, 2 * N - 1));
    // root?
    if (idx != 0) {
      propagate_to(parent(idx));
    }
    propagate(idx);
  }

  void apply_impl(si a, si b, T x, si idx, si l, si r) {
    MASSERT(LELT(0, l, r) && r <= (2 * N - 1));
    MASSERT(LELT(0, a, b) && b <= (2 * N - 1));
    MASSERT(LELT(0, idx, 2 * N - 1));
    propagate(idx);

    if (!(r <= a || b <= l)) {
      if (a <= l && r <= b) { // [l, r) covered by [a, b)
        tree[idx] = monoid.op(tree[idx], x);
      } else {
        si t = (l + r) / 2;
        apply_impl(a, b, x, left(idx), l, t);
        apply_impl(a, b, x, right(idx), t, r);
      }
    }
  }

public:
  DualSegmentTree(const Monoid<T>& _monoid) : monoid(_monoid) {
    FOR0(i, 2 * N - 1) {
      tree[i] = monoid.identity;
    }
  }

  /* operate x to [a, b) */
  void apply(si a, si b, T x) {
    MASSERT(LELT(0, a, b) && b <= (2 * N - 1));
    apply_impl(a, b, x, 0, 0, N);
  }

  // get i
  T query(si i) {
    MASSERT(LELT(0, i, N));
    sl idx = leaf(i);
    propagate_to(idx);
    return tree[idx];
  }
};
