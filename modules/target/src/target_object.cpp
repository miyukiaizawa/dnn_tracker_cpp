#include "dnn_tracker_cpp/target/target_object.h"
#include "dnn_tracker_cpp/object.h"

namespace dnn {

target_object::
target_object() :
  object_name(),
  print_name(),
  draw_color(0, 0, 0),
  show_info(true),
  can_alert(true),
  dependency(dependency_state::child),
  collision(region::collision_preset::any),
  count_of_appearance(5),
  distance(10),
  direction(true, true, true, true, true),
  probability(20),
  can_has_children(false),
  erase_low_probability_objects(false) {}

target_object::
target_object(std::tstring _object_name,
              std::tstring _print_name,
              cv::Scalar _draw_color,
              bool _show_info,
              bool _can_alert,
              dependency_state _dependency,
              region::collision_preset _collision,
              int _count_of_appearance,
              double _distance,
              target_direction _direction,
              double _probability,
              bool _can_has_children,
              bool _erase_low_probability_objects) :
  object_name(_object_name),
  print_name(_print_name),
  draw_color(_draw_color),
  show_info(_show_info),
  can_alert(_can_alert),
  dependency(_dependency),
  collision(_collision),
  count_of_appearance(_count_of_appearance),
  distance(_distance),
  direction(_direction),
  probability(_probability),
  can_has_children(_can_has_children),
  erase_low_probability_objects(_erase_low_probability_objects) {}
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
    return (obj.object_name.find(obj_name) != std::tstring::npos);
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