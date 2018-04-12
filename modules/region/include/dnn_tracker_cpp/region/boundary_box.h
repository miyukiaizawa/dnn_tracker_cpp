#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_BOUNDARY_BOX_H__
#define __DNN_TRACKER_CPP_REGION_BOUNDARY_BOX_H__
#include "dnn_tracker_cpp/core.h"

namespace dnn {

namespace region {

class boundary_box {
public:

  DNNTRR_API boundary_box();
  DNNTRR_API boundary_box(const core::bbox_t& _box);
  DNNTRR_API boundary_box(const boundary_box& _box);

  DNNTRR_API boundary_box& operator=(const boundary_box &box);

  DNNTRR_API core::bbox_t& operator()();
  DNNTRR_API const core::bbox_t& operator()() const;

  DNNTRR_API bool operator==(const boundary_box &box) const;

  DNNTRR_API bool is_same_id(const boundary_box &box) const;

  DNNTRR_API bool operator!=(const boundary_box &box) const;

  DNNTRR_API bool empty() const;

  DNNTRR_API void clear();

  DNNTRR_API cv::Point center() const;

  DNNTRR_API int area() const;

private:
  void set_properties();

public://property

  Declear_Properties(int,         boundary_box, x,           X);
  Declear_Properties(int,         boundary_box, y,           Y);
  Declear_Properties(int,         boundary_box, width,       Width);
  Declear_Properties(int,         boundary_box, height,      Height);
  Declear_Properties(int,         boundary_box, obj_id,      ObjectId);
  Declear_Properties(int,         boundary_box, track_id,    TrackId);
  Declear_Properties(int,         boundary_box, count,       Count);
  Declear_Properties(float,       boundary_box, prob,        Prob);
  Declear_Properties(std::string, boundary_box, object_name, ObjectName);
  Declear_Properties(cv::Size,    boundary_box, size,        Size);
  Declear_Properties(cv::Point,   boundary_box, lt,          LT);
  Declear_Properties(cv::Point,   boundary_box, br,          BR);
  Declear_Properties(cv::Rect,    boundary_box, rect,        Rect);


public:
  core::bbox_t box_;
  std::string name_;
};

}

namespace region {

DNNTRR_API bool is_same_id(const boundary_box &box1, const boundary_box &box2);

}

namespace region {

using boundary_boxes = std::vector<boundary_box>;

DNNTRR_API boundary_boxes make_boundaryboxes(const core::bboxes_t& vec);

}

}




#endif //__DNN_TRACKER_CPP_REGION_BOUNDARY_BOX_H__
