#include "dnn_tracker_cpp/object/child_object.h"
#include "dnn_tracker_cpp/object/dependent_object_ptrs.h"

namespace dnn {

child_object::
child_object() : dependent_object() {}

child_object::
child_object(region::track_box box) : dependent_object(box) {}

child_object::
child_object(region::inclusive_box box) : dependent_object(box) {}

child_object::
~child_object() {}

region::track_box&
child_object::
parent() {
  return parent_;
}

bool
child_object::
should_ignore() {
  return (appearance() == appearance_property::simulate) && !parent().empty();
}

bool
child_object::
find_reference(object_ptrs_t& objects,
               object_ptr_t& obj) {
  object_ptrs_t::iterator it;
  if (!parent().empty() && objects.find(parent(), it)) {
    obj = *it;
    return true;
  }
  return false;
}

bool
child_object::
can_add_reference(object_ptrs_t& objects) {
  remove_unvalid_reference(objects);
  return parent_.empty();
}

bool
child_object::
overwirte_referene(dependent_object* object) {
  parent() = object->inner();
  return true;
}

bool
child_object::
remove_unvalid_reference(object_ptrs_t& objects) {

  if (parent().empty()) {
    return false;
  }
  object_ptrs_t::iterator it;
  if (!objects.find(parent(), it)) {
    parent_.clear();
    return true;
  }
  return false;
}

void
child_object::
erase_reference(object_ptr_t& object) {
  parent().clear();
}

region::track_box
child_object::
make_outer() {
  //return parent();
  region::track_box box = inner();
  box().ObjectId = parent()().ObjectId;
  box().TrackId = parent()().TrackId;
  return box;
}

void
child_object::
clear_reference() {
  parent().clear();
}

std::tstring
make_parent_name(child_object& child, object_names& object_names, bool show_details) {
  std::tstringstream tss;
  object_names::name_t parent_name;
  if (object_names.get(child.parent().current_pos(), parent_name)) {

    tss << parent_name << _T(" ");
    
    if (show_details) {
      tss << _T("[No.") << child.parent().TrackId << _T("]");
    }
  }
  return tss.str();
}

child_object_ptr
to_child_object(dependent_object_ptr object) {
  return std::dynamic_pointer_cast<child_object>(object);
}

bool
is_child_object(dependent_object_ptr object) {
  return (to_child_object(object) != nullptr);
}

}
