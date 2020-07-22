//
//  FunctionSummary.hpp
//  MNN
//
//  Created by MNN on 2019/08/25.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#include <stdint.h>

#ifndef _MM_TRANSPOSE4_PS
#define _MM_TRANSPOSE4_PS(row0, row1, row2, row3) \
do { \
  __m128 tmp3, tmp2, tmp1, tmp0; \
  tmp0 = _mm_unpacklo_ps((row0), (row1)); \
  tmp2 = _mm_unpacklo_ps((row2), (row3)); \
  tmp1 = _mm_unpackhi_ps((row0), (row1)); \
  tmp3 = _mm_unpackhi_ps((row2), (row3)); \
  (row0) = _mm_movelh_ps(tmp0, tmp2); \
  (row1) = _mm_movehl_ps(tmp2, tmp0); \
  (row2) = _mm_movelh_ps(tmp1, tmp3); \
  (row3) = _mm_movehl_ps(tmp3, tmp1); \
} while (0)
#endif

// ========= CommonOptFunction.cpp ===========
extern "C" {

void _AVX_MNNAddBias(float* dst, const float* bias, size_t planeNumber, size_t biasNumber);

void _AVX_MNNAddBiasRelu(float* dst, const float* bias, size_t planeNumber, size_t biasNumber);

void _AVX_MNNAddBiasRelu6(float* dst, const float* bias, size_t planeNumber, size_t biasNumber);

// ========= MNNConvSlideWindowMiddle.cpp ===========

void _AVX_MNNConvSlideWindowMiddle(float* dst, const float* src, const float* weight, size_t width, size_t src_w_setup,
                                   size_t src_depth_quad, size_t src_depth_step, size_t fw, size_t fh, size_t dilateX_step,
                                   size_t dilateY_step, float* alpha);
void _AVX_MNNConvSlideWindowMiddleFMA(float* dst, const float* src, const float* weight, size_t width, size_t src_w_setup,
                                   size_t src_depth_quad, size_t src_depth_step, size_t fw, size_t fh, size_t dilateX_step,
                                   size_t dilateY_step, float* alpha);
void _AVX_MNNGemmFloatCommonFMA_4(float* dst, const float* src, const float* weight, size_t src_depth_quad, size_t dst_step,
                                  size_t dst_depth_quad, size_t width, size_t weight_depth_offset);

// ========= MNNGemmFloatCommon_4.cpp ===========

void _AVX_MNNGemmFloatCommon_4(float* dst, const float* src, const float* weight, size_t src_depth_quad, size_t dst_step,
                               size_t dst_depth_quad, size_t width, size_t weight_depth_offset);

void _AVX_MNNGemmFloatUnit_4(float* dstOrigin, const float* src, const float* weight, size_t src_depth_quad, size_t dst_step,
                        size_t dst_depth_quad, size_t weight_depth_offset);
void _AVX_MNNGemmFloatUnitFMA_4(float* dstOrigin, const float* src, const float* weight, size_t src_depth_quad, size_t dst_step,
                                size_t dst_depth_quad, size_t weight_depth_offset);

// ========= MNNMatrixAdd.cpp ===========

void _AVX_MNNMatrixAdd(float* C, const float* A, const float* B, size_t widthC4, size_t cStride, size_t aStride,
                       size_t bStride, size_t height);

// ========= MNNMatrixSub.cpp ===========

void _AVX_MNNMatrixSub(float* C, const float* A, const float* B, size_t widthC4, size_t cStride, size_t aStride,
                       size_t bStride, size_t height);

void _AVX_MNNStrassenMergeCFunction(float* c11, float* c12, float* c21, float* c22, float* xAddr, size_t cStride,
                               size_t length, size_t hSub);


void _AVX_MNNGemmInt8AddBiasScale_16x4_Unit(int8_t* dst, const int8_t* src, const int8_t* weight, const int32_t* bias,
                                       const float* scale, size_t src_depth_quad, size_t dst_step, size_t dst_depth_quad);
void _AVX_MNNPackedMatMul(float* C, const float* A, const float* B, const size_t* parameter, float* cache, const float* postParameters, const float* bias);
void _AVX_MNNPackedMatMulRemain(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, float* cache, const float* postParameters, const float* bias);

void _AVX_MNNPackedMatMulFMA(float* C, const float* A, const float* B, const size_t* parameter, float* cache, const float* postParameters, const float* bias);
void _AVX_MNNPackedMatMulRemainFMA(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, float* cache, const float* postParameters, const float* bias);


}
