#ifndef VECCORE_COMMON_H
#define VECCORE_COMMON_H

#include "CUDA.h"
#include "SIMD.h"

#ifndef VECCORE_NO_FORCED_INLINING
#ifdef MSVC
#define VECCORE_FORCE_INLINE __forceinline
#define VECCORE_FORCE_NOINLINE
#define __restrict__  __restrict
#define __attribute__(A) /* do nothing */
#include <memory>
//#define _mm_malloc(x,y) _aligned_malloc(x,y)
//#define _mm_malloc(x) malloc(x)
//#define _mm_free(x) _aligned_free(x);
#else
#define VECCORE_FORCE_NOINLINE __attribute__((noinline))
#define VECCORE_FORCE_INLINE inline __attribute__((always_inline))
#endif
#else
#define VECCORE_FORCE_NOINLINE
#define VECCORE_FORCE_INLINE

#endif

#endif
