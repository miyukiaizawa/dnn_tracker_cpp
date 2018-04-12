#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_REGION_DISTANCE_H__
#define __DNN_TRACKER_CPP_REGION_REGION_DISTANCE_H__

#include "dnn_tracker_cpp/core.h"

namespace dnn {
namespace region {

class distance {
public:
  DNNTRR_API distance();

  DNNTRR_API distance(double value);

  DNNTRR_API distance(cv::Point sp, cv::Point ep, bool abs = false);

  DNNTRR_API distance(double x, double y, double x2, double y2);

  DNNTRR_API double operator()() const;

private:
  double calc_distance(cv::Point sp, cv::Point ep);

  double abs_distance(cv::Point sp, cv::Point ep);

private:
  double distance_;
};

}
}

#endif //__DNN_TRACKER_CPP_REGION_REGION_DISTANCE_H__
