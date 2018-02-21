#pragma once
#ifndef __DNN_TRACKER_CPP_OBJECT_DEPENDENT_OBJECT_H__
#define __DNN_TRACKER_CPP_OBJECT_DEPENDENT_OBJECT_H__
#include "dnn_tracker_cpp/region.h"
#include "dnn_tracker_cpp/object/object_names.h"

//define
namespace dnn {
class dependent_object;
using dependent_object_ptr = std::shared_ptr<dependent_object>;
class dependent_object_ptrs;
}

//dependent_object
namespace dnn {

class dependent_object {
public:
  using object_ptrs_t = typename dependent_object_ptrs;
  using object_ptr_t = dependent_object_ptr;

  enum class appearance_property {
    real,    //show inner box as outer
    simulate,//show parent or children box as outer
    unknown
  };

  struct object_info {
    DNNTRR_API object_info();
    bool is_certain_count;//���̃J�E���g����
    bool is_certain_distance;//���̈ړ�������
    bool is_confirmed; //�m�肵����
    bool is_valid_move_direction;//�L���Ȉړ�������
    bool can_show;//�\���ł��邩
    bool can_alert; //�x���ł��邩
    bool should_alert; //�x���Ώۂ�
    bool is_stationary; //�Î~���Ă��邩
  };

  struct alert_info {
    enum class detection_state {
      none, firsttime, continuation
    };

    DNNTRR_API alert_info();
    bool is_unchecked;//����̌��o��
    bool is_alerted;//���o�ς݂�
    std::chrono::time_point<std::chrono::system_clock> detection_time; //���o�m�莞��
    detection_state state; //���o���
  };

public:
  DNNTRR_API dependent_object();
  DNNTRR_API dependent_object(region::track_box box);
  DNNTRR_API dependent_object(region::inclusive_box box);
  DNNTRR_API virtual ~dependent_object();

  DNNTRR_API region::track_box& inner();
  DNNTRR_API region::track_box& outer();

  //virtual track_box& parent() = 0;
  //virtual track_boxes& children() = 0;
  DNNTRR_API bool update_inner(region::track_boxes& boxes);
  DNNTRR_API bool update_outer(object_ptrs_t& objects);
  DNNTRR_API void switch_simuration();
  DNNTRR_API appearance_property appearance() {
    return appearance_;
  }
  DNNTRR_API void appearance(appearance_property prop) {
    appearance_ = prop;
  }
  DNNTRR_API virtual bool should_ignore() = 0;


protected:

  DNNTRR_API bool update_reference(object_ptrs_t& objects);
  DNNTRR_API bool update_current_reference(object_ptrs_t& boxes);
  DNNTRR_API bool find_new_reference(object_ptrs_t& objects);
  DNNTRR_API bool is_related_to(object_ptr_t& object);
  DNNTRR_API void cross_referencing(object_ptr_t& object);
  DNNTRR_API void start_simuration();
  DNNTRR_API void stop_simuration();
  DNNTRR_API void destory_simuration();

  DNNTRR_API bool detect_collision(object_ptr_t& object);

  DNNTRR_API virtual bool find_reference(object_ptrs_t& objects,
                              object_ptr_t& obj) = 0;
  DNNTRR_API virtual bool can_add_reference(object_ptrs_t& objects) = 0;
  DNNTRR_API virtual bool overwirte_referene(dependent_object* object) = 0;
  DNNTRR_API virtual bool remove_unvalid_reference(object_ptrs_t& objects) = 0;
  DNNTRR_API virtual void erase_reference(object_ptr_t& object) = 0;
  DNNTRR_API virtual region::track_box make_outer() = 0;
  DNNTRR_API virtual void clear_reference() = 0;

public: //property

  Declear_Properties(bool, dependent_object, is_certain_count, IsCertainCount);
  Declear_Properties(bool, dependent_object, is_certain_distance, IsCertain_Distance);
  Declear_Properties(bool, dependent_object, is_confirmed, IsConfirmed);
  Declear_Properties(bool, dependent_object, is_valid_move_direction, IsValidMoveDirection);
  Declear_Properties(bool, dependent_object, is_stationary, IsStationary);
  Declear_Properties(bool, dependent_object, can_show, CanShow);
  Declear_Properties(bool, dependent_object, can_alert, CanAlert);
  Declear_Properties(bool, dependent_object, should_alert, ShouldAlert);
  Declear_Properties(bool, dependent_object, is_unchecked, isUnChecked);
  Declear_Properties(bool, dependent_object, is_alerted, IsAlerted);
  Declear_Properties(alert_info::detection_state, dependent_object, state, State);
  Declear_Properties(std::chrono::time_point<std::chrono::system_clock>, dependent_object, detection_time, DetectionTime);

  Declear_Properties(region::track_box, dependent_object, _outer, Outer);
  Declear_Properties(region::track_box, dependent_object, _inner, Inner);

private:
  void set_properties();

private:
  object_info object_info_;
  alert_info alert_info_;
  region::inclusive_box self_;
  appearance_property appearance_;
};

}

namespace dnn {

std::tstring
DNNTRR_API to_tstring(dependent_object::appearance_property prop);

dependent_object::appearance_property
DNNTRR_API to_appearance_property(const std::tstring& prop);


}


#endif //__DEPENDENT_OBJECT_H__
