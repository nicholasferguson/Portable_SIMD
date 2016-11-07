=====================================================
Updated Nov 7 2016
	Replaced gtest with some code.  gtest lib did not work well with UMESIMD. gtest obsfucated template parameter being passed around.
	
	Replaced gtest with two general macros in backtest.cc  massert and massertInt
	For windows, added file printfInColor.h to print out Pass/Fail with colors as gtest.
=====================================================
	+ Built all code under Windows 10, with Visual Studio 2015, x64
	 Dependencies:
	  gtest 1.7.0 <==== removed....11/7/2016
	  
	  Current tests were for SIMD's AVX, AVX2, SSE2 only.
	
	+ This project is to test a SIMD type API, based on VecCore/VecGeom, that could allow switching 
	 SIMD wrappers, such as UMESIMD or VC. In this test, I reorganized code.
	+ VecGeom developed VecCore as an SIMD type API to be able to switch an app from using UMESIMD to using VC.  
	
	Questions to answer
	+ With metaprogramming, can an application switch to a particular SIMD wrapper, with minimal re-coding, 

	Issues Resolved
	+ Re-coded VecCore's backend.cc test file.  Removed much of gtest.  Now all tests run OK for both VC and UMESIMD.
	  Tests were running for VC but failing for UMESIMD.  I made code changes to that tests were also ok with UMESIMD.
	
	    + Added an if_enable around Get and Set in implementation.h
		+ Added to UMESIMD struct TypeTraits IsVector. ( see UMESimdCommon.h )  This works with if_enable.
		+ Added to UMESIMD struct TypeTraits tSize (UMESimdCommon.h and Scalar.h ). This  fixed VectorSize in implementation.h and deprecated.h 
		
	Issues Open
	+ VecCore's test code in quadratic.cc has some _aligned_free of containers that
	  generate errors.  Need to review why.
	+ statistics from quadratic.cc are off... in order to compute a mean and sigma, too many time 
	  intervals are measured.  This impacts reported performance.  Need to redo.

	+ To run test with VC
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_VC
	+ 	All tests were OK.
	+ To run test with UMESIMD
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_UMESIMD
	+ 	All tests were OK.
	
=====================================================

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

