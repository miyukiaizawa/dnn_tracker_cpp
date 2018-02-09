#ifndef __DNN_TRACKER_CPP_TARGET_DETECTIONG_TARGET_H__
#define __DNN_TRACKER_CPP_TARGET_DETECTIONG_TARGET_H__

#include "dnn_tracker_cpp/region.h"
#include "dnn_tracker_cpp/target/target_direction.h"

namespace dnn {

enum class dependency_state;

struct target_object {
  DNNTRR_API target_object();
  DNNTRR_API target_object(
    std::tstring _object_name,
    std::tstring _print_name,
    cv::Scalar _draw_color,
    bool _show_info,
    bool _can_alert,
    dependency_state _dependency,
    region::collision_preset _collision,
    int _count_of_appearance,
    double _distance,
    target_direction _direction,
    double _probability,
    bool _can_has_children,
    bool _erase_low_probability_objects);

  std::tstring object_name;
  std::tstring print_name;
  cv::Scalar draw_color;
  bool show_info;
  bool can_alert;
  dependency_state dependency;
  region::collision_preset collision;
  int count_of_appearance;
  double distance;
  target_direction direction;
  double probability;
  bool can_has_children;
  bool erase_low_probability_objects;
};

}

namespace dnn {

class target_objects {
public:
  using target_objects_t = std::vector<target_object>;
  using iterator = target_objects_t::iterator;
  using const_iterator = target_objects_t::const_iterator;

  DNNTRR_API target_objects();
  DNNTRR_API target_objects(const target_objects& objects);
  DNNTRR_API target_objects& operator=(const target_objects& objects);
  DNNTRR_API target_object& operator[](int index);
  DNNTRR_API target_objects_t& operator()();

  DNNTRR_API iterator begin() noexcept;
  DNNTRR_API const_iterator begin() const noexcept;
  DNNTRR_API iterator end() noexcept;
  DNNTRR_API const_iterator end() const noexcept;
  DNNTRR_API const_iterator find(const std::tstring& obj_name) const;
  DNNTRR_API bool find(const std::tstring& obj_name, target_object& dst) const;

  DNNTRR_API void push_back(target_object obj);
  DNNTRR_API void clear();
  DNNTRR_API void resize(size_t size);
  DNNTRR_API size_t size() const;
  DNNTRR_API bool empty() const;

private:
  target_objects_t data_;
};

}

namespace dnn {

DNNTRR_API
bool
find_target_object(const target_objects& targets,
                        const std::tstring& obj_name,
                        target_object& dst);

}


#endif //__DNN_TRACKER_CPP_TARGET_DETECTIONG_TARGET_H__
