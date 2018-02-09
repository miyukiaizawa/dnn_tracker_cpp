#ifndef __DNN_TRACKER_CPP_TARGET_TARGET_OBJECT_JUDGEMENTER_H__
#define __DNN_TRACKER_CPP_TARGET_TARGET_OBJECT_JUDGEMENTER_H__

#include "dnn_tracker_cpp/region.h"
#include "dnn_tracker_cpp/target.h"
#include "dnn_tracker_cpp/object.h"

namespace dnn {

class target_object_judgementer {
public:

  DNNTRR_API target_object_judgementer(region::distance _max_distance,
                                       double _min_distance_th = 5);

  DNNTRR_API target_object_judgementer(target_objects _targets,
                                       region::distance _max_distance,
                                       double _min_distance_th = 5);

  DNNTRR_API bool find_target_object(const std::tstring& obj_name,
                                     target_object& dst);

  DNNTRR_API bool is_certain_probability(dependent_object_ptr& object,
                                         const target_object& target);

  DNNTRR_API bool is_certain_count_of_apperance(dependent_object_ptr& object,
                                                const target_object& target);

  DNNTRR_API bool is_certain_move_distance(dependent_object_ptr& object,
                                           const target_object& target);

  DNNTRR_API bool is_stationary_object(dependent_object_ptr& object,
                                       const target_object& target);

  DNNTRR_API bool is_valid_move_direction(dependent_object_ptr& object,
                                          const target_object& target);

  DNNTRR_API bool judge_detection_targets(dependent_object_ptrs& objects,
                                          const object_names& _object_names);

  DNNTRR_API bool judge_detection_target(dependent_object_ptr& object,
                                         const object_names& _object_names);

  DNNTRR_API target_objects& targets();
  DNNTRR_API const target_objects& targets() const;
  DNNTRR_API void targets(const target_objects& _targets);

  DNNTRR_API target_direction& direction();
  DNNTRR_API const target_direction& direction() const;

  DNNTRR_API region::distance max_distance();
  DNNTRR_API const region::distance max_distance() const;
  DNNTRR_API void max_distance(const region::distance& distance);


private:
  target_objects targets_;
  target_direction target_direction_;
  region::distance target_distance_;
  region::distance max_distance_;
  region::distance min_distance_;
  double min_distance_th_;
};

}






#endif //__DNN_TRACKER_CPP_TARGET_TARGET_OBJECT_JUDGEMENTER_H__
