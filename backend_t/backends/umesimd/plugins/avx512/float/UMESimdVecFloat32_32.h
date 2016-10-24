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

#ifndef UME_SIMD_VEC_FLOAT32_32_H_
#define UME_SIMD_VEC_FLOAT32_32_H_

#include <type_traits>
#include <immintrin.h>

#include "../../../UMESimdInterface.h"

namespace UME {
namespace SIMD {

    template<>
    class SIMDVec_f<float, 32> :
        public SIMDVecFloatInterface<
            SIMDVec_f<float, 32>,
            SIMDVec_u<uint32_t, 32>,
            SIMDVec_i<int32_t, 32>,
            float,
            32,
            uint32_t,
            SIMDVecMask<32>,
            SIMDSwizzle<32>> ,
        public SIMDVecPackableInterface<
            SIMDVec_f<float, 32>,
            SIMDVec_f<float, 16>>
    {
        friend class SIMDVec_u<uint32_t, 32>;
        friend class SIMDVec_i<int32_t, 32>;


    private:
        __m512 mVec[2];

        UME_FORCE_INLINE SIMDVec_f(__m512 const & x0, __m512 const & x1) {
            mVec[0] = x0;
            mVec[1] = x1;
        }

    public:
        constexpr static uint32_t length() { return 32; }
        constexpr static uint32_t alignment() { return 64; }

        // ZERO-CONSTR
        UME_FORCE_INLINE SIMDVec_f() {}
        // SET-CONSTR
        UME_FORCE_INLINE SIMDVec_f(float f) {
            mVec[0] = _mm512_set1_ps(f);
            mVec[1] = mVec[0];
        }
        // This constructor is used to force types other than SCALAR_TYPES
        // to be promoted to SCALAR_TYPE instead of SCALAR_TYPE*. This prevents
        // ambiguity between SET-CONSTR and LOAD-CONSTR.
        template<typename T>
        UME_FORCE_INLINE SIMDVec_f(
            T i, 
            typename std::enable_if< std::is_same<T, int>::value && 
                                    !std::is_same<T, float>::value,
                                    void*>::type = nullptr)
        : SIMDVec_f(static_cast<float>(i)) {}
        // LOAD-CONSTR
        UME_FORCE_INLINE explicit SIMDVec_f(float const *p) { this->load(p); }
        // FULL-CONSTR
        UME_FORCE_INLINE SIMDVec_f(float f0,  float f1,  float f2,  float f3,
                         float f4,  float f5,  float f6,  float f7, 
                         float f8,  float f9,  float f10, float f11,
                         float f12, float f13, float f14, float f15,
                         float f16, float f17, float f18, float f19,
                         float f20, float f21, float f22, float f23,
                         float f24, float f25, float f26, float f27,
                         float f28, float f29, float f30, float f31) {
            mVec[0] = _mm512_setr_ps(f0, f1, f2,  f3,  f4,  f5,  f6,  f7,
                                  f8, f9, f10, f11, f12, f13, f14, f15 );

            mVec[1] = _mm512_setr_ps(f16, f17, f18, f19, f20, f21, f22, f23,
                                     f24, f25, f26, f27, f28, f29, f30, f31);
        }
        // EXTRACT
        UME_FORCE_INLINE float extract(uint32_t index) const {
            alignas(64) float raw[16];
            uint32_t t0;
            if (index < 16) {
                t0 = index;
                _mm512_store_ps(raw, mVec[0]);
            }
            else {
                t0 = index - 16;
                _mm512_store_ps(raw, mVec[1]);
            }
            return raw[t0];
        }
        UME_FORCE_INLINE float operator[] (uint32_t index) const {
            return extract(index);
        }

        // INSERT
        UME_FORCE_INLINE SIMDVec_f & insert(uint32_t index, float value) {
            alignas(64) float raw[16];
            uint32_t t0;
            if (index < 16) {
                t0 = index;
                _mm512_store_ps(raw, mVec[0]);
            }
            else {
                t0 = index - 16;
                _mm512_store_ps(raw, mVec[1]);
            }
            raw[t0] = value;
            if (index < 16) {
                mVec[0] = _mm512_load_ps(raw);
            }
            else {
                mVec[1] = _mm512_load_ps(raw);
            }
            return *this;
        }
        UME_FORCE_INLINE IntermediateIndex<SIMDVec_f, float> operator[] (uint32_t index) {
            return IntermediateIndex<SIMDVec_f, float>(index, static_cast<SIMDVec_f &>(*this));
        }

        // Override Mask Access operators
#if defined(USE_PARENTHESES_IN_MASK_ASSIGNMENT)
        UME_FORCE_INLINE IntermediateMask<SIMDVec_f, float, SIMDVecMask<32>> operator() (SIMDVecMask<32> const & mask) {
            return IntermediateMask<SIMDVec_f, float, SIMDVecMask<32>>(mask, static_cast<SIMDVec_f &>(*this));
        }
#else
        UME_FORCE_INLINE IntermediateMask<SIMDVec_f, float, SIMDVecMask<32>> operator[] (SIMDVecMask<32> const & mask) {
            return IntermediateMask<SIMDVec_f, float, SIMDVecMask<32>>(mask, static_cast<SIMDVec_f &>(*this));
        }
#endif

        // ****************************************************************************************
        // Overloading Interface functions starts here!
        // ****************************************************************************************

        //(Initialization)
        // ASSIGNV
        UME_FORCE_INLINE SIMDVec_f & assign(SIMDVec_f const & b) {
            mVec[0] = b.mVec[0];
            mVec[1] = b.mVec[1];
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator= (SIMDVec_f const & b) {
            return assign(b);
        }
        // MASSIGNV
        UME_FORCE_INLINE SIMDVec_f & assign(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_mov_ps(mVec[0], m0, b.mVec[0]);
            mVec[1] = _mm512_mask_mov_ps(mVec[1], m1, b.mVec[1]);
            return *this;
        }
        // ASSIGNS
        UME_FORCE_INLINE SIMDVec_f & assign(float b) {
            mVec[0] = _mm512_set1_ps(b);
            mVec[1] = mVec[0];
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator= (float b) {
            return assign(b);
        }
        // MASSIGNS
        UME_FORCE_INLINE SIMDVec_f & assign(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_mov_ps(mVec[0], m0, t0);
            mVec[1] = _mm512_mask_mov_ps(mVec[1], m1, t0);
            return *this;
        }

        //(Memory�access)
        //�LOAD
        UME_FORCE_INLINE SIMDVec_f & load(float const * p) {
            mVec[0] = _mm512_loadu_ps(p);
            mVec[1] = _mm512_loadu_ps(p + 16);
            return *this;
        }
        // MLOAD
        UME_FORCE_INLINE SIMDVec_f & load(SIMDVecMask<32> const & mask, float const * p) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_loadu_ps(mVec[0], m0, p);
            mVec[1] = _mm512_mask_loadu_ps(mVec[1], m1, p + 16);
            return *this;
        }
        // LOADA
        UME_FORCE_INLINE SIMDVec_f & loada(float const * p) {
            mVec[0] = _mm512_load_ps(p);
            mVec[1] = _mm512_load_ps(p + 16);
            return *this;
        }
        // MLOADA
        UME_FORCE_INLINE SIMDVec_f & loada(SIMDVecMask<32> const & mask, float const * p) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_loadu_ps(mVec[0], m0, p);
            mVec[1] = _mm512_mask_loadu_ps(mVec[1], m1, p + 16);
            return *this;
        }
        //�STORE
        UME_FORCE_INLINE float* store(float * p) const {
            _mm512_storeu_ps(p, mVec[0]);
            _mm512_storeu_ps(p + 16, mVec[1]);
            return p;
        }
        // MSTORE
        UME_FORCE_INLINE float * store(SIMDVecMask<32> const & mask, float * p) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            _mm512_mask_storeu_ps(p, m0, mVec[0]);
            _mm512_mask_storeu_ps(p + 16, m1, mVec[1]);
            return p;
        }
        // STOREA
        UME_FORCE_INLINE float* storea(float * p) const {
            _mm512_store_ps(p, mVec[0]);
            _mm512_store_ps(p + 16, mVec[1]);
            return p;
        }
        // MSTOREA
        UME_FORCE_INLINE float* storea(SIMDVecMask<32> const & mask, float * p) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            _mm512_mask_store_ps(p, m0, mVec[0]);
            _mm512_mask_store_ps(p + 16, m1, mVec[1]);
            return p;
        }
        // ADDV
        UME_FORCE_INLINE SIMDVec_f add(SIMDVec_f const & b) const {
            __m512 t0 = _mm512_add_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_add_ps(mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_f operator+ (SIMDVec_f const & b) const {
            return add(b);
        }
        // MADDV
        UME_FORCE_INLINE SIMDVec_f add(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_add_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_add_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        //�ADDS
        UME_FORCE_INLINE SIMDVec_f add(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_add_ps(mVec[0], t0);
            __m512 t2 = _mm512_add_ps(mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_f operator+ (float b) const {
            return add(b);
        }
        //�MADDS
        UME_FORCE_INLINE SIMDVec_f add(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_add_ps(mVec[0], m0, mVec[0], t0);
            __m512 t2 = _mm512_mask_add_ps(mVec[1], m1, mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        // ADDVA
        UME_FORCE_INLINE SIMDVec_f & adda(SIMDVec_f const & b) {
            mVec[0] = _mm512_add_ps(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_add_ps(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator+= (SIMDVec_f const & b) {
            return adda(b);
        }
        // MADDVA
        UME_FORCE_INLINE SIMDVec_f & adda(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_add_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_add_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        //�ADDSA
        UME_FORCE_INLINE SIMDVec_f & adda(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_add_ps(mVec[0], t0);
            mVec[1] = _mm512_add_ps(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator+= (float b) {
            return adda(b);
        }
        //�MADDSA
        UME_FORCE_INLINE SIMDVec_f & adda(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_add_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_add_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        //�SADDV
        //�MSADDV
        //�SADDS
        //�MSADDS
        //�SADDVA
        //�MSADDVA
        //�SADDSA
        //�MSADDSA
        //�POSTINC
        UME_FORCE_INLINE SIMDVec_f postinc() {
            __m512 t0 = mVec[0];
            __m512 t1 = mVec[1];
            __m512 t2 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_add_ps(mVec[0], t2);
            mVec[1] = _mm512_add_ps(mVec[1], t2);
            return SIMDVec_f(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_f operator++ (int) {
            __m512 t0 = mVec[0];
            __m512 t1 = mVec[1];
            __m512 t2 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_add_ps(mVec[0], t2);
            mVec[1] = _mm512_add_ps(mVec[1], t2);
            return SIMDVec_f(t0, t1);
        }
        //�MPOSTINC
        UME_FORCE_INLINE SIMDVec_f postinc(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = mVec[0];
            __m512 t1 = mVec[1];
            __m512 t2 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_mask_add_ps(mVec[0], m0, mVec[0], t2);
            mVec[1] = _mm512_mask_add_ps(mVec[1], m1, mVec[1], t2);
            return SIMDVec_f(t0, t1);
        }
        //�PREFINC
        UME_FORCE_INLINE SIMDVec_f & prefinc() {
            __m512 t0 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_add_ps(mVec[0], t0);
            mVec[1] = _mm512_add_ps(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator++ () {
            __m512 t0 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_add_ps(mVec[0], t0);
            mVec[1] = _mm512_add_ps(mVec[1], t0);
            return *this;
        }
        //�MPREFINC
        UME_FORCE_INLINE SIMDVec_f & prefinc(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_mask_add_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_add_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        //�SUBV
        UME_FORCE_INLINE SIMDVec_f sub(SIMDVec_f const & b) const {
            __m512 t0 = _mm512_sub_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_sub_ps(mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_f operator- (SIMDVec_f const & b) const {
            return sub(b);
        }
        //�MSUBV
        UME_FORCE_INLINE SIMDVec_f sub(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_sub_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_sub_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        //�SUBS
        UME_FORCE_INLINE SIMDVec_f sub(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_sub_ps(mVec[0], t0);
            __m512 t2 = _mm512_sub_ps(mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_f operator- (float b) const {
            return sub(b);
        }
        //�MSUBS
        UME_FORCE_INLINE SIMDVec_f sub(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_sub_ps(mVec[0], m0, mVec[0], t0);
            __m512 t2 = _mm512_mask_sub_ps(mVec[1], m1, mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        //�SUBVA
        UME_FORCE_INLINE SIMDVec_f & suba(SIMDVec_f const & b) {
            mVec[0] = _mm512_sub_ps(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_sub_ps(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator-=(SIMDVec_f const & b) {
            return suba(b);
        }
        //�MSUBVA
        UME_FORCE_INLINE SIMDVec_f & suba(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_sub_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_sub_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        //�SUBSA
        UME_FORCE_INLINE SIMDVec_f & suba(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_sub_ps(mVec[0], t0);
            mVec[1] = _mm512_sub_ps(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator-= (float b) {
            return suba(b);
        }
        //�MSUBSA
        UME_FORCE_INLINE SIMDVec_f & suba(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_sub_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_sub_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        //�SSUBV
        //�MSSUBV
        //�SSUBS
        //�MSSUBS
        //�SSUBVA
        //�MSSUBVA
        //�SSUBSA
        //�MSSUBSA
        //�SUBFROMV
        UME_FORCE_INLINE SIMDVec_f subfrom(SIMDVec_f const & b) const {
            __m512 t0 = _mm512_sub_ps(b.mVec[0], mVec[0]);
            __m512 t1 = _mm512_sub_ps(b.mVec[1], mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        //�MSUBFROMV
        UME_FORCE_INLINE SIMDVec_f subfrom(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_sub_ps(b.mVec[0], m0, b.mVec[0], mVec[0]);
            __m512 t1 = _mm512_mask_sub_ps(b.mVec[1], m1, b.mVec[1], mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        //�SUBFROMS
        UME_FORCE_INLINE SIMDVec_f subfrom(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1= _mm512_sub_ps(t0, mVec[0]);
            __m512 t2 = _mm512_sub_ps(t0, mVec[1]);
            return SIMDVec_f(t1, t2);
        }
        //�MSUBFROMS
        UME_FORCE_INLINE SIMDVec_f subfrom(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_sub_ps(t0, m0, t0, mVec[0]);
            __m512 t2 = _mm512_mask_sub_ps(t0, m1, t0, mVec[1]);
            return SIMDVec_f(t1, t2);
        }
        //�SUBFROMVA
        UME_FORCE_INLINE SIMDVec_f & subfroma(SIMDVec_f const & b) {
            mVec[0] = _mm512_sub_ps(b.mVec[0], mVec[0]);
            mVec[1] = _mm512_sub_ps(b.mVec[1], mVec[1]);
            return *this;
        }
        //�MSUBFROMVA
        UME_FORCE_INLINE SIMDVec_f & subfroma(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_sub_ps(b.mVec[0], m0, b.mVec[0], mVec[0]);
            mVec[1] = _mm512_mask_sub_ps(b.mVec[1], m1, b.mVec[1], mVec[1]);
            return *this;
        }
        //�SUBFROMSA
        UME_FORCE_INLINE SIMDVec_f & subfroma(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_sub_ps(t0, mVec[0]);
            mVec[1] = _mm512_sub_ps(t0, mVec[1]);
            return *this;
        }
        //�MSUBFROMSA
        UME_FORCE_INLINE SIMDVec_f & subfroma(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_sub_ps(t0, m0, t0, mVec[0]);
            mVec[1] = _mm512_mask_sub_ps(t0, m1, t0, mVec[1]);
            return *this;
        }
        //�POSTDEC
        UME_FORCE_INLINE SIMDVec_f postdec() {
            __m512 t0 = mVec[0];
            __m512 t1 = mVec[1];
            __m512 t2 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_sub_ps(mVec[0], t2);
            mVec[1] = _mm512_sub_ps(mVec[1], t2);
            return SIMDVec_f(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_f operator-- (int) {
            __m512 t0 = mVec[0];
            __m512 t1 = mVec[1];
            __m512 t2 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_sub_ps(mVec[0], t2);
            mVec[1] = _mm512_sub_ps(mVec[1], t2);
            return SIMDVec_f(t0, t1);
        }
        //�MPOSTDEC
        UME_FORCE_INLINE SIMDVec_f postdec(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = mVec[0];
            __m512 t1 = mVec[1];
            __m512 t2 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_mask_sub_ps(mVec[0], m0, mVec[0], t2);
            mVec[1] = _mm512_mask_sub_ps(mVec[1], m1, mVec[1], t2);
            return SIMDVec_f(t0, t1);
        }
        //�PREFDEC
        UME_FORCE_INLINE SIMDVec_f & prefdec() {
            __m512 t0 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_sub_ps(mVec[0], t0);
            mVec[1] = _mm512_sub_ps(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator-- () {
            __m512 t0 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_sub_ps(mVec[0], t0);
            mVec[1] = _mm512_sub_ps(mVec[1], t0);
            return *this;
        }
        //�MPREFDEC
        UME_FORCE_INLINE SIMDVec_f & prefdec(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(1.0f);
            mVec[0] = _mm512_mask_sub_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_sub_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        //�MULV
        UME_FORCE_INLINE SIMDVec_f mul(SIMDVec_f const & b) const {
            __m512 t0 = _mm512_mul_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mul_ps(mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_f operator* (SIMDVec_f const & b) const {
            return mul(b);
        }
        //�MMULV
        UME_FORCE_INLINE SIMDVec_f mul(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_mul_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_mul_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        //�MULS
        UME_FORCE_INLINE SIMDVec_f mul(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mul_ps(mVec[0], t0);
            __m512 t2 = _mm512_mul_ps(mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_f operator* (float b) const {
            return mul(b);
        }
        // MMULS
        UME_FORCE_INLINE SIMDVec_f mul(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_mul_ps(mVec[0], m0, mVec[0], t0);
            __m512 t2 = _mm512_mask_mul_ps(mVec[1], m1, mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        // MULVA
        UME_FORCE_INLINE SIMDVec_f & mula(SIMDVec_f const & b) {
            mVec[0] = _mm512_mul_ps(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mul_ps(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator*= (SIMDVec_f const & b) {
            return mula(b);
        }
        // MMULVA
        UME_FORCE_INLINE SIMDVec_f & mula(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_mul_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_mul_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // MULSA
        UME_FORCE_INLINE SIMDVec_f & mula(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mul_ps(mVec[0], t0);
            mVec[1] = _mm512_mul_ps(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator*= (float b) {
            return mula(b);
        }
        // MMULSA
        UME_FORCE_INLINE SIMDVec_f & mula(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_mul_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_mul_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // DIVV
        UME_FORCE_INLINE SIMDVec_f div(SIMDVec_f const & b) const {
            __m512 t0 = _mm512_div_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_div_ps(mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        UME_FORCE_INLINE SIMDVec_f operator/ (SIMDVec_f const & b) const {
            return div(b);
        }
        // MDIVV
        UME_FORCE_INLINE SIMDVec_f div(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_div_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_div_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // DIVS
        UME_FORCE_INLINE SIMDVec_f div(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_div_ps(mVec[0], t0);
            __m512 t2 = _mm512_div_ps(mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_f operator/ (float b) const {
            return div(b);
        }
        // MDIVS
        UME_FORCE_INLINE SIMDVec_f div(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_div_ps(mVec[0], m0, mVec[0], t0);
            __m512 t2 = _mm512_mask_div_ps(mVec[1], m1, mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        // DIVVA
        UME_FORCE_INLINE SIMDVec_f & diva(SIMDVec_f const & b) {
            mVec[0] = _mm512_div_ps(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_div_ps(mVec[1], b.mVec[1]);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator/= (SIMDVec_f const & b) {
            return diva(b);
        }
        // MDIVVA
        UME_FORCE_INLINE SIMDVec_f & diva(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_div_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_div_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // DIVSA
        UME_FORCE_INLINE SIMDVec_f & diva(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_div_ps(mVec[0], t0);
            mVec[1] = _mm512_div_ps(mVec[1], t0);
            return *this;
        }
        UME_FORCE_INLINE SIMDVec_f & operator/= (float b) {
            return diva(b);
        }
        // MDIVSA
        UME_FORCE_INLINE SIMDVec_f & diva(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_div_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_div_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // RCP
        UME_FORCE_INLINE SIMDVec_f rcp() const {
            __m512 t0 = _mm512_rcp14_ps(mVec[0]);
            __m512 t1 = _mm512_rcp14_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MRCP
        UME_FORCE_INLINE SIMDVec_f rcp(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_rcp14_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_rcp14_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // RCPS
        UME_FORCE_INLINE SIMDVec_f rcp(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_rcp14_ps(mVec[0]);
            __m512 t2 = _mm512_rcp14_ps(mVec[1]);
            __m512 t3 = _mm512_mul_ps(t0, t1);
            __m512 t4 = _mm512_mul_ps(t0, t2);
            return SIMDVec_f(t3, t4);
        }
        // MRCPS
        UME_FORCE_INLINE SIMDVec_f rcp(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_rcp14_ps(mVec[0], m0, mVec[0]);
            __m512 t2 = _mm512_mask_rcp14_ps(mVec[1], m1, mVec[1]);
            __m512 t3 = _mm512_mask_mul_ps(mVec[0], m0, t0, t1);
            __m512 t4 = _mm512_mask_mul_ps(mVec[1], m1, t0, t2);
            return SIMDVec_f(t3, t4);
        }
        // RCPA
        UME_FORCE_INLINE SIMDVec_f & rcpa() {
            mVec[0] = _mm512_rcp14_ps(mVec[0]);
            mVec[1] = _mm512_rcp14_ps(mVec[1]);
            return *this;
        }
        // MRCPA
        UME_FORCE_INLINE SIMDVec_f & rcpa(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_rcp14_ps(mVec[0], m0, mVec[0]);
            mVec[1] = _mm512_mask_rcp14_ps(mVec[1], m1, mVec[1]);
            return *this;
        }
        // RCPSA
        UME_FORCE_INLINE SIMDVec_f & rcpa(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_rcp14_ps(mVec[0]);
            __m512 t2 = _mm512_rcp14_ps(mVec[1]);
            mVec[0] = _mm512_mul_ps(t0, t1);
            mVec[1] = _mm512_mul_ps(t0, t2);
            return *this;
        }
        // MRCPSA
        UME_FORCE_INLINE SIMDVec_f & rcpa(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_rcp14_ps(mVec[0], m0, mVec[0]);
            __m512 t2 = _mm512_mask_rcp14_ps(mVec[1], m1, mVec[1]);
            mVec[0] = _mm512_mask_mul_ps(mVec[0], m0, t0, t1);
            mVec[1] = _mm512_mask_mul_ps(mVec[1], m1, t0, t2);
            return *this;
        }
        // CMPEQV
        UME_FORCE_INLINE SIMDVecMask<32> cmpeq(SIMDVec_f const & b) const {
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], b.mVec[0], 0);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], b.mVec[1], 0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator== (SIMDVec_f const & b) const {
            return cmpeq(b);
        }
        // CMPEQS
        UME_FORCE_INLINE SIMDVecMask<32> cmpeq(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], t0, 0);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], t0, 0);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator== (float b) const {
            return cmpeq(b);
        }
        // CMPNEV
        UME_FORCE_INLINE SIMDVecMask<32> cmpne(SIMDVec_f const & b) const {
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], b.mVec[0], 12);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], b.mVec[1], 12);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator!= (SIMDVec_f const & b) const {
            return cmpne(b);
        }
        // CMPNES
        UME_FORCE_INLINE SIMDVecMask<32> cmpne(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], t0, 12);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], t0, 12);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator!= (float b) const {
            return cmpne(b);
        }
        // CMPGTV
        UME_FORCE_INLINE SIMDVecMask<32> cmpgt(SIMDVec_f const & b) const {
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], b.mVec[0], 30);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], b.mVec[1], 30);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator> (SIMDVec_f const & b) const {
            return cmpgt(b);
        }
        // CMPGTS
        UME_FORCE_INLINE SIMDVecMask<32> cmpgt(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], t0, 30);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], t0, 30);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator> (float b) const {
            return cmpgt(b);
        }
        // CMPLTV
        UME_FORCE_INLINE SIMDVecMask<32> cmplt(SIMDVec_f const & b) const {
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], b.mVec[0], 17);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], b.mVec[1], 17);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator< (SIMDVec_f const & b) const {
            return cmplt(b);
        }
        // CMPLTS
        UME_FORCE_INLINE SIMDVecMask<32> cmplt(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], t0, 17);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], t0, 17);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator< (float b) const {
            return cmplt(b);
        }
        // CMPGEV
        UME_FORCE_INLINE SIMDVecMask<32> cmpge(SIMDVec_f const & b) const {
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], b.mVec[0], 29);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], b.mVec[1], 29);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator>= (SIMDVec_f const & b) const {
            return cmpge(b);
        }
        // CMPGES
        UME_FORCE_INLINE SIMDVecMask<32> cmpge(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], t0, 29);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], t0, 29);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator>= (float b) const {
            return cmpge(b);
        }
        // CMPLEV
        UME_FORCE_INLINE SIMDVecMask<32> cmple(SIMDVec_f const & b) const {
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], b.mVec[0], 18);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], b.mVec[1], 18);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator<= (SIMDVec_f const & b) const {
            return cmple(b);
        }
        // CMPLES
        UME_FORCE_INLINE SIMDVecMask<32> cmple(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], t0, 18);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], t0, 18);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
        }
        UME_FORCE_INLINE SIMDVecMask<32> operator<= (float b) const {
            return cmple(b);
        }
        // CMPEV
        UME_FORCE_INLINE bool cmpe(SIMDVec_f const & b) const {
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], b.mVec[0], 0);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], b.mVec[1], 0);
            return (m0 == 0xFFFF) && (m1 == 0xFFFF);
        }
        // CMPES
        UME_FORCE_INLINE bool cmpe(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __mmask16 m0 = _mm512_cmp_ps_mask(mVec[0], t0, 0);
            __mmask16 m1 = _mm512_cmp_ps_mask(mVec[1], t0, 0);
            return (m0 == 0xFFFF) && (m1 == 0xFFFF);
        }
        // BLENDV
        UME_FORCE_INLINE SIMDVec_f blend(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_mov_ps(mVec[0], m0, b.mVec[0]);
            __m512 t1 = _mm512_mask_mov_ps(mVec[1], m1, b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // BLENDS
        UME_FORCE_INLINE SIMDVec_f blend(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_mov_ps(mVec[0], m0, t0);
            __m512 t2 = _mm512_mask_mov_ps(mVec[1], m1, t0);
            return SIMDVec_f(t1, t2);
        }
        // SWIZZLE
        // SWIZZLEA
        // HADD
        UME_FORCE_INLINE float hadd() const {
            float t0 = _mm512_reduce_add_ps(mVec[0]);
            t0 += _mm512_reduce_add_ps(mVec[1]);
            return t0;
        }
        // MHADD
        UME_FORCE_INLINE float hadd(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            float t0 = _mm512_mask_reduce_add_ps(m0, mVec[0]);
            t0 += _mm512_mask_reduce_add_ps(m1, mVec[1]);
            return t0;
        }
        // HADDS
        UME_FORCE_INLINE float hadd(float b) const {
            float t0 = b;
            t0 += _mm512_reduce_add_ps(mVec[0]);
            t0 += _mm512_reduce_add_ps(mVec[1]);
            return t0;
        }
        // MHADDS
        UME_FORCE_INLINE float hadd(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            float t0 = b;
            t0 += _mm512_mask_reduce_add_ps(m0, mVec[0]);
            t0 += _mm512_mask_reduce_add_ps(m1, mVec[1]);
            return t0;
        }
        // HMUL
        UME_FORCE_INLINE float hmul() const {
            float t0 = _mm512_reduce_mul_ps(mVec[0]);
            t0 *= _mm512_reduce_mul_ps(mVec[1]);
            return t0;
        }
        // MHMUL
        UME_FORCE_INLINE float hmul(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            float t0 = _mm512_mask_reduce_mul_ps(m0, mVec[0]);
            t0 *= _mm512_mask_reduce_mul_ps(m0, mVec[1]);
            return t0;
        }
        // HMULS
        UME_FORCE_INLINE float hmul(float b) const {
            float t0 = b;
            t0 *= _mm512_reduce_mul_ps(mVec[0]);
            t0 *= _mm512_reduce_mul_ps(mVec[1]);
            return t0;
        }
        // MHMULS
        UME_FORCE_INLINE float hmul(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            float t0 = b;
            t0 *= _mm512_mask_reduce_mul_ps(m0, mVec[0]);
            t0 *= _mm512_mask_reduce_mul_ps(m1, mVec[1]);
            return t0;
        }
        // FMULADDV
        UME_FORCE_INLINE SIMDVec_f fmuladd(SIMDVec_f const & b, SIMDVec_f const & c) const {
            __m512 t0 = _mm512_fmadd_ps(mVec[0], b.mVec[0], c.mVec[0]);
            __m512 t1 = _mm512_fmadd_ps(mVec[1], b.mVec[1], c.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MFMULADDV
        UME_FORCE_INLINE SIMDVec_f fmuladd(SIMDVecMask<32> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_fmadd_ps(mVec[0], m0, b.mVec[0], c.mVec[0]);
            __m512 t1 = _mm512_mask_fmadd_ps(mVec[1], m1, b.mVec[1], c.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // FMULSUBV
        UME_FORCE_INLINE SIMDVec_f fmulsub(SIMDVec_f const & b, SIMDVec_f const & c) const {
            __m512 t0 = _mm512_fmsub_ps(mVec[0], b.mVec[0], c.mVec[0]);
            __m512 t1 = _mm512_fmsub_ps(mVec[1], b.mVec[1], c.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MFMULSUBV
        UME_FORCE_INLINE SIMDVec_f fmulsub(SIMDVecMask<32> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_fmsub_ps(mVec[0], m0, b.mVec[0], c.mVec[0]);
            __m512 t1 = _mm512_mask_fmsub_ps(mVec[1], m1, b.mVec[1], c.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // FADDMULV
        UME_FORCE_INLINE SIMDVec_f faddmul(SIMDVec_f const & b, SIMDVec_f const & c) const {
            __m512 t0 = _mm512_add_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_add_ps(mVec[1], b.mVec[1]);
            __m512 t2 = _mm512_mul_ps(t0, c.mVec[0]);
            __m512 t3 = _mm512_mul_ps(t1, c.mVec[1]);
            return SIMDVec_f(t2, t3);
        }
        // MFADDMULV
        UME_FORCE_INLINE SIMDVec_f faddmul(SIMDVecMask<32> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_add_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_add_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            __m512 t2 = _mm512_mask_mul_ps(mVec[0], m0, t0, c.mVec[0]);
            __m512 t3 = _mm512_mask_mul_ps(mVec[1], m1, t1, c.mVec[1]);
            return SIMDVec_f(t2, t3);
        }
        // FSUBMULV
        UME_FORCE_INLINE SIMDVec_f fsubmul(SIMDVec_f const & b, SIMDVec_f const & c) const {
            __m512 t0 = _mm512_sub_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_sub_ps(mVec[1], b.mVec[1]);
            __m512 t2 = _mm512_mul_ps(t0, c.mVec[0]);
            __m512 t3 = _mm512_mul_ps(t1, c.mVec[1]);
            return SIMDVec_f(t2, t3);
        }
        // MFSUBMULV
        UME_FORCE_INLINE SIMDVec_f fsubmul(SIMDVecMask<32> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_sub_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_sub_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            __m512 t2 = _mm512_mask_mul_ps(mVec[0], m0, t0, c.mVec[0]);
            __m512 t3 = _mm512_mask_mul_ps(mVec[1], m1, t1, c.mVec[1]);
            return SIMDVec_f(t2, t3);
        }
        // MAXV
        UME_FORCE_INLINE SIMDVec_f max(SIMDVec_f const & b) const {
            __m512 t0 = _mm512_max_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_max_ps(mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MMAXV
        UME_FORCE_INLINE SIMDVec_f max(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_max_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_max_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MAXS
        UME_FORCE_INLINE SIMDVec_f max(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_max_ps(mVec[0], t0);
            __m512 t2 = _mm512_max_ps(mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        // MMAXS
        UME_FORCE_INLINE SIMDVec_f max(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_max_ps(mVec[0], m0, mVec[0], t0);
            __m512 t2 = _mm512_mask_max_ps(mVec[1], m1, mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        // MAXVA
        UME_FORCE_INLINE SIMDVec_f & maxa(SIMDVec_f const & b) {
            mVec[0] = _mm512_max_ps(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_max_ps(mVec[1], b.mVec[1]);
            return *this;
        }
        // MMAXVA
        UME_FORCE_INLINE SIMDVec_f & maxa(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_max_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_max_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // MAXSA
        UME_FORCE_INLINE SIMDVec_f & maxa(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_max_ps(mVec[0], t0);
            mVec[1] = _mm512_max_ps(mVec[1], t0);
            return *this;
        }
        // MMAXSA
        UME_FORCE_INLINE SIMDVec_f & maxa(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_max_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_max_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // MINV
        UME_FORCE_INLINE SIMDVec_f min(SIMDVec_f const & b) const {
            __m512 t0 = _mm512_min_ps(mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_min_ps(mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MMINV
        UME_FORCE_INLINE SIMDVec_f min(SIMDVecMask<32> const & mask, SIMDVec_f const & b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_min_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            __m512 t1 = _mm512_mask_min_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MINS
        UME_FORCE_INLINE SIMDVec_f min(float b) const {
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_min_ps(mVec[0], t0);
            __m512 t2 = _mm512_min_ps(mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        // MMINS
        UME_FORCE_INLINE SIMDVec_f min(SIMDVecMask<32> const & mask, float b) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            __m512 t1 = _mm512_mask_min_ps(mVec[0], m0, mVec[0], t0);
            __m512 t2 = _mm512_mask_min_ps(mVec[1], m1, mVec[1], t0);
            return SIMDVec_f(t1, t2);
        }
        // MINVA
        UME_FORCE_INLINE SIMDVec_f & mina(SIMDVec_f const & b) {
            mVec[0] = _mm512_min_ps(mVec[0], b.mVec[0]);
            mVec[1] = _mm512_min_ps(mVec[1], b.mVec[1]);
            return *this;
        }
        // MMINVA
        UME_FORCE_INLINE SIMDVec_f & mina(SIMDVecMask<32> const & mask, SIMDVec_f const & b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_min_ps(mVec[0], m0, mVec[0], b.mVec[0]);
            mVec[1] = _mm512_mask_min_ps(mVec[1], m1, mVec[1], b.mVec[1]);
            return *this;
        }
        // MINSA
        UME_FORCE_INLINE SIMDVec_f & mina(float b) {
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_min_ps(mVec[0], t0);
            mVec[1] = _mm512_min_ps(mVec[1], t0);
            return *this;
        }
        // MMINSA
        UME_FORCE_INLINE SIMDVec_f & mina(SIMDVecMask<32> const & mask, float b) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_set1_ps(b);
            mVec[0] = _mm512_mask_min_ps(mVec[0], m0, mVec[0], t0);
            mVec[1] = _mm512_mask_min_ps(mVec[1], m1, mVec[1], t0);
            return *this;
        }
        // HMAX
        UME_FORCE_INLINE float hmax() const {
            float t0 = _mm512_reduce_max_ps(mVec[0]);
            float t1 = _mm512_reduce_max_ps(mVec[1]);
            return t0 > t1 ? t0 : t1;
        }
        // MHMAX
        UME_FORCE_INLINE float hmax(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            float t0 = _mm512_mask_reduce_max_ps(m0, mVec[0]);
            float t1 = _mm512_mask_reduce_max_ps(m1, mVec[1]);
            return t0 > t1 ? t0 : t1;
        }
        // IMAX
        // HMIN
        UME_FORCE_INLINE float hmin() const {
            float t0 = _mm512_reduce_min_ps(mVec[0]);
            float t1 = _mm512_reduce_min_ps(mVec[1]);
            return t0 < t1 ? t0 : t1;
        }
        // MHMIN
        UME_FORCE_INLINE float hmin(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            float t0 = _mm512_mask_reduce_min_ps(m0, mVec[0]);
            float t1 = _mm512_mask_reduce_min_ps(m1, mVec[1]);
            return t0 < t1 ? t0 : t1;
        }
        // IMIN
        // MIMIN
        // GATHERS
        /*UME_FORCE_INLINE SIMDVec_f & gather(float* baseAddr, uint32_t* indices) {
            alignas(64) float raw[8] = { baseAddr[indices[0]], baseAddr[indices[1]], baseAddr[indices[2]], baseAddr[indices[3]] };
            mVec = _mm512_load_ps(raw);
            return *this;
        }*/
        // MGATHERS
        /*UME_FORCE_INLINE SIMDVec_f & gather(SIMDVecMask<32> const & mask, float* baseAddr, uint32_t* indices) {
            alignas(64) float raw[8] = { baseAddr[indices[0]], baseAddr[indices[1]], baseAddr[indices[2]], baseAddr[indices[3]] };
            mVec = _mm512_mask_load_ps(mVec, mask.mMask, raw);
            return *this;
        }*/
        // GATHERV
        // MGATHERV
        // SCATTERS
        // MSCATTERS
        // SCATTERV
        // MSCATTERV
        // NEG
        UME_FORCE_INLINE SIMDVec_f neg() const {
            __m512 t0 = _mm512_setzero_ps();
            __m512 t1 = _mm512_sub_ps(t0, mVec[0]);
            __m512 t2 = _mm512_sub_ps(t0, mVec[1]);
            return SIMDVec_f(t1, t2);
        }
        UME_FORCE_INLINE SIMDVec_f operator- () const {
            return neg();
        }
        // MNEG
        UME_FORCE_INLINE SIMDVec_f neg(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_setzero_ps();
            __m512 t1 = _mm512_mask_sub_ps(mVec[0], m0, t0, mVec[0]);
            __m512 t2 = _mm512_mask_sub_ps(mVec[1], m1, t0, mVec[1]);
            return SIMDVec_f(t1, t2);
        }
        // NEGA
        UME_FORCE_INLINE SIMDVec_f & nega() {
            __m512 t0 = _mm512_setzero_ps();
            mVec[0] = _mm512_sub_ps(t0, mVec[0]);
            mVec[1] = _mm512_sub_ps(t0, mVec[1]);
            return *this;
        }
        // MNEGA
        UME_FORCE_INLINE SIMDVec_f & nega(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_setzero_ps();
            mVec[0] = _mm512_mask_sub_ps(mVec[0], m0, t0, mVec[0]);
            mVec[1] = _mm512_mask_sub_ps(mVec[1], m1, t0, mVec[1]);
            return *this;
        }
        // ABS
        UME_FORCE_INLINE SIMDVec_f abs() const {
            __m512 t0 = _mm512_abs_ps(mVec[0]);
            __m512 t1 = _mm512_abs_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MABS
        UME_FORCE_INLINE SIMDVec_f abs(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_abs_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_abs_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // ABSA
        UME_FORCE_INLINE SIMDVec_f & absa() {
            mVec[0] = _mm512_abs_ps(mVec[0]);
            mVec[1] = _mm512_abs_ps(mVec[1]);
            return *this;
        }
        // MABSA
        UME_FORCE_INLINE SIMDVec_f & absa(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_abs_ps(mVec[0], m0, mVec[0]);
            mVec[1] = _mm512_mask_abs_ps(mVec[1], m1, mVec[1]);
            return *this;
        }
        // CMPEQRV
        // CMPEQRS
        // SQR
        UME_FORCE_INLINE SIMDVec_f sqr() const {
            __m512 t0 = _mm512_mul_ps(mVec[0], mVec[0]);
            __m512 t1 = _mm512_mul_ps(mVec[1], mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MSQR
        UME_FORCE_INLINE SIMDVec_f sqr(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_mul_ps(mVec[0], m0, mVec[0], mVec[0]);
            __m512 t1 = _mm512_mask_mul_ps(mVec[1], m1, mVec[1], mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // SQRA
        UME_FORCE_INLINE SIMDVec_f & sqra() {
            mVec[0] = _mm512_mul_ps(mVec[0], mVec[0]);
            mVec[1] = _mm512_mul_ps(mVec[1], mVec[1]);
            return *this;
        }
        // MSQRA
        UME_FORCE_INLINE SIMDVec_f & sqra(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_mul_ps(mVec[0], m0, mVec[0], mVec[0]);
            mVec[1] = _mm512_mask_mul_ps(mVec[1], m1, mVec[1], mVec[1]);
            return *this;
        }
        // SQRT
        UME_FORCE_INLINE SIMDVec_f sqrt() const {
            __m512 t0 = _mm512_sqrt_ps(mVec[0]);
            __m512 t1 = _mm512_sqrt_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MSQRT
        UME_FORCE_INLINE SIMDVec_f sqrt(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_sqrt_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_sqrt_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // SQRTA
        UME_FORCE_INLINE SIMDVec_f & sqrta() {
            mVec[0] = _mm512_sqrt_ps(mVec[0]);
            mVec[1] = _mm512_sqrt_ps(mVec[1]);
            return *this;
        }
        // MSQRTA
        UME_FORCE_INLINE SIMDVec_f & sqrta(SIMDVecMask<32> const & mask) {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            mVec[0] = _mm512_mask_sqrt_ps(mVec[0], m0, mVec[0]);
            mVec[1] = _mm512_mask_sqrt_ps(mVec[1], m1, mVec[1]);
            return *this;
        }
        // POWV
        // MPOWV
        // POWS
        // MPOWS
        // ROUND
        UME_FORCE_INLINE SIMDVec_f round() const {
            __m512 t0 = _mm512_roundscale_ps(mVec[0], 0);
            __m512 t1 = _mm512_roundscale_ps(mVec[1], 0);
            return SIMDVec_f(t0, t1);
        }
        // MROUND
        UME_FORCE_INLINE SIMDVec_f round(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_roundscale_ps(mVec[0], m0, mVec[0], 0);
            __m512 t1 = _mm512_mask_roundscale_ps(mVec[1], m1, mVec[1], 0);
            return SIMDVec_f(t0, t1);
        }
        // TRUNC
        SIMDVec_i<int32_t, 32> trunc() const {
            __m512i t0 = _mm512_cvttps_epi32(mVec[0]);
            __m512i t1 = _mm512_cvttps_epi32(mVec[1]);
            return SIMDVec_i<int32_t, 32>(t0, t1);
        }
        //�MTRUNC
        SIMDVec_i<int32_t, 32> trunc(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512i t0 = _mm512_setzero_epi32();
            __m512i t1 = _mm512_mask_cvttps_epi32(t0, m0, mVec[0]);
            __m512i t2 = _mm512_mask_cvttps_epi32(t0, m1, mVec[1]);
            return SIMDVec_i<int32_t, 32>(t1, t2);
        }
        // FLOOR
        UME_FORCE_INLINE SIMDVec_f floor() const {
            __m512 t0 = _mm512_floor_ps(mVec[0]);
            __m512 t1 = _mm512_floor_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MFLOOR
        UME_FORCE_INLINE SIMDVec_f floor(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_floor_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_floor_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // CEIL
        UME_FORCE_INLINE SIMDVec_f ceil() const {
            __m512 t0 = _mm512_ceil_ps(mVec[0]);
            __m512 t1 = _mm512_ceil_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // MCEIL
        UME_FORCE_INLINE SIMDVec_f ceil(SIMDVecMask<32> const & mask) const {
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_ceil_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_ceil_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        }
        // ISFIN
        UME_FORCE_INLINE SIMDVecMask<32> isfin() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = _mm512_fpclass_ps_mask(mVec[0], 0x08);
            __mmask16 m1 = _mm512_fpclass_ps_mask(mVec[1], 0x08);
            __mmask16 m2 = _mm512_fpclass_ps_mask(mVec[0], 0x10);
            __mmask16 m3 = _mm512_fpclass_ps_mask(mVec[1], 0x10);
            __mmask16 m4 = (~m0) & (~m1);
            __mmask16 m5 = (~m2) & (~m3);
            __mmask32 m6 = m4 | (m5 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m6;
            return ret_mask;
#else
            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7F800000);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __mmask16 t5 = _mm512_cmpneq_epi32_mask(t3, t2);
            __mmask16 t6 = _mm512_cmpneq_epi32_mask(t4, t2);
            __mmask32 t7 = t5 | (t6 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t7;
            return ret_mask;
#endif
        }
        // ISINF
        UME_FORCE_INLINE SIMDVecMask<32> isinf() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = _mm512_fpclass_ps_mask(mVec[0], 0x08);
            __mmask16 m1 = _mm512_fpclass_ps_mask(mVec[1], 0x08);
            __mmask16 m2 = _mm512_fpclass_ps_mask(mVec[0], 0x10);
            __mmask16 m3 = _mm512_fpclass_ps_mask(mVec[1], 0x10);
            __mmask16 m4 = m0 | m1;
            __mmask16 m5 = m2 | m3;
            __mmask32 m6 = m4 | (m5 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m6;
            return ret_mask;
#else
            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7FFFFFFF);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __m512i t5 = _mm512_set1_epi32(0x7F800000);
            __mmask16 t6 = _mm512_cmpeq_epi32_mask(t3, t5);
            __mmask16 t7 = _mm512_cmpeq_epi32_mask(t4, t5);
            __mmask32 t8 = t6 | (t7 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t8;
            return ret_mask;
#endif
        }
        // ISAN
        UME_FORCE_INLINE SIMDVecMask<32> isan() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = _mm512_fpclass_ps_mask(mVec[0], 0x01);
            __mmask16 m1 = _mm512_fpclass_ps_mask(mVec[1], 0x01);
            __mmask16 m2 = _mm512_fpclass_ps_mask(mVec[0], 0x80);
            __mmask16 m3 = _mm512_fpclass_ps_mask(mVec[1], 0x80);
            __mmask16 m4 = (~m0) & (~m2);
            __mmask16 m5 = (~m1) & (~m3);
            __mmask32 m6 = m4 | (m5 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m6;
            return ret_mask;
#else
            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7F800000);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __mmask16 t5 = _mm512_cmpneq_epi32_mask(t3, t2);   // is finite
            __mmask16 t6 = _mm512_cmpneq_epi32_mask(t4, t2);

            __m512i t7 = _mm512_set1_epi32(0x007FFFFF);
            __m512i t8 = _mm512_and_epi32(t7, t0);
            __m512i t9 = _mm512_and_epi32(t7, t1);
            __m512i t10 = _mm512_setzero_epi32();
            __mmask16 t11 = _mm512_cmpeq_epi32_mask(t3, t2);
            __mmask16 t12 = _mm512_cmpeq_epi32_mask(t4, t2);
            __mmask16 t13 = _mm512_cmpneq_epi32_mask(t8, t10);
            __mmask16 t14 = _mm512_cmpneq_epi32_mask(t9, t10);
            __mmask16 t15 = ~(t11 & t13);                         // is not NaN
            __mmask16 t16 = ~(t12 & t14);                         // is not NaN

            __mmask16 t17 = t5 & t15;
            __mmask16 t18 = t6 & t16;
            __mmask32 t19 = t17 | (t18 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t19;
            return ret_mask;
#endif
        }
        // ISNAN
        UME_FORCE_INLINE SIMDVecMask<32> isnan() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = _mm512_fpclass_ps_mask(mVec[0], 0x01);
            __mmask16 m1 = _mm512_fpclass_ps_mask(mVec[1], 0x01);
            __mmask16 m2 = _mm512_fpclass_ps_mask(mVec[0], 0x80);
            __mmask16 m3 = _mm512_fpclass_ps_mask(mVec[1], 0x80);
            __mmask16 m4 = m0 | m2;
            __mmask16 m5 = m1 | m3;
            __mmask32 m6 = m4 | (m5 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m6;
            return ret_mask;
#else
            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7F800000);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __m512i t5 = _mm512_set1_epi32(0xFF800000);
            __m512i t6 = _mm512_andnot_epi32(t5, t0);
            __m512i t7 = _mm512_andnot_epi32(t5, t1);
            __m512i t8 = _mm512_setzero_epi32();
            __mmask16 t9 = _mm512_cmpeq_epi32_mask(t3, t2);
            __mmask16 t10 = _mm512_cmpeq_epi32_mask(t4, t2);
            __mmask16 t11 = _mm512_cmpneq_epi32_mask(t6, t8);
            __mmask16 t12 = _mm512_cmpneq_epi32_mask(t7, t8);
            __mmask16 t13 = t9 & t11;
            __mmask16 t14 = t10 & t12;
            __mmask32 t15 = t13 | (t14 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t15;
            return ret_mask;
#endif
        }
        // ISNORM
        UME_FORCE_INLINE SIMDVecMask<32> isnorm() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = ~_mm512_fpclass_ps_mask(mVec[0], 0x01);
            __mmask16 m1 = ~_mm512_fpclass_ps_mask(mVec[0], 0x02);
            __mmask16 m2 = ~_mm512_fpclass_ps_mask(mVec[0], 0x04);
            __mmask16 m3 = ~_mm512_fpclass_ps_mask(mVec[0], 0x08);
            __mmask16 m4 = ~_mm512_fpclass_ps_mask(mVec[0], 0x10);
            __mmask16 m5 = ~_mm512_fpclass_ps_mask(mVec[0], 0x20);
            __mmask16 m6 = ~_mm512_fpclass_ps_mask(mVec[0], 0x80);
            __mmask16 m7 = m0 & m1 & m2 & m3 & m4 & m5 & m6;
            m0 = ~_mm512_fpclass_ps_mask(mVec[1], 0x01);
            m1 = ~_mm512_fpclass_ps_mask(mVec[1], 0x02);
            m2 = ~_mm512_fpclass_ps_mask(mVec[1], 0x04);
            m3 = ~_mm512_fpclass_ps_mask(mVec[1], 0x08);
            m4 = ~_mm512_fpclass_ps_mask(mVec[1], 0x10);
            m5 = ~_mm512_fpclass_ps_mask(mVec[1], 0x20);
            m6 = ~_mm512_fpclass_ps_mask(mVec[1], 0x80);
            __mmask16 m8 = m0 & m1 & m2 & m3 & m4 & m5 & m6;
            __mmask32 m9 = m7 | (m8 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m9;
            return ret_mask;
#else

            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7F800000);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __mmask16 t5 = _mm512_cmpneq_epi32_mask(t3, t2);
            __mmask16 t6 = _mm512_cmpneq_epi32_mask(t4, t2);   // is not finite

            __m512i t7 = _mm512_set1_epi32(0x007FFFFF);
            __m512i t8 = _mm512_and_epi32(t7, t0);
            __m512i t9 = _mm512_and_epi32(t7, t1);
            __m512i t10 = _mm512_setzero_epi32();
            __mmask16 t11 = _mm512_cmpeq_epi32_mask(t3, t2);
            __mmask16 t12 = _mm512_cmpeq_epi32_mask(t4, t2);
            __mmask16 t13 = _mm512_cmpneq_epi32_mask(t8, t10);
            __mmask16 t14 = _mm512_cmpneq_epi32_mask(t9, t10);
            __mmask16 t15 = ~(t11 & t13);
            __mmask16 t16 = ~(t12 & t14);                         // is not NaN

            __mmask16 t17 = _mm512_cmpeq_epi32_mask(t3, t10);
            __mmask16 t18 = _mm512_cmpeq_epi32_mask(t4, t10);
            __mmask16 t19 = _mm512_cmpneq_epi32_mask(t8, t10);
            __mmask16 t20 = _mm512_cmpneq_epi32_mask(t9, t10);
            __mmask16 t21 = ~(t17 & t19);
            __mmask16 t22 = ~(t18 & t20);                      // is not subnormal

            __m512i t23 = _mm512_or_epi32(t3, t8);
            __m512i t24 = _mm512_or_epi32(t4, t9);
            __mmask16 t25 = _mm512_cmpneq_epi32_mask(t10, t23);
            __mmask16 t26 = _mm512_cmpneq_epi32_mask(t10, t24);      // is not zero

            __mmask16 t27 = (t5 & t15 & t21 & t25);
            __mmask16 t28 = (t6 & t16 & t22 & t26);
            __mmask32 t29 = t27 | (t28 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t29;
            return ret_mask;
#endif
        }
        // ISSUB
        UME_FORCE_INLINE SIMDVecMask<32> issub() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = _mm512_fpclass_ps_mask(mVec[0], 0x20);
            __mmask16 m1 = _mm512_fpclass_ps_mask(mVec[1], 0x20);
            __mmask32 m2 = m0 | (m1 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m2;
            return ret_mask;
#else
            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7F800000);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __m512i t5 = _mm512_setzero_epi32();
            __mmask16 t6 = _mm512_cmpeq_epi32_mask(t3, t5);
            __mmask16 t7 = _mm512_cmpeq_epi32_mask(t4, t5);
            __m512i t8 = _mm512_set1_epi32(0x007FFFFF);
            __m512i t9 = _mm512_and_epi32(t0, t8);
            __m512i t10 = _mm512_and_epi32(t1, t8);
            __mmask16 t11 = _mm512_cmpneq_epi32_mask(t9, t5);
            __mmask16 t12 = _mm512_cmpneq_epi32_mask(t10, t5);
            __mmask16 t13 = t6 & t11;
            __mmask16 t14 = t7 & t12;
            __mmask32 t15 = t13 | (t14 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t15;
            return ret_mask;
#endif
        }
        // ISZERO
        UME_FORCE_INLINE SIMDVecMask<32> iszero() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = _mm512_fpclass_ps_mask(mVec[0], 0x02);
            __mmask16 m1 = _mm512_fpclass_ps_mask(mVec[1], 0x02);
            __mmask16 m2 = _mm512_fpclass_ps_mask(mVec[0], 0x04);
            __mmask16 m3 = _mm512_fpclass_ps_mask(mVec[1], 0x04);
            __mmask16 m4 = m0 | m2;
            __mmask16 m5 = m1 | m3;
            __mmask32 m6 = m4 | (m5 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m6;
            return ret_mask;
#else
            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7FFFFFFF);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __mmask16 t5 = _mm512_cmpeq_epi32_mask(t3, _mm512_setzero_epi32());
            __mmask16 t6 = _mm512_cmpeq_epi32_mask(t4, _mm512_setzero_epi32());
            __mmask32 t7 = t5 | (t6 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t7;
            return ret_mask;
#endif
        }
        // ISZEROSUB
        UME_FORCE_INLINE SIMDVecMask<32> iszerosub() const {
#if defined(__AVX512DQ__)
            __mmask16 m0 = _mm512_fpclass_ps_mask(mVec[0], 0x02);
            __mmask16 m1 = _mm512_fpclass_ps_mask(mVec[0], 0x04);
            __mmask16 m2 = _mm512_fpclass_ps_mask(mVec[0], 0x20);
            __mmask16 m3 = m0 | m1 | m2;
            m0 = _mm512_fpclass_ps_mask(mVec[1], 0x02);
            m1 = _mm512_fpclass_ps_mask(mVec[1], 0x04);
            m2 = _mm512_fpclass_ps_mask(mVec[1], 0x20);
            __mmask16 m4 = m0 | m1 | m2;
            __mmask32 m5 = m3 | (m4 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = m5;
            return ret_mask;
#else
            __m512i t0 = _mm512_castps_si512(mVec[0]);
            __m512i t1 = _mm512_castps_si512(mVec[1]);
            __m512i t2 = _mm512_set1_epi32(0x7F800000);
            __m512i t3 = _mm512_and_epi32(t0, t2);
            __m512i t4 = _mm512_and_epi32(t1, t2);
            __m512i t5 = _mm512_setzero_epi32();
            __mmask16 t6 = _mm512_cmpeq_epi32_mask(t3, t5);
            __mmask16 t7 = _mm512_cmpeq_epi32_mask(t4, t5);
            __mmask32 t8 = t6 | (t7 << 16);
            SIMDVecMask<32> ret_mask;
            ret_mask.mMask = t8;
            return ret_mask;
#endif
        }
        
        // EXP
        UME_FORCE_INLINE SIMDVec_f exp() const {
        #if defined(UME_USE_SVML)
            __m512 t0 = _mm512_exp_ps(mVec[0]);
            __m512 t1 = _mm512_exp_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::expf<SIMDVec_f, SIMDVec_u<uint32_t, 32>>(*this);
        #endif
        }
        // MEXP
        UME_FORCE_INLINE SIMDVec_f exp(SIMDVecMask<32> const & mask) const {
        #if defined(UME_USE_SVML)
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_exp_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_exp_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::expf<SIMDVec_f, SIMDVec_u<uint32_t, 32>, SIMDVecMask<32>>(mask, *this);
        #endif
        }
        // LOG
        UME_FORCE_INLINE SIMDVec_f log() const {
        #if defined(UME_USE_SVML)
            __m512 t0 = _mm512_log_ps(mVec[0]);
            __m512 t1 = _mm512_log_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::logf<SIMDVec_f, SIMDVec_u<uint32_t, 32>>(*this);
        #endif
        }
        // MLOG
        UME_FORCE_INLINE SIMDVec_f log(SIMDVecMask<32> const & mask) const {
        #if defined(UME_USE_SVML)
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_log_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_log_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::logf<SIMDVec_f, SIMDVec_u<uint32_t, 32>, SIMDVecMask<32>>(mask, *this);
        #endif
        }
        // LOG2
        // MLOG2
        // LOG10
        // MLOG10
        // SIN
        UME_FORCE_INLINE SIMDVec_f sin() const {
        #if defined(UME_USE_SVML)
            __m512 t0 = _mm512_sin_ps(mVec[0]);
            __m512 t1 = _mm512_sin_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::sinf<SIMDVec_f, SIMDVec_i<int32_t, 32>, SIMDVecMask<32>>(*this);
        #endif
        }
        // MSIN
        UME_FORCE_INLINE SIMDVec_f sin(SIMDVecMask<32> const & mask) const {
        #if defined(UME_USE_SVML)
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_sin_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_sin_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::sinf<SIMDVec_f, SIMDVec_i<int32_t, 32>, SIMDVecMask<32>>(mask, *this);
        #endif
        }
        // COS
        UME_FORCE_INLINE SIMDVec_f cos() const {
        #if defined(UME_USE_SVML)
            __m512 t0 = _mm512_cos_ps(mVec[0]);
            __m512 t1 = _mm512_cos_ps(mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::cosf<SIMDVec_f, SIMDVec_i<int32_t, 32>, SIMDVecMask<32>>(*this);
        #endif
        }
        // MCOS
        UME_FORCE_INLINE SIMDVec_f cos(SIMDVecMask<32> const & mask) const {
        #if defined(UME_USE_SVML)
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            __m512 t0 = _mm512_mask_cos_ps(mVec[0], m0, mVec[0]);
            __m512 t1 = _mm512_mask_cos_ps(mVec[1], m1, mVec[1]);
            return SIMDVec_f(t0, t1);
        #else
            return VECTOR_EMULATION::cosf<SIMDVec_f, SIMDVec_i<int32_t, 32>, SIMDVecMask<32>>(mask, *this);
        #endif
        }
        // SINCOS
        UME_FORCE_INLINE void sincos(SIMDVec_f & sinvec, SIMDVec_f & cosvec) const {
        #if defined(UME_USE_SVML)
            alignas(64) float raw_cos0[16];
            alignas(64) float raw_cos1[16];
            sinvec.mVec[0] = _mm512_sincos_ps((__m512*)raw_cos0, mVec[0]);
            sinvec.mVec[1] = _mm512_sincos_ps((__m512*)raw_cos1, mVec[1]);
            cosvec.mVec[0] = _mm512_load_ps(raw_cos0);
            cosvec.mVec[1] = _mm512_load_ps(raw_cos1);
        #else
            VECTOR_EMULATION::sincosf<SIMDVec_f, SIMDVec_i<int32_t, 32>, SIMDVecMask<32>>(*this, sinvec, cosvec);
        #endif
        }
        // MSINCOS
        UME_FORCE_INLINE void sincos(SIMDVecMask<32> const & mask, SIMDVec_f & sinvec, SIMDVec_f & cosvec) const {
        #if defined(UME_USE_SVML)
            alignas(64) float raw_cos0[16];
            alignas(64) float raw_cos1[16];
            __mmask16 m0 = mask.mMask & 0x0000FFFF;
            __mmask16 m1 = (mask.mMask & 0xFFFF0000) >> 16;
            sinvec.mVec[0] = _mm512_mask_sincos_ps((__m512*)raw_cos0, mVec[0], mVec[0], m0, mVec[0]);
            sinvec.mVec[1] = _mm512_mask_sincos_ps((__m512*)raw_cos1, mVec[1], mVec[1], m1, mVec[1]);
            cosvec.mVec[0] = _mm512_load_ps(raw_cos0);
            cosvec.mVec[1] = _mm512_load_ps(raw_cos1);
        #else
            sinvec = SCALAR_EMULATION::MATH::sin<SIMDVec_f, SIMDVecMask<32>>(mask, *this);
            cosvec = SCALAR_EMULATION::MATH::cos<SIMDVec_f, SIMDVecMask<32>>(mask, *this);
        #endif
        }
        // TAN
        // MTAN
        // CTAN
        // MCTAN
        // PACK
        UME_FORCE_INLINE SIMDVec_f & pack(SIMDVec_f<float, 16> const & a, SIMDVec_f<float, 16> const & b) {
            mVec[0] = a.mVec;
            mVec[1] = b.mVec;
            return *this;
        }
        // PACKLO
        UME_FORCE_INLINE SIMDVec_f & packlo(SIMDVec_f<float, 16> const & a) {
            mVec[0] = a.mVec;
            return *this;
        }
        // PACKHI
        UME_FORCE_INLINE SIMDVec_f & packhi(SIMDVec_f<float, 16> const & b) {
            mVec[1] = b.mVec;
            return *this;
        }
        // UNPACK
        UME_FORCE_INLINE void unpack(SIMDVec_f<float, 16> & a, SIMDVec_f<float, 16> & b) const {
            a.mVec = mVec[0];
            b.mVec = mVec[1];
        }
        // UNPACKLO
        UME_FORCE_INLINE SIMDVec_f<float, 16> unpacklo() const {
            return SIMDVec_f<float, 16>(mVec[0]);
        }
        // UNPACKHI
        UME_FORCE_INLINE SIMDVec_f<float, 16> unpackhi() const {
            return SIMDVec_f<float, 16>(mVec[1]);
        }

        // PROMOTE
        // - 
        // DEGRADE
        // -

        // FTOU
        UME_FORCE_INLINE operator SIMDVec_u<uint32_t, 32>() const;
        // FTOI
        UME_FORCE_INLINE operator SIMDVec_i<int32_t, 32>() const;
    };
}
}

#endif
