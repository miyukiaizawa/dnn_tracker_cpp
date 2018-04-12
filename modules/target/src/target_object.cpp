#include "dnn_tracker_cpp/target/target_object.h"
#include "dnn_tracker_cpp/object.h"

namespace dnn {

target_object::
draw_info::
draw_info() :
  draw_color(),
  show_info(false) {}

target_object::
draw_info::
draw_info(cv::Scalar _draw_color,
          bool _show_info) :
  draw_color(_draw_color),
  show_info(_show_info) {}
}

namespace dnn {

target_object::
message_info::
message_info() :
  print_name(),
  message(),
  count_of_notify(0) {}

target_object::
message_info::
message_info(std::tstring _print_name,
             std::tstring _message,
             int _count_of_notify) :
  print_name(_print_name),
  message(_message),
  count_of_notify(_count_of_notify) {}

}

namespace dnn {

target_object::
object_info::
object_info() :
  object_name(),
  count_of_appearance(0),
  distance(),
  direction(),
  can_alert(false),
  probability(0),
  erase_low_probability_objects(false) {}

target_object::
object_info::
object_info(std::tstring _object_name,
            int _count_of_appearance,
            double _distance,
            target_direction _direction,
            bool _can_alert,
            double _probability,
            bool _erase_low_probability_objects) :
  object_name(_object_name),
  count_of_appearance(_count_of_appearance),
  distance(_distance),
  direction(_direction),
  can_alert(_can_alert),
  probability(_probability),
  erase_low_probability_objects(_erase_low_probability_objects) {}

}

namespace dnn {

target_object::
dependency_info::
dependency_info() :
  dependency(),
  collision(),
  can_has_children() {}

target_object::
dependency_info::
dependency_info(dependency_state _dependency,
                region::collision_preset _collision,
                bool _can_has_children) :
  dependency(_dependency),
  collision(_collision),
  can_has_children(_can_has_children) {}

}

namespace dnn {

target_object::
target_object() :
  object_info_(),
  draw_info_(),
  message_info_(),
  dependency_info_() {
  set_properties();
}

target_object::
target_object(object_info _object_info,
              draw_info _draw_info,
              message_info _message_info,
              dependency_info _dependency_info) :
  object_info_(_object_info),
  draw_info_(_draw_info),
  message_info_(_message_info),
  dependency_info_(_dependency_info) {
  set_properties();
}

target_object::
target_object(const target_object& object) :
  object_info_(object.object_info_),
  draw_info_(object.draw_info_),
  message_info_(object.message_info_),
  dependency_info_(object.dependency_info_) {
  set_properties();
}

target_object&
target_object::
operator = (const target_object& object) {
  object_info_ = object.object_info_;
  draw_info_ = object.draw_info_;
  message_info_ = object.message_info_;
  dependency_info_ = object.dependency_info_;
  set_properties();
  return (*this);
}


void
target_object::
set_properties() {
  draw_color(this);
  show_info(this);
  print_name(this);
  message(this);
  count_of_notify(this);
  object_name(this);
  count_of_appearance(this);
  distance(this);
  direction(this);
  can_alert(this);
  probability(this);
  erase_low_probability_objects(this);
  dependency(this);
  collision(this);
  can_has_children(this);
}

Define_Property(cv::Scalar, target_object, _draw_color,
{ return draw_info_.draw_color; },
{ return draw_info_.draw_color = value; });

Define_Property(bool, target_object, _show_info,
{ return draw_info_.show_info; },
{ return draw_info_.show_info = value; });

Define_Property(std::tstring, target_object, _print_name,
{ return message_info_.print_name; },
{ return message_info_.print_name = value; });

Define_Property(std::tstring, target_object, _message,
{ return message_info_.message; },
{ return message_info_.message = value; });

Define_Property(int, target_object, _count_of_notify,
{ return message_info_.count_of_notify; },
{ return message_info_.count_of_notify = value; });

Define_Property(std::tstring, target_object, _object_name,
{ return object_info_.object_name; },
{ return object_info_.object_name = value; });

Define_Property(int, target_object, _count_of_appearance,
{ return object_info_.count_of_appearance; },
{ return object_info_.count_of_appearance = value; });

Define_Property(double, target_object, _distance,
{ return object_info_.distance; },
{ return object_info_.distance = value; });

Define_Property(target_direction, target_object, _direction,
{ return object_info_.direction; },
{ return object_info_.direction = value; });

Define_Property(bool, target_object, _can_alert,
{ return object_info_.can_alert; },
{ return object_info_.can_alert = value; });

Define_Property(double, target_object, _probability,
{ return object_info_.probability; },
{ return object_info_.probability = value; });

Define_Property(bool, target_object, _erase_low_probability_objects,
{ return object_info_.erase_low_probability_objects; },
{ return object_info_.erase_low_probability_objects = value; });

Define_Property(dependency_state, target_object, _dependency,
{ return dependency_info_.dependency; },
{ return dependency_info_.dependency = value; });

Define_Property(region::collision_preset, target_object, _collision,
{ return dependency_info_.collision; },
{ return dependency_info_.collision = value; });

Define_Property(bool, target_object, _can_has_children,
{ return dependency_info_.can_has_children; },
{ return dependency_info_.can_has_children = value; });


}


namespace dnn {

target_objects::
target_objects() :
  data_() {}

target_objects::
target_objects(const target_objects& objects) {
  data_ = objects.data_;
}

target_objects&
target_objects::
operator=(const target_objects& objects) {
  data_ = objects.data_;
  return (*this);
}

target_object&
target_objects::
operator[](int index) {
  return data_[index];
}

target_objects::target_objects_t&
target_objects::
operator()() {
  return data_;
}

target_objects::iterator
target_objects::
begin() noexcept {
  return data_.begin();
}

target_objects::const_iterator
target_objects::
begin() const noexcept {
  return data_.begin();
}

target_objects::iterator
target_objects::
end() noexcept {
  return data_.end();
}

target_objects::const_iterator
target_objects::
end() const noexcept {
  return data_.end();
}

target_objects::const_iterator
target_objects::
find(const std::tstring& obj_name) const {
  return std::find_if(begin(), end(), [&obj_name](const target_object& obj) {
    return (obj.object_name().find(obj_name) != std::tstring::npos);
  });
}

bool
target_objects::
find(const std::tstring& obj_name,
     target_object& dst) const {
  auto target = find(obj_name);
  if (target == end()) {
    return false;
  }
  dst = *target;
  return true;
}


void
target_objects::
push_back(target_object obj) {
  data_.push_back(obj);
}

void
target_objects::
clear() {
  data_.clear();
}

void
target_objects::
resize(size_t size) {
  data_.resize(size);
}

size_t
target_objects::
size() const {
  return data_.size();
}

bool
target_objects::
empty() const {
  return data_.empty();
}

}

namespace dnn {

static
dependency_state
to_dependency_state(const std::tstring& str) {
  if (str.find(_T("parent")) != str.npos) {
    return dependency_state::parent;
  }
  if (str.find(_T("child")) != str.npos) {
    return dependency_state::child;
  }
  return dependency_state::none;
}

}

namespace dnn {

bool find_target_object(const target_objects& targets,
                        const std::tstring& obj_name,
                        target_object& dst) {

  auto target = targets.find(obj_name);
  if (target == targets.end()) {
    return false;
  }
  dst = *target;
  return true;
}

}