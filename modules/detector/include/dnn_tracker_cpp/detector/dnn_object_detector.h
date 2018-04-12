#pragma once
#ifndef __DNN_TRACKER_CPP_DNN_OBEJCT_DETECTOR_H__
#define __DNN_TRACKER_CPP_DNN_OBEJCT_DETECTOR_H__

#include "opencv2/opencv.hpp"
#include "dnn_tracker_cpp/detector/dependent_object_tracker.h"
#include "dnn_tracker_cpp/info.h"

namespace dnn {

class dnn_object_detector {
public:

  DNNTRR_API dnn_object_detector(std::tstring config_path,
                      std::tstring weight_path,
                      cv::Size detection_area,
                      int frame_story = 6,
                      float _threshold = 0.24);

  DNNTRR_API bool init(const std::tstring& filename,
            const target_objects &_targets);

  DNNTRR_API bool load_object_names(const std::tstring &filename);

  DNNTRR_API void set_target_objects(const target_objects &_targets);

  DNNTRR_API target_objects& get_target_objects();

  DNNTRR_API detection_info detect(cv::Mat &src, cv::Size init_size);

public:
  object_names object_names;
  target_object_judgementer checker;
  dependent_object_tracker tracker;
  float threshold;
  int frame_story;
private:
  core::object_detector detector_;
  cv::Size detection_area_;
};

}

#endif //__DNN_TRACKER_CPP_DNN_OBEJCT_DETECTOR_H__
