#include "dnn_tracker_cpp/object/child_object.h"
#include "dnn_tracker_cpp/object/parent_object.h"
#include "dnn_tracker_cpp/object/dependent_object_ptrs.h"
#include "dnn_tracker_cpp/target/target_object.h"
#include "dnn_tracker_cpp/object/dependent_object_factory.h"
#include <algorithm>

namespace dnn {

static
void
sepalete_objects(
  dependent_object_ptrs::objects_t& objects,
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

static
auto
find_object(dependent_object_ptrs& objects,
            const dependent_object_ptr& object) {
  return std::find_if(objects.begin(),
                      objects.end(),
                      [&object](dependent_object_ptr& obj) {
    return object->inner().is_same_id(obj->inner());
  });
}

static
auto
find_object(const dependent_object_ptrs& objects,
            const dependent_object_ptr& object) {
  return std::find_if(objects.begin(),
                      objects.end(),
                      [&object](const dependent_object_ptr& obj) {
    return object->inner().is_same_id(obj->inner());
  });
}

static
bool
find_object(dependent_object_ptrs& objects,
            dependent_object_ptr& object,
            dependent_object_ptrs::iterator& it) {
  it = find_object(objects, object);
  return (it != objects.end());
}

static
bool
find_object(const dependent_object_ptrs& objects,
            const dependent_object_ptr& object,
            dependent_object_ptrs::const_iterator& it) {
  it = find_object(objects, object);
  return (it != objects.end());
}


static
auto
find_object(dependent_object_ptrs& objects,
            const region::track_box& object) {
  return std::find_if(objects.begin(),
                      objects.end(),
                      [&object](dependent_object_ptr& obj) {
    return object.is_same_id(obj->inner());
  });
}

static
auto
find_object(const dependent_object_ptrs& objects,
            const region::track_box& object) {
  return std::find_if(objects.begin(),
                      objects.end(),
                      [&object](const dependent_object_ptr& obj) {
    return object.is_same_id(obj->inner());
  });
}

static
bool
find_object(dependent_object_ptrs& objects,
            const region::track_box& object,
            dependent_object_ptrs::iterator& it) {
  it = find_object(objects, object);
  return (it != objects.end());
}

static
bool
find_object(const dependent_object_ptrs& objects,
            const region::track_box& object,
            dependent_object_ptrs::const_iterator& it) {
  it = find_object(objects, object);
  return (it != objects.end());
}

}

namespace dnn {

dependent_object_ptrs::
dependent_object_ptrs() :
  objects_() {}

dependent_object_ptrs::
dependent_object_ptrs(const dependent_object_ptrs& ptrs) :
  objects_() {
  if (ptrs.empty()) {
    return;
  }
  for (auto& ptr : ptrs) {
    objects_.push_back(ptr);
  }
}

dependent_object_ptrs&
dependent_object_ptrs::
operator=(const dependent_object_ptrs& ptrs) {
  objects_.clear();
  for (auto& ptr : ptrs) {
    objects_.push_back(ptr);
  }
  return (*this);
}

dependent_object_ptrs::iterator
dependent_object_ptrs::
begin() { return objects_.begin(); }

dependent_object_ptrs::const_iterator
dependent_object_ptrs::
begin() const { return objects_.begin(); }

dependent_object_ptrs::iterator
dependent_object_ptrs::
end() { return objects_.end(); }

dependent_object_ptrs::const_iterator
dependent_object_ptrs::
end() const { return objects_.end(); }

dependent_object_ptrs::iterator
dependent_object_ptrs::
find(const dependent_object_ptr obj) {
  return find_object(*this, obj);
}

dependent_object_ptrs::const_iterator
dependent_object_ptrs::
find(const dependent_object_ptr obj) const {
  return find_object(*this, obj);
}

dependent_object_ptrs::iterator
dependent_object_ptrs::
find(const region::track_box box) {
  return find_object(*this, box);
}

dependent_object_ptrs::const_iterator
dependent_object_ptrs::
find(const region::track_box box) const {
  return find_object(*this, box);
}

bool
dependent_object_ptrs::
find(const dependent_object_ptr obj, iterator& it) {
  return find_object(*this, obj, it);
}

bool
dependent_object_ptrs::
find(const dependent_object_ptr obj, const_iterator& it) const {
  return find_object(*this, obj, it);
}

bool
dependent_object_ptrs::
find(const region::track_box box, iterator& it) {
  return find_object(*this, box, it);
}

bool
dependent_object_ptrs::
find(const region::track_box box, const_iterator& it) const {
  return find_object(*this, box, it);
}

void
dependent_object_ptrs::
push_back(dependent_object_ptr& obj) {
  objects_.push_back(obj);
}

dependent_object_ptrs::iterator
dependent_object_ptrs::
erase(iterator &it) {
  return objects_.erase(it);
}

void
dependent_object_ptrs::
resize(size_t size) {
  return objects_.resize(size);
}

size_t
dependent_object_ptrs::
size() const {
  return objects_.size();
}

bool
dependent_object_ptrs::
empty() const {
  return objects_.empty();
}

#if 0
void
dependent_object_ptrs::
update(const region::boundary_boxes &boxes,
       const object_names& object_names,
       const target_objects& targets) {
  update_inneres(boxes, object_names, targets);
  update_references();
  update_outeres();
}

void
dependent_object_ptrs::
erase_not_found_objects(const region::boundary_boxes &boxes) {
  region::boundary_boxes::const_iterator it;
  utils::erase_if(objects_,
                  [&boxes](dependent_object_ptr& obj) {

    auto it = utils::find_if(boxes,
                             [&obj](const region::boundary_box& box) {
      return obj->inner()().is_same_id(box);
    });
    return (it == boxes.end());
  });
}


bool
dependent_object_ptrs::
override_object(const region::boundary_box& box) {
  if (objects_.empty()) {
    return false;
  }

  auto it = utils::find_if(objects_, [&box](const dependent_object_ptr& obj) {
    return obj->inner()().is_same_id(box);
  });
  if (it == objects_.end()) {
    return false;
  }

  (*it)->inner().update(box);
  return true;
}

bool
dependent_object_ptrs::
push_back_new_object(const region::boundary_box& box,
                     const object_names& object_names,
                     const target_objects& targets) {
  auto new_obj = dependent_object_factory::generate(box, object_names, targets);
  if (new_obj != nullptr) {
    push_back(new_obj);
    return true;
  }
  return false;
}

void
dependent_object_ptrs::
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
dependent_object_ptrs::
update_references() {
  dependent_object_ptrs children, parents;
  sepalete_objects(objects_, children, parents);
  for (auto& child : children) {
    child->update_outer(parents);
  }
  for (auto& parent : parents) {
    parent->update_outer(children);
  }
}

void
dependent_object_ptrs::
update_outeres() {
  for (auto& object : objects_) {
    object->switch_simuration();
  }
}
#endif

}

