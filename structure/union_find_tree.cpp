template <si N>
class UnionFindTree {
  si arr[N];
  si rank[N];

  public:
  UnionFindTree(void) {
    FOR0(i, N) {
      arr[i] = i;
      rank[i] = 0;
    }
  }

  si root(si idx) {
    MASSERT(LELT(0, idx, N));
    si parent = arr[idx];
    while (parent != arr[parent]) {
      parent = arr[parent];
    }
    arr[idx] = parent;
    return parent;
  }

  bool is_connected(si a, si b) {
    MASSERT(LELT(0, a, N));
    MASSERT(LELT(0, b, N));
    return root(a) == root(b);
  }

  void unite(si a, si b) {
    MASSERT(LELT(0, a, N));
    MASSERT(LELT(0, b, N));
    si ra = root(a);
    si rb = root(b);

    if (ra == rb) {
      return;
    }

    if (rank[ra] < rank[rb]) {
      arr[ra] = rb;
    } else {
      arr[rb] = ra;
      if (rank[ra] == rank[rb]) {
        rank[ra]++;
      }
    }
  }
};
