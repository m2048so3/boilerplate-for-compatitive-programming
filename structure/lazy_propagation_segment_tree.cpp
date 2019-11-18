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

template <class T, class E, sl K>
class LazyPropagationSegmentTree {
  const Monoid<T> monoid;
  const Monoid<E> operator_monoid;
  const MonoidAction<T, E> action;
  const sl N = (1 << K);
  T tree[2 * (1 << K) - 1];
  E lazytree[2 * (1 << K) - 1];

  inline si parent(si i) {
    assert(LELT(0, i, 2 * N - 1));
    assert(i != 0);
    return (i - 1) / 2;
  }

  inline si left(si i) {
    assert(LELT(0, i, 2 * N - 1));
    return i * 2 + 1;
  }

  inline si right(si i) {
    assert(LELT(0, i, 2 * N - 1));
    return i * 2 + 2;
  }

  inline si leaf(si i) {
    assert(LELT(0, i, N));
    return i + N - 1;
  }

  inline bool is_leaf(si i) {
    assert(LELT(0, i, 2 * N - 1));
    return (N - 1 <= i);
  }

  inline void propagate(si idx) {
    assert(LELT(0, idx, 2 * N - 1));
    if (lazytree[idx] == operator_monoid.identity) {
      return;
    }
    if (!is_leaf(idx)) {
      lazytree[left(idx)] = operator_monoid.op(lazytree[left(idx)], lazytree[idx]);
      lazytree[right(idx)] = operator_monoid.op(lazytree[right(idx)], lazytree[idx]);
    }
    tree[idx] = action(tree[idx], lazytree[idx]);
    lazytree[idx] = operator_monoid.identity;
  }

  T apply_impl(si a, si b, E x, si idx, si l, si r) {
    assert(LELT(0, l, r) && r <= (2 * N - 1));
    assert(LELT(0, a, b) && b <= (2 * N - 1));
    assert(LELT(0, idx, 2 * N - 1));
    propagate(idx);
    if (r <= a || b <= l) {
      return tree[idx];
    }
    if (a <= l && r <= b) { // [l, r) covered by [a, b)
      lazytree[idx] = x;
      return action(tree[idx], lazytree[idx]);
    } else {
      si t = (l + r) / 2;
      T vL = apply_impl(a, b, x, left(idx), l, t);
      T vR = apply_impl(a, b, x, right(idx), t, r);
      tree[idx] = monoid.op(vL, vR);
      return tree[idx];
    }
  }

  T query_impl(si a, si b, si idx, si l, si r) {
    assert(LELT(0, l, r) && r <= (2 * N - 1));
    assert(LELT(0, a, b) && b <= (2 * N - 1));
    assert(LELT(0, idx, 2 * N - 1));
    propagate(idx);
    if (r <= a || b <= l) {
      return monoid.identity;
    }
    if (a <= l && r <= b) { // [l, r) covered by [a, b)
      return tree[idx];
    } else {
      si t = (l + r) / 2;
      T vL = query_impl(a, b, left(idx), l, t);
      T vR = query_impl(a, b, right(idx), t, r);
      return monoid.op(vL, vR);
    }
  }

public:
  LazyPropagationSegmentTree(const Monoid<T>& _monoid, const Monoid<E>& _operator, 
                             const MonoidAction<T, E>& _action, const T& default_value)
  : monoid(_monoid), operator_monoid(_operator), action(_action) {
    queue<si> Q;
    FOR0(i, N) {
      tree[leaf(i)] = default_value;
      if ((i & 1) == 0) {
        Q.push(parent(leaf(i)));
      }
    }
    while (!Q.empty()) {
      auto v = Q.front();
      Q.pop();
      tree[v] = monoid.op(tree[left(v)], tree[right(v)]);
      if (v != 0) {
        if (left(parent(v)) == v) {
          Q.push(parent(v));
        }
      }
    }
    FOR0(i, 2 * N - 1) {
      lazytree[i] = operator_monoid.identity;
    }
  }

  LazyPropagationSegmentTree(const Monoid<T>& _monoid, const Monoid<E>& _operator, 
                             const MonoidAction<T, E>& _action)
      : LazyPropagationSegmentTree(_monoid, _operator, _action, _monoid.identity) {
  }

  /* operate x to [a, b) */
  void apply(si a, si b, E x) {
    assert(LELT(0, a, b) && b <= (2 * N - 1));
    apply_impl(a, b, x, 0, 0, N);
  }

  // [a, b)
  T query(si a, si b) {
    assert(LELT(0, a, b) && b <= (2 * N - 1));
    return query_impl(a, b, 0, 0, N);
  }
};