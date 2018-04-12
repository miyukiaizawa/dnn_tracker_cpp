#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_CONVEXHULL_H__
#define __DNN_TRACKER_CPP_REGION_CONVEXHULL_H__
#include "dnn_tracker_cpp/core.h"
#include <vector>

namespace dnn {
namespace region {
using convexhull = std::vector<cv::Point>;

DNNTRR_API convexhull to_convexhull(const cv::Rect& rect);
DNNTRR_API convexhull to_convexhull(const cv::Point& tl, const cv::Point& br);
DNNTRR_API convexhull to_convexhull(const cv::Point2f& tl, const cv::Point2f& br);

DNNTRR_API bool winding_number(const convexhull& convex, const cv::Point2f &pt);
DNNTRR_API bool winding_number(const convexhull& convex, const cv::Point &pt);

DNNTRR_API void sort(convexhull& convex);

DNNTRR_API cv::Point2f center(const convexhull& _convexhull);

}
}

#endif //__DNN_TRACKER_CPP_REGION_CONVEXHULL_H__
