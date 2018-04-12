#ifndef __DNN_TRACKER_CPP_TARGET_DETECTIONG_TARGET_H__
#define __DNN_TRACKER_CPP_TARGET_DETECTIONG_TARGET_H__

#include "dnn_tracker_cpp/region.h"
#include "dnn_tracker_cpp/target/target_direction.h"
#include "dnn_tracker_cpp/core/rw_property.h"

namespace dnn {

enum class dependency_state;


class target_object {
public:

  struct draw_info {
    DNNTRR_API draw_info();
    DNNTRR_API draw_info(cv::Scalar _draw_color,
                         bool _show_info);
    cv::Scalar draw_color;
    bool show_info;
  };

  struct message_info {
    DNNTRR_API message_info();
    DNNTRR_API message_info(std::tstring _print_name,
                            std::tstring _message,
                            int _count_of_notify);
    std::tstring print_name;
    std::tstring message;
    int count_of_notify;
  };

  struct object_info {
    DNNTRR_API object_info();
    DNNTRR_API object_info(std::tstring object_name,
                           int _count_of_appearance,
                           double _distance,
                           target_direction _direction,
                           bool _can_alert,
                           double _probability,
                           bool _erase_low_probability_objects);

    std::tstring object_name;
    int count_of_appearance;
    double distance;
    target_direction direction;
    bool can_alert;
    double probability;
    bool erase_low_probability_objects;
  };

  struct dependency_info {
    DNNTRR_API dependency_info();
    DNNTRR_API dependency_info(dependency_state _dependency,
                               region::collision_preset _collision,
                               bool _can_has_children);

    dependency_state dependency;
    region::collision_preset collision;
    bool can_has_children;
  };

  DNNTRR_API target_object();
  DNNTRR_API target_object(object_info _object_info,
                           draw_info _draw_info,
                           message_info _message_info,
                           dependency_info _dependency_info);

  DNNTRR_API target_object(const target_object& object);
  DNNTRR_API target_object& operator = (const target_object& object);

public: //property
  Declear_Properties(cv::Scalar, target_object, _draw_color, draw_color);
  Declear_Properties(bool, target_object, _show_info, show_info);
  Declear_Properties(std::tstring, target_object, _print_name, print_name);
  Declear_Properties(std::tstring, target_object, _message, message);
  Declear_Properties(int, target_object, _count_of_notify, count_of_notify);
  Declear_Properties(std::tstring, target_object, _object_name, object_name);
  Declear_Properties(int, target_object, _count_of_appearance, count_of_appearance);
  Declear_Properties(double, target_object, _distance, distance);
  Declear_Properties(target_direction, target_object, _direction, direction);
  Declear_Properties(bool, target_object, _can_alert, can_alert);
  Declear_Properties(double, target_object, _probability, probability);
  Declear_Properties(bool, target_object, _erase_low_probability_objects, erase_low_probability_objects);
  Declear_Properties(dependency_state, target_object, _dependency, dependency);
  Declear_Properties(region::collision_preset, target_object, _collision, collision);
  Declear_Properties(bool, target_object, _can_has_children, can_has_children);

private:
  void set_properties();

private:
  object_info object_info_;
  draw_info draw_info_;
  message_info message_info_;
  dependency_info dependency_info_;
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
