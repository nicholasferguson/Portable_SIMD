=====================================================
2016.9.16 
	+ Built all code under Windows 10, with Visual Studio 2015, x64
	
	+ This project is to test a SIMD API, based on VecCore/VecGeom, to allow switching SIMD wrappers, such as UMESIMD or VC.
	
	Questions to answer
	+ Can an applicaiton switch to a particular SIMD backend, without any recoding, 
	+ Can only one backend + SIMD selection can be configured at compile time:  Example UMSIMD + AVX2  or VC + AVX2

	Issues
	+ backend.cc from VecCore is broken in its metaprogrammnig.  It resorts to copying into simd containers, using pointers
	+ quadratic.cc is a better test.
	+ To run test with VC
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_VC
	+ 	All tests were OK.
	+ To run test with UMESIMD
	+ 	build backend_t with Preprocessor Macro: VECCORE_ENABLE_UMESIMD
	+ 	issue with test using UME::SIMD::SIMDVec.  Container sizing is incorrect.  (fixed)	
		Working on a resolution.
	
=====================================================
	
This project extracted code from Cern's VecGEOM and Cern's umesimd.

- Essentially it uses backend interfaces of VecGEOM for various SIMD related code groups.
- It also extracts a backend tester from VecGEOM.  
- And currently includes code for umesimd.

umesimd has interfaces for	( Thanks to Cern's UMESIMD team )
- SSE
- SSE2
- AVX
- AVX2
- AVX512

