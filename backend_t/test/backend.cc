
//#include <Windows.h>
#include <VecCore/VecCore.h>
#include <VecCore/Common.h>
#include "VecCore/base/Global.h"
#include <Vc/Vc>
#include <type_traits>
#include <typeinfo>
#include <string>
#include <algorithm>
#include <stdint.h>
#include <vector>
#include "printfInColor.h"

using namespace testing;
using namespace vecCore;


int massertInt(bool cond) {
	if (cond) return 0; else { ColoredPrintf(COLOR_RED, "|FAIL     | Assertion failed at %d %s  \n", __LINE__, __FILE__); return 1; }
}
int massertInt(bool cond, const char* function, std::string Type) {
	if (cond) return 0; else { ColoredPrintf(COLOR_RED, "|FAIL     | Assertion failed at %d %s  \n", __LINE__, __FILE__); return 1; }
}
int massertInt(bool cond, const char* function) {
	if (cond) return 0; else {
		ColoredPrintf(COLOR_RED, "|FAIL     | Assertion failed at %d %s  \n", __LINE__, __FILE__); return 1;	}
}

void massert(bool cond) {
	cond ? ColoredPrintf(COLOR_GREEN, "|     PASS| Type: %s\n", __FUNCTION__) 
	: ColoredPrintf(COLOR_RED, "|FAIL     | Assertion failed at %d %s  \n", __LINE__, __FILE__); }

void massert(bool cond, const char* function) {
	cond ? ColoredPrintf(COLOR_GREEN, "|     PASS| Type: %s\n", function)
	: ColoredPrintf(COLOR_RED, "|FAIL     | Assertion failed at %d %s  \n", __LINE__, __FILE__);
}

void massert(bool cond, const char* function, std::string Type) {
	cond ? ColoredPrintf(COLOR_GREEN, "|     PASS| Type: %s %s\n", Type.c_str(),function)
	: ColoredPrintf(COLOR_RED, "|FAIL     | Assertion failed at %d %s  \n", __LINE__, __FILE__);
}
///////////////////////////////////////////////////////////////////////////////

static int check = 0;
template<typename T>
int ConstructorTest_Default()
{

	using Vector_t = T;
	check = 0;
	check = massertInt((std::is_constructible<Vector_t>::value), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ConstructorTest_Copy()
{
	using Vector_t = T;
	check = 0;
	check = massertInt((std::is_copy_constructible<Vector_t>::value), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ConstructorTest_Move()
{
	using Vector_t = T;
	check = 0;
	check = massertInt((std::is_move_constructible<Vector_t>::value), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ConstructorTest_FromScalar()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	check = 0;
	check = massertInt((std::is_constructible<Vector_t, Scalar_t>::value), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ConstructorTest_FromRefToScalar()
{
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	check = 0;
	check = massertInt((std::is_constructible<Vector_t, const Scalar_t &>::value), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ConstructorTest_FromPtrToScalar()
{

	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	size_t size = vecCore::VectorSize<Vector_t>();

	Scalar_t* tmp = new Scalar_t[size];
	Scalar_t *addr =&tmp[0];


	for (vecCore::UInt_s i = 0; i < size; i++) {
		tmp[i] = static_cast<Scalar_t>(i);
	}

	T x = vecCore::FromPtr<Vector_t>(addr);

	for (vecCore::UInt_s i = 0; i < vecCore::VectorSize<Vector_t>(); i++)
	check += massertInt(!vecCore::MaskEmpty(x == Vector_t(Scalar_t(i))), __FUNCTION__, typeid(T).name());

	delete[]tmp;
	return check;
}


///////////////////////////////////////////////////////////////////////////////

template<typename T> 
int ArithmeticsTest_Addition()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(1));
	Vector_t rhs(static_cast<Scalar_t>(1));
	Vector_t res(static_cast<Scalar_t>(2));

	check = massertInt(vecCore::MaskFull(res == (lhs + rhs)), __FUNCTION__, typeid(T).name());
	return check;;
}

template<typename T>
int ArithmeticsTest_AdditionAssign()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(1));
	Vector_t rhs(static_cast<Scalar_t>(1));
	Vector_t res(static_cast<Scalar_t>(2));

	lhs += rhs;
	check = massertInt(vecCore::MaskFull(res == lhs), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ArithmeticsTest_Subtraction()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(3));
	Vector_t rhs(static_cast<Scalar_t>(1));
	Vector_t res(static_cast<Scalar_t>(2));

	check = massertInt(vecCore::MaskFull(res == (lhs - rhs)), __FUNCTION__, typeid(T).name());
	return check;
}
;
template<typename T>
int ArithmeticsTest_SubtractionAssign()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(3));
	Vector_t rhs(static_cast<Scalar_t>(1));
	Vector_t res(static_cast<Scalar_t>(2));

	lhs -= rhs;
	check = massertInt(vecCore::MaskFull(res == lhs), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ArithmeticsTest_Multiplication()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(2));
	Vector_t rhs(static_cast<Scalar_t>(2));
	Vector_t res(static_cast<Scalar_t>(4));

	check = massertInt(vecCore::MaskFull(res == (lhs * rhs)), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ArithmeticsTest_MultiplicationAssign()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(2));
	Vector_t rhs(static_cast<Scalar_t>(2));
	Vector_t res(static_cast<Scalar_t>(4));

	lhs *= rhs;
	check = massertInt(vecCore::MaskFull(res == lhs), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ArithmeticsTest_Division()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(10));
	Vector_t rhs(static_cast<Scalar_t>(5));
	Vector_t res(static_cast<Scalar_t>(2));

	check = massertInt(vecCore::MaskFull(res == (lhs / rhs)), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int ArithmeticsTest_DivisionAssign()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	Vector_t lhs(static_cast<Scalar_t>(10));
	Vector_t rhs(static_cast<Scalar_t>(5));
	Vector_t res(static_cast<Scalar_t>(2));

	lhs /= rhs;
	check = massertInt(vecCore::MaskFull(res == lhs), __FUNCTION__, typeid(T).name());
	return check;
}



template<typename T>
int MaskArithmeticsTest_AND()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	check += massertInt(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) & Mask_t(true))), __FUNCTION__, typeid(T).name());
	check += massertInt(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) && Mask_t(true))), __FUNCTION__, typeid(T).name());
	check += massertInt(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) & Mask_t(true))), __FUNCTION__, typeid(T).name());
	check += massertInt(vecCore::MaskFull(Mask_t(false) == (Mask_t(true) && Mask_t(false))), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int MaskArithmeticsTest_OR()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	check += massertInt(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) | Mask_t(true))), __FUNCTION__, typeid(T).name());
	check += massertInt(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) || Mask_t(true))), __FUNCTION__, typeid(T).name());

	check += massertInt(vecCore::MaskFull(Mask_t(true) == (Mask_t(false) | Mask_t(true))), __FUNCTION__, typeid(T).name());
	check += massertInt(vecCore::MaskFull(Mask_t(true) == (Mask_t(true) || Mask_t(false))), __FUNCTION__, typeid(T).name());

	check += massertInt(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) | Mask_t(false))), __FUNCTION__, typeid(T).name());
	check += massertInt(vecCore::MaskFull(Mask_t(false) == (Mask_t(false) || Mask_t(false))), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int MaskArithmeticsTest_NEG()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	check += massertInt(vecCore::MaskFull(Mask_t(false) == !Mask_t(true)), __FUNCTION__, typeid(T).name());
	check += massertInt(vecCore::MaskFull(Mask_t(true) == !Mask_t(false)), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int MaskArithmeticsTest_ANDAssign()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	Mask_t rhs(true);
	rhs &= Mask_t(false);

	check = massertInt(vecCore::MaskFull(Mask_t(false) == rhs), __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int MaskArithmeticsTest_ORAssign()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	using Mask_t = TypeTraits<T>::MaskType;
	Mask_t rhs(false);
	rhs |= Mask_t(true);

	check = massertInt(vecCore::MaskFull(Mask_t(true) == rhs), __FUNCTION__, typeid(T).name());
	return check;
}


///////////////////////////////////////////////////////////////////////////////

template<typename T>
int VectorInterfaceTest_VectorSize()
{
	check = 0;
	using Vector_t = T;
	check = massertInt(vecCore::VectorSize<Vector_t>() > 0, __FUNCTION__, typeid(T).name());
	return check;
}

template<typename T>
int VectorInterfaceTest_VectorSizeVariable()
{
	check = 0;
	using Vector_t = T;
	Vector_t x;
	check = massertInt(vecCore::VectorSize(x) > 0);
	return check;
}

template<typename T>
int VectorInterfaceTest_StoreToPtr()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
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
	check += massertInt(input[i] == output[i]);
	return check;
}

template<typename T>
int VectorInterfaceTest_StoreMaskToPtr()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType; 
	using Vector_t = T;
	using Mask_t   = TypeTraits<T>::MaskType;
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
		check += massertInt(output[i] == (input[i] > Scalar_t(1)));
	}
	return check;
}

template<typename T>
int VectorInterfaceTest_VectorLaneRead()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;
	const auto kVS = vecCore::VectorSize<Vector_t>();
	Scalar_t* input = new Scalar_t[kVS];

	for (vecCore::UInt_s i = 0; i < kVS; ++i) {
		input[i] = i;
	}

	Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[0]));

	for (vecCore::UInt_s i = 0; i < kVS; ++i)
	check += massertInt(input[i] == vecCore::LaneAt<Vector_t>(tmp, i));
	return check;
}

template<typename T>
int VectorInterfaceTest_VectorLaneWrite()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;


	const auto kVS = vecCore::VectorSize<Vector_t>();
	Scalar_t* input = new Scalar_t[kVS];

	for (vecCore::UInt_s i = 0; i < kVS; ++i) {
		input[i] = i;
	}

	Vector_t tmp(vecCore::FromPtr<Vector_t>(&input[0]));

	for (vecCore::UInt_s i = 0; i < kVS; ++i)
	vecCore::AssignLane(tmp, i, Scalar_t(10));

	for (vecCore::UInt_s i = 0; i < kVS; ++i)
	check += massertInt(Scalar_t(10) == vecCore::LaneAt<Vector_t>(tmp, i));

	return check;
}

template<typename T>
int VectorInterfaceTest_MaskLaneRead()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;


	vecCore::Mask_v<Vector_t> fmask(false), tmask(true), mmask;

	const auto kVS = vecCore::VectorSize<Vector_t>();

	Vector_t input;

	for (size_t i = 0; i < kVS; ++i)
	vecCore::AssignLane(input, i, (i % 2 == 0) ? Scalar_t(1) : Scalar_t(0));

	mmask = input > Vector_t(Scalar_t(0));

	for (size_t i = 0; i < kVS; ++i) {
		check += massertInt(vecCore::MaskLaneAt(tmask, i) == true);
		check += massertInt(vecCore::MaskLaneAt(fmask, i) == false);
		check += massertInt(vecCore::MaskLaneAt(mmask, i) ==( i % 2 == 0));
	}
	return check;
}

template<typename T>
int VectorInterfaceTest_MaskLaneWrite()
{
	check = 0;
	using Scalar_t = TypeTraits<T>::ScalarType;
	using Vector_t = T;

	vecCore::Mask_v<Vector_t> mask(false);

	const auto kVS = vecCore::VectorSize<Vector_t>();

	// check for all false

	for (size_t i = 0; i < kVS; ++i)
		check += massertInt(vecCore::MaskLaneAt(mask, i) == false);

	// check for all true

	for (size_t i = 0; i < kVS; ++i)
	vecCore::AssignMaskLane(mask, i, true);

	for (size_t i = 0; i < kVS; ++i)
		check += massertInt(vecCore::MaskLaneAt(mask, i) == true);

	// check for interleaving true/false

	for (size_t i = 0; i < kVS; ++i)
	vecCore::AssignMaskLane(mask, i, i % 2 == 0);

	for (size_t i = 0; i < kVS; ++i)
		check += massertInt (vecCore::MaskLaneAt(mask, i) == ( i % 2 == 0));

	return check;
}

template<typename T>
int VectorInterfaceTest_Gather()
{
	check = 0;
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
		check += massertInt(vecCore::LaneAt(x, j) == input[i * j]);
	}
	return check;
}

template<typename T>
int VectorInterfaceTest_Scatter()
{
	check = 0;
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
	Vector_t  x = vecCore::FromPtr<Vector_t>(&input[0]);
	vecCore::Scatter<Vector_t>(x, &output[0], idx);
	Vector_t y = vecCore::FromPtr<Vector_t>(&output[0]);

	check += massertInt(vecCore::MaskFull(x == y));

	return check;
}


///////////////////////////////////////////////////////////////////////////////


template<typename T>
int VectorMaskTest_Constructor()
{
	check = 0;
	using Vector_t = T;

	check += massertInt(std::is_constructible<vecCore::Mask_v<Vector_t>>::value);
	check += massertInt(std::is_copy_constructible<vecCore::Mask_v<Vector_t>>::value);
	check += massertInt(std::is_move_constructible<vecCore::Mask_v<Vector_t>>::value);
	return check;
}

template<typename T>
int VectorMaskTest_MaskFull()
{
	check = 0;
	using Vector_t = T;

	vecCore::Mask_v<Vector_t> tmask(true), fmask(false);

	check += massertInt(vecCore::MaskFull(tmask));
	check += massertInt(vecCore::MaskFull(!fmask));
	return check;
}

template<typename T>
int VectorMaskTest_MaskEmpty()
{
	check = 0;
	using Vector_t = T;
	vecCore::Mask_v<Vector_t> tmask(true), fmask(false);

	check += massertInt(vecCore::MaskEmpty(fmask));
	check += massertInt(vecCore::MaskEmpty(!tmask));
	return check;
}

template<typename T>
int VectorMaskTest_MaskAssign()
{
	check = 0;
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
	check += massertInt(vecCore::MaskFull(a == Vector_t(Scalar_t(0))));

	vecCore::MaskedAssign(a, b > a, b);
	check += massertInt(vecCore::MaskFull(a == b));
	return check;
}

template<typename T>
int VectorMaskTest_MaskAssign2()
{
	check = 0;
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
	check += massertInt(vecCore::LaneAt<Vector_t>(dest, i) == output[i]);
	return check;
}

template<typename T>
int VectorMaskTest_Blend()
{
	check = 0;
	using Vector_t = T;
	using Scalar_t = TypeTraits<T>::ScalarType;

	Vector_t a(Scalar_t(0)), b(1);

	a = vecCore::Blend(a > b, a, b);
	return check;

}


template<typename T>
void RunTestOnType()
{
	massert(ConstructorTest_Default<T>() == 0,"\tConstructorTest_Default\t", typeid(T).name());
	massert(ConstructorTest_Copy<T>() == 0, "\tConstructorTest_Copy\t", typeid(T).name());
	massert(ConstructorTest_Move<T>() == 0, "\tConstructorTest_Move\t", typeid(T).name());
	massert(ConstructorTest_FromScalar<T>() == 0, "\tConstructorTest_FromScalar\t", typeid(T).name());
	massert(ConstructorTest_FromRefToScalar<T>() == 0, "\tConstructorTest_FromRefToScalar\t", typeid(T).name());
	massert(ConstructorTest_FromPtrToScalar<T>() == 0, "\tConstructorTest_FromPtrToScalar\t", typeid(T).name());
	massert(ArithmeticsTest_Addition<T>() == 0, "\tArithmeticsTest_Addition\t", typeid(T).name());
	massert(ArithmeticsTest_AdditionAssign<T>() == 0, "\tArithmeticsTest_AdditionAssign\t", typeid(T).name()); 
	massert(ArithmeticsTest_Subtraction<T>() == 0, "\tArithmeticsTest_Subtraction\t", typeid(T).name()); 
	massert(ArithmeticsTest_SubtractionAssign<T>() == 0, "\tArithmeticsTestSubtractionAssign\t", typeid(T).name()); 
	massert(ArithmeticsTest_Multiplication<T>() == 0, "\tArithmeticsTest_Multiplication\t", typeid(T).name()); 
	massert(ArithmeticsTest_MultiplicationAssign<T>() == 0, "\tArithmeticsTest_MultiplicationAssign\t", typeid(T).name()); 
	massert(ArithmeticsTest_Division<T>() == 0, "\tArithmeticsTest_Division\t", typeid(T).name()); 
	massert(ArithmeticsTest_DivisionAssign<T>() == 0, "\tArithmeticsTest_DivisionAssign\t", typeid(T).name()); 
	massert(MaskArithmeticsTest_AND<T>() == 0, "\tMaskArithmeticsTest_AND\t", typeid(T).name()); 
	massert(MaskArithmeticsTest_OR<T>() == 0, "\tArithmeticsTest_OR\t", typeid(T).name()); 
	massert(MaskArithmeticsTest_NEG<T>() == 0, "\tArithmeticsTest_NEG\t", typeid(T).name()); 
	massert(MaskArithmeticsTest_ANDAssign<T>() == 0, "\tArithmeticsTest_ANDAssign\t", typeid(T).name()); 
	massert(MaskArithmeticsTest_ORAssign<T>() == 0, "\tArithmeticsTest_ORAssign\t", typeid(T).name()); 
	massert(VectorInterfaceTest_VectorSize<T>() == 0, "\tVectorInterfaceTest_VectorSize\t", typeid(T).name()); 
	massert(VectorInterfaceTest_VectorSizeVariable<T>() == 0, "\tVectorInterfaceTest_VectorSizeVariable\t", typeid(T).name()); 
	massert(VectorInterfaceTest_StoreToPtr<T>() == 0, "\tVectorInterfaceTest_StoreToPtr\t", typeid(T).name()); 
	massert(VectorInterfaceTest_StoreMaskToPtr<T>() == 0, "\tVectorInterfaceTest_StoreMaskToPtr\t", typeid(T).name()); 
	massert(VectorInterfaceTest_VectorLaneRead<T>() == 0, "\tVectorInterfaceTest_VectorLaneRead\t", typeid(T).name()); 
	massert(VectorInterfaceTest_VectorLaneWrite<T>() == 0, "\tVectorInterfaceTest_VectorLaneWrite\t", typeid(T).name()); 
	massert(VectorInterfaceTest_MaskLaneRead<T>() == 0, "\tVectorInterfaceTest_MaskLaneRead\t", typeid(T).name()); 
	massert(VectorInterfaceTest_MaskLaneWrite<T>() == 0, "\tVectorInterfaceTest_MaskLaneWrite\t", typeid(T).name()); 
	massert(VectorInterfaceTest_Gather<T>() == 0, "\tVectorInterfaceTest_Gather\t", typeid(T).name()); 
	massert(VectorInterfaceTest_Scatter<T>() == 0, "\tVectorInterfaceTest_Scatter\t", typeid(T).name()); 
	massert(VectorMaskTest_Constructor<T>() == 0, "\tVectorMaskTest_Constructor\t", typeid(T).name()); 
	massert(VectorMaskTest_MaskFull<T>() == 0, "\tVectorMaskTest_MaskFull\t", typeid(T).name()); 
	massert(VectorMaskTest_MaskEmpty<T>() == 0, "\tVectorMaskTest_MaskEmpty\t", typeid(T).name()); 
	massert(VectorMaskTest_MaskAssign<T>() == 0, "\tVectorMaskTest_MaskAssign\t", typeid(T).name()); 
	massert(VectorMaskTest_MaskAssign2<T>() == 0, "\tVectorMaskTest_MaskAssign2\t", typeid(T).name()); 
	massert(VectorMaskTest_Blend<T>() == 0, "\tVectorMaskTest_Blend\t", typeid(T).name()); 

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
