template <class T>
struct Matrix {
  sl N, M;
  vector<vector<T>> mat;

  static Matrix<T> Identity(const sl& N) {
    Matrix<T> ret(N, N);
    FOR0(i, N) {
      ret.mat[i][i] = 1;
    }
    return std::move(ret);
  }

  static Matrix<T> Zero(const sl& N, const sl& M) {
    Matrix<T> ret(N, M);
    return std::move(ret);
  }

  Matrix(const sl& _N, const sl& _M) : N(_N), M(_M) {
    MASSERT(0 < N);
    MASSERT(0 < M);
    mat.resize(N);
    FOR0(i, N) {
      mat[i].resize(M, 0);
    }
  }

  Matrix(const Matrix<T>& _from) : N(_from.N), M(_from.M), mat(_from.mat) {}

  Matrix<T> operator=(const Matrix<T>& _from) {
    N = _from.N;
    M = _from.M;
    mat = _from.mat;
    return *this;
  }

  inline Matrix<T> add(const Matrix<T>& B) const {
    MASSERT(N == B.N);
    MASSERT(M == B.M);
    Matrix<T> ret(*this);
    FOR0(i, N) {
      FOR0(j, M) {
        ret.mat[i][j] += B.mat[i][j];
      }
    }
    return std::move(ret);
  }

  inline Matrix<T> sub(const Matrix<T>& B) const {
    MASSERT(N == B.N);
    MASSERT(M == B.M);
    Matrix<T> ret(*this);
    FOR0(i, N) {
      FOR0(j, M) {
        ret.mat[i][j] -= B.mat[i][j];
      }
    }
    return std::move(ret);
  }

  inline Matrix<T> mult(const Matrix<T>& B) const {
    MASSERT(M == B.N);
    Matrix<T> ret(N, B.M);
    FOR0(i, N) {
      FOR0(k, M) {
        auto mik = mat[i][k];
        FOR0(j, B.M) {
          ret[i][j] += (mik * B[k][j]);
        }
      }
    }
    return std::move(ret);
  }

  inline Matrix<T> power(const sl& x) const {
    MASSERT(0 < x);
    MASSERT(N == M);
    Matrix<T> ret = Matrix<T>::Identity(N);
    Matrix<T> temp = *this;
    sl t = x;
    while (t != 0) {
      if ((t & 1) == 1) {
        ret = ret.mult(temp);
      }
      temp = temp.mult(temp);
      t >>= 1;
    }
    return std::move(ret);
  }

  inline Matrix<T> scalarmult(const T& s) const {
    Matrix<T> ret(*this);
    FOR0(i, N) {
      FOR0(j, M) {
        ret.mat[i][j] *= s;
      }
    }
    return std::move(ret);
  }

  const vector<T>& operator[](const sl& idx) const {
    MASSERT(LELT(0, idx, N));
    return mat[idx];
  }

  vector<T>& operator[](const sl& idx) {
    MASSERT(LELT(0, idx, N));
    return mat[idx];
  }

  inline T determinant(void) const {
    MASSERT(N == M);
    vector<vector<T>> m = mat;
    T ret = 1;
    FOR0(i, N) {
      if (m[i][i] == 0) {
        FOR0(j, N) {
          if (m[j][i] != 0) {
            swap(m[i], m[j]);
            ret = -ret;
            break;
          }
        }
      }
    }
    FOR0(i, N) {
      FORi(j, i + 1, N) {
        auto c = -m[j][i] / m[i][i];
        FORi(k, i + 1, M) {
          m[j][k] += c * m[i][k];
        }
      }
      ret *= m[i][i];
    }
    return std::move(ret);
  }
};

template <class T>
ostream& operator<<(ostream& os, const Matrix<T>& mat) {
  os << "[";
  FOR0(i, mat.N) {
    os << "[";
    FOR0(j, mat.M) {
      os << mat.mat[i][j];
      if (j != mat.M - 1) {
        os << ", ";
      }
    }
    os << "]";
    if (i != mat.N - 1) {
      os << ", ";
    }
  }
  os << "]";
  return os;
}