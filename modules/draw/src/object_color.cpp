#include "dnn_tracker_cpp/draw/object_color.h"

namespace dnn {

const object_color object_color::no_color;

object_color::
object_color() :
  color_(-1, -1, -1) {}

object_color::
object_color(dependent_object_ptr& object,
             target_object& target,
             dependent_object_ptrs& objects,
             object_names& obj_names) :
  color_(select_color(object, target)) {}



cv::Scalar
object_color::
select_color(dependent_object_ptr& object,
             target_object& target,
             cv::Scalar alert_color,
             cv::Scalar safe_color) {

  cv::Scalar color = target.draw_color;
  if (object->CanAlert) {
    if (object->IsCertain_Distance) {
      color = (object->ShouldAlert) ? alert_color : safe_color;
    }
    if (object->IsStationary && object->ShouldAlert) {
      color = alert_color;
    }
  }
  return color;
}

cv::Scalar
object_color::
operator()() {
  return color_;
}

}