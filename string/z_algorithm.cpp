struct Z_algorithm {
  vector<ul> Z;
  ul n;

  Z_algorithm(const string& str) {
    ul n = str.size();
    this->n = n;
    Z.resize(n, 0);
    ul c = 0;
    FORi(i, 1, n) {
      if (Z[i - c] + i < Z[c] + c) {
        Z[i] = Z[i - c];
      } else {
        ul j = 0;
        if (i < c + Z[c]) {
          j = c + Z[c] - i;
        }
        while (i + j < n && str[i + j] == str[j]) {
          j++;
        }
        Z[i] = j;
        c = i;
      }
    }
    Z[0] = n;
  }

  ul distnict_max(void) const {
    ul res = 0;
    FOR0(i, n) {
      ul k = Z[i];
      if (k > i) {
        k = i;
      }
      res = max(k, res);
    }
    return res;
  }
};