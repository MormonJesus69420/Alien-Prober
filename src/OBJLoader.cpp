#include "include/OBJLoader.hpp"

namespace alien_prober {

objl::Vector3 objl::math::CrossV3(const objl::Vector3 a, const objl::Vector3 b)
{
  return Vector3(a.Y * b.Z - a.Z * b.Y,
      a.Z * b.X - a.X * b.Z,
      a.X * b.Y - a.Y * b.X);
}

float objl::math::MagnitudeV3(const objl::Vector3 in)
{
  return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
}

float objl::math::DotV3(const objl::Vector3 a, const objl::Vector3 b)
{
  return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

float objl::math::AngleBetweenV3(const objl::Vector3 a, const objl::Vector3 b)
{
  float angle = DotV3(a, b);
  angle /= (MagnitudeV3(a) * MagnitudeV3(b));
  return angle = acosf(angle);
}

objl::Vector3 objl::algorithm::operator*(const float& left, const objl::Vector3& right)
{
  return Vector3(right.X * left, right.Y * left, right.Z * left);
}

bool objl::algorithm::inTriangle(objl::Vector3 point, objl::Vector3 tri1, objl::Vector3 tri2, objl::Vector3 tri3)
{
  // Starting vars
  Vector3 u = tri2 - tri1;
  Vector3 v = tri3 - tri1;
  Vector3 w = point - tri1;
  Vector3 n = math::CrossV3(u, v);

  float y = (math::DotV3(math::CrossV3(u, w), n) / math::DotV3(n, n));
  float b = (math::DotV3(math::CrossV3(u, w), n) / math::DotV3(n, n));
  float a = 1 - y - b;

  if (a >= 0 && a <= 1
      && b >= 0 && b <= 1
      && y >= 0 && y <= 1) {
    return true;
  }
  else
    return false;
}
} // namespace alien_prober
