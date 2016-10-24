// The MIT License (MIT)
//
// Copyright (c) 2015 CERN
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

#ifndef UME_SIMD_VEC_UINT32_32_H_
#define UME_SIMD_VEC_UINT32_32_H_

#include <type_traits>
#include <immintrin.h>

#include "../../../UMESimdInterface.h"

namespace UME {
namespace SIMD {

    template<>
    class SIMDVec_u<uint32_t, 32> :
        public SIMDVecUnsignedInterface<
            SIMDVec_u<uint32_t, 32>,
            uint32_t,
            32,
            SIMDVecMask<32>,
            SIMDSwizzle<32>> ,
        public SIMDVecPackableInterface<
            SIMDVec_u<uint32_t, 32>,
            SIMDVec_u<uint32_t, 16>>
    {
        friend class SIMDVec_i<int32_t, 32>;
        friend class SIMDVec_f<float, 32>;

    private:
        __m512i mVec[2];

        UME_FORCE_INLINE explicit SIMDVec_u(__m512i & x0, __m512i & x1) { 
            mVec[0] = x0;
            mVec[1] = x1;
        }
        UME_FORCE_INLINE explicit SIMDVec_u(const __m512i & x0, const __m512i & x1) { 
            mVec[0] = x0;
            mVec[1] = x1;
        }
    public:

        constexpr static uint32_t length() { return 32; }
        constexpr static uint32_t alignment() { return 64; }

        // ZERO-CONSTR
        UME_FORCE_INLINE SIMDVec_u() {}
        // SET-CONSTR
        UME_FORCE_INLINE SIMDVec_u(uint32_t i) {
            mVec[0] = _mm512_set1_epi32(i);
            mVec[1] = mVec[0];
        }
        // This constructor is used to force types other than SCALAR_TYPES
        // to be promoted to SCALAR_TYPE instead of SCALAR_TYPE*. This prevents
        // ambiguity between SET-CONSTR and LOAD-CONSTR.
        template<typename T>
        UME_FORCE_INLINE SIMDVec_u(
            T i, 
            typename std::enable_if< std::is_same<T, int>::value && 
                                    !std::is_same<T, uint32_t>::value,
                                    void*>::type = nullptr)
        : SIMDVec_u(static_cast<uint32_t>(i)) {}
        
        // LOAD-CONSTR
        UME_FORCE_INLINE explicit SIMDVec_u(uint32_t const *p) { 
            load(p); 
        }
        // FULL-CONSTR
        UME_FORCE_INLINE SIMDVec_u(uint32_t i0,  uint32_t i1,  uint32_t i2,  uint32_t i3,
                         uint32_t i4,  uint32_t i5,  uint32_t i6,  uint32_t i7,
                         uint32_t i8,  uint32_t i9,  uint32_t i10, uint32_t i11,
                         uint32_t i12, uint32_t i13, uint32_t i14, uint32_t i15,
                         uint32_t i16, uint32_t i17, uint32_t i18, uint32_t i19,
                         uint32_t i20, uint32_t i21, uint32_t i22, uint32_t i23,
                         uint32_t i24, uint32_t i25, uint32_t i26, uint32_t i27,
                         uint32_t i28, uint32_t i29, uint32_t i30, uint32_t i31)
        {
            mVec[0] = _mm512_setr_epi32(i0, i1, i2, i3, i4, i5, i6, i7,
                                        i8, i9, i10, i11, i12, i13, i14, i15);
            mVec[1] = _mm512_setr_epi32(i16, i17, i18, i19, i20, i21, i22, i23,
                                        i24, i25, i26, i27, i28, i29, i30, i31);
        }
        // EXTRACT
        UME_FORCE_INLINE uint32_t extract(uint32_t index) const {
            alignas(64) uint32_t raw[16];
            uint32_t t0;
            if (index < 16) {
                _mm512_store_si512((__m512i*)raw, mVec[0]);
                t0 = index;
            }
            else {
                _mm512_store_si512((__m512i*)raw, mVec[1]);
                t0 = index - 16;
            }
            return raw[t0];
        }
        UME_FORCE_INLINE uint32_t operator[] (uint32_t index) const {
            return extract(index);
        }

        // INSERT
        UME_FORCE_INLINE SIMDVec_u & insert(uint32_t index, uint32_t value) {
            alignas(64) uint32_t raw[16];
            uint32_t t0;
            if (index < 16) {
                _mm512_store_si512((__m512i*)raw, mVec[0]);
                t0 = index;
            }
            else {
                _mm512_store_si512((__m512i*)raw, mVec[1]);
                t0 = index - 16;
            }
            
            raw[t0] = value;

            if (index < 16) {
                mVec[0] = _mm512_load_si512((__m512i*)raw);
            }
            else {
                mVec[1] = _mm512_load_si512((__m512i*)raw);
            }
            return *this;
        }
        UME_FORCE_INLINE IntermediateIndex<SIMDVec_u, uint32_t> operator[] (uint32_t index) {
            return IntermediateIndex<SIMDVec_u, uint32_t>(index, static_cast<SIMDVec_u &>(*this));
        }

        // Override Mask Access operators
#if defined(USE_PARENTHESES_IN_MASK_ASSIGNMENT)
        UME_FORCE_INLINE IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<32>> operator() (SIMDVecMask<32> const & mask) {
            return IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<32>>(mask, static_cast<SIMDVec_u &>(*this));
        }
#else
        UME_FORCE_INLINE IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<32>> operator[] (SIMDVecMask<32> const & mask) {
            return IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<32>>(mask, static_cast<SIMDVec_u &>(*this));
        }
#endif

        // ASSIGNV
        UME_FORCE_INLINE SIMDVec_u & assign(SIMDVec_u const & b) {
            mVec[0] = b.mVec[0];
            mVec[1] = b.mVec[1];
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator= (SIMDVec_u const & b) {
            return assign(b);
        }
        // MASSIGNV
        UME_FORCE_INLINE SIMDVec_u & assign(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_mov_epi32(mVec[0], m0, b.mVec[0]);
            mVec[1] = _mm512_mask_mov_epi32(mVec[1], m1, b.mVec[1]);
            return *this;
        }
        // ASSIGNS
        UME_FORCE_INLINE SIMDVec_u & assign(uint32_t b) {
            mVec[0] = _mm512_set1_epi32(b);
            mVec[1] = mVec[0];
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator= (uint32_t b) {
            return assign(b);
        }
        // MASSIGNS
        UME_FORCE_INLINE SIMDVec_u & assign(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_mov_epi32(mVec[0], m0, t0);
            mVec[1] = _mm512_mask_mov_epi32(mVec[1], m1, t0);
            return *this;
        }
        // PREFETCH0
        // PREFETCH1
        // PREFETCH2
        // LOAD
        UME_FORCE_INLINE SIMDVec_u & load(uint32_t const * p) {
            mVec[0] = _mm512_loadu_si512(p);
            mVec[1] = _mm512_loadu_si512(p + 16);
            return *this;
        }
        // MLOAD
        UME_FORCE_INLINE SIMDVec_u & load(SIMDVecMask<32> const & mask, uint32_t const * p) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_loadu_epi32(mVec[0], m0, p);
            mVec[1] = _mm512_mask_loadu_epi32(mVec[1], m1, p + 16);
            return *this;
        }
        // LOADA
        UME_FORCE_INLINE SIMDVec_u & loada(uint32_t const * p) {
            mVec[0] = _mm512_load_si512((__m512i*)p);
            mVec[1] = _mm512_load_si512((__m512i*)(p + 16));
            return *this;
        }
        // MLOADA
        UME_FORCE_INLINE SIMDVec_u & loada(SIMDVecMask<32> const & mask, uint32_t const * p) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_load_epi32(mVec[0], m0, p);
            mVec[1] = _mm512_mask_load_epi32(mVec[1], m1, p + 16);
            return *this;
        }
        // STORE
        UME_FORCE_INLINE uint32_t * store(uint32_t * p) const {
            _mm512_storeu_si512(p, mVec[0]);
            _mm512_storeu_si512(p + 16, mVec[1]);
            return p;
        }
        // MSTORE
        UME_FORCE_INLINE uint32_t * store(SIMDVecMask<32> const & mask, uint32_t * p) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            _mm512_mask_storeu_epi32(p, m0, mVec[0]);
            _mm512_mask_storeu_epi32(p + 16, m1, mVec[1]);
            return p;
        }
        // STOREA
        UME_FORCE_INLINE uint32_t * storea(uint32_t * p) {
            _mm512_store_si512((__m512i*)p, mVec[0]);
            _mm512_store_si512((__m512i*)(p + 16), mVec[1]);
            return p;
        }
        // MSTOREA
        UME_FORCE_INLINE uint32_t * storea(SIMDVecMask<32> const & mask, uint32_t * p) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            _mm512_mask_store_epi32(p,      m0, mVec[0]);
            _mm512_mask_store_epi32(p + 16, m1, mVec[1]);
            return p;
        }
        // BLENDV
        UME_FORCE_INLINE SIMDVec_u blend(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_mov_epi32(mVec[0], m0, b.mVec[0]);
            __m512i t1 = _mm512_mask_mov_epi32(mVec[1], m1, b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // BLENDS
        UME_FORCE_INLINE SIMDVec_u blend(SIMDVecMask<32> const & mask, uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t1 = _mm512_mask_mov_epi32(mVec[0], m0, t0);
            __m512i t2 = _mm512_mask_mov_epi32(mVec[1], m1, t0);
            return SIMDVec_u(t1, t2);
        }
        // SWIZZLE
        // SWIZZLEA
        // ADDV
        UME_FORCE_INLINE SIMDVec_u add(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_add_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_add_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator+ (SIMDVec_u const & b) const {
            __m512i t0 = _mm512_add_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_add_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MADDV
        UME_FORCE_INLINE SIMDVec_u add(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_add_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_add_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // ADDS
        UME_FORCE_INLINE SIMDVec_u add(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_add_epi32(mVec[0], t0);
            __m512i t2 = _mm512_add_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator+ (uint32_t b) const {
            return add(b);
        }
        // MADDS
        UME_FORCE_INLINE SIMDVec_u add(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_add_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_add_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // ADDVA
        UME_FORCE_INLINE SIMDVec_u & adda(SIMDVec_u const & b) {
            mVec[0] = _mm512_add_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_add_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator+= (SIMDVec_u const & b) {
            return adda(b);
        }
        // MADDVA
        UME_FORCE_INLINE SIMDVec_u & adda(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_add_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_add_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // ADDSA 
        UME_FORCE_INLINE SIMDVec_u & adda(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_add_epi32(mVec[0], t0);
            mVec[1] = _mm512_add_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator+= (uint32_t b) {
            return adda(b);
        }
        // MADDSA
        UME_FORCE_INLINE SIMDVec_u & adda(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_add_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_add_epi32(mVec[1], m1, mVec[1], t0);
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
        UME_FORCE_INLINE SIMDVec_u postinc() {
            __m512i t0 = _mm512_set1_epi32(1);
            __m512i t1 = mVec[0];
            __m512i t2 = mVec[1];
            mVec[0] = _mm512_add_epi32(mVec[0], t0);
            mVec[1] = _mm512_add_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator++ (int) {
            return postinc();
        }
        // MPOSTINC
        UME_FORCE_INLINE SIMDVec_u postinc(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(1);
            __m512i t1 = mVec[0];
            __m512i t2 = mVec[1];
            mVec[0] = _mm512_mask_add_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_add_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // PREFINC
        UME_FORCE_INLINE SIMDVec_u & prefinc() {
            __m512i t0 = _mm512_set1_epi32(1);
            mVec[0] = _mm512_add_epi32(mVec[0], t0);
            mVec[1] = _mm512_add_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator++ () {
            return prefinc();
        }
        // MPREFINC
        UME_FORCE_INLINE SIMDVec_u & prefinc(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(1);
            mVec[0] = _mm512_mask_add_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_add_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // SUBV
        UME_FORCE_INLINE SIMDVec_u sub(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_sub_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_sub_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator- (SIMDVec_u const & b) const {
            return sub(b);
        }
        // MSUBV
        UME_FORCE_INLINE SIMDVec_u sub(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_sub_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_sub_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // SUBS
        UME_FORCE_INLINE SIMDVec_u sub(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_sub_epi32(mVec[0], t0);
            __m512i t2 = _mm512_sub_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator- (uint32_t b) const {
            return sub(b);
        }
        // MSUBS
        UME_FORCE_INLINE SIMDVec_u sub(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_sub_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_sub_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // SUBVA
        UME_FORCE_INLINE SIMDVec_u & suba(SIMDVec_u const & b) {
            mVec[0] = _mm512_sub_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_sub_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator-= (SIMDVec_u const & b) {
            return suba(b);
        }
        // MSUBVA
        UME_FORCE_INLINE SIMDVec_u & suba(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_sub_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_sub_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // SUBSA
        UME_FORCE_INLINE SIMDVec_u & suba(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_sub_epi32(mVec[0], t0);
            mVec[1] = _mm512_sub_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator-= (uint32_t b) {
            return suba(b);
        }
        // MSUBSA
        UME_FORCE_INLINE SIMDVec_u & suba(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_sub_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_sub_epi32(mVec[1], m1, mVec[1], t0);
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
        UME_FORCE_INLINE SIMDVec_u subfrom(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_sub_epi32(b.mVec[0], mVec[0]);
            __m512i t1 = _mm512_sub_epi32(b.mVec[1], mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MSUBFROMV
        UME_FORCE_INLINE SIMDVec_u subfrom(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_sub_epi32(b.mVec[0], m0, b.mVec[0], mVec[0]);
            __m512i t1 = _mm512_mask_sub_epi32(b.mVec[1], m1, b.mVec[1], mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // SUBFROMS
        UME_FORCE_INLINE SIMDVec_u subfrom(uint32_t b) const {
            __m512i t0 = _mm512_sub_epi32(_mm512_set1_epi32(b), mVec[0]);
            __m512i t1 = _mm512_sub_epi32(_mm512_set1_epi32(b), mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MSUBFROMS
        UME_FORCE_INLINE SIMDVec_u subfrom(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_sub_epi32(t0, m0, t0, mVec[0]);
            __m512i t2 = _mm512_mask_sub_epi32(t0, m1, t0, mVec[1]);
            return SIMDVec_u(t1, t2);
        }
        // SUBFROMVA
        UME_FORCE_INLINE SIMDVec_u & subfroma(SIMDVec_u const & b) {
            mVec[0] = _mm512_sub_epi32(b.mVec[0], mVec[0]);
            mVec[1] = _mm512_sub_epi32(b.mVec[1], mVec[1]);
            return *this;
        }
        // MSUBFROMVA
        UME_FORCE_INLINE SIMDVec_u & subfroma(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_sub_epi32(b.mVec[0], m0, b.mVec[0], mVec[0]);
            mVec[1] = _mm512_mask_sub_epi32(b.mVec[1], m1, b.mVec[1], mVec[1]);
            return *this;
        }
        // SUBFROMSA
        UME_FORCE_INLINE SIMDVec_u & subfroma(uint32_t b) {
            mVec[0] = _mm512_sub_epi32(_mm512_set1_epi32(b), mVec[0]);
            mVec[1] = _mm512_sub_epi32(_mm512_set1_epi32(b), mVec[1]);
            return *this;
        }
        // MSUBFROMSA
        UME_FORCE_INLINE SIMDVec_u subfroma(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_sub_epi32(t0, m0, t0, mVec[0]);
            mVec[1] = _mm512_mask_sub_epi32(t0, m1, t0, mVec[1]);
            return *this;
        }
        // POSTDEC
        UME_FORCE_INLINE SIMDVec_u postdec() {
            __m512i t0 = _mm512_set1_epi32(1);
            __m512i t1 = mVec[0];
            __m512i t2 = mVec[1];
            mVec[0] = _mm512_sub_epi32(mVec[0], t0);
            mVec[1] = _mm512_sub_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator-- (int) {
            return postdec();
        }
        // MPOSTDEC
        UME_FORCE_INLINE SIMDVec_u postdec(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(1);
            __m512i t1 = mVec[0];
            __m512i t2 = mVec[1];
            mVec[0] = _mm512_mask_sub_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_sub_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // PREFDEC
        UME_FORCE_INLINE SIMDVec_u & prefdec() {
            __m512i t0 = _mm512_set1_epi32(1);
            mVec[0] = _mm512_sub_epi32(mVec[0], t0);
            mVec[1] = _mm512_sub_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator-- () {
            return prefdec();
        }
        // MPREFDEC
        UME_FORCE_INLINE SIMDVec_u & prefdec(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(1);
            mVec[0] = _mm512_mask_sub_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_sub_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // MULV
        UME_FORCE_INLINE SIMDVec_u mul(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_mullo_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mullo_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator* (SIMDVec_u const & b) const {
            return mul(b);
        }
        // MMULV
        UME_FORCE_INLINE SIMDVec_u mul(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_mullo_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_mullo_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MULS
        UME_FORCE_INLINE SIMDVec_u mul(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mullo_epi32(mVec[0], t0);
            __m512i t2 = _mm512_mullo_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator* (uint32_t b) const {
            return mul(b);
        }
        // MMULS
        UME_FORCE_INLINE SIMDVec_u mul(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_mullo_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_mullo_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // MULVA
        UME_FORCE_INLINE SIMDVec_u & mula(SIMDVec_u const & b) {
            mVec[0] = _mm512_mullo_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mullo_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator*= (SIMDVec_u const & b) {
            return mula(b);
        }
        // MMULVA
        UME_FORCE_INLINE SIMDVec_u & mula(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_mullo_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_mullo_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // MULSA
        UME_FORCE_INLINE SIMDVec_u & mula(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mullo_epi32(mVec[0], t0);
            mVec[1] = _mm512_mullo_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator*= (uint32_t b) {
            return mula(b);
        }
        // MMULSA
        UME_FORCE_INLINE SIMDVec_u & mula(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_mullo_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_mullo_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // DIVV
        UME_FORCE_INLINE SIMDVec_u operator/ (SIMDVec_u const & b) const {
            return div(b);
        }
        // MDIVV
        // DIVS
        UME_FORCE_INLINE SIMDVec_u operator/ (uint32_t b) const {
            return div(b);
        }
        // MDIVS
        // DIVVA
        UME_FORCE_INLINE SIMDVec_u & operator/= (SIMDVec_u const & b) {
            return diva(b);
        }
        // MDIVVA
        // DIVSA
        UME_FORCE_INLINE SIMDVec_u & operator/= (uint32_t b) {
            return diva(b);
        }
        // MDIVSA
        // RCP
        // MRCP
        // RCPS
        // MRCPS
        // RCPA
        // MRCPA
        // RCPSA
        // MRCPSA
        // CMPEQV
        UME_FORCE_INLINE SIMDVecMask<32> cmpeq(SIMDVec_u const & b) const {
            __mmask16 m0 = _mm512_cmpeq_epu32_mask(mVec[0], b.mVec[0]);
            __mmask16 m1 = _mm512_cmpeq_epu32_mask(mVec[1], b.mVec[1]);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator==(SIMDVec_u const & b) const {
            return cmpeq(b);
        }
        // CMPEQS
        UME_FORCE_INLINE SIMDVecMask<32> cmpeq(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = _mm512_cmpeq_epu32_mask(mVec[0], t0);
            __mmask16 m1 = _mm512_cmpeq_epu32_mask(mVec[1], t0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator== (uint32_t b) const {
            return cmpeq(b);
        }
        // CMPNEV
        UME_FORCE_INLINE SIMDVecMask<32> cmpne(SIMDVec_u const & b) const {
            __mmask16 m0 = _mm512_cmpneq_epu32_mask(mVec[0], b.mVec[0]);
            __mmask16 m1 = _mm512_cmpneq_epu32_mask(mVec[1], b.mVec[1]);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator!= (SIMDVec_u const & b) const {
            return cmpne(b);
        }
        // CMPNES
        UME_FORCE_INLINE SIMDVecMask<32> cmpne(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = _mm512_cmpneq_epu32_mask(mVec[0], t0);
            __mmask16 m1 = _mm512_cmpneq_epu32_mask(mVec[1], t0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator!= (uint32_t b) const {
            return cmpne(b);
        }
        // CMPGTV
        UME_FORCE_INLINE SIMDVecMask<32> cmpgt(SIMDVec_u const & b) const {
            __mmask16 m0 = _mm512_cmpgt_epu32_mask(mVec[0], b.mVec[0]);
            __mmask16 m1 = _mm512_cmpgt_epu32_mask(mVec[1], b.mVec[1]);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator> (SIMDVec_u const & b) const {
            return cmpgt(b);
        }
        // CMPGTS
        UME_FORCE_INLINE SIMDVecMask<32> cmpgt(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = _mm512_cmpgt_epu32_mask(mVec[0], t0);
            __mmask16 m1 = _mm512_cmpgt_epu32_mask(mVec[1], t0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator> (uint32_t b) const {
            return cmpgt(b);
        }
        // CMPLTV
        UME_FORCE_INLINE SIMDVecMask<32> cmplt(SIMDVec_u const & b) const {
            __mmask16 m0 = _mm512_cmplt_epu32_mask(mVec[0], b.mVec[0]);
            __mmask16 m1 = _mm512_cmplt_epu32_mask(mVec[1], b.mVec[1]);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator< (SIMDVec_u const & b) const {
            return cmplt(b);
        }
        // CMPLTS
        UME_FORCE_INLINE SIMDVecMask<32> cmplt(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = _mm512_cmplt_epu32_mask(mVec[0], t0);
            __mmask16 m1 = _mm512_cmplt_epu32_mask(mVec[1], t0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator< (uint32_t b) const {
            return cmplt(b);
        }
        // CMPGEV
        UME_FORCE_INLINE SIMDVecMask<32> cmpge(SIMDVec_u const & b) const {
            __mmask16 m0 = _mm512_cmpge_epu32_mask(mVec[0], b.mVec[0]);
            __mmask16 m1 = _mm512_cmpge_epu32_mask(mVec[1], b.mVec[1]);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator>= (SIMDVec_u const & b) const {
            return cmpge(b);
        }
        // CMPGES
        UME_FORCE_INLINE SIMDVecMask<32> cmpge(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = _mm512_cmpge_epu32_mask(mVec[0], t0);
            __mmask16 m1 = _mm512_cmpge_epu32_mask(mVec[1], t0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator>= (uint32_t b) const {
            return cmpge(b);
        }
        // CMPLEV
        UME_FORCE_INLINE SIMDVecMask<32> cmple(SIMDVec_u const & b) const {
            __mmask16 m0 = _mm512_cmple_epu32_mask(mVec[0], b.mVec[0]);
            __mmask16 m1 = _mm512_cmple_epu32_mask(mVec[1], b.mVec[1]);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator<= (SIMDVec_u const & b) const {
            return cmple(b);
        }
        // CMPLES
        UME_FORCE_INLINE SIMDVecMask<32> cmple(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = _mm512_cmple_epu32_mask(mVec[0], t0);
            __mmask16 m1 = _mm512_cmple_epu32_mask(mVec[1], t0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator<= (uint32_t b) const {
            return cmple(b);
        }
        // CMPEV
        UME_FORCE_INLINE bool cmpe(SIMDVec_u const & b) const {
            __mmask16 m0 = _mm512_cmple_epu32_mask(mVec[0], b.mVec[0]);
            __mmask16 m1 = _mm512_cmple_epu32_mask(mVec[1], b.mVec[1]);
            return (m0 == 0xFFFF) && (m1 == 0xFFFF);
        }
        // CMPES
        UME_FORCE_INLINE bool cmpe(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __mmask16 m0 = _mm512_cmpeq_epu32_mask(mVec[0], t0);
            __mmask16 m1 = _mm512_cmpeq_epu32_mask(mVec[1], t0);
            return (m0 == 0xFFFF) && (m1 == 0xFFFF);
        }
        // UNIQUE
        UME_FORCE_INLINE bool unique() const {
            alignas(64) uint32_t raw[32];
            _mm512_store_si512(raw, mVec[0]);
            _mm512_store_si512(raw + 16, mVec[1]);

            for (int i = 0; i < 31; i++) {
                for (int j = i; j < 32; j++) {
                    if (raw[i] == raw[j]) {
                        return false;
                    }
                }
            }

            return true;
        }
        // HADD
        UME_FORCE_INLINE uint32_t hadd() const {
            uint32_t t0 = _mm512_reduce_add_epi32(mVec[0]);
            uint32_t t1 = _mm512_reduce_add_epi32(mVec[1]);
            return t0 + t1;
        }
        // MHADD
        UME_FORCE_INLINE uint32_t hadd(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_add_epi32(m0, mVec[0]);
            uint32_t t1 = _mm512_mask_reduce_add_epi32(m1, mVec[1]);
            return t0 + t1;
        }
        // HADDS
        UME_FORCE_INLINE uint32_t hadd(uint32_t b) const {
            uint32_t t0 = _mm512_reduce_add_epi32(mVec[0]);
            uint32_t t1 = _mm512_reduce_add_epi32(mVec[1]);
            return t0 + t1 + b;
        }
        // MHADDS
        UME_FORCE_INLINE uint32_t hadd(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_add_epi32(m0, mVec[0]);
            uint32_t t1 = _mm512_mask_reduce_add_epi32(m1, mVec[1]);
            return t0 + t1 + b;
        }
        // HMUL
        UME_FORCE_INLINE uint32_t hmul() const {
            uint32_t t0 = _mm512_reduce_mul_epi32(mVec[0]);
            uint32_t t1 = _mm512_reduce_mul_epi32(mVec[1]);
            return t0 * t1;
        }
        // MHMUL
        UME_FORCE_INLINE uint32_t hmul(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_add_epi32(m0, mVec[0]);
            uint32_t t1 = _mm512_mask_reduce_add_epi32(m1, mVec[1]);
            return t0 * t1;
        }
        // HMULS
        UME_FORCE_INLINE uint32_t hmul(uint32_t b) const {
            uint32_t t0 = _mm512_reduce_mul_epi32(mVec[0]);
            uint32_t t1 = _mm512_reduce_mul_epi32(mVec[1]);
            return b * t0 * t1;
        }
        // MHMULS
        UME_FORCE_INLINE uint32_t hmul(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_add_epi32(m0, mVec[0]);
            uint32_t t1 = _mm512_mask_reduce_add_epi32(m1, mVec[1]);
            return b * t0 * t1;
        }
        // FMULADDV
        UME_FORCE_INLINE SIMDVec_u fmuladd(SIMDVec_u const & b, SIMDVec_u const & c) const {
            __m512i t0 = _mm512_mullo_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mullo_epi32(mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_add_epi32(t0, c.mVec[0]);
            __m512i t3 = _mm512_add_epi32(t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // MFMULADDV
        UME_FORCE_INLINE SIMDVec_u fmuladd(SIMDVecMask<32> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_mullo_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_mullo_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_mask_add_epi32(t0, m0, t0, c.mVec[0]);
            __m512i t3 = _mm512_mask_add_epi32(t1, m1, t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // FMULSUBV
        UME_FORCE_INLINE SIMDVec_u fmulsub(SIMDVec_u const & b, SIMDVec_u const & c) const {
            __m512i t0 = _mm512_mullo_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mullo_epi32(mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_sub_epi32(t0, c.mVec[0]);
            __m512i t3 = _mm512_sub_epi32(t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // MFMULSUBV
        UME_FORCE_INLINE SIMDVec_u fmulsub(SIMDVecMask<32> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_mullo_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_mullo_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_mask_sub_epi32(t0, m0, t0, c.mVec[0]);
            __m512i t3 = _mm512_mask_sub_epi32(t1, m1, t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // FADDMULV
        UME_FORCE_INLINE SIMDVec_u faddmul(SIMDVec_u const & b, SIMDVec_u const & c) const {
            __m512i t0 = _mm512_add_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_add_epi32(mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_mullo_epi32(t0, c.mVec[0]);
            __m512i t3 = _mm512_mullo_epi32(t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // MFADDMULV
        UME_FORCE_INLINE SIMDVec_u faddmul(SIMDVecMask<32> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_add_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_add_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_mask_mullo_epi32(t0, m0, t0, c.mVec[0]);
            __m512i t3 = _mm512_mask_mullo_epi32(t1, m1, t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // FSUBMULV
        UME_FORCE_INLINE SIMDVec_u fsubmul(SIMDVec_u const & b, SIMDVec_u const & c) const {
            __m512i t0 = _mm512_sub_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_sub_epi32(mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_mullo_epi32(t0, c.mVec[0]);
            __m512i t3 = _mm512_mullo_epi32(t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // MFSUBMULV
        UME_FORCE_INLINE SIMDVec_u fsubmul(SIMDVecMask<32> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_sub_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_sub_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            __m512i t2 = _mm512_mask_mullo_epi32(t0, m0, t0, c.mVec[0]);
            __m512i t3 = _mm512_mask_mullo_epi32(t1, m1, t1, c.mVec[1]);
            return SIMDVec_u(t2, t3);
        }
        // MAXV
        UME_FORCE_INLINE SIMDVec_u max(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_max_epu32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_max_epu32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MMAXV
        UME_FORCE_INLINE SIMDVec_u max(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_max_epu32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_max_epu32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MAXS
        UME_FORCE_INLINE SIMDVec_u max(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_max_epu32(mVec[0], t0);
            __m512i t2 = _mm512_max_epu32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // MMAXS
        UME_FORCE_INLINE SIMDVec_u max(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_max_epu32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_max_epu32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // MAXVA
        UME_FORCE_INLINE SIMDVec_u & maxa(SIMDVec_u const & b) {
            mVec[0] = _mm512_max_epu32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_max_epu32(mVec[1], b.mVec[1]);
            return *this;
        }
        // MMAXVA
        UME_FORCE_INLINE SIMDVec_u & maxa(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_max_epu32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_max_epu32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // MAXSA
        UME_FORCE_INLINE SIMDVec_u & maxa(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_max_epu32(mVec[0], t0);
            mVec[1] = _mm512_max_epu32(mVec[1], t0);
            return *this;
        }
        // MMAXSA
        UME_FORCE_INLINE SIMDVec_u & maxa(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_max_epu32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_max_epu32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // MINV
        UME_FORCE_INLINE SIMDVec_u min(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_min_epu32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_min_epu32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MMINV
        UME_FORCE_INLINE SIMDVec_u min(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_min_epu32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_min_epu32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MINS
        UME_FORCE_INLINE SIMDVec_u min(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_min_epu32(mVec[0], t0);
            __m512i t2 = _mm512_min_epu32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // MMINS
        UME_FORCE_INLINE SIMDVec_u min(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_min_epu32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_min_epu32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // MINVA
        UME_FORCE_INLINE SIMDVec_u & mina(SIMDVec_u const & b) {
            mVec[0] = _mm512_min_epu32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_min_epu32(mVec[1], b.mVec[1]);
            return *this;
        }
        // MMINVA
        UME_FORCE_INLINE SIMDVec_u & mina(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_min_epu32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_min_epu32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // MINSA
        UME_FORCE_INLINE SIMDVec_u & mina(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_min_epu32(mVec[0], t0);
            mVec[1] = _mm512_min_epu32(mVec[1], t0);
            return *this;
        }
        // MMINSA
        UME_FORCE_INLINE SIMDVec_u & mina(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_min_epu32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_min_epu32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // HMAX
        UME_FORCE_INLINE uint32_t hmax() const {
            uint32_t t0 = _mm512_reduce_max_epu32(mVec[0]);
            uint32_t t1 = _mm512_reduce_max_epu32(mVec[1]);
            return t0 > t1 ? t0 : t1;
        }       
        // MHMAX
        UME_FORCE_INLINE uint32_t hmax(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_max_epu32(m0, mVec[0]);
            uint32_t t1 = _mm512_mask_reduce_max_epu32(m1, mVec[1]);
            return t0 > t1 ? t0 : t1;
        }       
        // IMAX
        // MIMAX
        // HMIN
        UME_FORCE_INLINE uint32_t hmin() const {
            uint32_t t0 = _mm512_reduce_min_epu32(mVec[0]);
            uint32_t t1 = _mm512_reduce_min_epu32(mVec[1]);
            return t0 < t1 ? t0 : t1;
        }       
        // MHMIN
        UME_FORCE_INLINE uint32_t hmin(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_min_epu32(m0, mVec[0]);
            uint32_t t1 = _mm512_mask_reduce_min_epu32(m1, mVec[1]);
            return t0 < t1 ? t0 : t1;
        }       
        // IMIN
        // MIMIN

        // BANDV
        UME_FORCE_INLINE SIMDVec_u band(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_and_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_and_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator& (SIMDVec_u const & b) const {
            return band(b);
        }
        // MBANDV
        UME_FORCE_INLINE SIMDVec_u band(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_and_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_and_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // BANDS
        UME_FORCE_INLINE SIMDVec_u band(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_and_epi32(mVec[0], t0);
            __m512i t2 = _mm512_and_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator& (uint32_t b) const {
            return band(b);
        }
        // MBANDS
        UME_FORCE_INLINE SIMDVec_u band(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_and_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_and_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // BANDVA
        UME_FORCE_INLINE SIMDVec_u & banda(SIMDVec_u const & b) {
            mVec[0] = _mm512_and_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_and_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator&= (SIMDVec_u const & b) {
            return banda(b);
        }
        // MBANDVA
        UME_FORCE_INLINE SIMDVec_u & banda(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_and_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_and_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // BANDSA
        UME_FORCE_INLINE SIMDVec_u & banda(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_and_epi32(mVec[0], t0);
            mVec[1] = _mm512_and_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator&= (bool b) {
            return banda(b);
        }
        // MBANDSA
        UME_FORCE_INLINE SIMDVec_u & banda(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_and_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_and_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // BORV
        UME_FORCE_INLINE SIMDVec_u bor(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_or_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_or_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator| (SIMDVec_u const & b) const {
            return bor(b);
        }
        // MBORV
        UME_FORCE_INLINE SIMDVec_u bor(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_or_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_or_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // BORS
        UME_FORCE_INLINE SIMDVec_u bor(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_or_epi32(mVec[0], t0);
            __m512i t2 = _mm512_or_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator| (uint32_t b) const {
            return bor(b);
        }
        // MBORS
        UME_FORCE_INLINE SIMDVec_u bor(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_or_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_or_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // BORVA
        UME_FORCE_INLINE SIMDVec_u & bora(SIMDVec_u const & b) {
            mVec[0] = _mm512_or_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_or_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator|= (SIMDVec_u const & b) {
            return bora(b);
        }
        // MBORVA
        UME_FORCE_INLINE SIMDVec_u & bora(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_or_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_or_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // BORSA
        UME_FORCE_INLINE SIMDVec_u & bora(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_or_epi32(mVec[0], t0);
            mVec[1] = _mm512_or_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator|= (uint32_t b) {
            return bora(b);
        }
        // MBORSA
        UME_FORCE_INLINE SIMDVec_u & bora(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_or_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_or_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // BXORV
        UME_FORCE_INLINE SIMDVec_u bxor(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_xor_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_xor_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator^ (SIMDVec_u const & b) const {
            return bxor(b);
        }
        // MBXORV
        UME_FORCE_INLINE SIMDVec_u bxor(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_xor_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_xor_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // BXORS
        UME_FORCE_INLINE SIMDVec_u bxor(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_xor_epi32(mVec[0], t0);
            __m512i t2 = _mm512_xor_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator^ (uint32_t b) const {
            return bxor(b);
        }
        // MBXORS
        UME_FORCE_INLINE SIMDVec_u bxor(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_xor_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_xor_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // BXORVA
        UME_FORCE_INLINE SIMDVec_u & bxora(SIMDVec_u const & b) {
            mVec[0] = _mm512_xor_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_xor_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator^= (SIMDVec_u const & b) {
            return bxora(b);
        }
        // MBXORVA
        UME_FORCE_INLINE SIMDVec_u & bxora(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_xor_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_xor_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // BXORSA
        UME_FORCE_INLINE SIMDVec_u & bxora(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_xor_epi32(mVec[0], t0);
            mVec[1] = _mm512_xor_epi32(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_u & operator^= (uint32_t b) {
            return bxora(b);
        }
        // MBXORSA
        UME_FORCE_INLINE SIMDVec_u & bxora(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_xor_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_xor_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // BNOT
        UME_FORCE_INLINE SIMDVec_u bnot() const {
            __m512i t0 = _mm512_set1_epi32(0xFFFFFFFF);
            __m512i t1 = _mm512_andnot_epi32(mVec[0], t0);
            __m512i t2 = _mm512_andnot_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator~ () const {
            return bnot();
        }
        // MBNOT
        UME_FORCE_INLINE SIMDVec_u bnot(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(0xFFFFFFFF);
            __m512i t1 = _mm512_mask_andnot_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_andnot_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // BNOTA
        UME_FORCE_INLINE SIMDVec_u & bnota() {
            __m512i t0 = _mm512_set1_epi32(0xFFFFFFFF);
            mVec[0] = _mm512_andnot_epi32(mVec[0], t0);
            mVec[1] = _mm512_andnot_epi32(mVec[1], t0);
            return *this;
        }
        // MBNOTA
        UME_FORCE_INLINE SIMDVec_u bnota(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(0xFFFFFFFF);
            mVec[0] = _mm512_mask_andnot_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_andnot_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // HBAND
        UME_FORCE_INLINE uint32_t hband() const {
            uint32_t t0 = _mm512_reduce_and_epi32(mVec[0]);
            t0 &= _mm512_reduce_and_epi32(mVec[1]);
            return t0;
        }
        // MHBAND
        UME_FORCE_INLINE uint32_t hband(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_and_epi32(m0, mVec[0]);
            t0 &= _mm512_mask_reduce_and_epi32(m1, mVec[1]);
            return t0;
        }
        // HBANDS
        UME_FORCE_INLINE uint32_t hband(uint32_t b) const {
            uint32_t t0 = b;
            t0 &= _mm512_reduce_and_epi32(mVec[0]);
            t0 &= _mm512_reduce_and_epi32(mVec[1]);
            return t0;
        }
        // MHBANDS
        UME_FORCE_INLINE uint32_t hband(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = b;
            t0 &= _mm512_mask_reduce_and_epi32(m0, mVec[0]);
            t0 &= _mm512_mask_reduce_and_epi32(m1, mVec[1]);
            return t0;
        }
        // HBOR
        UME_FORCE_INLINE uint32_t hbor() const {
            uint32_t t0 = _mm512_reduce_or_epi32(mVec[0]);
            t0 |= _mm512_reduce_or_epi32(mVec[1]);
            return t0;
        }
        // MHBOR
        UME_FORCE_INLINE uint32_t hbor(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = _mm512_mask_reduce_or_epi32(m0, mVec[0]);
            t0 |= _mm512_mask_reduce_or_epi32(m1, mVec[1]);
            return t0;
        }
        // HBORS
        UME_FORCE_INLINE uint32_t hbor(uint32_t b) const {
            uint32_t t0 = b;
            t0 |= _mm512_reduce_or_epi32(mVec[0]);
            t0 |= _mm512_reduce_or_epi32(mVec[1]);
            return t0;
        }
        // MHBORS
        UME_FORCE_INLINE uint32_t hbor(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            uint32_t t0 = b;
            t0 |= _mm512_mask_reduce_or_epi32(m0, mVec[0]);
            t0 |= _mm512_mask_reduce_or_epi32(m1, mVec[1]);
            return t0;
        }
        // HBXOR
        UME_FORCE_INLINE uint32_t hbxor() const {
            alignas(64) uint32_t raw[32];
            _mm512_store_si512((__m512i*)raw, mVec[0]);
            _mm512_store_si512((__m512i*)(raw + 16), mVec[1]);
            uint32_t t0 = 0;
            for (int i = 0; i < 32; i++) {
                t0 ^= raw[i];
            }
            return t0;
        }
        // MHBXOR
        UME_FORCE_INLINE uint32_t hbxor(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            alignas(64) uint32_t raw[32];
            _mm512_store_si512((__m512i*)raw, mVec[0]);
            _mm512_store_si512((__m512i*)(raw + 16), mVec[1]);
            uint32_t t0 = 0;
            for (int i = 0; i < 32; i++) {
                if ((mask.mMask & (1 << i)) != 0) t0 ^= raw[i];
            }
            return t0;
        }
        // HBXORS
        UME_FORCE_INLINE uint32_t hbxor(uint32_t b) const {
            alignas(64) uint32_t raw[32];
            _mm512_store_si512((__m512i*)raw, mVec[0]);
            _mm512_store_si512((__m512i*)(raw + 16), mVec[1]);
            uint32_t t0 = b;
            for (int i = 0; i < 32; i++) {
                t0 ^= raw[i];
            }
            return t0;
        }
        // MHBXORS
        UME_FORCE_INLINE uint32_t hbxor(SIMDVecMask<32> const & mask, uint32_t b) const {
            alignas(64) uint32_t raw[32];
            _mm512_store_si512((__m512i*)raw, mVec[0]);
            _mm512_store_si512((__m512i*)(raw + 16), mVec[1]);
            uint32_t t0 = b;
            for (int i = 0; i < 32; i++) {
                if ((mask.mMask & (1 << i)) != 0) t0 ^= raw[i];
            }
            return t0;
        }
        // GATHERS
        UME_FORCE_INLINE SIMDVec_u & gather(uint32_t* baseAddr, uint32_t* indices) {
            alignas(64) uint32_t raw[32] = { 
                baseAddr[indices[0]], baseAddr[indices[1]],
                baseAddr[indices[2]], baseAddr[indices[3]],
                baseAddr[indices[4]], baseAddr[indices[5]],
                baseAddr[indices[6]], baseAddr[indices[7]],
                baseAddr[indices[8]], baseAddr[indices[9]],
                baseAddr[indices[10]], baseAddr[indices[11]],
                baseAddr[indices[12]], baseAddr[indices[13]],
                baseAddr[indices[14]], baseAddr[indices[15]],
                baseAddr[indices[16]], baseAddr[indices[17]],
                baseAddr[indices[18]], baseAddr[indices[19]],
                baseAddr[indices[20]], baseAddr[indices[21]],
                baseAddr[indices[22]], baseAddr[indices[23]],
                baseAddr[indices[24]], baseAddr[indices[25]],
                baseAddr[indices[26]], baseAddr[indices[27]],
                baseAddr[indices[28]], baseAddr[indices[29]],
                baseAddr[indices[30]], baseAddr[indices[31]]};
            mVec[0] = _mm512_load_si512((__m512i*)raw);
            mVec[1] = _mm512_load_si512((__m512i*)(raw + 16));
            return *this;
        }
        // MGATHERS
        UME_FORCE_INLINE SIMDVec_u & gather(SIMDVecMask<32> const & mask, uint32_t* baseAddr, uint32_t* indices) {
            alignas(64) uint32_t raw[32] = {
                baseAddr[indices[0]], baseAddr[indices[1]],
                baseAddr[indices[2]], baseAddr[indices[3]],
                baseAddr[indices[4]], baseAddr[indices[5]],
                baseAddr[indices[6]], baseAddr[indices[7]],
                baseAddr[indices[8]], baseAddr[indices[9]],
                baseAddr[indices[10]], baseAddr[indices[11]],
                baseAddr[indices[12]], baseAddr[indices[13]],
                baseAddr[indices[14]], baseAddr[indices[15]],
                baseAddr[indices[16]], baseAddr[indices[17]] ,
                baseAddr[indices[18]], baseAddr[indices[19]] ,
                baseAddr[indices[20]], baseAddr[indices[21]] ,
                baseAddr[indices[22]], baseAddr[indices[23]] ,
                baseAddr[indices[24]], baseAddr[indices[25]] ,
                baseAddr[indices[26]], baseAddr[indices[27]] ,
                baseAddr[indices[28]], baseAddr[indices[29]] ,
                baseAddr[indices[30]], baseAddr[indices[31]] };
            return *this;
        }
        // GATHERV
        UME_FORCE_INLINE SIMDVec_u & gather(uint32_t* baseAddr, SIMDVec_u const & indices) {
            alignas(64) uint32_t rawIndices[32];
            alignas(64) uint32_t rawData[32];
            _mm512_store_si512((__m512i*) rawIndices, indices.mVec[0]);
            _mm512_store_si512((__m512i*) (rawIndices + 16), indices.mVec[1]);
            rawData[0] = baseAddr[rawIndices[0]];
            rawData[1] = baseAddr[rawIndices[1]];
            rawData[2] = baseAddr[rawIndices[2]];
            rawData[3] = baseAddr[rawIndices[3]];
            rawData[4] = baseAddr[rawIndices[4]];
            rawData[5] = baseAddr[rawIndices[5]];
            rawData[6] = baseAddr[rawIndices[6]];
            rawData[7] = baseAddr[rawIndices[7]];
            rawData[8] = baseAddr[rawIndices[8]];
            rawData[9] = baseAddr[rawIndices[9]];
            rawData[10] = baseAddr[rawIndices[10]];
            rawData[11] = baseAddr[rawIndices[11]];
            rawData[12] = baseAddr[rawIndices[12]];
            rawData[13] = baseAddr[rawIndices[13]];
            rawData[14] = baseAddr[rawIndices[14]];
            rawData[15] = baseAddr[rawIndices[15]];
            rawData[16] = baseAddr[rawIndices[16]];
            rawData[17] = baseAddr[rawIndices[17]];
            rawData[18] = baseAddr[rawIndices[18]];
            rawData[19] = baseAddr[rawIndices[19]];
            rawData[20] = baseAddr[rawIndices[20]];
            rawData[21] = baseAddr[rawIndices[21]];
            rawData[22] = baseAddr[rawIndices[22]];
            rawData[23] = baseAddr[rawIndices[23]];
            rawData[24] = baseAddr[rawIndices[24]];
            rawData[25] = baseAddr[rawIndices[25]];
            rawData[26] = baseAddr[rawIndices[26]];
            rawData[27] = baseAddr[rawIndices[27]];
            rawData[28] = baseAddr[rawIndices[28]];
            rawData[29] = baseAddr[rawIndices[29]];
            rawData[30] = baseAddr[rawIndices[30]];
            rawData[31] = baseAddr[rawIndices[31]];
            mVec[0] = _mm512_load_si512((__m512i*)rawData);
            mVec[1] = _mm512_load_si512((__m512i*)(rawData + 16));
            return *this;
        }
        // MGATHERV
        UME_FORCE_INLINE SIMDVec_u & gather(SIMDVecMask<32> const & mask, uint32_t* baseAddr, SIMDVec_u const & indices) {
            alignas(64) uint32_t rawIndices[32];
            alignas(64) uint32_t rawData[32];
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            _mm512_store_si512((__m512i*) rawIndices, indices.mVec[0]);
            _mm512_store_si512((__m512i*) (rawIndices + 16), indices.mVec[1]);
            rawData[0] = baseAddr[rawIndices[0]];
            rawData[1] = baseAddr[rawIndices[1]];
            rawData[2] = baseAddr[rawIndices[2]];
            rawData[3] = baseAddr[rawIndices[3]];
            rawData[4] = baseAddr[rawIndices[4]];
            rawData[5] = baseAddr[rawIndices[5]];
            rawData[6] = baseAddr[rawIndices[6]];
            rawData[7] = baseAddr[rawIndices[7]];
            rawData[8] = baseAddr[rawIndices[8]];
            rawData[9] = baseAddr[rawIndices[9]];
            rawData[10] = baseAddr[rawIndices[10]];
            rawData[11] = baseAddr[rawIndices[11]];
            rawData[12] = baseAddr[rawIndices[12]];
            rawData[13] = baseAddr[rawIndices[13]];
            rawData[14] = baseAddr[rawIndices[14]];
            rawData[15] = baseAddr[rawIndices[15]];
            rawData[16] = baseAddr[rawIndices[16]];
            rawData[17] = baseAddr[rawIndices[17]];
            rawData[18] = baseAddr[rawIndices[18]];
            rawData[19] = baseAddr[rawIndices[19]];
            rawData[20] = baseAddr[rawIndices[20]];
            rawData[21] = baseAddr[rawIndices[21]];
            rawData[22] = baseAddr[rawIndices[22]];
            rawData[23] = baseAddr[rawIndices[23]];
            rawData[24] = baseAddr[rawIndices[24]];
            rawData[25] = baseAddr[rawIndices[25]];
            rawData[26] = baseAddr[rawIndices[26]];
            rawData[27] = baseAddr[rawIndices[27]];
            rawData[28] = baseAddr[rawIndices[28]];
            rawData[29] = baseAddr[rawIndices[29]];
            rawData[30] = baseAddr[rawIndices[30]];
            rawData[31] = baseAddr[rawIndices[31]];
            mVec[0] = _mm512_mask_load_epi32(mVec[0], m0, rawData);
            mVec[1] = _mm512_mask_load_epi32(mVec[1], m1, rawData + 16);
            return *this;
        }
        // SCATTERS
        UME_FORCE_INLINE uint32_t* scatter(uint32_t* baseAddr, uint32_t* indices) {
            alignas(64) uint32_t rawIndices[32] = { 
                indices[0],  indices[1],  indices[2],  indices[3],
                indices[4],  indices[5],  indices[6],  indices[7],
                indices[8],  indices[9],  indices[10], indices[11],
                indices[12], indices[13], indices[14], indices[15],
                indices[16], indices[17], indices[18], indices[19],
                indices[20], indices[21], indices[22], indices[23],
                indices[24], indices[25], indices[26], indices[27],
                indices[28], indices[29], indices[30], indices[31] };
            __m512i t0 = _mm512_load_si512((__m512i *) rawIndices);
            __m512i t1 = _mm512_load_si512((__m512i *)rawIndices);
            _mm512_i32scatter_epi32(baseAddr, t0, mVec[0], 4);
            _mm512_i32scatter_epi32(baseAddr, t1, mVec[1], 4);
            return baseAddr;
        }
        // MSCATTERS
        UME_FORCE_INLINE uint32_t* scatter(SIMDVecMask<32> const & mask, uint32_t* baseAddr, uint32_t* indices) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            alignas(64) uint32_t rawIndices[32] = { 
                indices[0], indices[1], indices[2], indices[3],
                indices[4], indices[5], indices[6], indices[7],
                indices[8],  indices[9],  indices[10], indices[11],
                indices[12], indices[13], indices[14], indices[15],
                indices[16], indices[17], indices[18], indices[19],
                indices[20], indices[21], indices[22], indices[23],
                indices[24], indices[25], indices[26], indices[27],
                indices[28], indices[29], indices[30], indices[31] };
            __m512i t0 = _mm512_mask_load_epi32(_mm512_set1_epi32(0), m0, (__m512i *) rawIndices);
            __m512i t1 = _mm512_mask_load_epi32(_mm512_set1_epi32(0), m1, (__m512i *) (rawIndices + 16));
            _mm512_mask_i32scatter_epi32(baseAddr, m0, t0, mVec[0], 4);
            _mm512_mask_i32scatter_epi32(baseAddr, m1, t1, mVec[1], 4);
            return baseAddr;
        }
        // SCATTERV
        UME_FORCE_INLINE uint32_t* scatter(uint32_t* baseAddr, SIMDVec_u const & indices) {
            _mm512_i32scatter_epi32(baseAddr, indices.mVec[0], mVec[0], 4);
            _mm512_i32scatter_epi32(baseAddr + 16, indices.mVec[1], mVec[1], 4);
            return baseAddr;
        }
        // MSCATTERV
        UME_FORCE_INLINE uint32_t* scatter(SIMDVecMask<32> const & mask, uint32_t* baseAddr, SIMDVec_u const & indices) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            _mm512_mask_i32scatter_epi32(baseAddr,      m0, indices.mVec[0], mVec[0], 4);
            _mm512_mask_i32scatter_epi32(baseAddr + 16, m1, indices.mVec[1], mVec[1], 4);
            return baseAddr;
        }
        // LSHV
        UME_FORCE_INLINE SIMDVec_u lsh(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_sllv_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_sllv_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator<< (SIMDVec_u const & b) const {
            return lsh(b);
        }
        // MLSHV
        UME_FORCE_INLINE SIMDVec_u lsh(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_sllv_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_sllv_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // LSHS
        UME_FORCE_INLINE SIMDVec_u lsh(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_sllv_epi32(mVec[0], t0);
            __m512i t2 = _mm512_sllv_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator<< (uint32_t b) const {
            return lsh(b);
        }
        // MLSHS
        UME_FORCE_INLINE SIMDVec_u lsh(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_sllv_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_sllv_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // LSHVA
        // MLSHVA
        // LSHSA
        // MLSHSA
        // RSHV
        UME_FORCE_INLINE SIMDVec_u rsh(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_srlv_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_srlv_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_u operator>> (SIMDVec_u const & b) const {
            return rsh(b);
        }
        // MRSHV
        UME_FORCE_INLINE SIMDVec_u rsh(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_srlv_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_srlv_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // RSHS
        UME_FORCE_INLINE SIMDVec_u rsh(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_srlv_epi32(mVec[0], t0);
            __m512i t2 = _mm512_srlv_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_u operator>> (uint32_t b) const {
            return rsh(b);
        }
        // MRSHS
        UME_FORCE_INLINE SIMDVec_u rsh(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_srlv_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_srlv_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // RSHVA
        // MRSHVA
        // RSHSA
        // MRSHSA
        // ROLV
        UME_FORCE_INLINE SIMDVec_u rol(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_rolv_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_rolv_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MROLV
        UME_FORCE_INLINE SIMDVec_u rol(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_rolv_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_rolv_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // ROLS
        UME_FORCE_INLINE SIMDVec_u rol(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_rolv_epi32(mVec[0], t0);
            __m512i t2 = _mm512_rolv_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // MROLS
        UME_FORCE_INLINE SIMDVec_u rol(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_rolv_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_rolv_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // ROLVA
        UME_FORCE_INLINE SIMDVec_u & rola(SIMDVec_u const & b) {
            mVec[0] = _mm512_rolv_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_rolv_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        // MROLVA
        UME_FORCE_INLINE SIMDVec_u & rola(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_rolv_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_rolv_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // ROLSA
        UME_FORCE_INLINE SIMDVec_u & rola(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_rolv_epi32(mVec[0], t0);
            mVec[1] = _mm512_rolv_epi32(mVec[1], t0);
            return *this;
        }
        // MROLSA
        UME_FORCE_INLINE SIMDVec_u & rola(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_rolv_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_rolv_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // RORV
        UME_FORCE_INLINE SIMDVec_u ror(SIMDVec_u const & b) const {
            __m512i t0 = _mm512_rorv_epi32(mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_rorv_epi32(mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // MRORV
        UME_FORCE_INLINE SIMDVec_u ror(SIMDVecMask<32> const & mask, SIMDVec_u const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_mask_rorv_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512i t1 = _mm512_mask_rorv_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_u(t0, t1);
        }
        // RORS
        UME_FORCE_INLINE SIMDVec_u ror(uint32_t b) const {
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_rorv_epi32(mVec[0], t0);
            __m512i t2 = _mm512_rorv_epi32(mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // MRORS
        UME_FORCE_INLINE SIMDVec_u ror(SIMDVecMask<32> const & mask, uint32_t b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            __m512i t1 = _mm512_mask_rorv_epi32(mVec[0], m0, mVec[0], t0);
            __m512i t2 = _mm512_mask_rorv_epi32(mVec[1], m1, mVec[1], t0);
            return SIMDVec_u(t1, t2);
        }
        // RORVA
        UME_FORCE_INLINE SIMDVec_u & rora(SIMDVec_u const & b) {
            mVec[0] = _mm512_rorv_epi32(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_rorv_epi32(mVec[1], b.mVec[1]);
            return *this;
        }
        // MRORVA
        UME_FORCE_INLINE SIMDVec_u & rora(SIMDVecMask<32> const & mask, SIMDVec_u const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_rorv_epi32(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_rorv_epi32(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // RORSA
        UME_FORCE_INLINE SIMDVec_u & rora(uint32_t b) {
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_rorv_epi32(mVec[0], t0);
            mVec[1] = _mm512_rorv_epi32(mVec[1], t0);
            return *this;
        }
        // MRORSA
        UME_FORCE_INLINE SIMDVec_u & rora(SIMDVecMask<32> const & mask, uint32_t b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_set1_epi32(b);
            mVec[0] = _mm512_mask_rorv_epi32(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_rorv_epi32(mVec[1], m1, mVec[1], t0);
            return *this;
        }

        // PACK
        UME_FORCE_INLINE SIMDVec_u & pack(SIMDVec_u<uint32_t, 16> const & a, SIMDVec_u<uint32_t, 16> const & b) {
            mVec[0] = a.mVec;
            mVec[1] = b.mVec;
            return *this;
        }
        // PACKLO
        UME_FORCE_INLINE SIMDVec_u & packlo(SIMDVec_u<uint32_t, 16> const & a) {
            mVec[0] = a.mVec;
            return *this;
        }
        // PACKHI
        UME_FORCE_INLINE SIMDVec_u & packhi(SIMDVec_u<uint32_t, 16> const & b) {
            mVec[1] = b.mVec;
            return *this;
        }
        // UNPACK
        UME_FORCE_INLINE void unpack(SIMDVec_u<uint32_t, 16> & a, SIMDVec_u<uint32_t, 16> & b) const {
            a.mVec = mVec[0];
            b.mVec = mVec[1];
        }
        // UNPACKLO
        UME_FORCE_INLINE SIMDVec_u<uint32_t, 16> unpacklo() const {
            return SIMDVec_u<uint32_t, 16>(mVec[0]);
        }
        // UNPACKHI
        UME_FORCE_INLINE SIMDVec_u<uint32_t, 16> unpackhi() const {
            return SIMDVec_u<uint32_t, 16>(mVec[1]);
        }

        // PROMOTE
        // - 
        // DEGRADE
        UME_FORCE_INLINE operator SIMDVec_u<uint16_t, 32>() const;

        // UTOI
        UME_FORCE_INLINE operator SIMDVec_i<int32_t, 32> () const;
        // UTOF
        UME_FORCE_INLINE operator SIMDVec_f<float, 32>() const;

    };

}
}

#endif
