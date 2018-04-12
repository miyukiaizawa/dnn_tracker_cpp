#include "dnn_tracker_cpp/detector/dependent_object_tracker.h"

namespace dnn {

static
void
sepalete_objects(
  dependent_object_ptrs& objects,
  dependent_object_ptrs& children,
  dependent_object_ptrs& parents) {

  for (auto& object : objects) {
    auto child = dynamic_cast<child_object*>(object.get());
    if (child != nullptr) {
      children.push_back(object);
    }
    auto parent = dynamic_cast<parent_object*>(object.get());
    if (parent != nullptr) {
      parents.push_back(object);
    }
  }
}

}

namespace dnn {

dependent_object_ptrs&
dependent_object_tracker::
tracking(const region::boundary_boxes &boxes,
       const object_names& object_names,
       const target_objects& targets) {
  update_inneres(boxes, object_names, targets);
  update_references();
  update_outeres();
  return objects;
}

void
dependent_object_tracker::
erase_not_found_objects(const region::boundary_boxes &boxes) {
  region::boundary_boxes::const_iterator it;
  utils::erase_if(objects,
                  [&boxes](dependent_object_ptr& obj) {

    auto it = utils::find_if(boxes,
                             [&obj](const region::boundary_box& box) {
      return obj->inner()().is_same_id(box);
    });
    return (it == boxes.end());
  });
}


bool
dependent_object_tracker::
override_object(const region::boundary_box& box) {
  if (objects.empty()) {
    return false;
  }

  auto it = utils::find_if(objects, [&box](const dependent_object_ptr& obj) {
    return obj->inner()().is_same_id(box);
  });
  if (it == objects.end()) {
    return false;
  }

  (*it)->inner().update(box);
  return true;
}

bool
dependent_object_tracker::
push_back_new_object(const region::boundary_box& box,
                     const object_names& object_names,
                     const target_objects& targets) {
  auto new_obj = dependent_object_factory::generate(box, object_names, targets);
  if (new_obj != nullptr) {
    objects.push_back(new_obj);
    return true;
  }
  return false;
}

void
dependent_object_tracker::
update_inneres(const region::boundary_boxes& boxes,
               const object_names& object_names,
               const target_objects& targets) {

  erase_not_found_objects(boxes);

  for (auto& box : boxes) {
    if (override_object(box)) {
      continue;
    }
    if (!push_back_new_object(box, object_names, targets)) {
      //error
    }
  }
}

void
dependent_object_tracker::
update_references() {
  dependent_object_ptrs children, parents;
  sepalete_objects(objects, children, parents);

  for (auto& child : children) {
    child->remove_unvalid_reference(parents);
  }
  for (auto& parent : parents) {
    parent->remove_unvalid_reference(children);
  }

  for (auto& child : children) {
    child->update_outer(parents);
  }
  for (auto& parent : parents) {
    parent->update_outer(children);
  }
}

void
dependent_object_tracker::
update_outeres() {
  for (auto& object : objects) {
    object->switch_simuration();
  }
}

}