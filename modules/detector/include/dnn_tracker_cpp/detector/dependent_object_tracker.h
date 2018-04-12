#pragma once
#ifndef __DNN_TRACKER_CPP_DEPENDENT_OBJECT_TRACKER_H__
#define __DNN_TRACKER_CPP_DEPENDENT_OBJECT_TRACKER_H__
#include "dnn_tracker_cpp/object/dependent_object_ptrs.h"
#include "dnn_tracker_cpp/target.h"

namespace dnn {

class dependent_object_tracker {
public:
  DNNTRR_API dependent_object_ptrs&
    tracking(const region::boundary_boxes &boxes,
             const object_names& object_names,
             const target_objects& targets);

private:
  void erase_not_found_objects(const region::boundary_boxes &boxes);
  bool override_object(const region::boundary_box& box);
  bool push_back_new_object(const region::boundary_box& box,
                            const object_names& object_names,
                            const target_objects& targets);

  void update_inneres(const region::boundary_boxes &boxes,
                      const object_names& object_names,
                      const target_objects& targets);

  void update_references();

  void update_outeres();

public:
  dependent_object_ptrs objects;
};

}


#endif //__DNN_TRACKER_CPP_DEPENDENT_OBJECT_TRACKER_H__
