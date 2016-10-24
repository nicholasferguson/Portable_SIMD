// The MIT License (MIT)
//
// Copyright (c) 2016 CERN
//
// Author: Przemyslaw Karpinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//  This piece of code was developed as part of ICE-DIP project at CERN.
//  "ICE-DIP is a European Industrial Doctorate project funded by the European Community's 
//  7th Framework programme Marie Curie Actions under grant PITN-GA-2012-316596".
//

#ifndef UME_SIMD_VEC_INT_PROTOTYPE_H_
#define UME_SIMD_VEC_INT_PROTOTYPE_H_

#include <type_traits>
#include "../../../UMESimdInterface.h"

#include "../UMESimdMask.h"
#include "../UMESimdSwizzle.h"
#include "../UMESimdVecUint.h"

namespace UME {
namespace SIMD {

    // ********************************************************************************************
    // SIGNED INTEGER VECTORS
    // ********************************************************************************************
    template<typename SCALAR_INT_TYPE, uint32_t VEC_LEN>
    struct SIMDVec_i_traits {
        // Generic trait class not containing type definition so that only correct explicit
        // type definitions are compiled correctly
    };

    // 8b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 1> {
        typedef NullType<1>             HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 1>   VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<2>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<1>          MASK_TYPE;
        typedef SIMDSwizzle<1>          SWIZZLE_MASK_TYPE;
        typedef NullType<3>             SCALAR_INT_LOWER_PRECISION;
        typedef int16_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    // 16b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 2> {
        typedef SIMDVec_i<int8_t, 1>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 2>   VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<2>          MASK_TYPE;
        typedef SIMDSwizzle<2>          SWIZZLE_MASK_TYPE;
        typedef NullType<2>             SCALAR_INT_LOWER_PRECISION;
        typedef int16_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int16_t, 1> {
        typedef NullType<1>             HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint16_t, 1>  VEC_UINT;
        typedef uint16_t                SCALAR_UINT_TYPE;
        typedef NullType<2>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<1>          MASK_TYPE;
        typedef SIMDSwizzle<1>          SWIZZLE_MASK_TYPE;
        typedef int8_t                  SCALAR_INT_LOWER_PRECISION;
        typedef int32_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    // 32b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 4> {
        typedef SIMDVec_i<int8_t, 2>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 4>   VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<4>          MASK_TYPE;
        typedef SIMDSwizzle<4>          SWIZZLE_MASK_TYPE;
        typedef NullType<2>             SCALAR_INT_LOWER_PRECISION;
        typedef int16_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int16_t, 2> {
        typedef SIMDVec_i<int16_t, 1>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint16_t, 2>  VEC_UINT;
        typedef uint16_t                SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<2>          MASK_TYPE;
        typedef SIMDSwizzle<2>          SWIZZLE_MASK_TYPE;
        typedef int8_t                  SCALAR_INT_LOWER_PRECISION;
        typedef int32_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int32_t, 1> {
        typedef NullType<1>             HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 1>  VEC_UINT;
        typedef uint32_t                SCALAR_UINT_TYPE;
        typedef float                   SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<1>          MASK_TYPE;
        typedef SIMDSwizzle<1>          SWIZZLE_MASK_TYPE;
        typedef int16_t                 SCALAR_INT_LOWER_PRECISION;
        typedef int64_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    // 64b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 8> {
        typedef SIMDVec_i<int8_t, 4>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 8>   VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<8>          MASK_TYPE;
        typedef SIMDSwizzle<8>          SWIZZLE_MASK_TYPE;
        typedef NullType<2>             SCALAR_INT_LOWER_PRECISION;
        typedef int16_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int16_t, 4> {
        typedef SIMDVec_i<int16_t, 2>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint16_t, 4>  VEC_UINT;
        typedef uint16_t                SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<4>          MASK_TYPE;
        typedef SIMDSwizzle<4>          SWIZZLE_MASK_TYPE;
        typedef int8_t                  SCALAR_INT_LOWER_PRECISION;
        typedef int32_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int32_t, 2> {
        typedef SIMDVec_i<int32_t, 1>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 2>  VEC_UINT;
        typedef uint32_t                SCALAR_UINT_TYPE;
        typedef float                   SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<2>          MASK_TYPE;
        typedef SIMDSwizzle<2>          SWIZZLE_MASK_TYPE;
        typedef int16_t                 SCALAR_INT_LOWER_PRECISION;
        typedef int64_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int64_t, 1> {
        typedef NullType<1>             HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 1>  VEC_UINT;
        typedef uint64_t                SCALAR_UINT_TYPE;
        typedef double                  SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<1>          MASK_TYPE;
        typedef SIMDSwizzle<1>          SWIZZLE_MASK_TYPE;
        typedef int32_t                 SCALAR_INT_LOWER_PRECISION;
        typedef NullType<2>             SCALAR_INT_HIGHER_PRECISION;
    };

    // 128b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 16> {
        typedef SIMDVec_i<int8_t, 8>    HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 16>  VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<16>         MASK_TYPE;
        typedef SIMDSwizzle<16>         SWIZZLE_MASK_TYPE;
        typedef NullType<2>             SCALAR_INT_LOWER_PRECISION;
        typedef int16_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int16_t, 8> {
        typedef SIMDVec_i<int16_t, 4>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint16_t, 8>  VEC_UINT;
        typedef uint16_t                SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<8>          MASK_TYPE;
        typedef SIMDSwizzle<8>          SWIZZLE_MASK_TYPE;
        typedef int8_t                  SCALAR_INT_LOWER_PRECISION;
        typedef int32_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int32_t, 4> {
        typedef SIMDVec_i<int32_t, 2>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 4>  VEC_UINT;
        typedef uint32_t                SCALAR_UINT_TYPE;
        typedef float                   SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<4>          MASK_TYPE;
        typedef SIMDSwizzle<4>          SWIZZLE_MASK_TYPE;
        typedef int16_t                 SCALAR_INT_LOWER_PRECISION;
        typedef int64_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int64_t, 2> {
        typedef SIMDVec_i<int64_t, 1>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 2>  VEC_UINT;
        typedef uint64_t                SCALAR_UINT_TYPE;
        typedef double                  SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<2>          MASK_TYPE;
        typedef SIMDSwizzle<2>          SWIZZLE_MASK_TYPE;
        typedef int32_t                 SCALAR_INT_LOWER_PRECISION;
        typedef NullType<2>             SCALAR_INT_HIGHER_PRECISION;
    };

    // 256b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 32> {
        typedef SIMDVec_i<int8_t, 16>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 32>  VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<32>         MASK_TYPE;
        typedef SIMDSwizzle<32>         SWIZZLE_MASK_TYPE;
        typedef NullType<2>             SCALAR_INT_LOWER_PRECISION;
        typedef int16_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int16_t, 16> {
        typedef SIMDVec_i<int16_t, 8>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint16_t, 16> VEC_UINT;
        typedef uint16_t                SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<16>         MASK_TYPE;
        typedef SIMDSwizzle<16>         SWIZZLE_MASK_TYPE;
        typedef int8_t                  SCALAR_INT_LOWER_PRECISION;
        typedef int32_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int32_t, 8> {
        typedef SIMDVec_i<int32_t, 4>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 8>  VEC_UINT;
        typedef uint32_t                SCALAR_UINT_TYPE;
        typedef float                   SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<8>          MASK_TYPE;
        typedef SIMDSwizzle<8>          SWIZZLE_MASK_TYPE;
        typedef int16_t                 SCALAR_INT_LOWER_PRECISION;
        typedef int64_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int64_t, 4> {
        typedef SIMDVec_i<int64_t, 2>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 4>  VEC_UINT;
        typedef uint64_t                SCALAR_UINT_TYPE;
        typedef double                  SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<4>          MASK_TYPE;
        typedef SIMDSwizzle<4>          SWIZZLE_MASK_TYPE;
        typedef int32_t                 SCALAR_INT_LOWER_PRECISION;
        typedef NullType<1>             SCALAR_INT_HIGHER_PRECISION;
    };

    // 512b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 64> {
        typedef SIMDVec_i<int8_t, 32>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 64>  VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<64>         MASK_TYPE;
        typedef SIMDSwizzle<64>         SWIZZLE_MASK_TYPE;
        typedef NullType<2>             SCALAR_INT_LOWER_PRECISION;
        typedef int16_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int16_t, 32> {
        typedef SIMDVec_i<int16_t, 16>  HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint16_t, 32> VEC_UINT;
        typedef uint16_t                SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<32>         MASK_TYPE;
        typedef SIMDSwizzle<32>         SWIZZLE_MASK_TYPE;
        typedef int8_t                  SCALAR_INT_LOWER_PRECISION;
        typedef int32_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int32_t, 16> {
        typedef SIMDVec_i<int32_t, 8>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 16> VEC_UINT;
        typedef uint32_t                SCALAR_UINT_TYPE;
        typedef float                   SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<16>         MASK_TYPE;
        typedef SIMDSwizzle<16>         SWIZZLE_MASK_TYPE;
        typedef int16_t                 SCALAR_INT_LOWER_PRECISION;
        typedef int64_t                 SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int64_t, 8> {
        typedef SIMDVec_i<int64_t, 4>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 8>  VEC_UINT;
        typedef uint64_t                SCALAR_UINT_TYPE;
        typedef double                  SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<8>          MASK_TYPE;
        typedef SIMDSwizzle<8>          SWIZZLE_MASK_TYPE;
        typedef int32_t                 SCALAR_INT_LOWER_PRECISION;
        typedef NullType<2>             SCALAR_INT_HIGHER_PRECISION;
    };

    // 1024b vectors
    template<>
    struct SIMDVec_i_traits<int8_t, 128> {
        typedef SIMDVec_i<int8_t, 64>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint8_t, 128> VEC_UINT;
        typedef uint8_t                 SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<128>        MASK_TYPE;
        typedef SIMDSwizzle<128>        SWIZZLE_MASK_TYPE;
        typedef NullType<2>             SCALAR_INT_LOWER_PRECISION;
        typedef NullType<3>             SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int16_t, 64> {
        typedef SIMDVec_i<int16_t, 32>  HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint16_t, 64> VEC_UINT;
        typedef uint16_t                SCALAR_UINT_TYPE;
        typedef NullType<1>             SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<64>         MASK_TYPE;
        typedef SIMDSwizzle<64>         SWIZZLE_MASK_TYPE;
        typedef int8_t                  SCALAR_INT_LOWER_PRECISION;
        typedef NullType<2>             SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int32_t, 32> {
        typedef SIMDVec_i<int32_t, 16>  HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint32_t, 32> VEC_UINT;
        typedef uint32_t                SCALAR_UINT_TYPE;
        typedef float                   SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<32>         MASK_TYPE;
        typedef SIMDSwizzle<32>         SWIZZLE_MASK_TYPE;
        typedef int16_t                 SCALAR_INT_LOWER_PRECISION;
        typedef NullType<1>             SCALAR_INT_HIGHER_PRECISION;
    };

    template<>
    struct SIMDVec_i_traits<int64_t, 16> {
        typedef SIMDVec_i<int64_t, 8>   HALF_LEN_VEC_TYPE;
        typedef SIMDVec_u<uint64_t, 16> VEC_UINT;
        typedef uint64_t                SCALAR_UINT_TYPE;
        typedef double                  SCALAR_FLOAT_TYPE;
        typedef SIMDVecMask<16>         MASK_TYPE;
        typedef SIMDSwizzle<16>         SWIZZLE_MASK_TYPE;
        typedef int32_t                 SCALAR_INT_LOWER_PRECISION;
        typedef NullType<1>             SCALAR_INT_HIGHER_PRECISION;
    };

    // ***************************************************************************
    // *
    // *    Implementation of signed integer SIMDx_8i, SIMDx_16i, SIMDx_32i, 
    // *    and SIMDx_64i.
    // *
    // *    This implementation uses scalar emulation available through to 
    // *    SIMDVecSignedInterface.
    // *
    // ***************************************************************************
    template<typename SCALAR_INT_TYPE, uint32_t VEC_LEN>
    class SIMDVec_i :
        public SIMDVecSignedInterface<
            SIMDVec_i<SCALAR_INT_TYPE, VEC_LEN>,
            typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::VEC_UINT,
            SCALAR_INT_TYPE,
            VEC_LEN,
            typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SCALAR_UINT_TYPE,
            typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::MASK_TYPE,
            typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SWIZZLE_MASK_TYPE>,
        public SIMDVecPackableInterface<
            SIMDVec_i<SCALAR_INT_TYPE, VEC_LEN>,
            typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::HALF_LEN_VEC_TYPE>
    {
    public:
        typedef SIMDVecEmuRegister<SCALAR_INT_TYPE, VEC_LEN> VEC_EMU_REG;

        typedef typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SCALAR_UINT_TYPE   SCALAR_UINT_TYPE;
        typedef typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SCALAR_FLOAT_TYPE  SCALAR_FLOAT_TYPE;
        typedef typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::VEC_UINT           VEC_UINT;
        typedef typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::MASK_TYPE          MASK_TYPE;

        typedef typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SCALAR_INT_LOWER_PRECISION  SCALAR_INT_LOWER_PRECISION;
        typedef typename SIMDVec_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SCALAR_INT_HIGHER_PRECISION SCALAR_INT_HIGHER_PRECISION;

        friend class SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN>;
        friend class SIMDVec_f<SCALAR_FLOAT_TYPE, VEC_LEN>;
        
    public:
        constexpr static uint32_t alignment() { return VEC_LEN*sizeof(SCALAR_INT_TYPE); }

    private:
        alignas(alignment()) SCALAR_INT_TYPE mVec[VEC_LEN];

    public:
        // ZERO-CONSTR
        UME_FORCE_INLINE SIMDVec_i() : mVec() {};

        // SET-CONSTR
        UME_FORCE_INLINE explicit SIMDVec_i(SCALAR_INT_TYPE x) {
            SCALAR_INT_TYPE *local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for (int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = x;
            }
        }

        // LOAD-CONSTR
        UME_FORCE_INLINE explicit SIMDVec_i(SCALAR_INT_TYPE const * p) { this->load(p); }

        UME_FORCE_INLINE SIMDVec_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1) {
            mVec[0] = i0;  mVec[1] = i1;
        }

        UME_FORCE_INLINE SIMDVec_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1,
            SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3) {
            insert(0, i0);  insert(1, i1);
            insert(2, i2);  insert(3, i3);
        }

        UME_FORCE_INLINE SIMDVec_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1,
            SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3,
            SCALAR_INT_TYPE i4, SCALAR_INT_TYPE i5,
            SCALAR_INT_TYPE i6, SCALAR_INT_TYPE i7)
        {
            insert(0, i0);  insert(1, i1);
            insert(2, i2);  insert(3, i3);
            insert(4, i4);  insert(5, i5);
            insert(6, i6);  insert(7, i7);
        }

        UME_FORCE_INLINE SIMDVec_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1,
            SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3,
            SCALAR_INT_TYPE i4, SCALAR_INT_TYPE i5,
            SCALAR_INT_TYPE i6, SCALAR_INT_TYPE i7,
            SCALAR_INT_TYPE i8, SCALAR_INT_TYPE i9,
            SCALAR_INT_TYPE i10, SCALAR_INT_TYPE i11,
            SCALAR_INT_TYPE i12, SCALAR_INT_TYPE i13,
            SCALAR_INT_TYPE i14, SCALAR_INT_TYPE i15)
        {
            insert(0, i0);    insert(1, i1);
            insert(2, i2);    insert(3, i3);
            insert(4, i4);    insert(5, i5);
            insert(6, i6);    insert(7, i7);
            insert(8, i8);    insert(9, i9);
            insert(10, i10);  insert(11, i11);
            insert(12, i12);  insert(13, i13);
            insert(14, i14);  insert(15, i15);
        }

        UME_FORCE_INLINE SIMDVec_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1,
            SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3,
            SCALAR_INT_TYPE i4, SCALAR_INT_TYPE i5,
            SCALAR_INT_TYPE i6, SCALAR_INT_TYPE i7,
            SCALAR_INT_TYPE i8, SCALAR_INT_TYPE i9,
            SCALAR_INT_TYPE i10, SCALAR_INT_TYPE i11,
            SCALAR_INT_TYPE i12, SCALAR_INT_TYPE i13,
            SCALAR_INT_TYPE i14, SCALAR_INT_TYPE i15,
            SCALAR_INT_TYPE i16, SCALAR_INT_TYPE i17,
            SCALAR_INT_TYPE i18, SCALAR_INT_TYPE i19,
            SCALAR_INT_TYPE i20, SCALAR_INT_TYPE i21,
            SCALAR_INT_TYPE i22, SCALAR_INT_TYPE i23,
            SCALAR_INT_TYPE i24, SCALAR_INT_TYPE i25,
            SCALAR_INT_TYPE i26, SCALAR_INT_TYPE i27,
            SCALAR_INT_TYPE i28, SCALAR_INT_TYPE i29,
            SCALAR_INT_TYPE i30, SCALAR_INT_TYPE i31)
        {
            insert(0, i0);    insert(1, i1);
            insert(2, i2);    insert(3, i3);
            insert(4, i4);    insert(5, i5);
            insert(6, i6);    insert(7, i7);
            insert(8, i8);    insert(9, i9);
            insert(10, i10);  insert(11, i11);
            insert(12, i12);  insert(13, i13);
            insert(14, i14);  insert(15, i15);
            insert(16, i16);  insert(17, i17);
            insert(18, i18);  insert(19, i19);
            insert(20, i20);  insert(21, i21);
            insert(22, i22);  insert(23, i23);
            insert(24, i24);  insert(25, i25);
            insert(26, i26);  insert(27, i27);
            insert(28, i28);  insert(29, i29);
            insert(30, i30);  insert(31, i31);
        }

        // EXTRACT
        UME_FORCE_INLINE SCALAR_INT_TYPE extract(uint32_t index) const {
            return mVec[index];
        }
        UME_FORCE_INLINE SCALAR_INT_TYPE operator[] (uint32_t index) const {
            return extract(index);
        }

        // INSERT
        UME_FORCE_INLINE SIMDVec_i & insert(uint32_t index, SCALAR_INT_TYPE value) {
            mVec[index] = value;
            return *this;
        }
        UME_FORCE_INLINE IntermediateIndex<SIMDVec_i, SCALAR_INT_TYPE> operator[] (uint32_t index) {
            return IntermediateIndex<SIMDVec_i, SCALAR_INT_TYPE>(index, static_cast<SIMDVec_i &>(*this));
        }

        // Override Mask Access operators
#if defined(USE_PARENTHESES_IN_MASK_ASSIGNMENT)
        UME_FORCE_INLINE IntermediateMask<SIMDVec_i, SCALAR_INT_TYPE, MASK_TYPE> operator() (MASK_TYPE const & mask) {
            return IntermediateMask<SIMDVec_i, SCALAR_INT_TYPE, MASK_TYPE>(mask, static_cast<SIMDVec_i &>(*this));
        }
#else
        UME_FORCE_INLINE IntermediateMask<SIMDVec_i, SCALAR_INT_TYPE, MASK_TYPE> operator[] (MASK_TYPE const & mask) {
            return IntermediateMask<SIMDVec_i, SCALAR_INT_TYPE, MASK_TYPE>(mask, static_cast<SIMDVec_i &>(*this));
        }
#endif

        // ASSIGNV
        UME_FORCE_INLINE SIMDVec_i & assign(SIMDVec_i const & src) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_src_ptr = &src.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = local_src_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator= (SIMDVec_i const & b) {
            return this->assign(b);
        }
        // MASSIGNV
        UME_FORCE_INLINE SIMDVec_i & assign(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & src) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_src_ptr = &src.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if (local_mask_ptr[i] == true) local_ptr[i] = local_src_ptr[i];
            }
            return *this;
        }
        // ASSIGNS
        UME_FORCE_INLINE SIMDVec_i & assign(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator= (SCALAR_INT_TYPE b) {
            return this->assign(b);
        }
        // MASSIGNS
        UME_FORCE_INLINE SIMDVec_i & assign(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if (local_mask_ptr[i] == true) local_ptr[i] = b;
            }
            return *this;
        }

        // PREFETCH0
        // PREFETCH1
        // PREFETCH2

        // LOAD
        UME_FORCE_INLINE SIMDVec_i & load(SCALAR_INT_TYPE const *p) {
            SCALAR_INT_TYPE *local_ptr = &mVec[0];
            SCALAR_INT_TYPE const *local_p_ptr = &p[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = local_p_ptr[i];
            }
            return *this;
        }
        // MLOAD
        UME_FORCE_INLINE SIMDVec_i & load(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE const *p) {
            SCALAR_INT_TYPE *local_ptr = &mVec[0];
            SCALAR_INT_TYPE const *local_p_ptr = &p[0];
            bool const *local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if (local_mask_ptr[i] == true) local_ptr[i] = local_p_ptr[i];
            }
            return *this;
        }
        // LOADA
        UME_FORCE_INLINE SIMDVec_i & loada(SCALAR_INT_TYPE const *p) {
            SCALAR_INT_TYPE *local_ptr = &mVec[0];
            SCALAR_INT_TYPE const *local_p_ptr = &p[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = local_p_ptr[i];
            }
            return *this;
        }
        // MLOADA
        UME_FORCE_INLINE SIMDVec_i & loada(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE const *p) {
            SCALAR_INT_TYPE *local_ptr = &mVec[0];
            SCALAR_INT_TYPE const *local_p_ptr = &p[0];
            bool const *local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if (local_mask_ptr[i] == true) local_ptr[i] = local_p_ptr[i];
            }
            return *this;
        }
        // STORE
        UME_FORCE_INLINE SCALAR_INT_TYPE* store(SCALAR_INT_TYPE* p) const {
            SCALAR_INT_TYPE const *local_ptr = &mVec[0];
            SCALAR_INT_TYPE *local_p_ptr = &p[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_p_ptr[i] = local_ptr[i];
            }
            return p;
        }
        // MSTORE
        UME_FORCE_INLINE SCALAR_INT_TYPE* store(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE* p) const {
            SCALAR_INT_TYPE const *local_ptr = &mVec[0];
            SCALAR_INT_TYPE *local_p_ptr = &p[0];
            bool const *local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if (local_mask_ptr[i] == true) local_p_ptr[i] = local_ptr[i];
            }
            return p;
        }
        // STOREA
        UME_FORCE_INLINE SCALAR_INT_TYPE* storea(SCALAR_INT_TYPE* p) const {
            SCALAR_INT_TYPE const *local_ptr = &mVec[0];
            SCALAR_INT_TYPE *local_p_ptr = &p[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_p_ptr[i] = local_ptr[i];
            }
            return p;
        }
        // MSTOREA
        UME_FORCE_INLINE SCALAR_INT_TYPE* storea(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE* p) const {
            SCALAR_INT_TYPE const *local_ptr = &mVec[0];
            SCALAR_INT_TYPE *local_p_ptr = &p[0];
            bool const *local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if (local_mask_ptr[i] == true) local_p_ptr[i] = local_ptr[i];
            }
            return p;
        }

        // BLENDV
        UME_FORCE_INLINE SIMDVec_i blend(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE *retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const *local_ptr = &mVec[0];
            SCALAR_INT_TYPE const *local_b_ptr = &b.mVec[0];
            bool const *local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) retval_ptr[i] = local_b_ptr[i];
                else retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BLENDS
        UME_FORCE_INLINE SIMDVec_i blend(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE const *local_ptr = &mVec[0];
            SCALAR_INT_TYPE *retval_ptr = &retval.mVec[0];
            bool const *local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) retval_ptr[i] = b;
                else retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // SWIZZLE
        // SWIZZLEA

        // ADDV
        UME_FORCE_INLINE SIMDVec_i add(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] + local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator+ (SIMDVec_i const & b) const {
            return add(b);
        }
        // MADDV
        UME_FORCE_INLINE SIMDVec_i add(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] + local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // ADDS
        UME_FORCE_INLINE SIMDVec_i add(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] + b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator+ (SCALAR_INT_TYPE b) const {
            return add(b);
        }
        // MADDS
        UME_FORCE_INLINE SIMDVec_i add(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] + b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // ADDVA
        UME_FORCE_INLINE SIMDVec_i & adda(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] += local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator+= (SIMDVec_i const & b) {
            return adda(b);
        }
        // MADDVA
        UME_FORCE_INLINE SIMDVec_i & adda(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] += local_b_ptr[i];
            }
            return *this;
        }
        // ADDSA
        UME_FORCE_INLINE SIMDVec_i & adda(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] += b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator+= (SCALAR_INT_TYPE b) {
            return adda(b);
        }
        // MADDSA
        UME_FORCE_INLINE SIMDVec_i & adda(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] += b;
            }
            return *this;
        }

        // SADDV
        // MSADDV
        // SADDS
        // MSADDS
        // SADDVA
        // MSADDVA
        // SADDSA
        // MSADDSA

        // POSTINC
        UME_FORCE_INLINE SIMDVec_i postinc() {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i]++;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator++ (int) {
            return postinc();
        }
        // MPOSTINC
        UME_FORCE_INLINE SIMDVec_i postinc(SIMDVecMask<VEC_LEN> const & mask) {
             SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i]++;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // PREFINC
        UME_FORCE_INLINE SIMDVec_i & prefinc() {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                ++local_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator++ () {
            return prefinc();
        }
        // MPREFINC
        UME_FORCE_INLINE SIMDVec_i & prefinc(SIMDVecMask<VEC_LEN> const & mask) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) ++local_ptr[i];
            }
            return *this;
        }
        // SUBV
        UME_FORCE_INLINE SIMDVec_i sub(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] - local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator- (SIMDVec_i const & b) const {
            return sub(b);
        }
        // MSUBV
        UME_FORCE_INLINE SIMDVec_i sub(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] - local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // SUBS
        UME_FORCE_INLINE SIMDVec_i sub(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] - b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator- (SCALAR_INT_TYPE b) const {
            return sub(b);
        }
        // MSUBS
        UME_FORCE_INLINE SIMDVec_i sub(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] - b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // SUBVA
        UME_FORCE_INLINE SIMDVec_i & suba(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] -= local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator-= (SIMDVec_i const & b) {
            return suba(b);
        }
        // MSUBVA
        UME_FORCE_INLINE SIMDVec_i & suba(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] -= local_b_ptr[i];
            }
            return *this;
        }
        // SUBSA
        UME_FORCE_INLINE SIMDVec_i & suba(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] -= b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator-= (SCALAR_INT_TYPE b) {
            return suba(b);
        }
        // MSUBSA
        UME_FORCE_INLINE SIMDVec_i & suba(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] -= b;
            }
            return *this;
        }

        // SSUBV
        // MSSUBV
        // SSUBS
        // MSSUBS
        // SSUBVA
        // MSSUBVA
        // SSUBSA
        // MSSUBSA

        // SUBFROMV
        UME_FORCE_INLINE SIMDVec_i subfrom(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_b_ptr[i] - local_ptr[i];
            }
            return retval;
        }
        // MSUBFROMV
        UME_FORCE_INLINE SIMDVec_i subfrom(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_b_ptr[i] - local_ptr[i];
                else local_retval_ptr[i] = local_b_ptr[i];
            }
            return retval;
        }
        // SUBFROMS
        UME_FORCE_INLINE SIMDVec_i subfrom(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = b - local_ptr[i];
            }
            return retval;
        }
        // MSUBFROMS
        UME_FORCE_INLINE SIMDVec_i subfrom(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = b - local_ptr[i];
                else local_retval_ptr[i] = b;
            }
            return retval;
        }
        // SUBFROMVA
        UME_FORCE_INLINE SIMDVec_i & subfroma(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] = local_b_ptr[i] - local_ptr[i];
            }
            return *this;
        }
        // MSUBFROMVA
        UME_FORCE_INLINE SIMDVec_i & subfroma(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] = local_b_ptr[i] - local_ptr[i];
                else local_ptr[i] = local_b_ptr[i];
            }
            return *this;
        }
        // SUBFROMSA
        UME_FORCE_INLINE SIMDVec_i & subfroma(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = b - local_ptr[i];
            }
            return *this;
        }
        // MSUBFROMSA
        UME_FORCE_INLINE SIMDVec_i & subfroma(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] = b - local_ptr[i];
                else local_ptr[i] = b;
            }
            return *this;
        }
        // POSTDEC
        UME_FORCE_INLINE SIMDVec_i postdec() {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i]--;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator-- (int) {
            return postdec();
        }
        // MPOSTDEC
        UME_FORCE_INLINE SIMDVec_i postdec(SIMDVecMask<VEC_LEN> const & mask) {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i]--;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // PREFDEC
        UME_FORCE_INLINE SIMDVec_i & prefdec() {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                --local_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator-- () {
            return prefdec();
        }
        // MPREFDEC
        UME_FORCE_INLINE SIMDVec_i & prefdec(SIMDVecMask<VEC_LEN> const & mask) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) --local_ptr[i];
            }
            return *this;
        }
        // MULV
        UME_FORCE_INLINE SIMDVec_i mul(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] * local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator* (SIMDVec_i const & b) const {
            return mul(b);
        }
        // MMULV
        UME_FORCE_INLINE SIMDVec_i mul(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] * local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // MULS
        UME_FORCE_INLINE SIMDVec_i mul(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] * b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator* (SCALAR_INT_TYPE b) const {
            return mul(b);
        }
        // MMULS
        UME_FORCE_INLINE SIMDVec_i mul(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] * b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // MULVA
        UME_FORCE_INLINE SIMDVec_i & mula(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] *= local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator*= (SIMDVec_i const & b) {
            return mula(b);
        }
        // MMULVA
        UME_FORCE_INLINE SIMDVec_i & mula(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] *= local_b_ptr[i];
            }
            return *this;
        }
        // MULSA
        UME_FORCE_INLINE SIMDVec_i & mula(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] *= b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator*= (SCALAR_INT_TYPE b) {
            return mula(b);
        }
        // MMULSA
        UME_FORCE_INLINE SIMDVec_i & mula(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] *= b;
            }
            return *this;
        }
        // DIVV
        UME_FORCE_INLINE SIMDVec_i div(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] / local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator/ (SIMDVec_i const & b) const {
            return div(b);
        }
        // MDIVV
        UME_FORCE_INLINE SIMDVec_i div(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] / local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // DIVS
        UME_FORCE_INLINE SIMDVec_i div(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] / b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator/ (SCALAR_INT_TYPE b) const {
            return div(b);
        }
        // MDIVS
        UME_FORCE_INLINE SIMDVec_i div(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] / b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // DIVVA
        UME_FORCE_INLINE SIMDVec_i & diva(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] /= local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator/= (SIMDVec_i const & b) {
            return diva(b);
        }
        // MDIVVA
        UME_FORCE_INLINE SIMDVec_i & diva(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] /= local_b_ptr[i];
            }
            return *this;
        }
        // DIVSA
        UME_FORCE_INLINE SIMDVec_i & diva(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] /= b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator/= (SCALAR_INT_TYPE b) {
            return diva(b);
        }
        // MDIVSA
        UME_FORCE_INLINE SIMDVec_i & diva(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] /= b;
            }
            return *this;
        }
        // RCP
        UME_FORCE_INLINE SIMDVec_i rcp() const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = SCALAR_INT_TYPE(1.0f) / local_ptr[i];
            }
            return retval;
        }
        // MRCP
        UME_FORCE_INLINE SIMDVec_i rcp(SIMDVecMask<VEC_LEN> const & mask) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = SCALAR_INT_TYPE(1.0f) / local_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // RCPS
        UME_FORCE_INLINE SIMDVec_i rcp(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = b / local_ptr[i];
            }
            return retval;
        }
        // MRCPS
        UME_FORCE_INLINE SIMDVec_i rcp(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = b / local_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // RCPA
        UME_FORCE_INLINE SIMDVec_i & rcpa() {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] = SCALAR_INT_TYPE(1.0f) / local_ptr[i];
            }
            return *this;
        }
        // MRCPA
        UME_FORCE_INLINE SIMDVec_i & rcpa(SIMDVecMask<VEC_LEN> const & mask) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] = SCALAR_INT_TYPE(1.0f) / local_ptr[i];
            }
            return *this;
        }
        // RCPSA
        UME_FORCE_INLINE SIMDVec_i & rcpa(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = b / local_ptr[i];
            }
            return *this;
        }
        // MRCPSA
        UME_FORCE_INLINE SIMDVec_i & rcpa(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] = b / local_ptr[i];
            }
            return *this;
        }
        // CMPEQV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpeq(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] == local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator== (SIMDVec_i const & b) const {
            return cmpeq(b);
        }
        // CMPEQS
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpeq(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] == b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator== (SCALAR_INT_TYPE b) const {
            return cmpeq(b);
        }
        // CMPNEV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpne(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] != local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator!= (SIMDVec_i const & b) const {
            return cmpne(b);
        }
        // CMPNES
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpne(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] != b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator!= (SCALAR_INT_TYPE b) const {
            return cmpne(b);
        }
        // CMPGTV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpgt(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] > local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator> (SIMDVec_i const & b) const {
            return cmpgt(b);
        }
        // CMPGTS
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpgt(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] > b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator> (SCALAR_INT_TYPE b) const {
            return cmpgt(b);
        }
        // CMPLTV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmplt(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] < local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator< (SIMDVec_i const & b) const {
            return cmplt(b);
        }
        // CMPLTS
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmplt(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] < b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator< (SCALAR_INT_TYPE b) const {
            return cmplt(b);
        }
        // CMPGEV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpge(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] >= local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator>= (SIMDVec_i const & b) const {
            return cmpge(b);
        }
        // CMPGES
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmpge(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] >= b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator>= (SCALAR_INT_TYPE b) const {
            return cmpge(b);
        }
        // CMPLEV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmple(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] <= local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator<= (SIMDVec_i const & b) const {
            return cmple(b);
        }
        // CMPLES
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> cmple(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool * local_retval_ptr = &retval.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] <= b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> operator<= (SCALAR_INT_TYPE b) const {
            return cmple(b);
        }
        // CMPEV
        UME_FORCE_INLINE bool cmpe(SIMDVec_i const & b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool local_mask_ptr[VEC_LEN];
            bool retval = true;
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_mask_ptr[i] = local_ptr[i] == local_b_ptr[i];
            }
            #pragma omp simd reduction(&&:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval && local_mask_ptr[i];
            }
            return retval;
        }
        // CMPES
        UME_FORCE_INLINE bool cmpe(SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool local_mask_ptr[VEC_LEN];
            bool retval = true;
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_mask_ptr[i] = local_ptr[i] == b;
            }
            #pragma omp simd reduction(&&:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval && local_mask_ptr[i];
            }
            return retval;
        }
        // UNIQUE
        // TODO

        // HADD
        UME_FORCE_INLINE SCALAR_INT_TYPE hadd() const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0.0f);
            #pragma omp simd reduction(+:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval + local_ptr[i];
            }
            return retval;
        }
        // MHADD
        UME_FORCE_INLINE SCALAR_INT_TYPE hadd(SIMDVecMask<VEC_LEN> const & mask) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0.0f);
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0.0f);
            }
            #pragma omp simd reduction(+:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval + masked_copy[i];
            }
            return retval;
        }
        // HADDS
        UME_FORCE_INLINE SCALAR_INT_TYPE hadd(SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd reduction(+:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval + local_ptr[i];
            }
            return retval;
        }
        // MHADDS
        UME_FORCE_INLINE SCALAR_INT_TYPE hadd(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0.0f);
            }
            #pragma omp simd reduction(+:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval + masked_copy[i];
            }
            return retval;
        }
        // HMUL
        UME_FORCE_INLINE SCALAR_INT_TYPE hmul() const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(1.0f);
            #pragma omp simd reduction(*:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval * local_ptr[i];
            }
            return retval;        }
        // MHMUL
        UME_FORCE_INLINE SCALAR_INT_TYPE hmul(SIMDVecMask<VEC_LEN> const & mask) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(1.0f);
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(1.0f);
            }
            #pragma omp simd reduction(*:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval * masked_copy[i];
            }
            return retval;
        }
        // HMULS
        UME_FORCE_INLINE SCALAR_INT_TYPE hmul(SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd reduction(*:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval * local_ptr[i];
            }
            return retval;
        }
        // MHMULS
        UME_FORCE_INLINE SCALAR_INT_TYPE hmul(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(1.0f);
            }
            #pragma omp simd reduction(*:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval * masked_copy[i];
            }
            return retval;
        }
        // FMULADDV
        UME_FORCE_INLINE SIMDVec_i fmuladd(SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] * local_b_ptr[i] + local_c_ptr[i];
            }
            return retval;
        }
        // MFMULADDV
        UME_FORCE_INLINE SIMDVec_i fmuladd(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] * local_b_ptr[i] + local_c_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // FMULSUBV
        UME_FORCE_INLINE SIMDVec_i fmulsub(SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] * local_b_ptr[i] - local_c_ptr[i];
            }
            return retval;
        }
        // MFMULSUBV
        UME_FORCE_INLINE SIMDVec_i fmulsub(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] * local_b_ptr[i] - local_c_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // FADDMULV
        UME_FORCE_INLINE SIMDVec_i faddmul(SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = (local_ptr[i] + local_b_ptr[i]) * local_c_ptr[i];
            }
            return retval;
        }
        // MFADDMULV
        UME_FORCE_INLINE SIMDVec_i faddmul(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = (local_ptr[i] + local_b_ptr[i]) * local_c_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // FSUBMULV
        UME_FORCE_INLINE SIMDVec_i fsubmul(SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = (local_ptr[i] - local_b_ptr[i]) * local_c_ptr[i];
            }
            return retval;
        }
        // MFSUBMULV
        UME_FORCE_INLINE SIMDVec_i fsubmul(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b, SIMDVec_i const & c) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            SCALAR_INT_TYPE const * local_c_ptr = &c.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = (local_ptr[i] - local_b_ptr[i]) * local_c_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // MAXV
        UME_FORCE_INLINE SIMDVec_i max(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] > local_b_ptr[i]) local_retval_ptr[i] = local_ptr[i];
                else local_retval_ptr[i] = local_b_ptr[i];
            }
            return retval;
        }
        // MMAXV
        UME_FORCE_INLINE SIMDVec_i max(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] > local_b_ptr[i];
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_retval_ptr[i] = local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // MAXS
        UME_FORCE_INLINE SIMDVec_i max(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] > b) local_retval_ptr[i] = local_ptr[i];
                else local_retval_ptr[i] = b;
            }
            return retval;
        }
        // MMAXS
        UME_FORCE_INLINE SIMDVec_i max(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] > b;
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_retval_ptr[i] = b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // MAXVA
        UME_FORCE_INLINE SIMDVec_i & maxa(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] <= local_b_ptr[i]) local_ptr[i] = local_b_ptr[i];
            }
            return *this;
        }
        // MMAXVA
        UME_FORCE_INLINE SIMDVec_i & maxa(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] > local_b_ptr[i];
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_ptr[i] = local_b_ptr[i];
            }
            return *this;
        }
        // MAXSA
        UME_FORCE_INLINE SIMDVec_i & maxa(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] <= b) local_ptr[i] = b;
            }
            return *this;
        }
        // MMAXSA
        UME_FORCE_INLINE SIMDVec_i & maxa(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] > b;
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_ptr[i] = b;
            }
            return *this;
        }
        // MINV
        UME_FORCE_INLINE SIMDVec_i min(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] < local_b_ptr[i]) local_retval_ptr[i] = local_ptr[i];
                else local_retval_ptr[i] = local_b_ptr[i];
            }
            return retval;
        }
        // MMINV
        UME_FORCE_INLINE SIMDVec_i min(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] < local_b_ptr[i];
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_retval_ptr[i] = local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // MINS
        UME_FORCE_INLINE SIMDVec_i min(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] < b) local_retval_ptr[i] = local_ptr[i];
                else local_retval_ptr[i] = b;
            }
            return retval;
        }
        // MMINS
        UME_FORCE_INLINE SIMDVec_i min(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] < b;
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_retval_ptr[i] = b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // MINVA
        UME_FORCE_INLINE SIMDVec_i & mina(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] > local_b_ptr[i]) local_ptr[i] = local_b_ptr[i];
            }
            return *this;
        }
        // MMINVA
        UME_FORCE_INLINE SIMDVec_i & mina(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] < local_b_ptr[i];
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_ptr[i] = local_b_ptr[i];
            }
            return *this;
        }
        // MINSA
        UME_FORCE_INLINE SIMDVec_i & mina(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] > b) local_ptr[i] = b;
            }
            return *this;
        }
        // MMINSA
        UME_FORCE_INLINE SIMDVec_i & mina(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] < b;
                bool cond = local_mask_ptr[i] && !predicate;
                if(cond) local_ptr[i] = b;
            }
            return *this;
        }

        // HMAX
        // MHMAX
        // IMAX
        // MIMAX
        // HMIN
        // MHMIN
        // IMIN
        // MIMIN

        // BANDV
        UME_FORCE_INLINE SIMDVec_i band(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] & local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator& (SIMDVec_i const & b) const {
            return band(b);
        }
        // MBANDV
        UME_FORCE_INLINE SIMDVec_i band(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] & local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BANDS
        UME_FORCE_INLINE SIMDVec_i band(int32_t b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] & b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator& (int32_t b) const {
            return band(b);
        }
        // MBANDS
        UME_FORCE_INLINE SIMDVec_i band(SIMDVecMask<VEC_LEN> const & mask, int32_t b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] & b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BANDVA
        UME_FORCE_INLINE SIMDVec_i & banda(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] &= local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator&= (SIMDVec_i const & b) {
            return banda(b);
        }
        // MBANDVA
        UME_FORCE_INLINE SIMDVec_i & banda(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] &= local_b_ptr[i];
            }
            return *this;
        }
        // BANDSA
        UME_FORCE_INLINE SIMDVec_i & banda(int32_t b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] &= b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator&= (bool b) {
            return banda(b);
        }
        // MBANDSA
        UME_FORCE_INLINE SIMDVec_i & banda(SIMDVecMask<VEC_LEN> const & mask, int32_t b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] &= b;
            }
            return *this;
        }
        // BORV
        UME_FORCE_INLINE SIMDVec_i bor(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] | local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator| (SIMDVec_i const & b) const {
            return bor(b);
        }
        // MBORV
        UME_FORCE_INLINE SIMDVec_i bor(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] | local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BORS
        UME_FORCE_INLINE SIMDVec_i bor(int32_t b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] | b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator| (int32_t b) const {
            return bor(b);
        }
        // MBORS
        UME_FORCE_INLINE SIMDVec_i bor(SIMDVecMask<VEC_LEN> const & mask, int32_t b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] | b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BORVA
        UME_FORCE_INLINE SIMDVec_i & bora(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] |= local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator|= (SIMDVec_i const & b) {
            return bora(b);
        }
        // MBORVA
        UME_FORCE_INLINE SIMDVec_i & bora(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] |= local_b_ptr[i];
            }
            return *this;
        }
        // BORSA
        UME_FORCE_INLINE SIMDVec_i & bora(int32_t b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] |= b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator|= (int32_t b) {
            return bora(b);
        }
        // MBORSA
        UME_FORCE_INLINE SIMDVec_i & bora(SIMDVecMask<VEC_LEN> const & mask, int32_t b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] |= b;
            }
            return *this;
        }
        // BXORV
        UME_FORCE_INLINE SIMDVec_i bxor(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] ^ local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator^ (SIMDVec_i const & b) const {
            return bxor(b);
        }
        // MBXORV
        UME_FORCE_INLINE SIMDVec_i bxor(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] ^ local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BXORS
        UME_FORCE_INLINE SIMDVec_i bxor(int32_t b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] ^ b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator^ (int32_t b) const {
            return bxor(b);
        }
        // MBXORS
        UME_FORCE_INLINE SIMDVec_i bxor(SIMDVecMask<VEC_LEN> const & mask, int32_t b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] ^ b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BXORVA
        UME_FORCE_INLINE SIMDVec_i & bxora(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] ^= local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator^= (SIMDVec_i const & b) {
            return bxora(b);
        }
        // MBXORVA
        UME_FORCE_INLINE SIMDVec_i & bxora(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] ^= local_b_ptr[i];
            }
            return *this;
        }
        // BXORSA
        UME_FORCE_INLINE SIMDVec_i & bxora(int32_t b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] ^= b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator^= (int32_t b) {
            return bxora(b);
        }
        // MBXORSA
        UME_FORCE_INLINE SIMDVec_i & bxora(SIMDVecMask<VEC_LEN> const & mask, int32_t b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] ^= b;
            }
            return *this;
        }
        // BNOT
        UME_FORCE_INLINE SIMDVec_i bnot() const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = ~local_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator~ () const {
            return bnot();
        }
        // MBNOT
        UME_FORCE_INLINE SIMDVec_i bnot(SIMDVecMask<VEC_LEN> const & mask) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = ~local_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // BNOTA
        UME_FORCE_INLINE SIMDVec_i & bnota() {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = ~local_ptr[i];
            }
            return *this;
        }
        // MBNOTA
        UME_FORCE_INLINE SIMDVec_i & bnota(SIMDVecMask<VEC_LEN> const & mask) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] = ~local_ptr[i];
            }
            return *this;
        }
        // HBAND
        UME_FORCE_INLINE SCALAR_INT_TYPE hband() const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0xFFFFFFFFFFFFFFFF);
            #pragma omp simd reduction(&:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval & local_ptr[i];
            }
            return retval;
        }
        // MHBAND
        UME_FORCE_INLINE SCALAR_INT_TYPE hband(SIMDVecMask<VEC_LEN> const & mask) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0xFFFFFFFFFFFFFFFF);
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0xFFFFFFFFFFFFFFFF);
            }
            #pragma omp simd reduction(&:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval & masked_copy[i];
            }
            return retval;
        }
        // HBANDS
        UME_FORCE_INLINE SCALAR_INT_TYPE hband(SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd reduction(&:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval & local_ptr[i];
            }
            return retval;
        }
        // MHBANDS
        UME_FORCE_INLINE SCALAR_INT_TYPE hband(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0xFFFFFFFFFFFFFFFF);
            }
            #pragma omp simd reduction(&:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval & masked_copy[i];
            }
            return retval;
        }
        // HBOR
        UME_FORCE_INLINE SCALAR_INT_TYPE hbor() const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0);
            #pragma omp simd reduction(|:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval | local_ptr[i];
            }
            return retval;
        }
        // MHBOR
        UME_FORCE_INLINE SCALAR_INT_TYPE hbor(SIMDVecMask<VEC_LEN> const & mask) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0);
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0);
            }
            #pragma omp simd reduction(&:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval | masked_copy[i];
            }
            return retval;
        }
        // HBORS
        UME_FORCE_INLINE SCALAR_INT_TYPE hbor(SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd reduction(|:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval | local_ptr[i];
            }
            return retval;
        }
        // MHBORS
        UME_FORCE_INLINE SCALAR_INT_TYPE hbor(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0);
            }
            #pragma omp simd reduction(|:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval | masked_copy[i];
            }
            return retval;
        }
        // HBXOR
        UME_FORCE_INLINE SCALAR_INT_TYPE hbxor() const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0);
            #pragma omp simd reduction(^:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval ^ local_ptr[i];
            }
            return retval;
        }
        // MHBXOR
        UME_FORCE_INLINE SCALAR_INT_TYPE hbxor(SIMDVecMask<VEC_LEN> const & mask) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = SCALAR_INT_TYPE(0);
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0);
            }
            #pragma omp simd reduction(^:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval ^ masked_copy[i];
            }
            return retval;
        }
        // HBXORS
        UME_FORCE_INLINE SCALAR_INT_TYPE hbxor(SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd reduction(^:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval ^ local_ptr[i];
            }
            return retval;
        }
        // MHBXORS
        UME_FORCE_INLINE SCALAR_INT_TYPE hbxor(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE masked_copy[VEC_LEN];
            bool const * local_mask_ptr = &mask.mMask[0];
            SCALAR_INT_TYPE retval = b;
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) masked_copy[i] = local_ptr[i];
                else masked_copy[i] = SCALAR_INT_TYPE(0);
            }
            #pragma omp simd reduction(^:retval)
            for(int i = 0; i < VEC_LEN; i++) {
                retval = retval ^ masked_copy[i];
            }
            return retval;
        }
        // REMV
        UME_FORCE_INLINE SIMDVec_i rem(SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] % local_b_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator% (SIMDVec_i const & b) const {
            return rem(b);
        }
        // MREMV
        UME_FORCE_INLINE SIMDVec_i rem(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] % local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // REMS
        UME_FORCE_INLINE SIMDVec_i rem(SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] % b;
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator% (SCALAR_INT_TYPE b) const {
            return rem(b);
        }
        // MREMS
        UME_FORCE_INLINE SIMDVec_i rem(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] % b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // REMVA
        UME_FORCE_INLINE SIMDVec_i & rema(SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] %= local_b_ptr[i];
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator%= (SIMDVec_i const & b) {
            return rema(b);
        }
        // MREMVA
        UME_FORCE_INLINE SIMDVec_i & rema(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_i const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] %= local_b_ptr[i];
            }
            return *this;
        }
        // REMSA
        UME_FORCE_INLINE SIMDVec_i & rema(SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] %= b;
            }
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_i & operator%= (SCALAR_INT_TYPE b) {
            return rema(b);
        }
        // MREMSA
        UME_FORCE_INLINE SIMDVec_i & rema(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] %= b;
            }
            return *this;
        }
        // LANDV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> land(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            bool * local_retval_ptr = &retval.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] && local_b_ptr[i];
            }
            return retval;
        }
        // LANDS
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> land(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            bool * local_retval_ptr = &retval.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] && b;
            }
            return retval;
        }
        // LORV
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> lor(SIMDVec_i const & b) const {
            SIMDVecMask<VEC_LEN> retval;
            bool * local_retval_ptr = &retval.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_INT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] || local_b_ptr[i];
            }
            return retval;
        }
        // LORS
        UME_FORCE_INLINE SIMDVecMask<VEC_LEN> lor(SCALAR_INT_TYPE b) const {
            SIMDVecMask<VEC_LEN> retval;
            bool * local_retval_ptr = &retval.mMask[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] || b;
            }
            return retval;
        }
        // GATHERS
        UME_FORCE_INLINE SIMDVec_i & gather(SCALAR_INT_TYPE * baseAddr, SCALAR_UINT_TYPE* indices) {
            for(int i = 0; i < VEC_LEN; i++)
            {
                mVec[i] = baseAddr[indices[i]];
            }
            return *this;
        }
        // MGATHERS
        UME_FORCE_INLINE SIMDVec_i & gather(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE* baseAddr, SCALAR_UINT_TYPE* indices) {
            for(int i = 0; i < VEC_LEN; i++)
            {
                if(mask.mMask[i] == true) mVec[i] = baseAddr[indices[i]];
            }
            return *this;
        }
        // GATHERV
        UME_FORCE_INLINE SIMDVec_i & gather(SCALAR_INT_TYPE * baseAddr, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & indices) {
            for(int i = 0; i < VEC_LEN; i++)
            {
                mVec[i] = baseAddr[indices.mVec[i]];
            }
            return *this;
        }
        // MGATHERV
        UME_FORCE_INLINE SIMDVec_i & gather(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE* baseAddr, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & indices) {
            for(int i = 0; i < VEC_LEN; i++)
            {
                if(mask.mMask[i] == true) mVec[i] = baseAddr[indices.mVec[i]];
            }
            return *this;
        }
        // SCATTERS
        UME_FORCE_INLINE SCALAR_INT_TYPE* scatter(SCALAR_INT_TYPE* baseAddr, SCALAR_UINT_TYPE* indices) const {
            for(int i = 0; i < VEC_LEN; i++)
            {
                baseAddr[indices[i]] = mVec[i];
            }
            return baseAddr;
        }
        // MSCATTERS
        UME_FORCE_INLINE SCALAR_INT_TYPE* scatter(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE* baseAddr, SCALAR_UINT_TYPE* indices) const {
            for(int i = 0; i < VEC_LEN; i++)
            {
                if(mask.mMask[i]) baseAddr[indices[i]] = mVec[i];
            }
            return baseAddr;
        }
        // SCATTERV
        UME_FORCE_INLINE SCALAR_INT_TYPE* scatter(SCALAR_INT_TYPE* baseAddr, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & indices) const {
            for(int i = 0; i < VEC_LEN; i++)
            {
                baseAddr[indices.mVec[i]] = mVec[i];
            }
            return baseAddr;
        }
        // MSCATTERV
        UME_FORCE_INLINE SCALAR_INT_TYPE* scatter(SIMDVecMask<VEC_LEN> const & mask, SCALAR_INT_TYPE* baseAddr, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & indices) const {
            for(int i = 0; i < VEC_LEN; i++)
            {
                if(mask.mMask[i]) baseAddr[indices.mVec[i]] = mVec[i];
            }
            return baseAddr;
        }
        // LSHV
        UME_FORCE_INLINE SIMDVec_i lsh(SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] << local_b_ptr[i];
            }
            return retval;
        }
        // MLSHV
        UME_FORCE_INLINE SIMDVec_i lsh(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] << local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // LSHS
        UME_FORCE_INLINE SIMDVec_i lsh(SCALAR_UINT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] << b;
            }
            return retval;
        }
        // MLSHS
        UME_FORCE_INLINE SIMDVec_i lsh(SIMDVecMask<VEC_LEN> const & mask, SCALAR_UINT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] << b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // LSHVA
        UME_FORCE_INLINE SIMDVec_i & lsha(SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] <<= local_b_ptr[i];
            }
            return *this;
        }
        // MLSHVA
        UME_FORCE_INLINE SIMDVec_i & lsha(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] <<= local_b_ptr[i];
            }
            return *this;
        }
        // LSHSA
        UME_FORCE_INLINE SIMDVec_i & lsha(SCALAR_UINT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] <<= b;
            }
            return *this;
        }
        // MLSHSA
        UME_FORCE_INLINE SIMDVec_i & lsha(SIMDVecMask<VEC_LEN> const & mask, SCALAR_UINT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] <<= b;
            }
            return *this;
        }
        // RSHV
        UME_FORCE_INLINE SIMDVec_i rsh(SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] >> local_b_ptr[i];
            }
            return retval;
        }
        // MRSHV
        UME_FORCE_INLINE SIMDVec_i rsh(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] >> local_b_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // RSHS
        UME_FORCE_INLINE SIMDVec_i rsh(SCALAR_UINT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = local_ptr[i] >> b;
            }
            return retval;
        }
        // MRSHS
        UME_FORCE_INLINE SIMDVec_i rsh(SIMDVecMask<VEC_LEN> const & mask, SCALAR_UINT_TYPE b) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = local_ptr[i] >> b;
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // RSHVA
        UME_FORCE_INLINE SIMDVec_i & rsha(SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
               local_ptr[i] >>= local_b_ptr[i];
            }
            return *this;
        }
        // MRSHVA
        UME_FORCE_INLINE SIMDVec_i & rsha(SIMDVecMask<VEC_LEN> const & mask, SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN> const & b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            SCALAR_UINT_TYPE const * local_b_ptr = &b.mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] >>= local_b_ptr[i];
            }
            return *this;
        }
        // RSHSA
        UME_FORCE_INLINE SIMDVec_i & rsha(SCALAR_UINT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] >>= b;
            }
            return *this;
        }
        // MRSHSA
        UME_FORCE_INLINE SIMDVec_i & rsha(SIMDVecMask<VEC_LEN> const & mask, SCALAR_UINT_TYPE b) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] >>= b;
            }
            return *this;
        }
        // ROLV
        // MROLV
        // ROLS
        // MROLS
        // ROLVA
        // MROLVA
        // ROLSA
        // MROLSA
        // RORV
        // MRORV
        // RORS
        // MRORS
        // RORVA
        // MRORVA
        // RORSA
        // MRORSA
        // NEG
        UME_FORCE_INLINE SIMDVec_i neg() const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_retval_ptr[i] = -local_ptr[i];
            }
            return retval;
        }
        UME_FORCE_INLINE SIMDVec_i operator- () const {
            return neg();
        }
        // MNEG
        UME_FORCE_INLINE SIMDVec_i neg(SIMDVecMask<VEC_LEN> const & mask) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_retval_ptr[i] = -local_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // NEGA
        UME_FORCE_INLINE SIMDVec_i & nega() {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                local_ptr[i] = -local_ptr[i];
            }
            return *this;
        }
        // MNEGA
        UME_FORCE_INLINE SIMDVec_i & nega(SIMDVecMask<VEC_LEN> const & mask) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_mask_ptr[i] == true) local_ptr[i] = -local_ptr[i];
            }
            return *this;
        }
        // ABS
        UME_FORCE_INLINE SIMDVec_i abs() const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] >= 0 ) local_retval_ptr[i] = local_ptr[i];
                else local_retval_ptr[i] = -local_ptr[i];
            }
            return retval;
        }
        // MABS
        UME_FORCE_INLINE SIMDVec_i abs(SIMDVecMask<VEC_LEN> const & mask) const {
            SIMDVec_i retval;
            SCALAR_INT_TYPE * local_retval_ptr = &retval.mVec[0];
            SCALAR_INT_TYPE const * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] < 0;
                bool cond = local_mask_ptr[i] && predicate;

                if(cond) local_retval_ptr[i] = -local_ptr[i];
                else local_retval_ptr[i] = local_ptr[i];
            }
            return retval;
        }
        // ABSA
        UME_FORCE_INLINE SIMDVec_i & absa() {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                if(local_ptr[i] < 0 ) local_ptr[i] = -local_ptr[i];
            }
            return *this;
        }
        // MABSA
        UME_FORCE_INLINE SIMDVec_i & absa(SIMDVecMask<VEC_LEN> const & mask) {
            SCALAR_INT_TYPE * local_ptr = &mVec[0];
            bool const * local_mask_ptr = &mask.mMask[0];
            #pragma omp simd simdlen(VEC_LEN) safelen(VEC_LEN)
            for(int i = 0; i < VEC_LEN; i++) {
                bool predicate = local_ptr[i] < 0;
                bool cond = local_mask_ptr[i] && predicate;

                if(cond) local_ptr[i] = -local_ptr[i];
            }
            return *this;
        }

        // DEGRADE
        UME_FORCE_INLINE operator SIMDVec_i<SCALAR_INT_LOWER_PRECISION, VEC_LEN>() const;
        // PROMOTE
        UME_FORCE_INLINE operator SIMDVec_i<SCALAR_INT_HIGHER_PRECISION, VEC_LEN>() const;

        // ITOU
        UME_FORCE_INLINE operator SIMDVec_u<SCALAR_UINT_TYPE, VEC_LEN>() const;
        // ITOF
        UME_FORCE_INLINE operator SIMDVec_f<SCALAR_FLOAT_TYPE, VEC_LEN>() const;
    };

    // SIMD NullTypes. These are used whenever a terminating
    // scalar type is used as a creator function for SIMD type.
    // These types cannot be instantiated, but are necessary for 
    // typeset to be consistent.
    template<>
    class SIMDVec_i<NullType<1>, 1>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<1>, 2>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<1>, 4>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<1>, 8>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<1>, 16>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<1>, 32>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<1>, 64>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<1>, 128>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 1>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 2>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 4>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 8>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 16>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 32>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 64>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<2>, 128>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 1>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 2>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 4>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 8>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 16>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 32>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 64>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };

    template<>
    class SIMDVec_i<NullType<3>, 128>
    {
    private:
        SIMDVec_i() {}
        ~SIMDVec_i() {}
    };
}
}

#endif
