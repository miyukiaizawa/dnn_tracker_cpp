#pragma once
#ifndef __DNN_TRACKER_CPP_DRAW_MAX_SIZE_H__
#define __DNN_TRACKER_CPP_DRAW_MAX_SIZE_H__

#include "dnn_tracker_cpp/core/types.h"

namespace dnn {

class max_size {
public:
  DNNTRR_API max_size(cv::Size a, cv::Size b);
  DNNTRR_API max_size(cv::Size a, int bx, int by);
  DNNTRR_API max_size(int ax, int ay, int bx, int by);
  DNNTRR_API max_size(int ax, int ay, cv::Size b);
  DNNTRR_API cv::Size& operator()();
private:
  cv::Size size_;
};

}

#endif //__DNN_TRACKER_CPP_DRAW_MAX_SIZE_H__
