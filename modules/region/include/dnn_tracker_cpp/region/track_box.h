#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_REGION_TRACK_BOX_H__
#define __DNN_TRACKER_CPP_REGION_REGION_TRACK_BOX_H__

#include "dnn_tracker_cpp/region/boundary_box.h"
#include "dnn_tracker_cpp/region/collision.h"
#include "dnn_tracker_cpp/region/distance.h"
#include "dnn_tracker_cpp/region/direction.h"

namespace dnn {
namespace region {

class track_box {
public:
  DNNTRR_API track_box();
  DNNTRR_API track_box(const boundary_box& _first_pos, collision _collision);
  DNNTRR_API track_box(const boundary_box& _first_pos,
                       const boundary_box& _current_pos, collision _collision);
  DNNTRR_API track_box(const track_box& box);

  DNNTRR_API boundary_box& operator()() const;
  DNNTRR_API bool operator==(const track_box& box) const;
  DNNTRR_API bool operator!=(const track_box& box) const;
  DNNTRR_API track_box& operator=(const track_box& box);
  DNNTRR_API track_box& operator <<(boundary_box& _current_box);

  DNNTRR_API bool empty() const;
  DNNTRR_API bool is_same_id(const track_box& box) const;
  DNNTRR_API void merge(track_box& box);
  DNNTRR_API void update(const boundary_box& _current_box);
  DNNTRR_API bool detect_collision(track_box& box);
  DNNTRR_API void clear();

  DNNTRR_API bool is_cross(track_box &box);
  DNNTRR_API bool contain(track_box &box);
private:
  void set_properties();

public://property

  Declear_Properties(boundary_box, track_box, _first_pos, FirstPos);
  Declear_Properties(boundary_box, track_box, _current_pos, CurrentPos);
  Declear_Properties(int, track_box, x, X);
  Declear_Properties(int, track_box, y, Y);
  Declear_Properties(int, track_box, width, Width);
  Declear_Properties(int, track_box, height, Height);
  Declear_Properties(int, track_box, obj_id, ObjectId);
  Declear_Properties(int, track_box, track_id, TrackId);
  Declear_Properties(int, track_box, count, Count);
  Declear_Properties(float, track_box, prob, Prob);
  Declear_Properties(std::string, track_box, object_name, ObjectName);
  Declear_Properties(cv::Size, track_box, size, Size);
  Declear_Properties(cv::Point, track_box, lt, LT);
  Declear_Properties(cv::Point, track_box, br, BR);
  Declear_Properties(cv::Rect, track_box, rect, Rect);


public:
  boundary_box first_pos;
  boundary_box current_pos;
  collision collision;
  distance distance;
  direction direction;

};
}
namespace region {

bool is_same_id(const track_box &box1, const track_box &box2);

}
}

#endif //__DNN_TRACKER_CPP_REGION_REGION_TRACK_BOX_H__
