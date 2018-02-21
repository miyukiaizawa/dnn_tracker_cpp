#include "dnn_tracker_cpp/object/parent_object.h"
#include "dnn_tracker_cpp/object/dependent_object_ptrs.h"

namespace dnn {

parent_object::
parent_object(bool _can_has_children) :
  dependent_object(),
  can_has_children_(_can_has_children) {}

parent_object::
parent_object(region::track_box box, bool _can_has_children) :
  dependent_object(box),
  can_has_children_(_can_has_children) {}

parent_object::
parent_object(region::inclusive_box box, bool _can_has_children) :
  dependent_object(box),
  can_has_children_(_can_has_children) {}

parent_object::
~parent_object() {}


region::track_boxes&
parent_object::
children() {
  return children_;
}

bool
parent_object::
should_ignore() {
  return false;
}

bool
parent_object::
find_reference(object_ptrs_t& objects,
               object_ptr_t& obj) {
  if (children().empty()) {
    return false;
  }

  object_ptrs_t::iterator it;
  bool ret = false;
  for (auto& child : children()) {
    if (objects.find(child, it)) {
      ret = true;
      obj = *it;
      break;
    }
  }
  return ret;

  return false;
}

bool
parent_object::
can_add_reference(object_ptrs_t& objects) {
  remove_unvalid_reference(objects);
  return children().empty() || can_has_children();
}

bool
parent_object::
overwirte_referene(dependent_object* object) {
  region::track_boxes::iterator it;
  if (children().find(object->inner(), it)) {
    *it = object->inner();
    return true;
  }
  else {
    children().push_back(object->inner());
    return true;
  }
  return false;
}

bool
parent_object::
remove_unvalid_reference(object_ptrs_t& objects) {
  if (children().empty()) {
    return false;
  }
  bool ret = false;
  for (auto child = children_.begin(); child != children_.end();) {
    object_ptrs_t::iterator it;
    if (!objects.find(*child, it)) {
      child = children_.erase(child);
      ret = true;
    }
    else {
      ++child;
    }
  }
  return ret;
}

void
parent_object::
erase_reference(object_ptr_t& object) {
  region::track_boxes::iterator it;
  if (children().find(object->inner(), it)) {
    children().erase(it);
  }
}

region::track_box
parent_object::
make_outer() {
#if 0
  track_box box = inner();
  for (auto& child : children()) {
    box.merge(child);
  }
  return box;
#endif
  return inner();
}

void parent_object::
clear_reference() {
  children().resize(0);
}

bool
parent_object::
can_has_children() {
  return can_has_children_;
}

std::tstring
make_children_names(parent_object& parent, object_names& object_names, bool show_details) {
  std::tstringstream tss;
  for (auto& child : parent.children()) {
    object_names::name_t child_name;
    if (!object_names.get(child.current_pos(), child_name)) {
      continue;
    }

    tss << child_name << _T(" ");

    if (show_details) {
      tss << _T("[No.") << child.TrackId << _T("] ");
    }
  }
  return tss.str();
}

parent_object_ptr
to_parent_object(dependent_object_ptr object) {
  return std::dynamic_pointer_cast<parent_object>(object);
}

bool
is_parent_object(dependent_object_ptr object) {
  return (to_parent_object(object) != nullptr);
}

}
