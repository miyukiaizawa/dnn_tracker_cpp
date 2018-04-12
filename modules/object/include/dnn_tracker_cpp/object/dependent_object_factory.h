#pragma once
#ifndef __DNN_TRACKER_CPP_OBJECT_DEPENDENT_OBJECT_FACTORY_H__
#define __DNN_TRACKER_CPP_OBJECT_DEPENDENT_OBJECT_FACTORY_H__

#include "dnn_tracker_cpp/target.h"
#include "dnn_tracker_cpp/object/dependent_object_ptrs.h"

namespace dnn {

enum class dependency_state {
  child,
  parent,
  none
};

DNNTRR_API dependency_state to_dependency_state(const std::tstring& str);

}

namespace dnn {

class dependent_object_factory {
public:
  DNNTRR_API dependent_object_factory() {}

  DNNTRR_API static dependent_object_ptr generate(const region::boundary_box &box,
                                       const object_names& object_names,
                                       const target_objects& targets);

  DNNTRR_API static dependent_object_ptr generate(const region::track_box &box,
                                       const object_names& object_names,
                                       const target_objects& targets);

};

}


#endif // !__DEPENDENT_OBJECT_FACTORY_H__
