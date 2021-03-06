﻿#pragma once
#ifndef __DNN_TRACKER_CPP_DRAW_OBJECT_COLOR_H__
#define __DNN_TRACKER_CPP_DRAW_OBJECT_COLOR_H__
#include "dnn_tracker_cpp/object.h"

namespace dnn {
class object_color {
public:
  DNNTRR_API object_color(const dependent_object_ptr& object,
                          const target_object& target,
                          const dependent_object_ptrs& objects,
                          const object_names& obj_names);

  DNNTRR_API cv::Scalar operator()();

private:
  object_color();

  cv::Scalar select_color(const dependent_object_ptr& object,
                          const target_object& target,
                          const cv::Scalar alert_color = cv::Scalar(0, 0, 180),
                          const cv::Scalar safe_color = cv::Scalar(180, 0, 0));

public:
  const static object_color no_color;
private:
  cv::Scalar color_;
};
}

#endif //__DNN_TRACKER_CPP_DRAW_OBJECT_COLOR_H__

