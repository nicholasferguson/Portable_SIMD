=====================================================
2016.9.16 
	+ Built all code under Windows 10, with Visual Studio 2015, x64
	
	+ This project is to test a SIMD type API, based on VecCore/VecGeom, that could allow switching 
	 SIMD wrappers, such as UMESIMD or VC. In this test, I reorganized code.
	+ VecGeom developed VecCore as an SIMD type API to be able to switch an app from using UMESIMD to using VC.  
	
	Questions to answer
	+ With metaprogramming, can an application switch to a particular SIMD wrapper, with minimal re-coding, 

	Issues
	+ VecCore's test code in backend.cc  is broken in its metaprogrammnig.  It resorts to copying 
	  into simd containers, using pointers. ( And though it works with VC, it is broken with UMESIMD).
	
	+ VecCore's test code in quadratic.cc is a better test.  But some _aligned_free of containers 
	  generate errors.  Need to review why.
	+ statistics from quadratic.cc are off... in order to compute a mean and sigma, too many time 
	  intervals are measured.  This impacts reported performance.

	+ To run test with VC
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_VC
	+ 	All tests were OK.
	+ To run test with UMESIMD
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_UMESIMD
	+ 	issue with test using UME::SIMD::SIMDVec.  Container sizing is incorrect.  (fixed)	
		Working on a resolution.
	
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
