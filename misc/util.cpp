template <class T>
std::set<T> set_intersection(const std::set<T>& X, const std::set<T>& Y) {
  std::set<T> ret;
  std::set_intersection(X.begin(), X.end(), Y.begin(), Y.end(), std::inserter(ret, ret.end()));
  return std::move(ret);
}