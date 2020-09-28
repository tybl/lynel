// License: The Unlicense (https://unlicense.org)

#include <algorithm>
#include <array>

namespace tybl::lynel::std::array_vector {

template <typename T, size_t M>
auto operator+(::std::array<T,M> const& l, ::std::array<T,M> const& r) -> ::std::array<T,M> {
  ::std::array<T,M> result;
  ::std::transform(l.cbegin(), l.cend(), r.cbegin(), result.begin(), ::std::plus());
  return result;
}

template <typename T, size_t M>
auto operator*(::std::array<T,M> l, T r) -> ::std::array<T,M> {
  for (auto& e : l) { e *= r; }
  return l;
}

template <typename T, size_t M>
auto operator*(T l, ::std::array<T,M> const& r) -> ::std::array<T,M> {
  return r * l;
}

} // namespace tybl::lynel::std::array_vector

using namespace tybl::lynel::std::array_vector;

#include <doctest/doctest.h>

TEST_CASE("Associative law for vector addition") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  std::array<double,3> c{ 7, 8, 9 };

  auto l = (a + b)+ c;
  auto r =  a +(b + c);

  CHECK(l == r);
}

TEST_CASE("Commutative law for vector addition") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };

  auto l = a + b;
  auto r = b + a;

  CHECK(l == r);
}

TEST_CASE("Associate law for scalar-vector multiplication") {
  std::array<double,3> a{ 1, 2, 3 };
  double s = 5.0;
  double t = 3.0;

  auto l = (s * t)* a;
  auto r =  s *(t * a);

  CHECK(l == r);
}

TEST_CASE("Commutative law for scalar-vector multiplication") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  double t = 9.0;

  auto l = t * (a + b);
  auto r = (t * a) + (t * b);

  CHECK(l == r);
}

