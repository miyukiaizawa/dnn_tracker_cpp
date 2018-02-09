#pragma once
#include "object_names.h"

#ifndef __DNN_TRACKER_CPP_OBJECT_OBJECT_NAMES_IMPL_H__
#define __DNN_TRACKER_CPP_OBJECT_OBJECT_NAMES_IMPL_H__

namespace dnn {

template<class _Elem, class _Traits>
inline
object_names_<_Elem, _Traits>::
object_names_() :
  no_name(),
  names_() {}

template<class _Elem, class _Traits>
inline
object_names_<_Elem, _Traits>::
object_names_(const name_list_t& _names) :
  no_name(),
  names_(_names) {}

template<class _Elem, class _Traits>
inline
object_names_<_Elem, _Traits>::
object_names_(const path_t& _path) {
  load(_path);
}

template<class _Elem, class _Traits>
inline
size_t
object_names_<_Elem, _Traits>::
size() const {
  return names_.size();
}

template<class _Elem, class _Traits>
inline
const typename object_names_<_Elem, _Traits>::name_t&
object_names_<_Elem, _Traits>::
operator[](int index) const {
  return get(index);
}

template<class _Elem, class _Traits>
inline
const typename object_names_<_Elem, _Traits>::name_t&
object_names_<_Elem, _Traits>::
operator[](const region::boundary_box& box) const {
  return get(box);
}

template<class _Elem, class _Traits>
inline
const typename object_names_<_Elem, _Traits>::name_t&
object_names_<_Elem, _Traits>::
operator[](const region::track_box& box) const {
  return get(box);
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
operator()(int index, name_t &name) const {
  return get(index, name);
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
operator()(const region::boundary_box& box, name_t &name) const {
  return get(box(), name);
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
operator()(const region::track_box& box, name_t &name) const {
  return get(box(), name);
}

template<class _Elem, class _Traits>
inline
const typename object_names_<_Elem, _Traits>::name_t&
object_names_<_Elem, _Traits>::
get(int index) const {
  return names_[index];
}

template<class _Elem, class _Traits>
inline
const typename object_names_<_Elem, _Traits>::name_t&
object_names_<_Elem, _Traits>::
get(const region::boundary_box& box) const {
  if (utils::in_range((int)box.ObjectId, -1, (int)size())) {
    return names_[box.ObjectId];
  }
  return no_name;
}

template<class _Elem, class _Traits>
inline
const typename object_names_<_Elem, _Traits>::name_t&
object_names_<_Elem, _Traits>::
get(const region::track_box& box) const {
  return get(box());
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
get(int index, name_t &name) const {
  name.resize(0);
  name = get(index);
  return !name.empty();
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
get(const region::boundary_box& box, name_t &name) const {
  return get(box.ObjectId, name);
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
get(const region::track_box& box, name_t &name) const {
  return get(box(), name);
}

template<class _Elem, class _Traits>
inline
typename object_names_<_Elem, _Traits>::iterator
object_names_<_Elem, _Traits>::
begin() {
  return names_.begin();
}

template<class _Elem, class _Traits>
inline
typename object_names_<_Elem, _Traits>::const_iterator
object_names_<_Elem, _Traits>::
begin() const {
  return names_.begin();
}

template<class _Elem, class _Traits>
inline
typename object_names_<_Elem, _Traits>::iterator
object_names_<_Elem, _Traits>::
end() {
  return names_.end();
}

template<class _Elem, class _Traits>
inline
typename object_names_<_Elem, _Traits>::const_iterator
object_names_<_Elem, _Traits>::
end() const {
  return names_.end();
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
empty() const {
  return names_.empty();
}

template<class _Elem, class _Traits>
inline
void
object_names_<_Elem, _Traits>::
push_back(name_t &name) {
  names_.push_back(name);
}

template<class _Elem, class _Traits>
inline
bool
object_names_<_Elem, _Traits>::
load(const path_t& _path) {

  std::tifstream file(_path);
  if (!file.is_open()) {
    return false;
  }

  for (std::tstring line; getline(file, line);) {
    names_.push_back(line);
  }

  return (!empty());
}

}

#endif //__OBJECT_NAMES_IMPLE_H__

