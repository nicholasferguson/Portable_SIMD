/// \file vector3d.h
/// \author Johannes de Fine Licht (johannes.definelicht@cern.ch)

#ifndef VECGEOM_BASE_VECTOR3D_H_
#define VECGEOM_BASE_VECTOR3D_H_

#include "base/Global.h"

#include "backend/Backend.h"
#include "base/AlignedBase.h"

#include <cstdlib>
#include <ostream>
#include <string>

namespace vecgeom {

VECGEOM_DEVICE_FORWARD_DECLARE(template <typename Type> class Vector3D;);

inline namespace VECGEOM_IMPL_NAMESPACE {

/**
 * @brief Three dimensional vector class supporting most arithmetic operations.
 * @details If vector acceleration is enabled, the scalar template instantiation
 *          will use vector instructions for operations when possible.
 */
template <typename Type>
class Vector3D : public AlignedBase {

  typedef Vector3D<Type> VecType;

private:
  Type vec[3];

public:
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Vector3D(const Type a, const Type b, const Type c)
  {
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
  }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Vector3D()
  {
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
  }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Vector3D(const Type a)
  {
    vec[0] = a;
    vec[1] = a;
    vec[2] = a;
  }

  template <typename TypeOther>
  VECGEOM_FORCE_INLINE
  VECGEOM_CUDA_HEADER_BOTH
  Vector3D(Vector3D<TypeOther> const &other)
  {
    vec[0] = other[0];
    vec[1] = other[1];
    vec[2] = other[2];
  }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Vector3D &operator=(Vector3D const &other)
  {
    vec[0] = other[0];
    vec[1] = other[1];
    vec[2] = other[2];
    return *this;
  }

  /**
   * Constructs a vector from an std::string of the same format as output by the
   * "<<"-operator for outstreams.
   * @param str String formatted as "(%d, %d, %d)".
   */
  VECGEOM_CUDA_HEADER_HOST
  Vector3D(std::string const &str)
  {
    int begin = 1, end = str.find(",");
    vec[0] = std::atof(str.substr(begin, end - begin).c_str());
    begin  = end + 2;
    end    = str.find(",", begin);
    vec[1] = std::atof(str.substr(begin, end - begin).c_str());
    begin  = end + 2;
    end    = str.find(")", begin);
    vec[2] = std::atof(str.substr(begin, end - begin).c_str());
  }

  /**
   * Contains no check for correct indexing to avoid impairing performance.
   * @param index Index of content in the range [0-2].
   */
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type &operator[](const int index) { return vec[index]; }

  /**
   * Contains no check for correct indexing to avoid impairing performance.
   * @param index Index of content in the range [0-2].
   */
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type const &operator[](const int index) const { return vec[index]; }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type &x() { return vec[0]; }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type const &x() const { return vec[0]; }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type &y() { return vec[1]; }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type const &y() const { return vec[1]; }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type &z() { return vec[2]; }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type const &z() const { return vec[2]; }

  VECGEOM_CUDA_HEADER_BOTH
  void Set(Type const &a, Type const &b, Type const &c)
  {
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;
  }

  VECGEOM_CUDA_HEADER_BOTH
  void Set(const Type a) { Set(a, a, a); }

  /// \return the length squared perpendicular to z direction
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Perp2() const { return vec[0] * vec[0] + vec[1] * vec[1]; }

  /// \return the length perpendicular to z direction
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Perp() const { return Sqrt(Perp2()); }

  /// The dot product of two Vector3D<T> objects
  /// \return T (where T is float, double, or various SIMD vector types)
  template <typename Type2>
  VECGEOM_FORCE_INLINE
  VECGEOM_CUDA_HEADER_BOTH
  static Type Dot(Vector3D<Type> const &left, Vector3D<Type2> const &right)
  {
    return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
  }

  /// The dot product of two Vector3D<T> objects
  /// \return T (where T is float, double, or various SIMD vector types)
  template <typename Type2>
  VECGEOM_FORCE_INLINE
  VECGEOM_CUDA_HEADER_BOTH
  Type Dot(Vector3D<Type2> const &right) const
  {
    return Dot(*this, right);
  }

  // For UVector3 compatibility. Is equal to normal multiplication.
  // TODO: check if there are implicit dot products in USolids...
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  VecType MultiplyByComponents(VecType const &other) const { return *this * other; }

  /// \return Squared magnitude of the vector.
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Mag2() const { return Dot(*this, *this); }

  /// \return Magnitude of the vector.
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Mag() const { return Sqrt(Mag2()); }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Length() const { return Mag(); }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Length2() const { return Mag2(); }

  /// Normalizes the vector by dividing each entry by the length.
  /// \sa Vector3D::Length()
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  void Normalize() { *this *= (1. / Length()); }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Vector3D<Type> Normalized() const { return Vector3D<Type>(*this) * (1. / Length()); }

  // checks if vector is normalized
  // only reasonable to call with standard scalare usage
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  bool IsNormalized() const
  {
    // static_assert here that Type should be primitive type
    Precision norm = Mag2();
    return 1. - vecgeom::kTolerance < norm && norm < 1 + vecgeom::kTolerance;
  }

  /// \return Azimuthal angle between -pi and pi.
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Phi() const { return ATan2(vec[1], vec[0]); }

  /// \return Polar angle between 0 and pi.
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Theta() const { return ACos(vec[2] / Mag()); }

  /// The cross (vector) product of two Vector3D<T> objects
  /// \return Type (where Type is float, double, or various SIMD vector types)
  template <class FirstType, class SecondType>
  VECGEOM_FORCE_INLINE
  VECGEOM_CUDA_HEADER_BOTH
  static Vector3D<Type> Cross(Vector3D<FirstType> const &left, Vector3D<SecondType> const &right)
  {
    return Vector3D<Type>(left[1] * right[2] - left[2] * right[1], left[2] * right[0] - left[0] * right[2],
                          left[0] * right[1] - left[1] * right[0]);
  }

  /// The cross (vector) product of two Vector3D<T> objects
  /// \return Type (where Type is float, double, or various SIMD vector types)
  template <class OtherType>
  VECGEOM_FORCE_INLINE
  VECGEOM_CUDA_HEADER_BOTH
  Vector3D<Type> Cross(Vector3D<OtherType> const &right) const
  {
    return Cross<Type, OtherType>(*this, right);
  }

  /// Maps each vector entry to a function that manipulates the entry type.
  /// \param f A function of type "Type f(const Type&)" to map over entries.
  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  void Map(Type (*f)(const Type &))
  {
    vec[0] = f(vec[0]);
    vec[1] = f(vec[1]);
    vec[2] = f(vec[2]);
  }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Vector3D<Type> Abs() const
  {
    return Vector3D<Type>(vecCore::math::Abs(vec[0]), vecCore::math::Abs(vec[1]), vecCore::math::Abs(vec[2]));
  }

  template <typename BoolType>
  VECGEOM_FORCE_INLINE
  VECGEOM_CUDA_HEADER_BOTH
  void MaskedAssign(Vector3D<BoolType> const &condition, Vector3D<Type> const &value)
  {
    vec[0] = (condition[0]) ? value[0] : vec[0];
    vec[1] = (condition[1]) ? value[1] : vec[1];
    vec[2] = (condition[2]) ? value[2] : vec[2];
  }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Min() const { return vecCore::math::Min(vec[0], vec[1], vec[2]); }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  Type Max() const { return vecCore::math::Max(vec[0], vec[1], vec[2]); }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  VecType Unit() const
  {
    const Type mag2 = Mag2();
    VecType output(*this);
    output /= Sqrt(mag2 + kMinimum);
    return output;
  }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  static VecType FromCylindrical(Type r, Type phi, Type z) { return VecType(r * cos(phi), r * sin(phi), z); }

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  VecType &FixZeroes()
  {
    using vecCore::math::Abs;
    for (int i = 0; i < 3; ++i) {
      vecCore::MaskedAssign(vec[i], Abs(vec[i]) < kTolerance, Type(0.0));
    }
    return *this;
  }

// Inplace binary operators

#define VECTOR3D_TEMPLATE_INPLACE_BINARY_OP(OPERATOR)                                                        \
  VECGEOM_CUDA_HEADER_BOTH                                                                                   \
  VECGEOM_FORCE_INLINE                                                                                       \
  VecType &operator OPERATOR(const VecType &other)                                                           \
  {                                                                                                          \
    vec[0] OPERATOR other.vec[0];                                                                            \
    vec[1] OPERATOR other.vec[1];                                                                            \
    vec[2] OPERATOR other.vec[2];                                                                            \
    return *this;                                                                                            \
  }                                                                                                          \
  template <typename OtherType>                                                                              \
  VECGEOM_CUDA_HEADER_BOTH VECGEOM_FORCE_INLINE VecType &operator OPERATOR(const Vector3D<OtherType> &other) \
  {                                                                                                          \
    vec[0] OPERATOR other[0];                                                                                \
    vec[1] OPERATOR other[1];                                                                                \
    vec[2] OPERATOR other[2];                                                                                \
    return *this;                                                                                            \
  }                                                                                                          \
  VECGEOM_CUDA_HEADER_BOTH                                                                                   \
  VECGEOM_FORCE_INLINE                                                                                       \
  VecType &operator OPERATOR(const Type &scalar)                                                             \
  {                                                                                                          \
    vec[0] OPERATOR scalar;                                                                                  \
    vec[1] OPERATOR scalar;                                                                                  \
    vec[2] OPERATOR scalar;                                                                                  \
    return *this;                                                                                            \
  }
  VECTOR3D_TEMPLATE_INPLACE_BINARY_OP(+=)
  VECTOR3D_TEMPLATE_INPLACE_BINARY_OP(-=)
  VECTOR3D_TEMPLATE_INPLACE_BINARY_OP(*=)
  VECTOR3D_TEMPLATE_INPLACE_BINARY_OP(/=)
#undef VECTOR3D_TEMPLATE_INPLACE_BINARY_OP

  VECGEOM_CUDA_HEADER_BOTH
  VECGEOM_FORCE_INLINE
  operator bool() const { return vec[0] && vec[1] && vec[2]; }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, Vector3D<T> const &vec)
{
  os << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
  return os;
}

#define VECTOR3D_BINARY_OP(OPERATOR, INPLACE)                                                                    \
  template <typename Type, typename OtherType>                                                                   \
  VECGEOM_FORCE_INLINE VECGEOM_CUDA_HEADER_BOTH Vector3D<Type> operator OPERATOR(const Vector3D<Type> &lhs,      \
                                                                                 const Vector3D<OtherType> &rhs) \
  {                                                                                                              \
    Vector3D<Type> result(lhs);                                                                                  \
    result INPLACE rhs;                                                                                          \
    return result;                                                                                               \
  }                                                                                                              \
  template <typename Type, typename ScalarType>                                                                  \
  VECGEOM_FORCE_INLINE VECGEOM_CUDA_HEADER_BOTH Vector3D<Type> operator OPERATOR(Vector3D<Type> const &lhs,      \
                                                                                 const ScalarType rhs)           \
  {                                                                                                              \
    Vector3D<Type> result(lhs);                                                                                  \
    result INPLACE rhs;                                                                                          \
    return result;                                                                                               \
  }                                                                                                              \
  template <typename Type, typename ScalarType>                                                                  \
  VECGEOM_FORCE_INLINE VECGEOM_CUDA_HEADER_BOTH Vector3D<Type> operator OPERATOR(const ScalarType lhs,           \
                                                                                 Vector3D<Type> const &rhs)      \
  {                                                                                                              \
    Vector3D<Type> result(lhs);                                                                                  \
    result INPLACE rhs;                                                                                          \
    return result;                                                                                               \
  }
VECTOR3D_BINARY_OP(+, +=)
VECTOR3D_BINARY_OP(-, -=)
VECTOR3D_BINARY_OP(*, *=)
VECTOR3D_BINARY_OP(/, /=)
#undef VECTOR3D_BINARY_OP

VECGEOM_FORCE_INLINE
VECGEOM_CUDA_HEADER_BOTH
bool operator==(Vector3D<Precision> const &lhs, Vector3D<Precision> const &rhs)
{
  return Abs(lhs[0] - rhs[0]) < kTolerance && Abs(lhs[1] - rhs[1]) < kTolerance && Abs(lhs[2] - rhs[2]) < kTolerance;
}

VECGEOM_FORCE_INLINE
VECGEOM_CUDA_HEADER_BOTH
Vector3D<bool> operator!=(Vector3D<Precision> const &lhs, Vector3D<Precision> const &rhs)
{
  return !(lhs == rhs);
}

template <typename Type>
VECGEOM_FORCE_INLINE
VECGEOM_CUDA_HEADER_BOTH
Vector3D<Type> operator-(Vector3D<Type> const &vec)
{
  return Vector3D<Type>(-vec[0], -vec[1], -vec[2]);
}

VECGEOM_CUDA_HEADER_BOTH
VECGEOM_FORCE_INLINE
Vector3D<bool> operator!(Vector3D<bool> const &vec)
{
  return Vector3D<bool>(!vec[0], !vec[1], !vec[2]);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#define VECTOR3D_SCALAR_BOOLEAN_LOGICAL_OP(OPERATOR)                                               \
  VECGEOM_CUDA_HEADER_BOTH                                                                         \
  VECGEOM_FORCE_INLINE                                                                             \
  Vector3D<bool> operator OPERATOR(Vector3D<bool> const &lhs, Vector3D<bool> const &rhs)           \
  {                                                                                                \
    return Vector3D<bool>(lhs[0] OPERATOR rhs[0], lhs[1] OPERATOR rhs[1], lhs[2] OPERATOR rhs[2]); \
  }
VECTOR3D_SCALAR_BOOLEAN_LOGICAL_OP(&&)
VECTOR3D_SCALAR_BOOLEAN_LOGICAL_OP(||)
#undef VECTOR3D_SCALAR_BOOLEAN_LOGICAL_OP
#pragma GCC diagnostic pop
} // End inline namespace
} // End global namespace

namespace vecCore {

template <typename T>
VECGEOM_FORCE_INLINE
VECGEOM_CUDA_HEADER_BOTH
void MaskedAssign(vecgeom::Vector3D<T> &v, const vecCore::Mask<T> &mask, const vecgeom::Vector3D<T> &val)
{
  vecCore::MaskedAssign(v[0], mask, val[0]);
  vecCore::MaskedAssign(v[1], mask, val[1]);
  vecCore::MaskedAssign(v[2], mask, val[2]);
}
}

#endif // VECGEOM_BASE_VECTOR3D_H_
