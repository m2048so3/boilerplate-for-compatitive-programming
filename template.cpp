#define NDEBUG

#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <numeric>
#include <utility>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <tuple>
#include <set>
#include <map>

// [0, max)
#define FOR0(var, max) for (sl (var) = 0; (var) < (max); ++(var))
// [min, max)
#define FORi(var, min, max) for (sl (var) = (min); (var) < (max); ++(var))
// [min, max)
#define FORi_INV(var, min, max) for (sl (var) = (max) - 1; (var) + 1 > (min); --(var))
#define FORITER(var, iter) for (auto (iter) = (var).begin(); (iter) != (var).end(); (iter)++)
#define FORITER_INV(var, iter) for (auto (iter) = (var).rbegin(); (iter) != (var).rend(); (iter)++)

// a < b < c
#define LTLT(a, b, c) (((a) < (b)) && ((b) < (c)))
// a <= b < c
#define LELT(a, b, c) (((a) <= (b)) && ((b) < (c)))
// a < b <= c
#define LTLE(a, b, c) (((a) < (b)) && ((b) <= (c)))
// a <= b <= c
#define LELE(a, b, c) (((a) <= (b)) && ((b) <= (c)))

#ifndef NDEBUG
#  define MASSERT(cond) m_assert(cond, __LINE__, #cond);
#else
#  define MASSERT(...)
#endif

using namespace std;

using uc = unsigned char;
using ui = unsigned int;
using ul = unsigned long long int;

using sc = signed char;
using si = signed int;
using sl = signed long long int;

using ld = long double;

void m_assert(const bool& cond, const sl& line, const char *condstr) {
  if (!cond) {
    cerr << "Assertion Failed: " << condstr << " at line " << line << endl;
    exit(1);
  }
}

void solve(void) {
}

int main(void) {
  solve();
  return 0;
}

