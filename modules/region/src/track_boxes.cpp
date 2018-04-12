#include "dnn_tracker_cpp/region/track_boxes.h"
#include <algorithm>

namespace dnn {
namespace region {

static
track_boxes::const_iterator
find_if(const track_boxes& objects,
        const track_box& object) {
  return std::find_if(objects.begin(),
                      objects.end(),
                      [&object](const region::track_box& obj) {
    return object.is_same_id(obj);
  });
}

static
track_boxes::iterator
find_if(region::track_boxes& objects,
        const region::track_box& object) {
  return std::find_if(objects.begin(),
                      objects.end(),
                      [&object](region::track_box& obj) {
    return object.is_same_id(obj);
  });
}


static
bool
find_if(const region::track_boxes& objects,
        const region::track_box& object,
        region::track_boxes::const_iterator& it) {
  it = find_if(objects, object);
  return (it != objects.end());
}

static
bool
find_if(region::track_boxes& objects,
        region::track_box& object,
        region::track_boxes::iterator& it) {
  it = std::find_if(objects.begin(),
                    objects.end(),
                    [&object](region::track_box& obj) {
    return object.is_same_id(obj);
  });
  return (it != objects.end());
}

}

namespace region {

track_boxes::
track_boxes() :
  boxes_() {}

track_boxes::boxes_t&
track_boxes::
operator()() {
  return boxes_;
}

track_box&
track_boxes::
operator[](int index) {
  return boxes_[index];
}

track_boxes::iterator
track_boxes::
begin() {
  return boxes_.begin();
}

track_boxes::const_iterator
track_boxes::
begin() const {
  return boxes_.begin();
}

track_boxes::iterator
track_boxes::
end() {
  return boxes_.end();
}

track_boxes::const_iterator
track_boxes::
end() const {
  return boxes_.end();
}

void
track_boxes::
push_back(track_box& box) {
  boxes_.push_back(box);
}

void
track_boxes::
clear() {
  boxes_.clear();
}

void
track_boxes::
resize(size_t size) {
  boxes_.resize(size);
}


track_boxes::iterator
track_boxes::
erase(iterator it) {
  return boxes_.erase(it);
}

bool
track_boxes::
empty() {
  return boxes_.empty();
}

track_boxes::iterator
track_boxes::
find(const region::track_box& object) {
  return find_if(*this, object);
}

track_boxes::const_iterator
track_boxes::
find(const region::track_box& object) const {
  return find_if(*this, object);
}

bool
track_boxes::
find(const region::track_box& object,
     iterator& it) {
  return find_if(*this, object, it);
}

bool
track_boxes::
find(const region::track_box& object,
     const_iterator& it) const {
  return find_if(*this, object, it);
}

}
}