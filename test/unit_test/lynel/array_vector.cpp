// License: The Unlicense (https://unlicense.org)

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>

namespace tybl::lynel::std::array_vector {

template <typename T, size_t M>
auto operator+(::std::array<T,M> const& l, ::std::array<T,M> const& r) -> ::std::array<T,M> {
  ::std::array<T,M> result;
  ::std::transform(l.cbegin(), l.cend(), r.cbegin(), result.begin(), ::std::plus());
  return result;
}

template <typename T, size_t M>
auto operator-(::std::array<T,M> const& l, ::std::array<T,M> const& r) -> ::std::array<T,M> {
  ::std::array<T,M> result;
  ::std::transform(l.cbegin(), l.cend(), r.cbegin(), result.begin(), ::std::minus());
  return result;
}

template <typename T, size_t M>
auto operator*(T l, ::std::array<T,M> r) -> ::std::array<T,M> {
  for (auto& e : r) { e *= l; }
  return r;
}

template <typename T, size_t M>
constexpr auto operator*(::std::array<T,M> const& l, T r) -> ::std::array<T,M> {
  return r * l;
}

template <typename T, size_t M>
auto operator-(::std::array<T,M> const& v) -> ::std::array<T,M> {
  return static_cast<T>(-1) * v;
}

template <typename T, size_t M>
constexpr auto dot_product(::std::array<T,M> const& l, ::std::array<T,M> const& r) -> T {
  return ::std::inner_product(l.begin(), l.end(), r.begin(), 0.0);
}

template <typename T, size_t M>
constexpr auto magnitude(::std::array<T,M> const& v) -> T {
  return ::std::sqrt(dot_product(v,v));
}

template <typename T>
constexpr auto cross_product(::std::array<T,3> const& l, ::std::array<T,3> const& r) -> ::std::array<T,3> {
  return ::std::array<T,3>{ l[1]*r[2] - l[2]*r[1],
                            l[2]*r[0] - l[0]*r[2],
                            l[0]*r[1] - l[1]*r[0] };
}

template <typename T, size_t M>
constexpr auto projection(::std::array<T,M> const& l, ::std::array<T,M> const& r) -> ::std::array<T,M> {
  return (dot_product(l, r) / dot_product(r, r)) * r;
}

template <typename T, size_t M>
constexpr auto rejection(::std::array<T,M> const& l, ::std::array<T,M> const& r) -> ::std::array<T,M> {
  return l - projection(l,r);
}

template <typename T, size_t M>
auto operator<<(::std::ostream& out, ::std::array<T,M> const r) -> ::std::ostream& {
  for (auto x : r) { out << x << " "; }
  return out;
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

TEST_CASE("dot product") {
  std::array<double,3> a{ 1, 0, 0 };
  std::array<double,3> b{ 0, 2, 0 };
  std::array<double,3> c{ 2, 2, 2 };

  CHECK(1.0 == dot_product(a,a));
  CHECK(0.0 == dot_product(a,b));
  CHECK(4.0 == dot_product(b,b));
  CHECK(12.0 == dot_product(c,c));
}

TEST_CASE("Commutative law for the dot product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };

  auto l = dot_product(a, b);
  auto r = dot_product(b, a);

  CHECK(l == r);
}

TEST_CASE("Distributive law for the dot product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  std::array<double,3> c{ 7, 8, 9 };

  auto l = dot_product(a, (b + c));
  auto r = dot_product(a, b) + dot_product(a, c);

  CHECK(l == r);
}

TEST_CASE("Scalar factorization for the dot product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  double t = 9.0;

  auto l = dot_product(t * a, b);
  auto c = dot_product(a, t * b);
  auto r = t * dot_product(a, b);

  CHECK(l == c);
  CHECK(c == r);
}

TEST_CASE("magnitude") {
  std::array<double,3> a{ 3, 4, 0 };
  std::array<double,3> i{ 1, 0, 0 };
  std::array<double,3> z{ 0, 0, 0 };

  CHECK(5.0 == magnitude(a));
  CHECK(1.0 == magnitude(i));
  CHECK(0.0 == magnitude(z));
}

TEST_CASE("cross product") {
  std::array<double,3> i{ 1, 0, 0 };
  std::array<double,3> j{ 0, 1, 0 };
  std::array<double,3> k{ 0, 0, 1 };

  CHECK(k == cross_product(i, j));
  CHECK(-k == cross_product(j, i));
  CHECK(i == cross_product(j, k));
  CHECK(-i == cross_product(k, j));
  CHECK(j == cross_product(k, i));
  CHECK(-j == cross_product(i, k));
}

TEST_CASE("Anticommutativity of the cross product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };

  auto l = cross_product(a, b);
  auto r = cross_product(-b, a);

  CHECK(l == r);
}

TEST_CASE("Distributive law for the cross product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  std::array<double,3> c{ 7, 8, 9 };

  auto l = cross_product(a, (b + c));
  auto r = cross_product(a, b) + cross_product(a, c);

  CHECK(l == r);
}

TEST_CASE("Scalar factorization for the cross product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  double t = 9.0;

  auto l = cross_product((t * a), b);
  auto c = cross_product(a, (t * b));
  auto r = t * cross_product(a, b);

  CHECK(l == c);
  CHECK(c == r);
}

TEST_CASE("Vector triple product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  std::array<double,3> c{ 7, 8, 9 };

  auto l = cross_product(a, cross_product(b, c));
  auto r = b * dot_product(a, c) - c * dot_product(a, b);

  CHECK(l == r);
}

TEST_CASE("Lagrange's identity") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };

  auto tmp = cross_product(a,b);
  auto l = dot_product(tmp, tmp);
  auto r = dot_product(a, a) * dot_product(b, b) - dot_product(a,b) * dot_product(a,b);

  CHECK(l == r);
}

TEST_CASE("Scalar triple product") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };
  std::array<double,3> c{ 7, 8, 9 };

  auto l = dot_product(cross_product(a, b), c);
  auto m = dot_product(cross_product(b, c), a);
  auto r = dot_product(cross_product(c, a), b);

  CHECK(l == m);
  CHECK(m == r);
}

TEST_CASE("Projection/Rejection") {
  std::array<double,3> a{ 1, 2, 3 };
  std::array<double,3> b{ 4, 5, 6 };

  auto p = projection(a,b);
  auto r = rejection(a,b);

  CHECK(doctest::Approx(0.0) == dot_product(p,r));
}
