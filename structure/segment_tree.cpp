/* (identity element, operation) */
template <class T>
struct Monoid {
  const T identity;
  const function<T(T, T)> op;

  Monoid (const T& _ident, const function<T(T, T)>& _op)
    : identity(_ident), op(_op) {};
};

/* f: T * E -> T */
template <class T, class E>
using MonoidAction = function<T(T, E)>;

template <class T, si K>
class SegmentTree {
  const Monoid<T> monoid;
  const sl N = (1 << K);
  T tree[2 * (1 << K) - 1];

  inline si parent(si i) const {
    assert(LELT(0, i, 2 * N - 1));
    assert(i != 0);
    return (i - 1) / 2;
  }

  inline si leaf(si i) const {
    assert(LELT(0, i, 2 * N - 1));
    return i + N - 1;
  }

  inline si left(si i) const {
    assert(LELT(0, i, 2 * N - 1));
    return i * 2 + 1;
  }

  inline si right(si i) const {
    assert(LELT(0, i, 2 * N - 1));
    return i * 2 + 2;
  }

  inline bool is_leaf(si i) const {
    assert(LELT(0, i, 2 * N - 1));
    return (N - 1 <= i);
  }

  inline bool is_root(si i) const {
    assert(LELT(0, i, 2 * N - 1));
    return i == 0;
  }

  inline si root(void) const {
    return 0;
  }

public:
  /* Initialize Segment Tree with Monoid `_monoid` */
  SegmentTree(const Monoid<T>& _monoid, const T& default_value) : monoid(_monoid) {
    queue<si> Q;
    FOR0(i, N) {
      tree[leaf(i)] = default_value;
      if (i % 2 == 0) {
        Q.push(parent(leaf(i)));
      }
    }
    while (!Q.empty()) {
      auto v = Q.front();
      Q.pop();
      tree[v] = monoid.op(tree[left(v)], tree[right(v)]);
      if (!is_root(v)) {
        if (left(parent(v)) == v) {
          Q.push(parent(v));
        }
      }
    }
  }

  SegmentTree(const Monoid<T>& _monoid)
      : SegmentTree(_monoid, _monoid.identity) {
  }

  void update(si i, T x) {
    assert(LELT(0, i, 2 * N - 1));
    si cur = leaf(i);
    tree[cur] = x;
    while (!is_root(cur)) {
      cur = parent(cur);
      tree[cur] = monoid.op(tree[left(cur)], tree[right(cur)]);
    }
  }

  // [a, b)
  T query(si a, si b) {
    assert(LELT(0, a, b) && b <= 2 * N - 1);
    T resL = monoid.identity;
    T resR = monoid.identity;
    si vL = leaf(a);
    si vR = leaf(b - 1);
    while (vL != vR) {
      if (right(parent(vL)) == vL) {
        resL = monoid.op(resL, tree[vL]);
        vL = vL + 1;
      }
      if (vL == vR) {
        break;
      }
      if (left(parent(vR)) == vR) {
        resR = monoid.op(tree[vR], resR);
        vR = vR - 1;
      }
      vL = parent(vL);
      vR = parent(vR);
    }
    resL = monoid.op(resL, tree[vL]);
    return monoid.op(resL, resR);
  }
};