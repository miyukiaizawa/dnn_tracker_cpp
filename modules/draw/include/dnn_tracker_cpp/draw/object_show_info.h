#pragma once
#ifndef __DNN_TRACKER_CPP_DRAW_OBJECT_SHOW_INFO_H__
#define __DNN_TRACKER_CPP_DRAW_OBJECT_SHOW_INFO_H__
#include "dnn_tracker_cpp/object.h"

namespace dnn {

class object_show_info {
public:
  DNNTRR_API object_show_info(const dependent_object_ptr& obj, 
                              const object_names& obj_names, 
                              bool show_details = false);

private:
  void make_messages(const dependent_object_ptr& obj, 
                     const object_names& obj_names, 
                     bool show_details = false);

  void make_object_name(const dependent_object_ptr& obj, 
                        const object_names& obj_names, 
                        bool show_details = false);

  void make_count_info(const region::boundary_box& inner);

  void make_dependency(const dependent_object_ptr& obj, 
                       const object_names& obj_names, 
                       bool show_details = true);


public:
  std::tstring obj_name;
  std::tstring count;
  std::tstring dependency;
  const std::vector<std::tstring*> strings;
};

}

#endif //__DNN_TRACKER_CPP_DRAW_OBJECT_SHOW_INFO_H__
