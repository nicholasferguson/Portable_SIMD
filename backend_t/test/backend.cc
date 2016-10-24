

#include <VecCore/VecCore.h>
#include <VecCore/Common.h>
#include "VecCore/base/Global.h"
#include <Vc/Vc>
#include <gtest/gtest.h>
#include <type_traits>
#include <typeinfo>
#include <string>
#include <algorithm>
#include <stdint.h>


using namespace testing;
using namespace vecCore;


///////////////////////////////////////////////////////////////////////////////


template<typename T>
void ConstructorTest_Default()
{
  using Vector_t = T;
  std::cout << __FUNCTION__ <<"\t" << typeid(T).name() << "\t";
  EXPECT_TRUE((std::is_constructible<Vector_t>::value));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ConstructorTest_Copy()
{
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  EXPECT_TRUE((std::is_copy_constructible<Vector_t>::value));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ConstructorTest_Move()
{
using Vector_t = T;
  std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  EXPECT_TRUE((std::is_move_constructible<Vector_t>::value));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ConstructorTest_FromScalar()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  EXPECT_TRUE((std::is_constructible<Vector_t, Scalar_t>::value));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ConstructorTest_FromRefToScalar()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";

  EXPECT_TRUE((std::is_constructible<Vector_t, const Scalar_t &>::value));
  std::cout << "PASS" << std::endl;
}
static int count = 0;

/*
template < typename T, typename U>
typename std::enable_if<TypeTraits<T>::isVector, void>::type
do_stuff(T& x, U* addr)
{
	x.load(addr);

}

template < typename T, typename U>
typename std::enable_if<!TypeTraits<T>::isVector, void>::type
do_stuff(T& x, U* addr)
{
	x = vecCore::FromPtr<T>(addr);

}
*/
template<typename T>
void ConstructorTest_FromPtrToScalar()
{

	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
	if (count == 12)
		int a = 10;
	count++;

	size_t size = 0;


	std::string name(typeid(Vector_t).name());

	size = vecCore::VectorSize<Vector_t>(); 

	Scalar_t* tmp = new Scalar_t[size];
	Scalar_t *addr =&tmp[0];


	for (vecCore::UInt_s i = 0; i < size; i++) {
		tmp[i] = static_cast<Scalar_t>(i);
	}
	//vecCore::TypeTraits<Vector_t>::VectorType x;

//	do_stuff<Vector_t, Scalar_t>(x, addr);
	T x = vecCore::FromPtr<Vector_t>(addr);

	for (vecCore::UInt_s i = 0; i < vecCore::VectorSize<Vector_t>(); i++)
		EXPECT_TRUE(!vecCore::MaskEmpty(x == Vector_t(Scalar_t(i))));

	delete[]tmp;
	std::cout << "PASS" << std::endl;
}


///////////////////////////////////////////////////////////////////////////////

template<typename T> 
void ArithmeticsTest_Addition()
{
  using Scalar_t = TypeTraits<T>::ScalarType;
  using Vector_t = T;
  std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(1));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs + rhs)));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ArithmeticsTest_AdditionAssign()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(1));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  lhs += rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ArithmeticsTest_Subtraction()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(3));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs - rhs)));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ArithmeticsTest_SubtractionAssign()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(3));
  Vector_t rhs(static_cast<Scalar_t>(1));
  Vector_t res(static_cast<Scalar_t>(2));

  lhs -= rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ArithmeticsTest_Multiplication()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(2));
  Vector_t rhs(static_cast<Scalar_t>(2));
  Vector_t res(static_cast<Scalar_t>(4));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs * rhs)));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ArithmeticsTest_MultiplicationAssign()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(2));
  Vector_t rhs(static_cast<Scalar_t>(2));
  Vector_t res(static_cast<Scalar_t>(4));

  lhs *= rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ArithmeticsTest_Division()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(10));
  Vector_t rhs(static_cast<Scalar_t>(5));
  Vector_t res(static_cast<Scalar_t>(2));

  EXPECT_TRUE(vecCore::MaskFull(res == (lhs / rhs)));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void ArithmeticsTest_DivisionAssign()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t lhs(static_cast<Scalar_t>(10));
  Vector_t rhs(static_cast<Scalar_t>(5));
  Vector_t res(static_cast<Scalar_t>(2));

  lhs /= rhs;
  EXPECT_TRUE(vecCore::MaskFull(res == lhs));
  std::cout << "PASS" << std::endl;
}



template<typename T>
void MaskArithmeticsTest_AND()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) & Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) && Mask_t(true))));

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) & Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(true) && Mask_t(false))));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void MaskArithmeticsTest_OR()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) | Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) || Mask_t(true))));

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(false) | Mask_t(true))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) || Mask_t(false))));

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) | Mask_t(false))));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) || Mask_t(false))));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void MaskArithmeticsTest_NEG()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == !Mask_t(true)));
  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == !Mask_t(false)));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void MaskArithmeticsTest_ANDAssign()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Mask_t rhs(true);
  rhs &= Mask_t(false);

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(false) == rhs));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void MaskArithmeticsTest_ORAssign()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Mask_t rhs(false);
  rhs |= Mask_t(true);

  EXPECT_TRUE(vecCore::MaskFull(Mask_t(true) == rhs));
  std::cout << "PASS" << std::endl;
}


///////////////////////////////////////////////////////////////////////////////

template<typename T>
void VectorInterfaceTest_VectorSize()
{
  using Vector_t = T;
  std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  EXPECT_TRUE(vecCore::VectorSize<Vector_t>() > 0);
  std::cout << "PASS" << std::endl;
}

template<typename T>
void VectorInterfaceTest_VectorSizeVariable()
{
  using Vector_t = T;
  std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  Vector_t x;
  EXPECT_TRUE(vecCore::VectorSize(x) > 0);
  std::cout << "PASS" << std::endl;
}

template<typename T>
void VectorInterfaceTest_StoreToPtr()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
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
  std::cout << "PASS" << std::endl;
}

template<typename T>
void VectorInterfaceTest_StoreMaskToPtr()
{
  using Scalar_t = TypeTraits<T>::ScalarType; 
  using Vector_t = T;
  using Mask_t   = TypeTraits<T>::MaskType;
  std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
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
	//  Vector_t tmp; do_stuff<Vector_t, Scalar_t>(tmp,&input[i * kVS]);
    Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[i * kVS]));
    Mask_t m = tmp > Vector_t(1);
    vecCore::StoreMask(m, &output[i * kVS]);
  }

  for (vecCore::UInt_s i = 0; i < N; ++i)
  {
	//  std::cout << output[i] << " " << input[i] << " " << Scalar_t(1) << std::endl;
	  EXPECT_EQ(output[i], input[i] > Scalar_t(1));

  }
  std::cout << "PASS" << std::endl;
}

template<typename T>
void VectorInterfaceTest_VectorLaneRead()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;

	std::cout << __FUNCTION__ << "\t" << typeid(T).name() << "\t";
  const auto kVS = vecCore::VectorSize<Vector_t>();
  Scalar_t* input = new Scalar_t[kVS];

  for (vecCore::UInt_s i = 0; i < kVS; ++i) {
    input[i] = i;
  }

 Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[0]));
 // Vector_t tmp; do_stuff<Vector_t, Scalar_t>(tmp, &input[0]);

  for (vecCore::UInt_s i = 0; i < kVS; ++i)
    EXPECT_EQ(input[i], vecCore::LaneAt<Vector_t>(tmp, i));
  std::cout << "PASS" << std::endl;
}

template<typename T>
void VectorInterfaceTest_VectorLaneWrite()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;


  const auto kVS = vecCore::VectorSize<Vector_t>();
  Scalar_t* input = new Scalar_t[kVS];

  for (vecCore::UInt_s i = 0; i < kVS; ++i) {
    input[i] = i;
  }

  Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[0]));
 // Vector_t tmp; do_stuff<Vector_t, Scalar_t>(tmp, &input[0]);

  for (vecCore::UInt_s i = 0; i < kVS; ++i)
    vecCore::AssignLane(tmp, i, Scalar_t(10));

  for (vecCore::UInt_s i = 0; i < kVS; ++i)
    EXPECT_EQ(Scalar_t(10), vecCore::LaneAt<Vector_t>(tmp, i));
}

template<typename T>
void VectorInterfaceTest_MaskLaneRead()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;


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

template<typename T>
void VectorInterfaceTest_MaskLaneWrite()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;

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

template<typename T>
void VectorInterfaceTest_Gather()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
  using Index_v  = typename vecCore::Index_v<T>;
  using Index_t  = typename vecCore::ScalarType<T>::Type;

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

template<typename T>
void VectorInterfaceTest_Scatter()
{
  using Scalar_t = TypeTraits<T>::ScalarType;
  using Vector_t = T;
  using Index_v = typename vecCore::Index_v<T>;
  using Index_t = typename vecCore::ScalarType<Index_v>::Type;

  const auto  N = vecCore::VectorSize<Vector_t>();

  Index_t* index = new Index_t[N];
  Scalar_t* input = new Scalar_t[N];
  Scalar_t* output  = new Scalar_t[N];

  for (vecCore::UInt_s i = 0; i < N; ++i) {
    input[i] = i;
    index[i] = i;
  }

 Index_v idx(vecCore::FromPtr<Index_v>(&index[0]));
//  Index_v idx; do_stuff<Vector_t, Scalar_t>(idx, &input[0]);

  Vector_t  x = vecCore::FromPtr<Vector_t>(&input[0]);
 // Vector_t x; do_stuff<Vector_t, Scalar_t>(x, &input[0]);

  vecCore::Scatter<Vector_t>(x, &output[0], idx);

  Vector_t y = vecCore::FromPtr<Vector_t>(&output[0]);
  //Vector_t y; do_stuff<Vector_t, Scalar_t>(y, &input[0]);

  EXPECT_TRUE(vecCore::MaskFull(x == y));
}


///////////////////////////////////////////////////////////////////////////////


template<typename T>
void VectorMaskTest_Constructor()
{
  using Vector_t = T;

  EXPECT_TRUE(std::is_constructible<vecCore::Mask_v<Vector_t>>::value);
  EXPECT_TRUE(std::is_copy_constructible<vecCore::Mask_v<Vector_t>>::value);
  EXPECT_TRUE(std::is_move_constructible<vecCore::Mask_v<Vector_t>>::value);
}

template<typename T>
void VectorMaskTest_MaskFull()
{
  using Vector_t = T;

  vecCore::Mask_v<Vector_t> tmask(true), fmask(false);

  EXPECT_TRUE(vecCore::MaskFull(tmask));
  EXPECT_TRUE(vecCore::MaskFull(!fmask));
}

template<typename T>
void VectorMaskTest_MaskEmpty()
{
  using Vector_t = T;

  vecCore::Mask_v<Vector_t> tmask(true), fmask(false);

  EXPECT_TRUE(vecCore::MaskEmpty(fmask));
  EXPECT_TRUE(vecCore::MaskEmpty(!tmask));
}

template<typename T>
void VectorMaskTest_MaskAssign()
{
  using Vector_t = T;
  using Scalar_t = TypeTraits<T>::ScalarType;

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

template<typename T>
void VectorMaskTest_MaskAssign2()
{
	using Vector_t = T;
	using Scalar_t = TypeTraits<T>::ScalarType;

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

template<typename T>
void VectorMaskTest_Blend()
{
	using Vector_t = T;
	using Scalar_t = TypeTraits<T>::ScalarType;

  Vector_t a(Scalar_t(0)), b(1);

  a = vecCore::Blend(a > b, a, b);
}
template<typename T>
void RunTestOnType()
{
	ConstructorTest_Default<T>();
	ConstructorTest_Copy<T>();
	ConstructorTest_Move<T>();
	ConstructorTest_FromScalar<T>();
	ConstructorTest_FromRefToScalar<T>();
	ConstructorTest_FromPtrToScalar<T>();
	ArithmeticsTest_Addition<T>();
	ArithmeticsTest_AdditionAssign<T>();
	ArithmeticsTest_Subtraction<T>();
	ArithmeticsTest_SubtractionAssign<T>();
	ArithmeticsTest_Multiplication<T>();
	ArithmeticsTest_MultiplicationAssign<T>();
	ArithmeticsTest_Division<T>();
	ArithmeticsTest_DivisionAssign<T>();
	MaskArithmeticsTest_AND<T>();
	MaskArithmeticsTest_OR<T>();
	MaskArithmeticsTest_NEG<T>();
	MaskArithmeticsTest_ANDAssign<T>();
	MaskArithmeticsTest_ORAssign<T>();
	VectorInterfaceTest_VectorSize<T>();
	VectorInterfaceTest_VectorSizeVariable<T>();
	VectorInterfaceTest_StoreToPtr<T>();
	VectorInterfaceTest_StoreMaskToPtr<T>();
	VectorInterfaceTest_VectorLaneRead<T>();
	VectorInterfaceTest_VectorLaneWrite<T>();
	VectorInterfaceTest_MaskLaneRead<T>();
	VectorInterfaceTest_MaskLaneWrite<T>();
	VectorInterfaceTest_Gather<T>();
	VectorInterfaceTest_Scatter<T>();
	VectorMaskTest_Constructor<T>();
	VectorMaskTest_MaskFull<T>();
	VectorMaskTest_MaskEmpty<T>();
	VectorMaskTest_MaskAssign<T>();
	VectorMaskTest_MaskAssign2<T>();
	VectorMaskTest_Blend<T>();

}

template<typename Backend>
void runTestsVC()
{

	RunTestOnType<Backend::Real_v>();
	RunTestOnType<Backend::Float_v>();
	RunTestOnType<Backend::Double_v>();
	RunTestOnType<Backend::Int_v>();
	RunTestOnType<Backend::Int16_v>();
	RunTestOnType<Backend::Int32_v>();
	//RunTestOnType<Backend::Int64_v>(); // not allowed with current version of VC
	RunTestOnType<Backend::UInt_v>();
	RunTestOnType<Backend::UInt16_v>();
	RunTestOnType<Backend::UInt32_v>();
	//RunTestOnType<Backend::UInt64_v>(); // not allowed with current version of VC

}
template<typename Backend>
void runTests()
{

	RunTestOnType<Backend::Real_v>();
	RunTestOnType<Backend::Float_v>();
	RunTestOnType<Backend::Double_v>();
	RunTestOnType<Backend::Int_v>();
	RunTestOnType<Backend::Int16_v>();
	RunTestOnType<Backend::Int32_v>();
	RunTestOnType<Backend::Int64_v>();
	RunTestOnType<Backend::UInt_v>();
	RunTestOnType<Backend::UInt16_v>();
	RunTestOnType<Backend::UInt32_v>();
	RunTestOnType<Backend::UInt64_v>();

}
void runTestsPrimitives()
{

	RunTestOnType<float>();
	RunTestOnType<double>();
	RunTestOnType<int>();
	RunTestOnType<int16_t>();
	RunTestOnType<int32_t>();
	RunTestOnType<int64_t>();
	RunTestOnType<unsigned int>();
	RunTestOnType<uint16_t>();
	RunTestOnType<uint32_t>();
	RunTestOnType<uint64_t>();
}
int main(int argc, char *argv[])
{

#ifdef VECCORE_ENABLE_UMESIMD
	runTestsPrimitives();
	runTests<backend::UMESimd>();
	runTests<backend::UMESimdArray<1> >();
	runTests<backend::UMESimdArray<2> >();
	runTests<backend::UMESimdArray<4> >();
	runTests<backend::UMESimdArray<8> >();
	runTests<backend::UMESimdArray<16> >();
#else 
	runTests<backend::ScalarT<Real_s> >();
	runTests<backend::ScalarWrapperT<Real_s> >();
    runTestsVC<backend::VcScalarT<Real_s> >();
	runTestsVC<backend::VcSimdArray<1> >();
	runTestsVC<backend::VcSimdArray<2> >();
	runTestsVC<backend::VcSimdArray<4> >();
	runTestsVC<backend::VcSimdArray<8> >();
	runTestsVC<backend::VcSimdArray<16> >();
#endif

	return 0;
}
