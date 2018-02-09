#pragma once
#ifndef __DNN_TRACKER_CPP_INFO_DETECTION_INFO_H__
#define __DNN_TRACKER_CPP_INFO_DETECTION_INFO_H__

#include "dnn_tracker_cpp/region.h"
#include "dnn_tracker_cpp/object.h"
#include <chrono>

namespace dnn {

class detection_info {
public:
  DNNTRR_API detection_info();
  DNNTRR_API detection_info(dependent_object_ptrs _boxes,
                 std::chrono::time_point<std::chrono::system_clock> time,
                 bool _detected);

public:
  std::chrono::time_point<std::chrono::system_clock> last_update_tp;
  dependent_object_ptrs boxes;
  bool detected;
};

}

#endif //__DNN_TRACKER_CPP_INFO_DETECTION_INFO_H__
