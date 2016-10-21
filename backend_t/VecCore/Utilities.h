#ifndef VECCORE_UTILITIES_H
#define VECCORE_UTILITIES_H

#ifdef ICC
#include <mm_malloc.h>
#elif MSVC
#include <memory>
#define _mm_malloc(x,y) _aligned_malloc(x,y)
//#define _mm_malloc(x) malloc(x)
#define _mm_free(x) _aligned_free(x)
#endif

namespace vecCore {

inline void *AlignedAlloc(size_t alignment, size_t size)
{
  return _mm_malloc(size, alignment);
}

inline void AlignedFree(void *ptr)
{
  _mm_free(ptr);
}
}

#endif
