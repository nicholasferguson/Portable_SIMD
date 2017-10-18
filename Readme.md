#Introduction

	+ I abstracted code and added some code, in this project,
	 to test a  generic SIMD API, based on VecCore/VecGeom.  I made it Windows oriented.
	+ As a generic SIMD API, it allows C++ apps to switch from using SSEn to AVXn without any application code changes.  Switches are done with preprocessor macros, via config files, or hard coded.
	+ This generic API has code to use SIMD wrapper libraries of UMESIMD and VC 
	
#Questions to answer

* With metaprogramming, can an application:
	+ switch to a particular 3rd Party SIMD wrapper, with minimal re-coding.
	+ and with minimal recoding switch to a different SIMD: SSEn, AVXn

#Tested Windows build instructions

* Build using backend.cc as a default test application.
	+ To run test of an application using `VC SIMD wrapper library`
	+ 	build backend_t with Preprocessor Macro: `VECCORE_ENABLE_VC`
	+   Add as a Preprocessor Macro:  `__AVX__`
	+ 	All tests were OK.
	+ To run test of an application using `UMESIMD SIMD wrapper library`
	+ 	build backend_t with Preprocessor Macro: `VECCORE_ENABLE_UMESIMD`
	+   Add as a Preprocessor Macro:  `__AVX__`
	+ 	All tests were OK.	
	
#Library folder's structure

* `backend_t\VecCore\Backend` - This has logic to handle various SIMD wrapper libraries
* `backend_t\backends\umesimd` -  umesimd - SIMD wrapper library
* `backend_t\backends\vc` - 	VC - SIMD wrapper library
* `backend_t\test` - These files test generic SIMD API. Current tests include  AVX, AVX2, SSE2. 
* `backend_t\` - This has VC2015 solution file)



#Open Issues

	+ VecCore's test code in quadratic.cc has some _aligned_free of containers that
	  generate errors.  Need to review why.
	+ statistics from quadratic.cc are off... in order to compute a mean and sigma, too many time 
	  intervals are measured.  This impacts reported performance.  Need to redo.	
	  
#Updates

* `Nov 7 2016`
	+ Replaced gtest with some code.  gtest lib did not work well with UMESIMD. gtest obsfucated template parameter being passed around.
	
	+ Replaced gtest with two general macros in backtest.cc  massert and massertInt
	+ For windows, added file printfInColor.h to print out Pass/Fail with colors as gtest.	
	+ Added an if_enable around Get and Set in implementation.h
	+ Added to UMESIMD struct TypeTraits IsVector. ( see UMESimdCommon.h )  This works with if_enable.
	+ Added to UMESIMD struct TypeTraits tSize (UMESimdCommon.h and Scalar.h ). This  fixed VectorSize in implementation.h and deprecated.h 
		
#Links

VecGeom/VecCore
https://gitlab.cern.ch/VecGeom

umesimd has interfaces for	( Thanks to Cern's UMESIMD team )
https://github.com/edanor/umesimd
- SSE
- SSE2
- AVX
- AVX2
- AVX512 ( Xeon Phi )

Vc has interfaces for ( Thanks to VC team)
https://github.com/VcDevel/Vc
- SSE
- SSE2
- SSE3
- SSE4.1
- SSE4.2
- AVX
- AVX2
- AVX512 ( Xeon Phi ) (Many Integrated Core (MIC) )  

/////////Results of tests in backend.cc
|     PASS| Type: float         ConstructorTest_Default
|     PASS| Type: float         ConstructorTest_Copy
|     PASS| Type: float         ConstructorTest_Move
|     PASS| Type: float         ConstructorTest_FromScalar
|     PASS| Type: float         ConstructorTest_FromRefToScalar
|     PASS| Type: float         ConstructorTest_FromPtrToScalar
|     PASS| Type: float         ArithmeticsTest_Addition
|     PASS| Type: float         ArithmeticsTest_AdditionAssign
|     PASS| Type: float         ArithmeticsTest_Subtraction
|     PASS| Type: float         ArithmeticsTestSubtractionAssign
|     PASS| Type: float         ArithmeticsTest_Multiplication
|     PASS| Type: float         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: float         ArithmeticsTest_Division
|     PASS| Type: float         ArithmeticsTest_DivisionAssign
|     PASS| Type: float         MaskArithmeticsTest_AND
|     PASS| Type: float         ArithmeticsTest_OR
|     PASS| Type: float         ArithmeticsTest_NEG
|     PASS| Type: float         ArithmeticsTest_ANDAssign
|     PASS| Type: float         ArithmeticsTest_ORAssign
|     PASS| Type: float         VectorInterfaceTest_VectorSize
|     PASS| Type: float         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: float         VectorInterfaceTest_StoreToPtr
|     PASS| Type: float         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: float         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: float         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: float         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: float         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: float         VectorInterfaceTest_Gather
|     PASS| Type: float         VectorInterfaceTest_Scatter
|     PASS| Type: float         VectorMaskTest_Constructor
|     PASS| Type: float         VectorMaskTest_MaskFull
|     PASS| Type: float         VectorMaskTest_MaskEmpty
|     PASS| Type: float         VectorMaskTest_MaskAssign
|     PASS| Type: float         VectorMaskTest_MaskAssign2
|     PASS| Type: float         VectorMaskTest_Blend
|     PASS| Type: float         ConstructorTest_Default
|     PASS| Type: float         ConstructorTest_Copy
|     PASS| Type: float         ConstructorTest_Move
|     PASS| Type: float         ConstructorTest_FromScalar
|     PASS| Type: float         ConstructorTest_FromRefToScalar
|     PASS| Type: float         ConstructorTest_FromPtrToScalar
|     PASS| Type: float         ArithmeticsTest_Addition
|     PASS| Type: float         ArithmeticsTest_AdditionAssign
|     PASS| Type: float         ArithmeticsTest_Subtraction
|     PASS| Type: float         ArithmeticsTestSubtractionAssign
|     PASS| Type: float         ArithmeticsTest_Multiplication
|     PASS| Type: float         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: float         ArithmeticsTest_Division
|     PASS| Type: float         ArithmeticsTest_DivisionAssign
|     PASS| Type: float         MaskArithmeticsTest_AND
|     PASS| Type: float         ArithmeticsTest_OR
|     PASS| Type: float         ArithmeticsTest_NEG
|     PASS| Type: float         ArithmeticsTest_ANDAssign
|     PASS| Type: float         ArithmeticsTest_ORAssign
|     PASS| Type: float         VectorInterfaceTest_VectorSize
|     PASS| Type: float         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: float         VectorInterfaceTest_StoreToPtr
|     PASS| Type: float         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: float         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: float         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: float         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: float         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: float         VectorInterfaceTest_Gather
|     PASS| Type: float         VectorInterfaceTest_Scatter
|     PASS| Type: float         VectorMaskTest_Constructor
|     PASS| Type: float         VectorMaskTest_MaskFull
|     PASS| Type: float         VectorMaskTest_MaskEmpty
|     PASS| Type: float         VectorMaskTest_MaskAssign
|     PASS| Type: float         VectorMaskTest_MaskAssign2
|     PASS| Type: float         VectorMaskTest_Blend
|     PASS| Type: double        ConstructorTest_Default
|     PASS| Type: double        ConstructorTest_Copy
|     PASS| Type: double        ConstructorTest_Move
|     PASS| Type: double        ConstructorTest_FromScalar
|     PASS| Type: double        ConstructorTest_FromRefToScalar
|     PASS| Type: double        ConstructorTest_FromPtrToScalar
|     PASS| Type: double        ArithmeticsTest_Addition
|     PASS| Type: double        ArithmeticsTest_AdditionAssign
|     PASS| Type: double        ArithmeticsTest_Subtraction
|     PASS| Type: double        ArithmeticsTestSubtractionAssign
|     PASS| Type: double        ArithmeticsTest_Multiplication
|     PASS| Type: double        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: double        ArithmeticsTest_Division
|     PASS| Type: double        ArithmeticsTest_DivisionAssign
|     PASS| Type: double        MaskArithmeticsTest_AND
|     PASS| Type: double        ArithmeticsTest_OR
|     PASS| Type: double        ArithmeticsTest_NEG
|     PASS| Type: double        ArithmeticsTest_ANDAssign
|     PASS| Type: double        ArithmeticsTest_ORAssign
|     PASS| Type: double        VectorInterfaceTest_VectorSize
|     PASS| Type: double        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: double        VectorInterfaceTest_StoreToPtr
|     PASS| Type: double        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: double        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: double        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: double        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: double        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: double        VectorInterfaceTest_Gather
|     PASS| Type: double        VectorInterfaceTest_Scatter
|     PASS| Type: double        VectorMaskTest_Constructor
|     PASS| Type: double        VectorMaskTest_MaskFull
|     PASS| Type: double        VectorMaskTest_MaskEmpty
|     PASS| Type: double        VectorMaskTest_MaskAssign
|     PASS| Type: double        VectorMaskTest_MaskAssign2
|     PASS| Type: double        VectorMaskTest_Blend
|     PASS| Type: int   ConstructorTest_Default
|     PASS| Type: int   ConstructorTest_Copy
|     PASS| Type: int   ConstructorTest_Move
|     PASS| Type: int   ConstructorTest_FromScalar
|     PASS| Type: int   ConstructorTest_FromRefToScalar
|     PASS| Type: int   ConstructorTest_FromPtrToScalar
|     PASS| Type: int   ArithmeticsTest_Addition
|     PASS| Type: int   ArithmeticsTest_AdditionAssign
|     PASS| Type: int   ArithmeticsTest_Subtraction
|     PASS| Type: int   ArithmeticsTestSubtractionAssign
|     PASS| Type: int   ArithmeticsTest_Multiplication
|     PASS| Type: int   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: int   ArithmeticsTest_Division
|     PASS| Type: int   ArithmeticsTest_DivisionAssign
|     PASS| Type: int   MaskArithmeticsTest_AND
|     PASS| Type: int   ArithmeticsTest_OR
|     PASS| Type: int   ArithmeticsTest_NEG
|     PASS| Type: int   ArithmeticsTest_ANDAssign
|     PASS| Type: int   ArithmeticsTest_ORAssign
|     PASS| Type: int   VectorInterfaceTest_VectorSize
|     PASS| Type: int   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: int   VectorInterfaceTest_StoreToPtr
|     PASS| Type: int   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: int   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: int   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: int   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: int   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: int   VectorInterfaceTest_Gather
|     PASS| Type: int   VectorInterfaceTest_Scatter
|     PASS| Type: int   VectorMaskTest_Constructor
|     PASS| Type: int   VectorMaskTest_MaskFull
|     PASS| Type: int   VectorMaskTest_MaskEmpty
|     PASS| Type: int   VectorMaskTest_MaskAssign
|     PASS| Type: int   VectorMaskTest_MaskAssign2
|     PASS| Type: int   VectorMaskTest_Blend
|     PASS| Type: short         ConstructorTest_Default
|     PASS| Type: short         ConstructorTest_Copy
|     PASS| Type: short         ConstructorTest_Move
|     PASS| Type: short         ConstructorTest_FromScalar
|     PASS| Type: short         ConstructorTest_FromRefToScalar
|     PASS| Type: short         ConstructorTest_FromPtrToScalar
|     PASS| Type: short         ArithmeticsTest_Addition
|     PASS| Type: short         ArithmeticsTest_AdditionAssign
|     PASS| Type: short         ArithmeticsTest_Subtraction
|     PASS| Type: short         ArithmeticsTestSubtractionAssign
|     PASS| Type: short         ArithmeticsTest_Multiplication
|     PASS| Type: short         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: short         ArithmeticsTest_Division
|     PASS| Type: short         ArithmeticsTest_DivisionAssign
|     PASS| Type: short         MaskArithmeticsTest_AND
|     PASS| Type: short         ArithmeticsTest_OR
|     PASS| Type: short         ArithmeticsTest_NEG
|     PASS| Type: short         ArithmeticsTest_ANDAssign
|     PASS| Type: short         ArithmeticsTest_ORAssign
|     PASS| Type: short         VectorInterfaceTest_VectorSize
|     PASS| Type: short         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: short         VectorInterfaceTest_StoreToPtr
|     PASS| Type: short         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: short         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: short         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: short         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: short         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: short         VectorInterfaceTest_Gather
|     PASS| Type: short         VectorInterfaceTest_Scatter
|     PASS| Type: short         VectorMaskTest_Constructor
|     PASS| Type: short         VectorMaskTest_MaskFull
|     PASS| Type: short         VectorMaskTest_MaskEmpty
|     PASS| Type: short         VectorMaskTest_MaskAssign
|     PASS| Type: short         VectorMaskTest_MaskAssign2
|     PASS| Type: short         VectorMaskTest_Blend
|     PASS| Type: int   ConstructorTest_Default
|     PASS| Type: int   ConstructorTest_Copy
|     PASS| Type: int   ConstructorTest_Move
|     PASS| Type: int   ConstructorTest_FromScalar
|     PASS| Type: int   ConstructorTest_FromRefToScalar
|     PASS| Type: int   ConstructorTest_FromPtrToScalar
|     PASS| Type: int   ArithmeticsTest_Addition
|     PASS| Type: int   ArithmeticsTest_AdditionAssign
|     PASS| Type: int   ArithmeticsTest_Subtraction
|     PASS| Type: int   ArithmeticsTestSubtractionAssign
|     PASS| Type: int   ArithmeticsTest_Multiplication
|     PASS| Type: int   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: int   ArithmeticsTest_Division
|     PASS| Type: int   ArithmeticsTest_DivisionAssign
|     PASS| Type: int   MaskArithmeticsTest_AND
|     PASS| Type: int   ArithmeticsTest_OR
|     PASS| Type: int   ArithmeticsTest_NEG
|     PASS| Type: int   ArithmeticsTest_ANDAssign
|     PASS| Type: int   ArithmeticsTest_ORAssign
|     PASS| Type: int   VectorInterfaceTest_VectorSize
|     PASS| Type: int   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: int   VectorInterfaceTest_StoreToPtr
|     PASS| Type: int   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: int   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: int   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: int   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: int   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: int   VectorInterfaceTest_Gather
|     PASS| Type: int   VectorInterfaceTest_Scatter
|     PASS| Type: int   VectorMaskTest_Constructor
|     PASS| Type: int   VectorMaskTest_MaskFull
|     PASS| Type: int   VectorMaskTest_MaskEmpty
|     PASS| Type: int   VectorMaskTest_MaskAssign
|     PASS| Type: int   VectorMaskTest_MaskAssign2
|     PASS| Type: int   VectorMaskTest_Blend
|     PASS| Type: __int64       ConstructorTest_Default
|     PASS| Type: __int64       ConstructorTest_Copy
|     PASS| Type: __int64       ConstructorTest_Move
|     PASS| Type: __int64       ConstructorTest_FromScalar
|     PASS| Type: __int64       ConstructorTest_FromRefToScalar
|     PASS| Type: __int64       ConstructorTest_FromPtrToScalar
|     PASS| Type: __int64       ArithmeticsTest_Addition
|     PASS| Type: __int64       ArithmeticsTest_AdditionAssign
|     PASS| Type: __int64       ArithmeticsTest_Subtraction
|     PASS| Type: __int64       ArithmeticsTestSubtractionAssign
|     PASS| Type: __int64       ArithmeticsTest_Multiplication
|     PASS| Type: __int64       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: __int64       ArithmeticsTest_Division
|     PASS| Type: __int64       ArithmeticsTest_DivisionAssign
|     PASS| Type: __int64       MaskArithmeticsTest_AND
|     PASS| Type: __int64       ArithmeticsTest_OR
|     PASS| Type: __int64       ArithmeticsTest_NEG
|     PASS| Type: __int64       ArithmeticsTest_ANDAssign
|     PASS| Type: __int64       ArithmeticsTest_ORAssign
|     PASS| Type: __int64       VectorInterfaceTest_VectorSize
|     PASS| Type: __int64       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: __int64       VectorInterfaceTest_StoreToPtr
|     PASS| Type: __int64       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: __int64       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: __int64       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: __int64       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: __int64       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: __int64       VectorInterfaceTest_Gather
|     PASS| Type: __int64       VectorInterfaceTest_Scatter
|     PASS| Type: __int64       VectorMaskTest_Constructor
|     PASS| Type: __int64       VectorMaskTest_MaskFull
|     PASS| Type: __int64       VectorMaskTest_MaskEmpty
|     PASS| Type: __int64       VectorMaskTest_MaskAssign
|     PASS| Type: __int64       VectorMaskTest_MaskAssign2
|     PASS| Type: __int64       VectorMaskTest_Blend
|     PASS| Type: unsigned int  ConstructorTest_Default
|     PASS| Type: unsigned int  ConstructorTest_Copy
|     PASS| Type: unsigned int  ConstructorTest_Move
|     PASS| Type: unsigned int  ConstructorTest_FromScalar
|     PASS| Type: unsigned int  ConstructorTest_FromRefToScalar
|     PASS| Type: unsigned int  ConstructorTest_FromPtrToScalar
|     PASS| Type: unsigned int  ArithmeticsTest_Addition
|     PASS| Type: unsigned int  ArithmeticsTest_AdditionAssign
|     PASS| Type: unsigned int  ArithmeticsTest_Subtraction
|     PASS| Type: unsigned int  ArithmeticsTestSubtractionAssign
|     PASS| Type: unsigned int  ArithmeticsTest_Multiplication
|     PASS| Type: unsigned int  ArithmeticsTest_MultiplicationAssign
|     PASS| Type: unsigned int  ArithmeticsTest_Division
|     PASS| Type: unsigned int  ArithmeticsTest_DivisionAssign
|     PASS| Type: unsigned int  MaskArithmeticsTest_AND
|     PASS| Type: unsigned int  ArithmeticsTest_OR
|     PASS| Type: unsigned int  ArithmeticsTest_NEG
|     PASS| Type: unsigned int  ArithmeticsTest_ANDAssign
|     PASS| Type: unsigned int  ArithmeticsTest_ORAssign
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorSize
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: unsigned int  VectorInterfaceTest_StoreToPtr
|     PASS| Type: unsigned int  VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorLaneRead
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: unsigned int  VectorInterfaceTest_MaskLaneRead
|     PASS| Type: unsigned int  VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: unsigned int  VectorInterfaceTest_Gather
|     PASS| Type: unsigned int  VectorInterfaceTest_Scatter
|     PASS| Type: unsigned int  VectorMaskTest_Constructor
|     PASS| Type: unsigned int  VectorMaskTest_MaskFull
|     PASS| Type: unsigned int  VectorMaskTest_MaskEmpty
|     PASS| Type: unsigned int  VectorMaskTest_MaskAssign
|     PASS| Type: unsigned int  VectorMaskTest_MaskAssign2
|     PASS| Type: unsigned int  VectorMaskTest_Blend
|     PASS| Type: unsigned short        ConstructorTest_Default
|     PASS| Type: unsigned short        ConstructorTest_Copy
|     PASS| Type: unsigned short        ConstructorTest_Move
|     PASS| Type: unsigned short        ConstructorTest_FromScalar
|     PASS| Type: unsigned short        ConstructorTest_FromRefToScalar
|     PASS| Type: unsigned short        ConstructorTest_FromPtrToScalar
|     PASS| Type: unsigned short        ArithmeticsTest_Addition
|     PASS| Type: unsigned short        ArithmeticsTest_AdditionAssign
|     PASS| Type: unsigned short        ArithmeticsTest_Subtraction
|     PASS| Type: unsigned short        ArithmeticsTestSubtractionAssign
|     PASS| Type: unsigned short        ArithmeticsTest_Multiplication
|     PASS| Type: unsigned short        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: unsigned short        ArithmeticsTest_Division
|     PASS| Type: unsigned short        ArithmeticsTest_DivisionAssign
|     PASS| Type: unsigned short        MaskArithmeticsTest_AND
|     PASS| Type: unsigned short        ArithmeticsTest_OR
|     PASS| Type: unsigned short        ArithmeticsTest_NEG
|     PASS| Type: unsigned short        ArithmeticsTest_ANDAssign
|     PASS| Type: unsigned short        ArithmeticsTest_ORAssign
|     PASS| Type: unsigned short        VectorInterfaceTest_VectorSize
|     PASS| Type: unsigned short        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: unsigned short        VectorInterfaceTest_StoreToPtr
|     PASS| Type: unsigned short        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: unsigned short        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: unsigned short        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: unsigned short        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: unsigned short        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: unsigned short        VectorInterfaceTest_Gather
|     PASS| Type: unsigned short        VectorInterfaceTest_Scatter
|     PASS| Type: unsigned short        VectorMaskTest_Constructor
|     PASS| Type: unsigned short        VectorMaskTest_MaskFull
|     PASS| Type: unsigned short        VectorMaskTest_MaskEmpty
|     PASS| Type: unsigned short        VectorMaskTest_MaskAssign
|     PASS| Type: unsigned short        VectorMaskTest_MaskAssign2
|     PASS| Type: unsigned short        VectorMaskTest_Blend
|     PASS| Type: unsigned int  ConstructorTest_Default
|     PASS| Type: unsigned int  ConstructorTest_Copy
|     PASS| Type: unsigned int  ConstructorTest_Move
|     PASS| Type: unsigned int  ConstructorTest_FromScalar
|     PASS| Type: unsigned int  ConstructorTest_FromRefToScalar
|     PASS| Type: unsigned int  ConstructorTest_FromPtrToScalar
|     PASS| Type: unsigned int  ArithmeticsTest_Addition
|     PASS| Type: unsigned int  ArithmeticsTest_AdditionAssign
|     PASS| Type: unsigned int  ArithmeticsTest_Subtraction
|     PASS| Type: unsigned int  ArithmeticsTestSubtractionAssign
|     PASS| Type: unsigned int  ArithmeticsTest_Multiplication
|     PASS| Type: unsigned int  ArithmeticsTest_MultiplicationAssign
|     PASS| Type: unsigned int  ArithmeticsTest_Division
|     PASS| Type: unsigned int  ArithmeticsTest_DivisionAssign
|     PASS| Type: unsigned int  MaskArithmeticsTest_AND
|     PASS| Type: unsigned int  ArithmeticsTest_OR
|     PASS| Type: unsigned int  ArithmeticsTest_NEG
|     PASS| Type: unsigned int  ArithmeticsTest_ANDAssign
|     PASS| Type: unsigned int  ArithmeticsTest_ORAssign
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorSize
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: unsigned int  VectorInterfaceTest_StoreToPtr
|     PASS| Type: unsigned int  VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorLaneRead
|     PASS| Type: unsigned int  VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: unsigned int  VectorInterfaceTest_MaskLaneRead
|     PASS| Type: unsigned int  VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: unsigned int  VectorInterfaceTest_Gather
|     PASS| Type: unsigned int  VectorInterfaceTest_Scatter
|     PASS| Type: unsigned int  VectorMaskTest_Constructor
|     PASS| Type: unsigned int  VectorMaskTest_MaskFull
|     PASS| Type: unsigned int  VectorMaskTest_MaskEmpty
|     PASS| Type: unsigned int  VectorMaskTest_MaskAssign
|     PASS| Type: unsigned int  VectorMaskTest_MaskAssign2
|     PASS| Type: unsigned int  VectorMaskTest_Blend
|     PASS| Type: unsigned __int64      ConstructorTest_Default
|     PASS| Type: unsigned __int64      ConstructorTest_Copy
|     PASS| Type: unsigned __int64      ConstructorTest_Move
|     PASS| Type: unsigned __int64      ConstructorTest_FromScalar
|     PASS| Type: unsigned __int64      ConstructorTest_FromRefToScalar
|     PASS| Type: unsigned __int64      ConstructorTest_FromPtrToScalar
|     PASS| Type: unsigned __int64      ArithmeticsTest_Addition
|     PASS| Type: unsigned __int64      ArithmeticsTest_AdditionAssign
|     PASS| Type: unsigned __int64      ArithmeticsTest_Subtraction
|     PASS| Type: unsigned __int64      ArithmeticsTestSubtractionAssign
|     PASS| Type: unsigned __int64      ArithmeticsTest_Multiplication
|     PASS| Type: unsigned __int64      ArithmeticsTest_MultiplicationAssign
|     PASS| Type: unsigned __int64      ArithmeticsTest_Division
|     PASS| Type: unsigned __int64      ArithmeticsTest_DivisionAssign
|     PASS| Type: unsigned __int64      MaskArithmeticsTest_AND
|     PASS| Type: unsigned __int64      ArithmeticsTest_OR
|     PASS| Type: unsigned __int64      ArithmeticsTest_NEG
|     PASS| Type: unsigned __int64      ArithmeticsTest_ANDAssign
|     PASS| Type: unsigned __int64      ArithmeticsTest_ORAssign
|     PASS| Type: unsigned __int64      VectorInterfaceTest_VectorSize
|     PASS| Type: unsigned __int64      VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: unsigned __int64      VectorInterfaceTest_StoreToPtr
|     PASS| Type: unsigned __int64      VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: unsigned __int64      VectorInterfaceTest_VectorLaneRead
|     PASS| Type: unsigned __int64      VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: unsigned __int64      VectorInterfaceTest_MaskLaneRead
|     PASS| Type: unsigned __int64      VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: unsigned __int64      VectorInterfaceTest_Gather
|     PASS| Type: unsigned __int64      VectorInterfaceTest_Scatter
|     PASS| Type: unsigned __int64      VectorMaskTest_Constructor
|     PASS| Type: unsigned __int64      VectorMaskTest_MaskFull
|     PASS| Type: unsigned __int64      VectorMaskTest_MaskEmpty
|     PASS| Type: unsigned __int64      VectorMaskTest_MaskAssign
|     PASS| Type: unsigned __int64      VectorMaskTest_MaskAssign2
|     PASS| Type: unsigned __int64      VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<float>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<float>   VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<double>  ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<double>  ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<double>  ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<double>  ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<double>  ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<double>  ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<double>  MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<double>  ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<double>  VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<short>   ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<short>   ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<short>   ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<short>   ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<short>   ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<short>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<short>   MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<short>   ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<short>   VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<int>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<int>     VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<__int64>         MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<__int64>         ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<__int64>         VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<unsigned short>  VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<unsigned int>    VectorMaskTest_Blend
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ConstructorTest_Default
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ConstructorTest_Copy
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ConstructorTest_Move
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ConstructorTest_FromScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ConstructorTest_FromRefToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_Addition
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_Subtraction
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTestSubtractionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_Multiplication
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_Division
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        MaskArithmeticsTest_AND
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_OR
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_NEG
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_ANDAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        ArithmeticsTest_ORAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_VectorSize
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_Gather
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorInterfaceTest_Scatter
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorMaskTest_Constructor
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorMaskTest_MaskFull
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorMaskTest_MaskEmpty
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorMaskTest_MaskAssign
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorMaskTest_MaskAssign2
|     PASS| Type: class vecCore::WrappedScalar<unsigned __int64>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTestSubtractionAssign

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_MultiplicationAssign

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Division
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorSizeVariable

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_StoreMaskToPtr

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorLaneRead

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorLaneWrite

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_MaskLaneRead

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_MaskLaneWrite

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTestSubtractionAssign

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_MultiplicationAssign

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Division
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorSizeVariable

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_StoreMaskToPtr

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorLaneRead

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorLaneWrite

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_MaskLaneRead

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_MaskLaneWrite

|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTestSubtractionAssign

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_MultiplicationAssign

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorSizeVariable

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_StoreMaskToPtr

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorLaneRead

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorLaneWrite

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_MaskLaneRead

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_MaskLaneWrite

|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTestSubtractionAssign

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_MultiplicationAssign

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Division
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorSizeVariable

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_StoreMaskToPtr

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorLaneRead

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorLaneWrite

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_MaskLaneRead

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_MaskLaneWrite

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTestSubtractionAssign

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_MultiplicationAssign

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_Division
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorSizeVariable

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_StoreMaskToPtr

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorLaneRead

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_VectorLaneWrite

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_MaskLaneRead

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_MaskLaneWrite

|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>      VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTestSubtractionAssign

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_MultiplicationAssign

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_Division
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorSizeVariable

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_StoreMaskToPtr

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorLaneRead

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_VectorLaneWrite

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_MaskLaneRead

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_MaskLaneWrite

|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_FromScalar

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_FromRefToScalar

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_FromPtrToScalar

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Addition

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_AdditionAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Subtraction

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Multiplication

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Division

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_DivisionAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_ANDAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_ORAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorSize

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_StoreToPtr

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_Gather

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_Scatter

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_Constructor

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskEmpty

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskAssign2

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_FromScalar

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_FromRefToScalar

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ConstructorTest_FromPtrToScalar

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Addition

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_AdditionAssign

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Subtraction

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Multiplication

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_Division

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_DivisionAssign

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_ANDAssign

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     ArithmeticsTest_ORAssign

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorSize

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_StoreToPtr

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_Gather

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorInterfaceTest_Scatter

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_Constructor

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskEmpty

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskAssign

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_MaskAssign2

|     PASS| Type: class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_Default
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_Move
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_FromScalar

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_FromRefToScalar

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ConstructorTest_FromPtrToScalar

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Addition

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_AdditionAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Subtraction

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Multiplication

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_Division

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_DivisionAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_ANDAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       ArithmeticsTest_ORAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorSize

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_StoreToPtr

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_Gather

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorInterfaceTest_Scatter

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_Constructor

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskEmpty

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskAssign

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_MaskAssign2

|     PASS| Type: class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,1,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<double,1,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<short,1,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,1,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned short,1,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,1,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,2,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<double,2,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Sse>,2>      VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<short,2,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,2,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Scalar>,1>         VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned short,2,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,2,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Scalar>,1>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,4,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Sse>,4>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<double,4,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<short,4,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Scalar>,1>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,4,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned short,4,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Scalar>,1>   VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,4,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,8,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<double,8,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>      VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<short,8,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>        VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,8,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>    VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned short,8,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>      VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,8,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>
VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<float,16,class Vc_1::Vector<float,struct Vc_1::VectorAbi::Avx>,8>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<double,16,class Vc_1::Vector<double,struct Vc_1::VectorAbi::Avx>,4>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<short,16,class Vc_1::Vector<short,struct Vc_1::VectorAbi::Sse>,8>       VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<int,16,class Vc_1::Vector<int,struct Vc_1::VectorAbi::Sse>,4>   VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned short,16,class Vc_1::Vector<unsigned short,struct Vc_1::VectorAbi::Sse>,8>     VectorMaskTest_Blend
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_Default
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_Copy
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_Move
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_FromScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_FromRefToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ConstructorTest_FromPtrToScalar
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Addition
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_AdditionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Subtraction
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTestSubtractionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Multiplication
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_MultiplicationAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_Division
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_DivisionAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         MaskArithmeticsTest_AND
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_OR
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_NEG
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_ANDAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         ArithmeticsTest_ORAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorSize
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorSizeVariable
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_StoreToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_StoreMaskToPtr
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_VectorLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_MaskLaneRead
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_MaskLaneWrite
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_Gather
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorInterfaceTest_Scatter
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_Constructor
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskFull
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskEmpty
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskAssign
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_MaskAssign2
|     PASS| Type: class Vc_1::SimdArray<unsigned int,16,class Vc_1::Vector<unsigned int,struct Vc_1::VectorAbi::Sse>,4>         VectorMaskTest_Blend
