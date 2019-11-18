template <ui N>
class UnionFindTree {
  ui arr[N];
  ui rank[N];

  public:
  UnionFindTree(void) {
    FOR0(i, N) {
      arr[i] = i;
      rank[i] = 0;
    }
  }

  ui root(ui idx) {
    ui parent = arr[idx];
    while (parent != arr[parent]) {
      parent = arr[parent];
    }
    arr[idx] = parent;
    return parent;
  }

  bool is_connected(ui a, ui b) {
    return root(a) == root(b);
  }

  void unite(ui a, ui b) {
    ui ra = root(a);
    ui rb = root(b);

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