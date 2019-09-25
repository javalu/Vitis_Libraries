

#ifndef _XF_CANNY_CONFIG_H__
#define _XF_CANNY_CONFIG_H__

#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.h"
#include "common/xf_utility.h"
#include "imgproc/xf_canny.hpp"
#include "imgproc/xf_edge_tracing.hpp"
#include "xf_config_params.h"

#define WIDTH 128
#define HEIGHT 128

#if NO
#define INTYPE XF_NPPC1
#define OUTTYPE XF_NPPC32
#elif RO
#define INTYPE XF_NPPC8
#define OUTTYPE XF_NPPC32
#endif

#if L1NORM
#define NORM_TYPE XF_L1NORM
#elif L2NORM
#define NORM_TYPE XF_L2NORM
#endif

void canny_accel(xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, INTYPE>& _src,
                 xf::cv::Mat<XF_2UC1, HEIGHT, WIDTH, XF_NPPC32>& _dst1,
                 xf::cv::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC8>& _dst2,
                 unsigned char low_threshold,
                 unsigned char high_threshold);

#endif