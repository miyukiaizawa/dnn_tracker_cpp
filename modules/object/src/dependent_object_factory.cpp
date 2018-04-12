#include "dnn_tracker_cpp/object/dependent_object_factory.h"
#include "dnn_tracker_cpp/object/dependent_object.h"
#include "dnn_tracker_cpp/object/dependent_object_ptrs.h"
#include "dnn_tracker_cpp/object/child_object.h"
#include "dnn_tracker_cpp/object/parent_object.h"

namespace dnn {

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

dependent_object_ptr
dependent_object_factory::
generate(const region::boundary_box &box,
         const object_names& object_names,
         const target_objects& targets) {

  object_names::name_t name;
  if (!object_names.get(box(), name)) {
    return nullptr;
  }

  target_object target;
  if (!targets.find(name, target)) {
    return nullptr;
  }
  auto collision = target.collision();
  auto trackbox = region::track_box(box, region::collision_generator::generate(collision));
  return generate(trackbox, object_names, targets);
}

dependent_object_ptr
dependent_object_factory::
generate(const region::track_box &box,
         const object_names& object_names,
         const target_objects& targets) {

  object_names::name_t name;
  if (!object_names.get(box()(), name)) {
    return nullptr;
  }

  target_object target;
  if (!targets.find(name, target)) {
    return nullptr;
  }

  dependent_object_ptr object = nullptr;
  if (target.dependency == dependency_state::child) {
    object = std::make_shared<child_object>(box);
  }
  else if (target.dependency == dependency_state::parent) {
    object = std::make_shared<parent_object>(box, target.can_has_children);
  }
  else if (target.dependency == dependency_state::none) {
    //@todo
    object = std::make_shared<child_object>(box);
  }

  return object;
}

}
