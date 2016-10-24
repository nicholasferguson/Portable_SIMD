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

#ifndef UME_SIMD_VEC_UINT32_1_H_
#define UME_SIMD_VEC_UINT32_1_H_

#include <type_traits>
#include <immintrin.h>

#include "../../../UMESimdInterface.h"

namespace UME {
namespace SIMD {

    template<>
    class SIMDVec_u<uint32_t, 1> :
        public SIMDVecUnsignedInterface<
            SIMDVec_u<uint32_t, 1>, // DERIVED_UINT_VEC_TYPE
            uint32_t,                        // SCALAR_UINT_TYPE
            1,
            SIMDVecMask<1>,
            SIMDSwizzle<1>>
    {
    private:
        // This is the only data member and it is a low level representation of vector register.
        uint32_t mVec;

        friend class SIMDVec_i<int32_t, 1>;
        friend class SIMDVec_f<float, 1>;

        friend class SIMDVec_u<uint32_t, 2>;

    public:
        constexpr static uint32_t length() { return 1; }
        constexpr static uint32_t alignment() { return 4; }

        // ZERO-CONSTR
        inline SIMDVec_u() {}
        // SET-CONSTR
        inline SIMDVec_u(uint32_t i) {
            mVec = i;
        }
        // This constructor is used to force types other than SCALAR_TYPES
        // to be promoted to SCALAR_TYPE instead of SCALAR_TYPE*. This prevents
        // ambiguity between SET-CONSTR and LOAD-CONSTR.
        template<typename T>
        inline SIMDVec_u(
            T i, 
            typename std::enable_if< std::is_same<T, int>::value && 
                                    !std::is_same<T, uint32_t>::value,
                                    void*>::type = nullptr)
        : SIMDVec_u(static_cast<uint32_t>(i)) {}
        // LOAD-CONSTR
        inline explicit SIMDVec_u(uint32_t const *p) {
            mVec = p[0];
        }

        // EXTRACT
        inline uint32_t extract(uint32_t index) const {
            return mVec;
        }
        inline uint32_t operator[] (uint32_t index) const {
            return extract(index);
        }

        // INSERT
        inline SIMDVec_u & insert(uint32_t index, uint32_t value) {
            mVec = value;
            return *this;
        }
        inline IntermediateIndex<SIMDVec_u, uint32_t> operator[] (uint32_t index) {
            return IntermediateIndex<SIMDVec_u, uint32_t>(index, static_cast<SIMDVec_u &>(*this));
        }

        // Override Mask Access operators
#if defined(USE_PARENTHESES_IN_MASK_ASSIGNMENT)
        inline IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<1>> operator() (SIMDVecMask<1> const & mask) {
            return IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<1>>(mask, static_cast<SIMDVec_u &>(*this));
        }
#else
        inline IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<1>> operator[] (SIMDVecMask<1> const & mask) {
            return IntermediateMask<SIMDVec_u, uint32_t, SIMDVecMask<1>>(mask, static_cast<SIMDVec_u &>(*this));
        }
#endif

        // ASSIGNV
        inline SIMDVec_u & assign(SIMDVec_u const & src) {
            mVec = src.mVec;
            return *this;
        }
        inline SIMDVec_u & operator= (SIMDVec_u const & b) {
            return assign(b);
        }
        // MASSIGNV
        inline SIMDVec_u & assign(SIMDVecMask<1> const & mask, SIMDVec_u const & src) {
            if (mask.mMask == true) mVec = src.mVec;
            return *this;
        }
        // ASSIGNS
        inline SIMDVec_u & assign(uint32_t b) {
            mVec = b;
            return *this;
        }
        inline SIMDVec_u & operator= (uint32_t b) {
            return assign(b);
        }
        // MASSIGNS
        inline SIMDVec_u & assign(SIMDVecMask<1> const & mask, uint32_t b) {
            if(mask.mMask == true) mVec = b;
            return *this;
        }

        // PREFETCH0
        // PREFETCH1
        // PREFETCH2

        // LOAD
        inline SIMDVec_u & load(uint32_t const *p) {
            mVec = p[0];
            return *this;
        }
        // MLOAD
        inline SIMDVec_u & load(SIMDVecMask<1> const & mask, uint32_t const *p) {
            if (mask.mMask == true) mVec = p[0];
            return *this;
        }
        // LOADA
        inline SIMDVec_u & loada(uint32_t const *p) {
            mVec = p[0];
            return *this;
        }
        // MLOADA
        inline SIMDVec_u & loada(SIMDVecMask<1> const & mask, uint32_t const *p) {
            if (mask.mMask == true) mVec = p[0];
            return *this;
        }
        // STORE
        inline uint32_t* store(uint32_t* p) const {
            p[0] = mVec;
            return p;
        }
        // MSTORE
        inline uint32_t* store(SIMDVecMask<1> const & mask, uint32_t* p) const {
            if (mask.mMask == true) p[0] = mVec;
            return p;
        }
        // STOREA
        inline uint32_t* storea(uint32_t* p) const {
            p[0] = mVec;
            return p;
        }
        // MSTOREA
        inline uint32_t* storea(SIMDVecMask<1> const & mask, uint32_t* p) const {
            if (mask.mMask == true) p[0] = mVec;
            return p;
        }

        // BLENDV
        inline SIMDVec_u blend(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // BLENDS
        inline SIMDVec_u blend(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? b : mVec;
            return SIMDVec_u(t0);
        }
        // SWIZZLE
        // SWIZZLEA

        // ADDV
        inline SIMDVec_u add(SIMDVec_u const & b) const {
            uint32_t t0 = mVec + b.mVec;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator+ (SIMDVec_u const & b) const {
            return add(b);
        }
        // MADDV
        inline SIMDVec_u add(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec + b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // ADDS
        inline SIMDVec_u add(uint32_t b) const {
            uint32_t t0 = mVec + b;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator+ (uint32_t b) const {
            return add(b);
        }
        // MADDS
        inline SIMDVec_u add(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec + b : mVec;
            return SIMDVec_u(t0);
        }
        // ADDVA
        inline SIMDVec_u & adda(SIMDVec_u const & b) {
            mVec += b.mVec;
            return *this;
        }
        inline SIMDVec_u & operator+= (SIMDVec_u const & b) {
            return adda(b);
        }
        // MADDVA
        inline SIMDVec_u & adda(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            mVec = mask.mMask ? mVec + b.mVec : mVec;
            return *this;
        }
        // ADDSA
        inline SIMDVec_u & adda(uint32_t b) {
            mVec += b;
            return *this;
        }
        inline SIMDVec_u & operator+= (uint32_t b) {
            return adda(b);
        }
        // MADDSA
        inline SIMDVec_u & adda(SIMDVecMask<1> const & mask, uint32_t b) {
            mVec = mask.mMask ? mVec + b : mVec;
            return *this;
        }
        // SADDV
        inline SIMDVec_u sadd(SIMDVec_u const & b) const {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            uint32_t t0 = (mVec > MAX_VAL - b.mVec) ? MAX_VAL : mVec + b.mVec;
            return SIMDVec_u(t0);
        }
        // MSADDV
        inline SIMDVec_u sadd(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec > MAX_VAL - b.mVec) ? MAX_VAL : mVec + b.mVec;
            }
            return SIMDVec_u(t0);
        }
        // SADDS
        inline SIMDVec_u sadd(uint32_t b) const {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            uint32_t t0 = (mVec > MAX_VAL - b) ? MAX_VAL : mVec + b;
            return SIMDVec_u(t0);
        }
        // MSADDS
        inline SIMDVec_u sadd(SIMDVecMask<1> const & mask, uint32_t b) const {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec > MAX_VAL - b) ? MAX_VAL : mVec + b;
            }
            return SIMDVec_u(t0);
        }
        // SADDVA
        inline SIMDVec_u & sadda(SIMDVec_u const & b) {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            mVec = (mVec > MAX_VAL - b.mVec) ? MAX_VAL : mVec + b.mVec;
            return *this;
        }
        // MSADDVA
        inline SIMDVec_u & sadda(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            if (mask.mMask == true) {
                mVec = (mVec > MAX_VAL - b.mVec) ? MAX_VAL : mVec + b.mVec;
            }
            return *this;
        }
        // SADDSA
        inline SIMDVec_u & sadd(uint32_t b) {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            mVec = (mVec > MAX_VAL - b) ? MAX_VAL : mVec + b;
            return *this;
        }
        // MSADDSA
        inline SIMDVec_u & sadda(SIMDVecMask<1> const & mask, uint32_t b) {
            const uint32_t MAX_VAL = std::numeric_limits<uint32_t>::max();
            if (mask.mMask == true) {
                mVec = (mVec > MAX_VAL - b) ? MAX_VAL : mVec + b;
            }
            return *this;
        }
        // POSTINC
        inline SIMDVec_u postinc() {
            uint32_t t0 = mVec;
            mVec++;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator++ (int) {
            return postinc();
        }
        // MPOSTINC
        inline SIMDVec_u postinc(SIMDVecMask<1> const & mask) {
            uint32_t t0 = mVec;
            if(mask.mMask == true) mVec++;
            return SIMDVec_u(t0);
        }
        // PREFINC
        inline SIMDVec_u & prefinc() {
            mVec++;
            return *this;
        }
        inline SIMDVec_u & operator++ () {
            return prefinc();
        }
        // MPREFINC
        inline SIMDVec_u & prefinc(SIMDVecMask<1> const & mask) {
            if (mask.mMask == true) mVec++;
            return *this;
        }
        // SUBV
        inline SIMDVec_u sub(SIMDVec_u const & b) const {
            uint32_t t0 = mVec - b.mVec;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator- (SIMDVec_u const & b) const {
            return sub(b);
        }
        // MSUBV
        inline SIMDVec_u sub(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec - b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // SUBS
        inline SIMDVec_u sub(uint32_t b) const {
            uint32_t t0 = mVec - b;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator- (uint32_t b) const {
            return this->sub(b);
        }
        // MSUBS
        inline SIMDVec_u sub(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec - b : mVec;
            return SIMDVec_u(t0);
        }
        // SUBVA
        inline SIMDVec_u & suba(SIMDVec_u const & b) {
            mVec -= b.mVec;
            return *this;
        }
        inline SIMDVec_u & operator-= (SIMDVec_u const & b) {
            return suba(b);
        }
        // MSUBVA
        inline SIMDVec_u & suba(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            mVec = mask.mMask ? mVec - b.mVec : mVec;
            return *this;
        }
        // SUBSA
        inline SIMDVec_u & suba(uint32_t b) {
            mVec -= b;
            return *this;
        }
        inline SIMDVec_u & operator-= (uint32_t b) {
            return suba(b);
        }
        // MSUBSA
        inline SIMDVec_u & suba(SIMDVecMask<1> const & mask, uint32_t b) {
            mVec = mask.mMask ? mVec - b : mVec;
            return *this;
        }
        // SSUBV
        inline SIMDVec_u ssub(SIMDVec_u const & b) const {
            uint32_t t0 = (mVec < b.mVec) ? 0 : mVec - b.mVec;
            return SIMDVec_u(t0);
        }
        // MSSUBV
        inline SIMDVec_u ssub(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec < b.mVec) ? 0 : mVec - b.mVec;
            }
            return SIMDVec_u(t0);
        }
        // SSUBS
        inline SIMDVec_u ssub(uint32_t b) const {
            uint32_t t0 = (mVec < b) ? 0 : mVec - b;
            return SIMDVec_u(t0);
        }
        // MSSUBS
        inline SIMDVec_u ssub(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec < b) ? 0 : mVec - b;
            }
            return SIMDVec_u(t0);
        }
        // SSUBVA
        inline SIMDVec_u & ssuba(SIMDVec_u const & b) {
            mVec =  (mVec < b.mVec) ? 0 : mVec - b.mVec;
            return *this;
        }
        // MSSUBVA
        inline SIMDVec_u & ssuba(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if (mask.mMask == true) {
                mVec = (mVec < b.mVec) ? 0 : mVec - b.mVec;
            }
            return *this;
        }
        // SSUBSA
        inline SIMDVec_u & ssuba(uint32_t b) {
            mVec = (mVec < b) ? 0 : mVec - b;
            return *this;
        }
        // MSSUBSA
        inline SIMDVec_u & ssuba(SIMDVecMask<1> const & mask, uint32_t b)  {
            if (mask.mMask == true) {
                mVec = (mVec < b) ? 0 : mVec - b;
            }
            return *this;
        }
        // SUBFROMV
        inline SIMDVec_u subfrom(SIMDVec_u const & b) const {
            uint32_t t0 = b.mVec - mVec;
            return SIMDVec_u(t0);
        }
        // MSUBFROMV
        inline SIMDVec_u subfrom(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? b.mVec - mVec: b.mVec;
            return SIMDVec_u(t0);
        }
        // SUBFROMS
        inline SIMDVec_u subfrom(uint32_t b) const {
            uint32_t t0 = b - mVec;
            return SIMDVec_u(t0);
        }
        // MSUBFROMS
        inline SIMDVec_u subfrom(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? b - mVec : b;
            return SIMDVec_u(t0);
        }
        // SUBFROMVA
        inline SIMDVec_u & subfroma(SIMDVec_u const & b) {
            mVec = b.mVec - mVec;
            return *this;
        }
        // MSUBFROMVA
        inline SIMDVec_u & subfroma(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            mVec = mask.mMask ? b.mVec - mVec : b.mVec;
            return *this;
        }
        // SUBFROMSA
        inline SIMDVec_u & subfroma(uint32_t b) {
            mVec = b - mVec;
            return *this;
        }
        // MSUBFROMSA
        inline SIMDVec_u & subfroma(SIMDVecMask<1> const & mask, uint32_t b) {
            mVec = mask.mMask ? b - mVec : b;
            return *this;
        }
        // POSTDEC
        inline SIMDVec_u postdec() {
            uint32_t t0 = mVec;
            mVec--;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator-- (int) {
            return postdec();
        }
        // MPOSTDEC
        inline SIMDVec_u postdec(SIMDVecMask<1> const & mask) {
            uint32_t t0 = mVec;
            if (mask.mMask == true) mVec--;
            return SIMDVec_u(t0);
        }
        // PREFDEC
        inline SIMDVec_u & prefdec() {
            mVec--;
            return *this;
        }
        inline SIMDVec_u & operator-- () {
            return prefdec();
        }
        // MPREFDEC
        inline SIMDVec_u & prefdec(SIMDVecMask<1> const & mask) {
            if (mask.mMask == true) mVec--;
            return *this;
        }
        // MULV
        inline SIMDVec_u mul(SIMDVec_u const & b) const {
            uint32_t t0 = mVec * b.mVec;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator* (SIMDVec_u const & b) const {
            return mul(b);
        }
        // MMULV
        inline SIMDVec_u mul(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec * b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // MULS
        inline SIMDVec_u mul(uint32_t b) const {
            uint32_t t0 = mVec * b;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator* (uint32_t b) const {
            return mul(b);
        }
        // MMULS
        inline SIMDVec_u mul(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec * b : mVec;
            return SIMDVec_u(t0);
        }
        // MULVA
        inline SIMDVec_u & mula(SIMDVec_u const & b) {
            mVec *= b.mVec;
            return *this;
        }
        inline SIMDVec_u & operator*= (SIMDVec_u const & b) {
            return mula(b);
        }
        // MMULVA
        inline SIMDVec_u & mula(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            mVec = mask.mMask ? mVec * b.mVec : mVec;
            return *this;
        }
        // MULSA
        inline SIMDVec_u & mula(uint32_t b) {
            mVec *= b;
            return *this;
        }
        inline SIMDVec_u & operator*= (uint32_t b) {
            return mula(b);
        }
        // MMULSA
        inline SIMDVec_u & mula(SIMDVecMask<1> const & mask, uint32_t b) {
            mVec = mask.mMask ? mVec * b : mVec;
            return *this;
        }
        // DIVV
        inline SIMDVec_u div(SIMDVec_u const & b) const {
            uint32_t t0 = mVec / b.mVec;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator/ (SIMDVec_u const & b) const {
            return div(b);
        }
        // MDIVV
        inline SIMDVec_u div(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec / b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // DIVS
        inline SIMDVec_u div(uint32_t b) const {
            uint32_t t0 = mVec / b;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator/ (uint32_t b) const {
            return div(b);
        }
        // MDIVS
        inline SIMDVec_u div(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec / b : mVec;
            return SIMDVec_u(t0);
        }
        // DIVVA
        inline SIMDVec_u & diva(SIMDVec_u const & b) {
            mVec /= b.mVec;
            return *this;
        }
        inline SIMDVec_u & operator/= (SIMDVec_u const & b) {
            return diva(b);
        }
        // MDIVVA
        inline SIMDVec_u & diva(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            mVec = mask.mMask ? mVec / b.mVec : mVec;
            return *this;
        }
        // DIVSA
        inline SIMDVec_u & diva(uint32_t b) {
            mVec /= b;
            return *this;
        }
        inline SIMDVec_u & operator/= (uint32_t b) {
            return diva(b);
        }
        // MDIVSA
        inline SIMDVec_u & diva(SIMDVecMask<1> const & mask, uint32_t b) {
            mVec = mask.mMask ? mVec / b : mVec;
            return *this;
        }
        // RCP
        // MRCP
        // RCPS
        // MRCPS
        // RCPA
        // MRCPA
        // RCPSA
        // MRCPSA
        // CMPEQV
        inline SIMDVecMask<1> cmpeq (SIMDVec_u const & b) const {
            bool m0 = mVec == b.mVec;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator== (SIMDVec_u const & b) const {
            return cmpeq(b);
        }
        // CMPEQS
        inline SIMDVecMask<1> cmpeq (uint32_t b) const {
            bool m0 = mVec == b;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator== (uint32_t b) const {
            return cmpeq(b);
        }
        // CMPNEV
        inline SIMDVecMask<1> cmpne (SIMDVec_u const & b) const {
            bool m0 = mVec != b.mVec;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator!= (SIMDVec_u const & b) const {
            return cmpne(b);
        }
        // CMPNES
        inline SIMDVecMask<1> cmpne (uint32_t b) const {
            bool m0 = mVec != b;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator!= (uint32_t b) const {
            return cmpne(b);
        }
        // CMPGTV
        inline SIMDVecMask<1> cmpgt (SIMDVec_u const & b) const {
            bool m0 = mVec > b.mVec;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator> (SIMDVec_u const & b) const {
            return cmpgt(b);
        }
        // CMPGTS
        inline SIMDVecMask<1> cmpgt (uint32_t b) const {
            bool m0 = mVec > b;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator> (uint32_t b) const {
            return cmpgt(b);
        }
        // CMPLTV
        inline SIMDVecMask<1> cmplt (SIMDVec_u const & b) const {
            bool m0 = mVec < b.mVec;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator< (SIMDVec_u const & b) const {
            return cmplt(b);
        }
        // CMPLTS
        inline SIMDVecMask<1> cmplt (uint32_t b) const {
            bool m0 = mVec < b;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator< (uint32_t b) const {
            return cmplt(b);
        }
        // CMPGEV
        inline SIMDVecMask<1> cmpge (SIMDVec_u const & b) const {
            bool m0 = mVec >= b.mVec;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator>= (SIMDVec_u const & b) const {
            return cmpge(b);
        }
        // CMPGES
        inline SIMDVecMask<1> cmpge (uint32_t b) const {
            bool m0 = mVec >= b;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator>= (uint32_t b) const {
            return cmpge(b);
        }
        // CMPLEV
        inline SIMDVecMask<1> cmple (SIMDVec_u const & b) const {
            bool m0 = mVec <= b.mVec;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator<= (SIMDVec_u const & b) const {
            return cmple(b);
        }
        // CMPLES
        inline SIMDVecMask<1> cmple (uint32_t b) const {
            bool m0 = mVec <= b;
            return SIMDVecMask<1>(m0);
        }
        inline SIMDVecMask<1> operator<= (uint32_t b) const {
            return cmple(b);
        }
        // CMPEV
        inline bool cmpe (SIMDVec_u const & b) const {
            return mVec == b.mVec;
        }
        // CMPES
        inline bool cmpe(uint32_t b) const {
            return mVec == b;
        }
        // UNIQUE
        inline bool unique() const {
            return true;
        }
        // HADD
        inline uint32_t hadd() const {
            return mVec;
        }
        // MHADD
        inline uint32_t hadd(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? mVec : 0;
            return t0;
        }
        // HADDS
        inline uint32_t hadd(uint32_t b) const {
            return mVec + b;
        }
        // MHADDS
        inline uint32_t hadd(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec + b : b;
            return t0;
        }
        // HMUL
        inline uint32_t hmul() const {
            return mVec;
        }
        // MHMUL
        inline uint32_t hmul(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? mVec : 1;
            return t0;
        }
        // HMULS
        inline uint32_t hmul(uint32_t b) const {
            return mVec * b;
        }
        // MHMULS
        inline uint32_t hmul(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec * b : b;
            return t0;
        }

        // FMULADDV
        inline SIMDVec_u fmuladd(SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = mVec * b.mVec + c.mVec;
            return SIMDVec_u(t0);
        }
        // MFMULADDV
        inline SIMDVec_u fmuladd(SIMDVecMask<1> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = mask.mMask ? (mVec * b.mVec + c.mVec) : mVec;
            return SIMDVec_u(t0);
        }
        // FMULSUBV
        inline SIMDVec_u fmulsub(SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = mVec * b.mVec - c.mVec;
            return SIMDVec_u(t0);
        }
        // MFMULSUBV
        inline SIMDVec_u fmulsub(SIMDVecMask<1> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = mask.mMask ? (mVec * b.mVec - c.mVec) : mVec;
            return SIMDVec_u(t0);
        }
        // FADDMULV
        inline SIMDVec_u faddmul(SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = (mVec + b.mVec) * c.mVec;
            return SIMDVec_u(t0);
        }
        // MFADDMULV
        inline SIMDVec_u faddmul(SIMDVecMask<1> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = mask.mMask ? ((mVec + b.mVec) * c.mVec) : mVec;
            return SIMDVec_u(t0);
        }
        // FSUBMULV
        inline SIMDVec_u fsubmul(SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = (mVec - b.mVec) * c.mVec;
            return SIMDVec_u(t0);
        }
        // MFSUBMULV
        inline SIMDVec_u fsubmul(SIMDVecMask<1> const & mask, SIMDVec_u const & b, SIMDVec_u const & c) const {
            uint32_t t0 = mask.mMask ? ((mVec - b.mVec) * c.mVec) : mVec;
            return SIMDVec_u(t0);
        }

        // MAXV
        inline SIMDVec_u max(SIMDVec_u const & b) const {
            uint32_t t0 = mVec > b.mVec ? mVec : b.mVec;
            return SIMDVec_u(t0);
        }
        // MMAXV
        inline SIMDVec_u max(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = mVec > b.mVec ? mVec : b.mVec;
            }
            return SIMDVec_u(t0);
        }
        // MAXS
        inline SIMDVec_u max(uint32_t b) const {
            uint32_t t0 = mVec > b ? mVec : b;
            return SIMDVec_u(t0);
        }
        // MMAXS
        inline SIMDVec_u max(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = mVec > b ? mVec : b;
            }
            return SIMDVec_u(t0);
        }
        // MAXVA
        inline SIMDVec_u & maxa(SIMDVec_u const & b) {
            mVec = mVec > b.mVec ? mVec : b.mVec;
            return *this;
        }
        // MMAXVA
        inline SIMDVec_u & maxa(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if (mask.mMask == true && mVec > b.mVec) {
                mVec = b.mVec;
            }
            return *this;
        }
        // MAXSA
        inline SIMDVec_u & maxa(uint32_t b) {
            mVec = mVec > b ? mVec : b;
            return *this;
        }
        // MMAXSA
        inline SIMDVec_u & maxa(SIMDVecMask<1> const & mask, uint32_t b) {
            if (mask.mMask == true && mVec > b) {
                mVec = b;
            }
            return *this;
        }
        // MINV
        inline SIMDVec_u min(SIMDVec_u const & b) const {
            uint32_t t0 = mVec < b.mVec ? mVec : b.mVec;
            return SIMDVec_u(t0);
        }
        // MMINV
        inline SIMDVec_u min(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = mVec < b.mVec ? mVec : b.mVec;
            }
            return SIMDVec_u(t0);
        }
        // MINS
        inline SIMDVec_u min(uint32_t b) const {
            uint32_t t0 = mVec < b ? mVec : b;
            return SIMDVec_u(t0);
        }
        // MMINS
        inline SIMDVec_u min(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mVec;
            if (mask.mMask == true) {
                t0 = mVec < b ? mVec : b;
            }
            return SIMDVec_u(t0);
        }
        // MINVA
        inline SIMDVec_u & mina(SIMDVec_u const & b) {
            mVec = mVec < b.mVec ? mVec : b.mVec;
            return *this;
        }
        // MMINVA
        inline SIMDVec_u & mina(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if (mask.mMask == true && mVec < b.mVec) {
                mVec = b.mVec;
            }
            return *this;
        }
        // MINSA
        inline SIMDVec_u & mina(uint32_t b) {
            mVec = mVec < b ? mVec : b;
            return *this;
        }
        // MMINSA
        inline SIMDVec_u & mina(SIMDVecMask<1> const & mask, uint32_t b) {
            if (mask.mMask == true && mVec < b) {
                mVec = b;
            }
            return *this;
        }
        // HMAX
        inline uint32_t hmax () const {
            return mVec;
        }
        // MHMAX
        inline uint32_t hmax(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? mVec : std::numeric_limits<uint32_t>::min();
            return t0;
        }
        // IMAX
        inline uint32_t imax() const {
            return 0;
        }
        // MIMAX
        inline uint32_t imax(SIMDVecMask<1> const & mask) const {
            return mask.mMask ? 0 : 0xFFFFFFFF;
        }
        // HMIN
        inline uint32_t hmin() const {
            return mVec;
        }
        // MHMIN
        inline uint32_t hmin(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? mVec : std::numeric_limits<uint32_t>::max();
            return t0;
        }
        // IMIN
        inline uint32_t imin() const {
            return 0;
        }
        // MIMIN
        inline uint32_t imin(SIMDVecMask<1> const & mask) const {
            return mask.mMask ? 0 : 0xFFFFFFFF;
        }

        // BANDV
        inline SIMDVec_u band(SIMDVec_u const & b) const {
            uint32_t t0 = mVec & b.mVec;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator& (SIMDVec_u const & b) const {
            return band(b);
        }
        // MBANDV
        inline SIMDVec_u band(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec & b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // BANDS
        inline SIMDVec_u band(uint32_t b) const {
            uint32_t t0 = mVec & b;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator& (uint32_t b) const {
            return band(b);
        }
        // MBANDS
        inline SIMDVec_u band(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec & b : mVec;
            return SIMDVec_u(t0);
        }
        // BANDVA
        inline SIMDVec_u & banda(SIMDVec_u const & b) {
            mVec &= b.mVec;
            return *this;
        }
        inline SIMDVec_u & operator&= (SIMDVec_u const & b) {
            return banda(b);
        }
        // MBANDVA
        inline SIMDVec_u & banda(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if (mask.mMask) mVec &= b.mVec;
            return *this;
        }
        // BANDSA
        inline SIMDVec_u & banda(uint32_t b) {
            mVec &= b;
            return *this;
        }
        inline SIMDVec_u & operator&= (bool b) {
            return banda(b);
        }
        // MBANDSA
        inline SIMDVec_u & banda(SIMDVecMask<1> const & mask, uint32_t b) {
            if(mask.mMask) mVec &= b;
            return *this;
        }
        // BORV
        inline SIMDVec_u bor(SIMDVec_u const & b) const {
            uint32_t t0 = mVec | b.mVec;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator| (SIMDVec_u const & b) const {
            return bor(b);
        }
        // MBORV
        inline SIMDVec_u bor(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec | b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // BORS
        inline SIMDVec_u bor(uint32_t b) const {
            uint32_t t0 = mVec | b;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator| (uint32_t b) const {
            return bor(b);
        }
        // MBORS
        inline SIMDVec_u bor(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec | b : mVec;
            return SIMDVec_u(t0);
        }
        // BORVA
        inline SIMDVec_u & bora(SIMDVec_u const & b) {
            mVec |= b.mVec;
            return *this;
        }
        inline SIMDVec_u & operator|= (SIMDVec_u const & b) {
            return bora(b);
        }
        // MBORVA
        inline SIMDVec_u & bora(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if (mask.mMask) mVec |= b.mVec;
            return *this;
        }
        // BORSA
        inline SIMDVec_u & bora(uint32_t b) {
            mVec |= b;
            return *this;
        }
        inline SIMDVec_u & operator|= (uint32_t b) {
            return bora(b);
        }
        // MBORSA
        inline SIMDVec_u & bora(SIMDVecMask<1> const & mask, uint32_t b) {
            if (mask.mMask) mVec |= b;
            return *this;
        }
        // BXORV
        inline SIMDVec_u bxor(SIMDVec_u const & b) const {
            uint32_t t0 = mVec ^ b.mVec;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator^ (SIMDVec_u const & b) const {
            return bxor(b);
        }
        // MBXORV
        inline SIMDVec_u bxor(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec ^ b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // BXORS
        inline SIMDVec_u bxor(uint32_t b) const {
            uint32_t t0 = mVec ^ b;
            return SIMDVec_u(t0);
        }
        inline SIMDVec_u operator^ (uint32_t b) const {
            return bxor(b);
        }
        // MBXORS
        inline SIMDVec_u bxor(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec ^ b : mVec;
            return SIMDVec_u(t0);
        }
        // BXORVA
        inline SIMDVec_u & bxora(SIMDVec_u const & b) {
            mVec ^= b.mVec;
            return *this;
        }
        inline SIMDVec_u & operator^= (SIMDVec_u const & b) {
            return bxora(b);
        }
        // MBXORVA
        inline SIMDVec_u & bxora(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if (mask.mMask) mVec ^= b.mVec;
            return *this;
        }
        // BXORSA
        inline SIMDVec_u & bxora(uint32_t b) {
            mVec ^= b;
            return *this;
        }
        inline SIMDVec_u & operator^= (uint32_t b) {
            return bxora(b);
        }
        // MBXORSA
        inline SIMDVec_u & bxora(SIMDVecMask<1> const & mask, uint32_t b) {
            if (mask.mMask) mVec ^= b;
            return *this;
        }
        // BNOT
        inline SIMDVec_u bnot() const {
            return SIMDVec_u(~mVec);
        }
        inline SIMDVec_u operator~ () const {
            return bnot();
        }
        // MBNOT
        inline SIMDVec_u bnot(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? ~mVec : mVec;
            return SIMDVec_u(t0);
        }
        // BNOTA
        inline SIMDVec_u & bnota() {
            mVec = ~mVec;
            return *this;
        }
        // MBNOTA
        inline SIMDVec_u & bnota(SIMDVecMask<1> const & mask) {
            if(mask.mMask) mVec = ~mVec;
            return *this;
        }
        // HBAND
        inline uint32_t hband() const {
            return mVec;
        }
        // MHBAND
        inline uint32_t hband(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? mVec : 0xFFFFFFFF;
            return t0;
        }
        // HBANDS
        inline uint32_t hband(uint32_t b) const {
            return mVec & b;
        }
        // MHBANDS
        inline uint32_t hband(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec & b: b;
            return t0;
        }
        // HBOR
        inline uint32_t hbor() const {
            return mVec;
        }
        // MHBOR
        inline uint32_t hbor(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? mVec : 0;
            return t0;
        }
        // HBORS
        inline uint32_t hbor(uint32_t b) const {
            return mVec | b;
        }
        // MHBORS
        inline uint32_t hbor(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec | b : b;
            return t0;
        }
        // HBXOR
        inline uint32_t hbxor() const {
            return mVec;
        }
        // MHBXOR
        inline uint32_t hbxor(SIMDVecMask<1> const & mask) const {
            uint32_t t0 = mask.mMask ? mVec : 0;
            return t0;
        }
        // HBXORS
        inline uint32_t hbxor(uint32_t b) const {
            return mVec ^ b;
        }
        // MHBXORS
        inline uint32_t hbxor(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec ^ b : b;
            return t0;
        }

        // GATHER
        inline SIMDVec_u & gather(uint32_t * baseAddr, uint32_t* indices) {
            mVec = baseAddr[indices[0]];
            return *this;
        }
        // MGATHER
        inline SIMDVec_u & gather(SIMDVecMask<1> const & mask, uint32_t* baseAddr, uint32_t* indices) {
            if (mask.mMask == true) mVec = baseAddr[indices[0]];
            return *this;
        }
        // GATHERV
        inline SIMDVec_u gather(uint32_t * baseAddr, SIMDVec_u const & indices) {
            mVec = baseAddr[indices.mVec];
            return *this;
        }
        // MGATHERV
        inline SIMDVec_u gather(SIMDVecMask<1> const & mask, uint32_t* baseAddr, SIMDVec_u const & indices) {
            if (mask.mMask == true) mVec = baseAddr[indices.mVec];
            return *this;
        }
        // SCATTER
        inline uint32_t* scatter(uint32_t* baseAddr, uint32_t* indices) const {
            baseAddr[indices[0]] = mVec;
            return baseAddr;
        }
        // MSCATTER
        inline uint32_t*  scatter(SIMDVecMask<1> const & mask, uint32_t* baseAddr, uint32_t* indices) const {
            if (mask.mMask == true) baseAddr[indices[0]] = mVec;
            return baseAddr;
        }
        // SCATTERV
        inline uint32_t*  scatter(uint32_t* baseAddr, SIMDVec_u const & indices) const {
            baseAddr[indices.mVec] = mVec;
            return baseAddr;
        }
        // MSCATTERV
        inline uint32_t*  scatter(SIMDVecMask<1> const & mask, uint32_t* baseAddr, SIMDVec_u const & indices) const {
            if (mask.mMask == true) baseAddr[indices.mVec] = mVec;
            return baseAddr;
        }

        // LSHV
        inline SIMDVec_u lsh(SIMDVec_u const & b) const {
            uint32_t t0 = mVec << b.mVec;
            return SIMDVec_u(t0);
        }
        // MLSHV
        inline SIMDVec_u lsh(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec << b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // LSHS
        inline SIMDVec_u lsh(uint32_t b) const {
            uint32_t t0 = mVec << b;
            return SIMDVec_u(t0);
        }
        // MLSHS
        inline SIMDVec_u lsh(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec << b : mVec;
            return SIMDVec_u(t0);
        }
        // LSHVA
        inline SIMDVec_u & lsha(SIMDVec_u const & b) {
            mVec = mVec << b.mVec;
            return *this;
        }
        // MLSHVA
        inline SIMDVec_u & lsha(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if(mask.mMask) mVec = mVec << b.mVec;
            return *this;
        }
        // LSHSA
        inline SIMDVec_u & lsha(uint32_t b) {
            mVec = mVec << b;
            return *this;
        }
        // MLSHSA
        inline SIMDVec_u & lsha(SIMDVecMask<1> const & mask, uint32_t b) {
            if(mask.mMask) mVec = mVec << b;
            return *this;
        }
        // RSHV
        inline SIMDVec_u rsh(SIMDVec_u const & b) const {
            uint32_t t0 = mVec >> b.mVec;
            return SIMDVec_u(t0);
        }
        // MRSHV
        inline SIMDVec_u rsh(SIMDVecMask<1> const & mask, SIMDVec_u const & b) const {
            uint32_t t0 = mask.mMask ? mVec >> b.mVec : mVec;
            return SIMDVec_u(t0);
        }
        // RSHS
        inline SIMDVec_u rsh(uint32_t b) const {
            uint32_t t0 = mVec >> b;
            return SIMDVec_u(t0);
        }
        // MRSHS
        inline SIMDVec_u rsh(SIMDVecMask<1> const & mask, uint32_t b) const {
            uint32_t t0 = mask.mMask ? mVec >> b : mVec;
            return SIMDVec_u(t0);
        }
        // RSHVA
        inline SIMDVec_u & rsha(SIMDVec_u const & b) {
            mVec = mVec >> b.mVec;
            return *this;
        }
        // MRSHVA
        inline SIMDVec_u & rsha(SIMDVecMask<1> const & mask, SIMDVec_u const & b) {
            if (mask.mMask) mVec = mVec >> b.mVec;
            return *this;
        }
        // RSHSA
        inline SIMDVec_u & rsha(uint32_t b) {
            mVec = mVec >> b;
            return *this;
        }
        // MRSHSA
        inline SIMDVec_u & rsha(SIMDVecMask<1> const & mask, uint32_t b) {
            if (mask.mMask) mVec = mVec >> b;
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

        // PACK
        // -
        // PACKLO
        // -
        // PACKHI
        // -
        // UNPACK
        // -
        // PROMOTE
        inline operator SIMDVec_u<uint64_t, 1>() const;
        // DEGRADE
        inline operator SIMDVec_u<uint16_t, 1>() const;

        // UTOI
        inline operator SIMDVec_i<int32_t, 1>() const;
        // UTOF
        inline operator SIMDVec_f<float, 1>() const;
    };

}
}

#endif
