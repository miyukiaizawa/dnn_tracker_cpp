#include "dnn_tracker_cpp/target/target_object_judgementer.h"

namespace dnn {

target_object_judgementer::
target_object_judgementer(region::distance _max_distance,
                          double _min_distance_th) :
  targets_(),
  max_distance_(_max_distance),
  min_distance_th_(_min_distance_th),
  min_distance_(max_distance_() / min_distance_th_) {}


target_object_judgementer::
target_object_judgementer(target_objects _targets,
                          region::distance _max_distance,
                          double _min_distance_th) :
  targets_(_targets),
  max_distance_(_max_distance),
  min_distance_th_(_min_distance_th),
  min_distance_(max_distance_() / min_distance_th_) {}

bool
target_object_judgementer::
find_target_object(const std::tstring& obj_name,
                   target_object& dst) {
  return dnn::find_target_object(targets_, obj_name, dst);
}

bool
target_object_judgementer::
is_certain_probability(dependent_object_ptr& object,
                       const target_object& target) {
  return object->IsCertainProbability = (object->outer().Prob >= target.probability);
}

bool
target_object_judgementer::
is_certain_count_of_apperance(dependent_object_ptr& object,
                              const target_object& target) {
  return object->IsCertainCount = (object->outer().Count >= target.count_of_appearance);
}

bool
target_object_judgementer::
is_certain_move_distance(dependent_object_ptr& object,
                         const target_object& target) {

  return object->IsCertain_Distance = (object->outer().distance() > target.distance);
}

bool
target_object_judgementer::
is_stationary_object(dependent_object_ptr& object,
                     const target_object& target) {
  return object->IsStationary
    = object->IsCertainCount && (object->outer().distance() < min_distance_());
}



bool
target_object_judgementer::
is_valid_move_direction(dependent_object_ptr& object,
                        const target_object& target) {
  return object->IsValidMoveDirection 
    = target.direction().valid_direction(object->outer().direction());
}

bool
target_object_judgementer::
judge_detection_targets(dependent_object_ptrs& objects,
                        const object_names& _object_names) {
  bool ret = false;
  for (auto& object : objects) {
    if (judge_detection_target(object, _object_names)) {
      ret = true;
    }
  }
  return ret;
}

bool
target_object_judgementer::
judge_detection_target(dependent_object_ptr& object,
                       const object_names& _object_names) {

  //* do not change following check order

  dnn::target_object target;
  if (!find_target_object(_object_names[object->outer()], target)) {
    return false;
  }

  if (!(object->CanShow = target.show_info)) {
    return false;
  }

  if (!(object->CanAlert = target.can_alert)) {
    return false;
  }

  bool should_alert = true;
  if (!is_certain_count_of_apperance(object, target)) {
    should_alert = false;
  }

  if (!is_certain_move_distance(object, target)) {
    should_alert = false;
  }
  is_stationary_object(object, target);

  if (!is_certain_probability(object, target)) {
    should_alert = false;
  }

  object->IsConfirmed = should_alert;

  if (!is_valid_move_direction(object, target)) {
    should_alert = false;
  }

  if (object->should_ignore()) {
    should_alert = false;
  }

  object->ShouldAlert = should_alert;

  return should_alert;
}

target_objects&
target_object_judgementer::
targets() {
  return targets_;
}

const target_objects&
target_object_judgementer::
targets() const {
  return targets_;
}

void
target_object_judgementer::
targets(const target_objects& _targets) {
  targets_ = _targets;
}

target_direction&
target_object_judgementer::
direction() {
  return target_direction_;
}

const target_direction&
target_object_judgementer::
direction() const {
  return target_direction_;
}

region::distance
target_object_judgementer::
max_distance() {
  return max_distance_;
}

const region::distance
target_object_judgementer::
max_distance() const {
  return max_distance_;
}

void
target_object_judgementer::
max_distance(const region::distance& distance) {
  max_distance_ = distance;
}



}