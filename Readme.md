=====================================================
2016.9.16 
	+ Built all code under Windows 10, with Visual Studio 2015, x64
	
	+ This project is to test a SIMD type API, based on VecCore/VecGeom, that could allow switching SIMD wrappers, such as UMESIMD or VC. In this test, I reorganized code.
	
	Questions to answer
	+ With metaprogramming, can an application switch to a particular SIMD backend, without any recoding, 
	+ Can only one backend + SIMD selection can be configured at compile time:  Example UMSIMD + AVX2  or VC + AVX2

	Issues
	+ backend.cc from VecCore is broken in its metaprogrammnig.  It resorts to copying into simd containers, using pointers. ( And though it works with VC, it is broken with UMESIMD)
	+ quadratic.cc is a better test.  But some _aligned_free of containers generate errors.  Need to review why.
	+ To run test with VC
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_VC
	+ 	All tests were OK.
	+ To run test with UMESIMD
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_UMESIMD
	+ 	issue with test using UME::SIMD::SIMDVec.  Container sizing is incorrect.  (fixed)	
		Working on a resolution.
	
=====================================================
	
This project extracted code from Cern's VecGEOM and Cern's umesimd, and VcDevel's VC

- Essentially it uses backend interfaces of VecGEOM/VecCore for various SIMD related code groups.
- And currently includes code groups:  umesimd and Vc

VecGeom/VecCore
https://gitlab.cern.ch/VecGeom

umesimd has interfaces for	( Thanks to Cern's UMESIMD team )
https://github.com/edanor/umesimd
- SSE
- SSE2
- AVX
- AVX2
- AVX512

Vc has interfaces for ( Thanks to VC team)
https://github.com/VcDevel/Vc
- SSE
- SSE2
- SSE3
- SSE4.1
- SSE4.2
- AVX
- AVX2