#include "dnn_tracker_cpp/object/dependent_object.h"
#include "dnn_tracker_cpp/object/dependent_object_ptrs.h"

namespace dnn {

dependent_object::
object_info::
object_info() :
  is_certain_count(false),
  is_certain_distance(false),
  is_certain_probability(false),
  is_confirmed(false),
  is_valid_move_direction(false),
  can_show(false),
  can_alert(false),
  should_alert(false) {}

dependent_object::
object_info::
object_info(object_info& info) :
  is_certain_count(info.is_certain_count),
  is_certain_distance(info.is_certain_distance),
  is_certain_probability(info.is_certain_probability),
  is_confirmed(info.is_confirmed),
  is_valid_move_direction(info.is_valid_move_direction),
  can_show(info.can_show),
  can_alert(info.can_alert),
  should_alert(info.should_alert) {}

dependent_object::
object_info&
dependent_object::
object_info::
operator = (object_info& info) {
  is_certain_count = info.is_certain_count;
  is_certain_distance = info.is_certain_distance;
  is_certain_probability = info.is_certain_probability;
  is_confirmed = info.is_confirmed;
  is_valid_move_direction = info.is_valid_move_direction;
  can_show = info.can_show;
  can_alert = info.can_alert;
  should_alert = info.should_alert;
  return (*this);
}

dependent_object::
alert_info::
alert_info() :
  is_unchecked(true),
  is_alerted(false),
  is_notifiable(true),
  detection_time(),
  state(alert_info::detection_state::none) {}

dependent_object::
alert_info::
alert_info(alert_info& info) :
  is_unchecked(info.is_unchecked),
  is_alerted(info.is_alerted),
  is_notifiable(info.is_notifiable),
  detection_time(info.detection_time),
  state(info.state) {}

dependent_object::
alert_info&
dependent_object::
alert_info::
operator = (alert_info& info) {
  is_unchecked = info.is_unchecked;
  is_alerted = info.is_alerted;
  is_notifiable = info.is_notifiable;
  detection_time = info.detection_time;
  state = info.state;
  return (*this);
}

dependent_object::
dependent_object() :
  self_(),
  appearance_(appearance_property::real) {
  set_properties();
}

dependent_object::
dependent_object(region::track_box box) :
  self_(box),
  appearance_(appearance_property::real) {
  set_properties();
}

dependent_object::
dependent_object(region::inclusive_box box) :
  self_(box),
  appearance_(appearance_property::real) {
  set_properties();
}

dependent_object::
~dependent_object() {}

dependent_object::
dependent_object(dependent_object* obj) :
  object_info_(obj->object_info_),
  alert_info_(obj->alert_info_),
  self_(obj->self_),
  appearance_(obj->appearance_) {}

dependent_object&
dependent_object::
operator = (dependent_object* obj) {
  object_info_ = obj->object_info_;
  alert_info_ = obj->alert_info_;
  self_ = obj->self_;
  appearance_ = obj->appearance_;
  return (*this);
}


bool
dependent_object::
update_inner(region::track_boxes& boxes) {
  region::track_boxes::iterator it;
  if (boxes.find(inner(), it)) {
    inner() = *it;
    return true;
  }
  return false;
}

bool
dependent_object::
update_outer(object_ptrs_t& objects) {
  if (update_reference(objects)) {
    appearance_ = appearance_property::simulate;
    return true;
  }
  appearance_ = appearance_property::real;
  return false;
}

void
dependent_object::
switch_simuration() {
  switch (appearance_) {
  case appearance_property::real:
    stop_simuration();
    clear_reference();
    break;
  case appearance_property::simulate:
    start_simuration();
    break;
  }
}

bool
dependent_object::
update_reference(object_ptrs_t& objects) {
  return update_current_reference(objects) || find_new_reference(objects);
}

bool
dependent_object::
update_current_reference(object_ptrs_t& objects) {
  object_ptr_t obj;
  if (!find_reference(objects, obj)) {
    return false;
  }
  if (!is_related_to(obj)) {
    //交差していない場合、物体同士が離れているのでお互いの参照を削除する
    erase_reference(obj);
    return false;
  }

  overwirte_referene(obj.get());
  return true;
}

bool
dependent_object::
find_new_reference(object_ptrs_t& objects) {
  bool ret = false;
  for (auto& object : objects) {
    if ((*object).inner() == (*this).inner()) { continue; }
    if (!is_related_to(object)) {
      continue;
    }
    if (can_add_reference(objects) && object->can_add_reference(objects)) {
      cross_referencing(object);
      ret = true;
    }
  }
  return ret;
}

bool
dependent_object::
is_related_to(object_ptr_t& object) {
  return detect_collision(object);
}

void
dependent_object::
cross_referencing(object_ptr_t& object) {
  overwirte_referene(object.get());
  object->overwirte_referene(this);
}

bool
dependent_object::
detect_collision(object_ptr_t& object) {
  return
    inner().detect_collision(object->inner()) &&
    object->inner().detect_collision(inner());
}

void
dependent_object::
start_simuration() {
  auto local = make_outer();
  outer() = local;
}

void
dependent_object::
stop_simuration() {
  outer() = inner();
}

void
dependent_object::
destory_simuration() {
  stop_simuration();
  clear_reference();
}



region::track_box&
dependent_object::
inner() { return self_.inner(); }

region::track_box&
dependent_object::
outer() { return self_.outer(); }


Define_Property(bool, dependent_object, is_certain_count,
{ return object_info_.is_certain_count; },
{ return object_info_.is_certain_count = value; })

Define_Property(bool, dependent_object, is_certain_distance,
{ return object_info_.is_certain_distance; },
{ return object_info_.is_certain_distance = value; })

Define_Property(bool, dependent_object, is_certain_probability,
{ return object_info_.is_certain_probability; },
{ return object_info_.is_certain_probability = value; })

Define_Property(bool, dependent_object, is_confirmed,
{ return object_info_.is_confirmed; },
{ return object_info_.is_confirmed = value; })

Define_Property(bool, dependent_object, is_valid_move_direction,
{ return object_info_.is_valid_move_direction; },
{ return object_info_.is_valid_move_direction = value; })

Define_Property(bool, dependent_object, is_stationary,
{ return object_info_.is_stationary; },
{ return object_info_.is_stationary = value; })

Define_Property(bool, dependent_object, can_show,
{ return object_info_.can_show; },
{ return object_info_.can_show = value; })

Define_Property(bool, dependent_object, can_alert,
{ return object_info_.can_alert; },
{ return object_info_.can_alert = value; })

Define_Property(bool, dependent_object, should_alert,
{ return object_info_.should_alert; },
{ return object_info_.should_alert = value; })

Define_Property(bool, dependent_object, is_unchecked,
{ return alert_info_.is_unchecked; },
{ return alert_info_.is_unchecked = value; })

Define_Property(bool, dependent_object, is_alerted,
{ return alert_info_.is_alerted; },
{ return alert_info_.is_alerted = value; })

Define_Property(bool, dependent_object, is_notifiable,
{ return alert_info_.is_notifiable; },
{ return alert_info_.is_notifiable = value; })

Define_Property(dependent_object::alert_info::detection_state, dependent_object, state,
{ return alert_info_.state; },
{ return alert_info_.state = value; })

Define_Property(std::chrono::time_point<std::chrono::system_clock>, dependent_object, detection_time,
{ return alert_info_.detection_time; },
{ return alert_info_.detection_time = value; })


Define_Property(region::track_box, dependent_object, _outer,
{ return self_.Outer; },
{ return self_.Outer = value; })

Define_Property(region::track_box, dependent_object, _inner,
{ return self_.Inner; },
{ return self_.Inner = value; })

void
dependent_object::
set_properties() {
  IsCertainCount(this);
  IsCertain_Distance(this);
  IsCertainProbability(this);
  IsConfirmed(this);
  IsValidMoveDirection(this);
  IsStationary(this);
  CanShow(this);
  CanAlert(this);
  ShouldAlert(this);
  isUnChecked(this);
  IsAlerted(this);
  IsNotifiable(this);
  DetectionTime(this);
  Outer(this);
  Inner(this);
  State(this);
}


}

namespace dnn {

std::tstring
to_tstring(dependent_object::appearance_property prop) {
  switch (prop) {
  case dependent_object::appearance_property::real:
    return _T("real");
  case dependent_object::appearance_property::simulate:
    return _T("simulate");
  case dependent_object::appearance_property::unknown:
    return _T("unknown");
  }
  return _T("unknown");
}

dependent_object::appearance_property
to_appearance_property(const std::tstring& prop) {

  if (prop.find(_T("real")) != prop.npos) {
    return dependent_object::appearance_property::real;
  }
  if (prop.find(_T("simulate")) != prop.npos) {
    return dependent_object::appearance_property::simulate;
  }
  if (prop.find(_T("unknown")) != prop.npos) {
    return dependent_object::appearance_property::unknown;
  }
  return dependent_object::appearance_property::unknown;
}


}

