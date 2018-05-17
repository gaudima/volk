/* -*- c++ -*- */
/*
 * Copyright 2012, 2014 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*!
 * \page volk_32fc_deinterleave_imag_32f
 *
 * \b Overview
 *
 * Deinterleaves the complex floating point vector and return the imaginary
 * part (quadrature) of the samples.
 *
 * <b>Dispatcher Prototype</b>
 * \code
 * void volk_32fc_deinterleave_image_32f(float* qBuffer, const lv_32fc_t* complexVector, unsigned int num_points)
 * \endcode
 *
 * \b Inputs
 * \li complexVector: The complex input vector.
 * \li num_points: The number of complex data values to be deinterleaved.
 *
 * \b Outputs
 * \li qBuffer: The Q buffer output data.
 *
 * \b Example
 * Generate complex numbers around the top half of the unit circle and
 * extract all of the imaginary parts to a float buffer.
 * \code
 *   int N = 10;
 *   unsigned int alignment = volk_get_alignment();
 *   lv_32fc_t* in  = (lv_32fc_t*)volk_malloc(sizeof(lv_32fc_t)*N, alignment);
 *   float* im = (float*)volk_malloc(sizeof(float)*N, alignment);
 *
 *   for(unsigned int ii = 0; ii < N; ++ii){
 *       float real = 2.f * ((float)ii / (float)N) - 1.f;
 *       float imag = std::sqrt(1.f - real * real);
 *       in[ii] = lv_cmake(real, imag);
 *   }
 *
 *   volk_32fc_deinterleave_imag_32f(im, in, N);
 *
 *   printf("          imaginary part\n");
 *   for(unsigned int ii = 0; ii < N; ++ii){
 *       printf("out(%i) = %+.1f\n", ii, im[ii]);
 *   }
 *
 *   volk_free(in);
 *   volk_free(im);
 * \endcode
 */

#ifndef INCLUDED_volk_32fc_deinterleave_imag_32f_a_H
#define INCLUDED_volk_32fc_deinterleave_imag_32f_a_H

#include <inttypes.h>
#include <stdio.h>

#ifdef LV_HAVE_AVX
#include <immintrin.h>

static inline void
volk_32fc_deinterleave_imag_32f_a_avx(float* qBuffer, const lv_32fc_t* complexVector,
                                      unsigned int num_points)
{
  unsigned int number = 0;
  const unsigned int eighthPoints = num_points / 8;
  const float* complexVectorPtr = (const float*)complexVector;
  float* qBufferPtr = qBuffer;

  __m256 cplxValue1, cplxValue2, complex1, complex2, qValue;
  for(;number < eighthPoints; number++){

    cplxValue1 = _mm256_load_ps(complexVectorPtr);
    complexVectorPtr += 8;

    cplxValue2 = _mm256_load_ps(complexVectorPtr);
    complexVectorPtr += 8;

    complex1 = _mm256_permute2f128_ps(cplxValue1, cplxValue2, 0x20);
    complex2 = _mm256_permute2f128_ps(cplxValue1, cplxValue2, 0x31);

    // Arrange in q1q2q3q4 format
    qValue = _mm256_shuffle_ps(complex1, complex2, 0xdd);

    _mm256_store_ps(qBufferPtr, qValue);

    qBufferPtr += 8;
  }

  number = eighthPoints * 8;
  for(; number < num_points; number++){
    complexVectorPtr++;
    *qBufferPtr++ = *complexVectorPtr++;
  }
}
#endif /* LV_HAVE_AVX */

#ifdef LV_HAVE_SSE
#include <xmmintrin.h>

static inline void
volk_32fc_deinterleave_imag_32f_a_sse(float* qBuffer, const lv_32fc_t* complexVector,
                                      unsigned int num_points)
{
  unsigned int number = 0;
  const unsigned int quarterPoints = num_points / 4;

  const float* complexVectorPtr = (const float*)complexVector;
  float* qBufferPtr = qBuffer;

  __m128 cplxValue1, cplxValue2, iValue;
  for(;number < quarterPoints; number++){

    cplxValue1 = _mm_load_ps(complexVectorPtr);
    complexVectorPtr += 4;

    cplxValue2 = _mm_load_ps(complexVectorPtr);
    complexVectorPtr += 4;

    // Arrange in q1q2q3q4 format
    iValue = _mm_shuffle_ps(cplxValue1, cplxValue2, _MM_SHUFFLE(3,1,3,1));

    _mm_store_ps(qBufferPtr, iValue);

    qBufferPtr += 4;
  }

  number = quarterPoints * 4;
  for(; number < num_points; number++){
    complexVectorPtr++;
    *qBufferPtr++ = *complexVectorPtr++;
  }
}
#endif /* LV_HAVE_SSE */

#ifdef LV_HAVE_NEON
#include <arm_neon.h>

static inline void
volk_32fc_deinterleave_imag_32f_neon(float* qBuffer, const lv_32fc_t* complexVector,
                                     unsigned int num_points)
{
  unsigned int number = 0;
  unsigned int quarter_points = num_points / 4;
  const float* complexVectorPtr = (float*)complexVector;
  float* qBufferPtr = qBuffer;
  float32x4x2_t complexInput;

  for(number = 0; number < quarter_points; number++){
    complexInput = vld2q_f32(complexVectorPtr);
    vst1q_f32( qBufferPtr, complexInput.val[1] );
    complexVectorPtr += 8;
    qBufferPtr += 4;
  }

  for(number = quarter_points*4; number < num_points; number++){
    complexVectorPtr++;
    *qBufferPtr++ = *complexVectorPtr++;
  }
}
#endif /* LV_HAVE_NEON */

#ifdef LV_HAVE_NEON64
#include <arm_neon.h>

static inline void
volk_32fc_deinterleave_imag_32f_neon64(float* qBuffer, const lv_32fc_t* complexVector,
                                     unsigned int num_points)
{
  unsigned int number = 0;
  unsigned int quarter_points = num_points / 4;
  const float* complexVectorPtr = (float*)complexVector;
  float* qBufferPtr = qBuffer;
  float32x4x2_t complexInput;

  for(number = 0; number < quarter_points; number++){
    complexInput = vld2q_f32(complexVectorPtr);
    vst1q_f32( qBufferPtr, complexInput.val[1] );
    complexVectorPtr += 8;
    qBufferPtr += 4;
  }

  for(number = quarter_points*4; number < num_points; number++){
    complexVectorPtr++;
    *qBufferPtr++ = *complexVectorPtr++;
  }
}
#endif /* LV_HAVE_NEON64 */


#ifdef LV_HAVE_GENERIC

static inline void
volk_32fc_deinterleave_imag_32f_generic(float* qBuffer, const lv_32fc_t* complexVector,
                                        unsigned int num_points)
{
  unsigned int number = 0;
  const float* complexVectorPtr = (float*)complexVector;
  float* qBufferPtr = qBuffer;
  for(number = 0; number < num_points; number++){
    complexVectorPtr++;
    *qBufferPtr++ = *complexVectorPtr++;
  }
}
#endif /* LV_HAVE_GENERIC */


#endif /* INCLUDED_volk_32fc_deinterleave_imag_32f_a_H */
