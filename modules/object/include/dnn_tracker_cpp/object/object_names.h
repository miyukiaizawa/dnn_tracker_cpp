#pragma once
#ifndef __DNN_TRACKER_CPP_OBJECT_OBJECT_NAMES_H__
#define __DNN_TRACKER_CPP_OBJECT_OBJECT_NAMES_H__
#include "dnn_tracker_cpp/region.h"
#include "dnn_tracker_cpp/core/utils.h"

namespace dnn {

template<class _Elem, class _Traits = std::char_traits<_Elem>>
class object_names_ {
public:
  using name_t = typename std::basic_string<_Elem, std::char_traits<_Elem>>;
  using path_t = typename name_t;
  using name_list_t = typename std::vector<name_t>;
  using value_type = typename std::vector<name_t>::value_type;
  using iterator = typename name_list_t::iterator;
  using const_iterator = typename name_list_t::const_iterator;

  object_names_();
  object_names_(const name_list_t& _names);
  object_names_(const path_t& _path);
  object_names_(const object_names_& _names) {
    names_.clear();
    for (auto& name : _names) {
      names_.push_back(name);
    }
  }
  object_names_& operator = (const object_names_& _names) {
    names_.clear();
    for (auto& name : _names) {
      names_.push_back(name);
    }
    return (*this);
  }

  const name_t& operator[](int index) const;
  const name_t& operator[](const region::boundary_box& box) const;
  const name_t& operator[](const region::track_box& box) const;

  bool operator()(int index, name_t &name) const;
  bool operator()(const region::boundary_box& box, name_t &name) const;
  bool operator()(const region::track_box& box, name_t &name) const;

  const name_t& get(int index) const;
  const name_t& get(const region::boundary_box& box) const;
  const name_t& get(const region::track_box& box) const;

  bool get(int index, name_t &name) const;
  bool get(const region::boundary_box& box, name_t &name) const;
  bool get(const region::track_box& box, name_t &name) const;

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

  bool empty() const;

  void push_back(name_t &name);

  size_t size() const;

  bool load(const path_t& _path);

private:
  const name_t no_name;
  name_list_t names_;
};

using object_names = object_names_<tchar, std::char_traits<tchar>>;

}

#include "object_names_impl.h"

#endif //__OBJECT_NAMES_H__
