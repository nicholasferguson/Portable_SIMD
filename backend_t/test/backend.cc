

#include <VecCore/VecCore.h>
#include "base/Global.h"
//#include <VecCore/Backend/UMESimdCommon.h>
//#include <backend/Backend.h>
#include <type_traits>
#include <typeinfo>
#include <gtest/gtest.h>
#include <string>

using namespace testing;

#if defined(GTEST_HAS_TYPED_TEST) && defined(GTEST_HAS_TYPED_TEST_P)

template <class Backend>
using FloatTypes = Types<typename Backend::Float_v, typename Backend::Double_v>;

template <class Backend>
using IntTypes =
    Types<typename Backend::Int16_v, typename Backend::UInt16_v, typename Backend::Int32_v, typename Backend::UInt32_v>;

template <class Backend>
using VectorTypes = Types<typename Backend::Float_v, typename Backend::Double_v, typename Backend::Int16_v,
                          typename Backend::UInt16_v, typename Backend::Int32_v, typename Backend::UInt32_v>;

///////////////////////////////////////////////////////////////////////////////

template <class T>
class VectorTypeTest : public Test {
public:
  using Scalar_t = typename vecCore::ScalarType<T>::Type;
  using Vector_t = T;
};

///////////////////////////////////////////////////////////////////////////////

template <class T>
class ConstructorTest : public VectorTypeTest<T> {
};

TYPED_TEST_CASE_P(ConstructorTest);

TYPED_TEST_P(ConstructorTest, Default)
{
  using Vector_t = typename TestFixture::Vector_t;

  EXPECT_TRUE((std::is_constructible<Vector_t>::value));
}

TYPED_TEST_P(ConstructorTest, Copy)
{
  using Vector_t = typename TestFixture::Vector_t;

  EXPECT_TRUE((std::is_copy_constructible<Vector_t>::value));
}

TYPED_TEST_P(ConstructorTest, Move)
{
  using Vector_t = typename TestFixture::Vector_t;

  EXPECT_TRUE((std::is_move_constructible<Vector_t>::value));
}

TYPED_TEST_P(ConstructorTest, FromScalar)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  EXPECT_TRUE((std::is_constructible<Vector_t, Scalar_t>::value));
}

TYPED_TEST_P(ConstructorTest, FromRefToScalar)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;


  EXPECT_TRUE((std::is_constructible<Vector_t, const Scalar_t &>::value));
}
static int count = 0;
TYPED_TEST_P(ConstructorTest, FromPtrToScalar)
{
	using Scalar_t = typename TestFixture::Scalar_t;
	using Vector_t = typename TestFixture::Vector_t;
	//using Vector_X = typename  vecCore::Vector_v<Vector_t>;


	if (count == 12)
		int a = 10;
	count++;

	size_t size = 0;

	std::cout << "TYPED_TEST_P(ConstructorTest, FromPtrToScalar)\t" << typeid(Vector_t).name() << std::endl;
	std::string name(typeid(Vector_t).name());

	size = vecCore::VectorSize<Vector_t>(); 
	if (size > 4)
		int b = 10;

	Scalar_t* tmp = new Scalar_t[size];
	Scalar_t *addr =&tmp[0];


	for (vecCore::UInt_s i = 0; i < size; i++) {
		tmp[i] = static_cast<Scalar_t>(i);
	}
	vecCore::backend::UMESimdArray<8>::Float_v xx;
	//vecCore::backend::VcSimdArray<8>::Float_v  xy;
	// transfer to output via FromPtr; Store sequence
	for (vecCore::UInt_s i = 0; i < size; ++i) {
		//x=vecCore::FromPtr<Vector_t>(&addr[i]);
		xx.insert(i, i);
	//	vecCore::Store<Vector_t>(m, &x[i]);
	}
//	Vector_t x(xx);
//	x = vecCore::FromPtr<Vector_t>(addr);
	

//	for (int i = 0; i < size; ++i)
//	{
//		x = addr[i];
//	}
//	for (vecCore::UInt_s i = 0; i < vecCore::VectorSize<Vector_t>(); i++)
//		EXPECT_TRUE(!vecCore::MaskEmpty(x == Vector_t(Scalar_t(i))));


	for (vecCore::UInt_s i = 0; i < size; i++)
	{
		Vector_t y = Vector_t(Scalar_t(i));
	//	if (!vecCore::MaskEmpty(x == y))  // checks if a mask value is there.
	//		std::cout << "MaskEmpty ok" << std::endl;
	}
	delete[]tmp;
}

/*
static int count = 0;
TYPED_TEST_P(ConstructorTest, FromPtrToScalar)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t v;
  std::string s = typeid(v).name();
  std::cout << " FromPtrToScalar type: " << s.c_str() << std::endl;
  int f = s.find("Vector");
  Scalar_t* tmp;
  if (f > 0)
  {

	  const auto N = vecCore::VectorSize<Vector_t>();
	  std::cout << "Vector " << N << std::endl;

	  int a = sizeof(vecCore::Scalar<Vector_t>);
	  int a1 = sizeof(Vector_t);
	  std::cout << "Vector " << a << " " << a1 << std::endl;
	  vecCore::Scalar<Vector_t>* t = new vecCore::Scalar<Vector_t>();
	  tmp = new Scalar_t[N];
	  delete t;
  }
  else {
	  const auto N = vecCore::VectorSize<Vector_t>();
	  tmp = new Scalar_t[N];

  }


//  if (s.find_first_not_of("SIMDVec") > 0)
  //
	//  const auto N = vecCore::VectorSize<Vector_t>();
//	  Scalar_t* tmp = new Scalar_t[N];


//  const auto N1= vecCore::Size();
//  const auto N2 = vecgeom::VECGEOM_IMPL_NAMESPACE::Size<Vector_t>();
//  Scalar_t tmp[vecCore::VectorSize<Vector_t>(v)];
 // Scalar_t* tmp = new Scalar_t[N];
  Scalar_t *addr = &tmp[0];
  count++;
  if (count > 12) {

	//  vecCore::VectorSizeX<Vector_t>(v, count);
	//  std::string tname = typeid(Vector_t).name();
	//  if (tname.find("SIMDVec") != std::string::npos )
	//	  int a = 20;
	  int a = 2;
  }

  for (vecCore::UInt_s i = 0; i < vecCore::VectorSize<Vector_t>(v); i++) {
    tmp[i] = static_cast<Scalar_t>(i);
  }
  if (count > 12) {
//	  vecCore::VectorSizeX<Vector_t>(count); 
  }
  Vector_t x = vecCore::FromPtr<Vector_t>(addr);

  for (vecCore::UInt_s i = 0; i < vecCore::VectorSize<Vector_t>(); i++)
    EXPECT_TRUE(!vecCore::MaskEmpty(x == Vector_t(Scalar_t(i))));
}
*/
REGISTER_TYPED_TEST_CASE_P(ConstructorTest, Default, Copy, Move, FromScalar, FromRefToScalar, FromPtrToScalar);

///////////////////////////////////////////////////////////////////////////////

template <class T>
class ArithmeticsTest : public VectorTypeTest<T> {
};

TYPED_TEST_CASE_P(ArithmeticsTest);

TYPED_TEST_P(ArithmeticsTest, Addition)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(1));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs + rhs)));
}

TYPED_TEST_P(ArithmeticsTest, AdditionAssign)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(1));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  lhs += rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
}

TYPED_TEST_P(ArithmeticsTest, Subtraction)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(3));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs - rhs)));
}

TYPED_TEST_P(ArithmeticsTest, SubtractionAssign)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(3));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  lhs -= rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
}

TYPED_TEST_P(ArithmeticsTest, Multiplication)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(2));
  Vector_t rhs(static_cast<Scalar_t>(2));
  Vector_t res(static_cast<Scalar_t>(4));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs * rhs)));
}

TYPED_TEST_P(ArithmeticsTest, MultiplicationAssign)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(2));
  Vector_t rhs(static_cast<Scalar_t>(2));
  Vector_t res(static_cast<Scalar_t>(4));

  lhs *= rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
}

TYPED_TEST_P(ArithmeticsTest, Division)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(10));
  Vector_t rhs(static_cast<Scalar_t>(5));
  Vector_t res(static_cast<Scalar_t>(2));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs / rhs)));
}

TYPED_TEST_P(ArithmeticsTest, DivisionAssign)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t lhs(static_cast<Scalar_t>(10));
  Vector_t rhs(static_cast<Scalar_t>(5));
  Vector_t res(static_cast<Scalar_t>(2));

  lhs /= rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
}

REGISTER_TYPED_TEST_CASE_P(ArithmeticsTest, Addition, Subtraction, Multiplication, Division, AdditionAssign,
                           SubtractionAssign, MultiplicationAssign, DivisionAssign);

///////////////////////////////////////////////////////////////////////////////

template <class T>
class MaskArithmeticsTest : public VectorTypeTest<T> {
};

TYPED_TEST_CASE_P(MaskArithmeticsTest);

TYPED_TEST_P(MaskArithmeticsTest, AND)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Mask_t   = typename vecCore::Mask_v<Vector_t>;

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) & Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) && Mask_t(true))));

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) & Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(true) && Mask_t(false))));
}

TYPED_TEST_P(MaskArithmeticsTest, OR)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Mask_t   = typename vecCore::Mask_v<Vector_t>;

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) | Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) || Mask_t(true))));

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(false) | Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) || Mask_t(false))));

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) | Mask_t(false))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) || Mask_t(false))));
}

TYPED_TEST_P(MaskArithmeticsTest, NEG)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Mask_t   = typename vecCore::Mask_v<Vector_t>;

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == !Mask_t(true)));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == !Mask_t(false)));
}

TYPED_TEST_P(MaskArithmeticsTest, ANDAssign)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Mask_t   = typename vecCore::Mask_v<Vector_t>;

  Mask_t rhs(true);
  rhs &= Mask_t(false);

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == rhs));
}

TYPED_TEST_P(MaskArithmeticsTest, ORAssign)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Mask_t   = typename vecCore::Mask_v<Vector_t>;

  Mask_t rhs(false);
  rhs |= Mask_t(true);

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == rhs));
}

REGISTER_TYPED_TEST_CASE_P(MaskArithmeticsTest, AND, OR, NEG, ANDAssign, ORAssign);

///////////////////////////////////////////////////////////////////////////////

template <class T>
class VectorInterfaceTest : public VectorTypeTest<T> {
};

TYPED_TEST_CASE_P(VectorInterfaceTest);

TYPED_TEST_P(VectorInterfaceTest, VectorSize)
{
  using Vector_t = typename TestFixture::Vector_t;

  EXPECT_TRUE(vecCore::VectorSize<Vector_t>() > 0);
}

TYPED_TEST_P(VectorInterfaceTest, VectorSizeVariable)
{
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t x;
  EXPECT_TRUE(vecCore::VectorSize(x) > 0);
}

TYPED_TEST_P(VectorInterfaceTest, StoreToPtr)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;

  const int kVS = vecCore::VectorSize<Vector_t>();
  const int N   = 2 * kVS;
  Scalar_t* input = new Scalar_t[N];
  Scalar_t* output = new Scalar_t[N];

  // init input; output
  for (vecCore::UInt_s i = 0; i < N; ++i) {
    input[i]  = 2.0 * i;
    output[i] = 0;
  }

  // transfer to output via FromPtr; Store sequence
  for (vecCore::UInt_s i = 0; i < 2; ++i) {
    Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[i * kVS]));
    vecCore::Store<Vector_t>(tmp, &output[i * kVS]);
  }

  // assert input == output
  for (vecCore::UInt_s i = 0; i < N; ++i)
    EXPECT_EQ(input[i], output[i]);
}

TYPED_TEST_P(VectorInterfaceTest, StoreMaskToPtr)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;
  using Mask_t   = typename vecCore::Mask_v<Vector_t>;

  const int kVS = vecCore::VectorSize<Vector_t>();
  const int N   = 2 * kVS;
  Scalar_t* input = new Scalar_t[N];
  bool* output = new bool[N];

  // init input; output
  for (vecCore::UInt_s i = 0; i < N; ++i) {
    input[i]  = 2 * i;
    output[i] = false;
  }

  for (vecCore::UInt_s i = 0; i < 2; ++i) {
    Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[i * kVS]));
    Mask_t m = tmp > Vector_t(1);
    vecCore::StoreMask(m, &output[i * kVS]);
  }

  for (vecCore::UInt_s i = 0; i < N; ++i)
  {
	  std::cout << output[i] << " " << input[i] << " " << Scalar_t(1) << std::endl;
	  EXPECT_EQ(output[i], input[i] > Scalar_t(1));

  }
}

TYPED_TEST_P(VectorInterfaceTest, VectorLaneRead)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;

  const auto kVS = vecCore::VectorSize<Vector_t>();
  Scalar_t* input = new Scalar_t[kVS];

  for (vecCore::UInt_s i = 0; i < kVS; ++i) {
    input[i] = i;
  }

  Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[0]));

  for (vecCore::UInt_s i = 0; i < kVS; ++i)
    EXPECT_EQ(input[i], vecCore::LaneAt<Vector_t>(tmp, i));
}

TYPED_TEST_P(VectorInterfaceTest, VectorLaneWrite)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;

  const auto kVS = vecCore::VectorSize<Vector_t>();
  Scalar_t* input = new Scalar_t[kVS];

  for (vecCore::UInt_s i = 0; i < kVS; ++i) {
    input[i] = i;
  }

  Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[0]));

  for (vecCore::UInt_s i = 0; i < kVS; ++i)
    vecCore::AssignLane(tmp, i, Scalar_t(10));

  for (vecCore::UInt_s i = 0; i < kVS; ++i)
    EXPECT_EQ(Scalar_t(10), vecCore::LaneAt<Vector_t>(tmp, i));
}

TYPED_TEST_P(VectorInterfaceTest, MaskLaneRead)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;

  vecCore::Mask_v<Vector_t> fmask(false), tmask(true), mmask;

  const auto kVS = vecCore::VectorSize<Vector_t>();

  Vector_t input;

  for (size_t i = 0; i < kVS; ++i)
    vecCore::AssignLane(input, i, (i % 2 == 0) ? Scalar_t(1) : Scalar_t(0));

  mmask = input > Vector_t(Scalar_t(0));

  for (size_t i = 0; i < kVS; ++i) {
    EXPECT_EQ(vecCore::MaskLaneAt(tmask, i), true);
    EXPECT_EQ(vecCore::MaskLaneAt(fmask, i), false);
    EXPECT_EQ(vecCore::MaskLaneAt(mmask, i), i % 2 == 0);
  }
}

TYPED_TEST_P(VectorInterfaceTest, MaskLaneWrite)
{
  using Vector_t = typename TestFixture::Vector_t;

  vecCore::Mask_v<Vector_t> mask(false);

  const auto kVS = vecCore::VectorSize<Vector_t>();

  // check for all false

  for (size_t i = 0; i < kVS; ++i)
    EXPECT_EQ(vecCore::MaskLaneAt(mask, i), false);

  // check for all true

  for (size_t i = 0; i < kVS; ++i)
    vecCore::AssignMaskLane(mask, i, true);

  for (size_t i = 0; i < kVS; ++i)
    EXPECT_EQ(vecCore::MaskLaneAt(mask, i), true);

  // check for interleaving true/false

  for (size_t i = 0; i < kVS; ++i)
    vecCore::AssignMaskLane(mask, i, i % 2 == 0);

  for (size_t i = 0; i < kVS; ++i)
    EXPECT_EQ(vecCore::MaskLaneAt(mask, i), i % 2 == 0);
}

TYPED_TEST_P(VectorInterfaceTest, Gather)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;
  using Index_v  = typename vecCore::Index_v<Vector_t>;
  using Index_t  = typename vecCore::ScalarType<Index_v>::Type;

  const auto N = vecCore::VectorSize<Vector_t>();

  Scalar_t* input = new Scalar_t[N * N];
  for (vecCore::UInt_s i = 0; i < N * N; ++i) {
    input[i] = i;
  }

  Index_v idx;
  for (vecCore::UInt_s i = 0; i < N; ++i)
    vecCore::AssignLane(idx, i, Index_t(i));

  for (vecCore::UInt_s i = 1; i <= N; ++i) {
    Index_v iidx = Index_v(i) * idx;

    Vector_t x = vecCore::Gather<Vector_t>(input, iidx);

    for (vecCore::UInt_s j = 0; j < N; ++j)
      EXPECT_TRUE(vecCore::LaneAt(x, j) == input[i * j]);
  }
}

TYPED_TEST_P(VectorInterfaceTest, Scatter)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;
  using Index_v  = typename vecCore::Index_v<Vector_t>;
  using Index_t  = typename vecCore::ScalarType<Index_v>::Type;

  const auto  N = vecCore::VectorSize<Vector_t>();

  Index_t* index = new Index_t[N];
  Scalar_t* input = new Scalar_t[N];
  Scalar_t* output  = new Scalar_t[N];

  for (vecCore::UInt_s i = 0; i < N; ++i) {
    input[i] = i;
    index[i] = i;
  }

  Index_v idx(vecCore::FromPtr<Index_v>(&index[0]));

  Vector_t x = vecCore::FromPtr<Vector_t>(&input[0]);

  vecCore::Scatter<Vector_t>(x, &output[0], idx);

  Vector_t y = vecCore::FromPtr<Vector_t>(&output[0]);

  EXPECT_TRUE(vecCore::MaskFull(x == y));
}

REGISTER_TYPED_TEST_CASE_P(VectorInterfaceTest, VectorSize, VectorSizeVariable, StoreToPtr, StoreMaskToPtr,
                           VectorLaneRead, VectorLaneWrite, MaskLaneRead, MaskLaneWrite, Gather, Scatter);

///////////////////////////////////////////////////////////////////////////////

template <class T>
class VectorMaskTest : public VectorTypeTest<T> {
};

TYPED_TEST_CASE_P(VectorMaskTest);

TYPED_TEST_P(VectorMaskTest, Constructor)
{
  using Vector_t = typename TestFixture::Vector_t;

  EXPECT_TRUE(std::is_constructible<vecCore::Mask_v<Vector_t>>::value);
  EXPECT_TRUE(std::is_copy_constructible<vecCore::Mask_v<Vector_t>>::value);
  EXPECT_TRUE(std::is_move_constructible<vecCore::Mask_v<Vector_t>>::value);
}

TYPED_TEST_P(VectorMaskTest, MaskFull)
{
  using Vector_t = typename TestFixture::Vector_t;

  vecCore::Mask_v<Vector_t> tmask(true), fmask(false);

  EXPECT_TRUE(vecCore::MaskFull(tmask));
  EXPECT_TRUE(vecCore::MaskFull(!fmask));
}

TYPED_TEST_P(VectorMaskTest, MaskEmpty)
{
  using Vector_t = typename TestFixture::Vector_t;

  vecCore::Mask_v<Vector_t> tmask(true), fmask(false);

  EXPECT_TRUE(vecCore::MaskEmpty(fmask));
  EXPECT_TRUE(vecCore::MaskEmpty(!tmask));
}

TYPED_TEST_P(VectorMaskTest, MaskAssign)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;

  // casting 0 with Scalar_t is necessary here
  // as 0 can be interpreted as the null-pointer
  // which leads to ambiguities with some vector types constructors
  // (For example the float instantiation of UME::SIMD vector has 'only'
  //  constructor taking a float and another taking a float* both requiring
  //  one conversion from an integer '0'.)
  Vector_t a(Scalar_t(0)), b(1);

  vecCore::MaskedAssign(a, a > b, b);
  EXPECT_TRUE(vecCore::MaskFull(a == Vector_t(Scalar_t(0))));

  vecCore::MaskedAssign(a, b > a, b);
  EXPECT_TRUE(vecCore::MaskFull(a == b));
}

TYPED_TEST_P(VectorMaskTest, MaskAssign2)
{
  using Vector_t = typename TestFixture::Vector_t;
  using Scalar_t = typename TestFixture::Scalar_t;

  const int kVS = vecCore::VectorSize<Vector_t>();
  Scalar_t* input = new Scalar_t[kVS];
  Scalar_t* output = new Scalar_t[kVS];

  for (vecCore::UInt_s i = 0; i < kVS; ++i) {
    input[i]  = (i % 2 == 0) ? i : -i;
    output[i] = (input[i] > 0) ? input[i] : 0;
  }

  Vector_t c(vecCore::FromPtr<Vector_t>(&input[0])), dest(Scalar_t(0));
  vecCore::MaskedAssign(dest, c > Vector_t(Scalar_t(0)), c);

  for (vecCore::UInt_s i = 0; i < kVS; ++i)
    EXPECT_EQ(vecCore::LaneAt<Vector_t>(dest, i), output[i]);
}

TYPED_TEST_P(VectorMaskTest, Blend)
{
  using Scalar_t = typename TestFixture::Scalar_t;
  using Vector_t = typename TestFixture::Vector_t;

  Vector_t a(Scalar_t(0)), b(1);

  a = vecCore::Blend(a > b, a, b);
}

REGISTER_TYPED_TEST_CASE_P(VectorMaskTest, Constructor, MaskFull, MaskEmpty, MaskAssign, MaskAssign2, Blend);

#define TEST_BACKEND_P(name, x)                                                               \
  INSTANTIATE_TYPED_TEST_CASE_P(name, ConstructorTest, VectorTypes<vecCore::backend::x>);     \
  INSTANTIATE_TYPED_TEST_CASE_P(name, ArithmeticsTest, VectorTypes<vecCore::backend::x>);     \
  INSTANTIATE_TYPED_TEST_CASE_P(name, MaskArithmeticsTest, VectorTypes<vecCore::backend::x>); \
  INSTANTIATE_TYPED_TEST_CASE_P(name, VectorMaskTest, VectorTypes<vecCore::backend::x>);      \
  INSTANTIATE_TYPED_TEST_CASE_P(name, VectorInterfaceTest, VectorTypes<vecCore::backend::x>)

#define TEST_BACKEND(x) TEST_BACKEND_P(x, x)

///////////////////////////////////////////////////////////////////////////////

TEST_BACKEND(Scalar);
TEST_BACKEND(ScalarWrapper);

#ifdef VECCORE_ENABLE_VC
TEST_BACKEND(VcScalar);
TEST_BACKEND(VcVector);
TEST_BACKEND_P(VcSimdArray, VcSimdArray<16>);
#endif

#ifdef VECCORE_ENABLE_UMESIMD
//TEST_BACKEND(UMESimd);
TEST_BACKEND_P(UMESimdArray, UMESimdArray<8>);
#endif

#else // if !GTEST_HAS_TYPED_TEST
TEST(DummyTest, TypedTestsAreNotSupportedOnThisPlatform)
{
}
#endif

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
	//UME::SIMD::SIMDVec_f<float, 16>* f = new UME::SIMD::SIMDVec_f<float, 16>();
	//size_t len = f->length();
	//size_t len2 = vecCore::Mask_v<UME::SIMD::SIMDVec_f<float, 16> >::length();
//	using T = Vc_1::Vector<float, struct Vc_1::VectorAbi::Avx>;
//	size_t c = sizeof(T);  // c is 32
//	size_t t = sizeof(vecCore::Scalar<T>); // t is 4
//	size_t VectorSize = c / t;  // VectorSize is 8

	


	return 0;
}
