#Introduction

	+ I abstracted code and added some code, in this project,
	 to test a  generic SIMD API, based on VecCore/VecGeom.  I made it Windows oriented.
	+ As a generic SIMD API, it allows C++ apps to switch from using SSEn to AVXn without any application code changes.  Switches are done with preprocessor macros.
	+ This generic API has code to use SIMD wrapper libraries of UMSIMD and VC 
	
#Questions to answer

* With metaprogramming, can an application:
	+ switch to a particular SIMD wrapper, with minimal re-coding.
	+ and use 3rd Party SIMD wrapper libraries.

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
* `backend_t\test` - These files test generic SIMD API. Current tests inlude  AVX, AVX2, SSE2. 
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

