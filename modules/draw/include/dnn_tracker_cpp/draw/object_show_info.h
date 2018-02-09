#pragma once
#ifndef __DNN_TRACKER_CPP_DRAW_OBJECT_SHOW_INFO_H__
#define __DNN_TRACKER_CPP_DRAW_OBJECT_SHOW_INFO_H__
#include "dnn_tracker_cpp/object.h"

namespace dnn {

class object_show_info {
public:
  DNNTRR_API object_show_info(dependent_object_ptr& obj, object_names& obj_names);

private:
  void make_messages(dependent_object_ptr& obj, object_names& obj_names);
  void make_object_name(region::boundary_box& inner, object_names& obj_names, bool is_certain_count);
  void make_count_info(region::boundary_box& inner);
  void make_dependency(dependent_object_ptr& obj, object_names& obj_names);


public:
  std::tstring obj_name;
  std::tstring count;
  std::tstring dependency;
  const std::vector<std::tstring*> strings;
};

}

#endif //__DNN_TRACKER_CPP_DRAW_OBJECT_SHOW_INFO_H__
