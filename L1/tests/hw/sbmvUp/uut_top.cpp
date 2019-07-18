/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ap_int.h"
#include "hls_stream.h"
#include "gbmv.h"
#include "xf_blas/helpers.h"

using namespace xf::linear_algebra::blas;


void uut_top(
  uint32_t p_m,
  uint32_t p_n,
  uint32_t p_kl,
  uint32_t p_ku,
  BLAS_dataType p_alpha,
  BLAS_dataType p_beta,
  BLAS_dataType p_a[BLAS_matrixSize],
  BLAS_dataType p_x[BLAS_vectorSize],
  BLAS_dataType p_y[BLAS_matrixSize/BLAS_vectorSize],
  BLAS_dataType p_aRes[BLAS_matrixSize],
  BLAS_dataType p_yRes[BLAS_matrixSize/BLAS_vectorSize]
  ) {
#pragma HLS DATAFLOW
  hls::stream<WideType<BLAS_dataType, BLAS_parEntries> > l_strA;
  #pragma HLS data_pack variable=l_strA
  hls::stream<WideType<BLAS_dataType, BLAS_parEntries> > l_strX;
  #pragma HLS data_pack variable=l_strX
  hls::stream<WideType<BLAS_dataType, BLAS_parEntries> > l_strYR;
  #pragma HLS data_pack variable=l_strYR
  #pragma HLS DATAFLOW
  sbmSuper2Stream<BLAS_dataType, BLAS_parEntries>(p_n, p_ku, p_a, l_strA);
  vec2SbMatStream<BLAS_dataType, BLAS_parEntries>(p_n, p_ku, p_x, l_strX);
  gbmv<BLAS_dataType, BLAS_parEntries, BLAS_parBlocks>(p_m, p_ku, p_ku, l_strA, l_strX, l_strYR);
  writeStream2Vec<BLAS_dataType, BLAS_parEntries>(l_strYR, p_m, p_yRes);
}

