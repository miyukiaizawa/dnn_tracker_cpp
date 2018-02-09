#pragma once
#ifndef __DNN_TRACKER_CPP_TYPES_H__
#define __DNN_TRACKER_CPP_TYPES_H__

#include "akstdutils/akstdutils.h"
#include <vector>

#ifdef OPENCV
#include "opencv2/opencv.hpp"
#endif

#ifdef DARKNET
#include "yolo_v2_class.hpp"
#endif

#ifdef DNN_TRACKER_CPP_EXPORTS
#if defined(_MSC_VER)
#define DNNTRR_API __declspec(dllexport) 
#else
#define DNNTRR_API __attribute__((visibility("default")))
#endif
#else
#if defined(_MSC_VER)
#define DNNTRR_API __declspec(dllimport) 
#else
#define DNNTRR_API
#endif
#endif

#include "rw_property.h"

namespace dnn {

namespace core {

#ifdef DARKNET
using bbox_t = ::bbox_t;

class object_detector {
public:
  object_detector(std::string config_path,
                  std::string weight_path,
                  int _frame_story = 6,
                  float _threshold = 0.24) :
    frame_story(_frame_story),
    threshold(_threshold),
    detector_(config_path, weight_path) {}

  template<typename Func>
  auto detect(cv::Mat &src,
              const cv::Size &init_size,
              Func erase_unvalid_objects,
              bool use_mean = true) {

    auto img = detector_.mat_to_image(src);
    frame_basis_objects = detector_.detect_resized(*img,
                                                   init_size,
                                                   threshold,
                                                   use_mean);
    erase_unvalid_objects(frame_basis_objects);
    return detector_.tracking(frame_basis_objects, frame_story);
  }


public:
  int frame_story;
  float threshold;
  std::vector<bbox_t> frame_basis_objects;
private:
  Detector detector_;
};

#else
struct bbox_t {
  unsigned int x, y, w, h;
  float prob;
  unsigned int obj_id;
  unsigned int track_id;
  unsigned int count;
};

class object_detector {
public:
  object_detector() {}
  ~object_detector() {}
};

#endif

using bboxes_t = std::vector<bbox_t>;

}

}

#endif //__DETECTOR_TYPES_H__


