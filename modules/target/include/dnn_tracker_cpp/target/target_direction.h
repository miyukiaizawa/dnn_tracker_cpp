#ifndef __DNN_TRACKER_CPP_TARGET_TARGET_DIRECTION_H__
#define __DNN_TRACKER_CPP_TARGET_TARGET_DIRECTION_H__

#include "dnn_tracker_cpp/region.h"

namespace dnn {

struct direction_info {
  direction_info() :
    is_valid(false),
    message() {}

  direction_info(bool _is_valid,
                 const std::tstring& _message) :
    is_valid(_is_valid),
    message(_message) {}

  bool is_valid;
  std::tstring message;
};

class target_direction {
public:

  DNNTRR_API target_direction();

  DNNTRR_API target_direction(const direction_info& _up,
                              const direction_info&_left,
                              const direction_info& _down,
                              const direction_info& _right,
                              const direction_info& _stop);

  DNNTRR_API bool valid_direction(region::direction dir) const;

public:
  direction_info up;
  direction_info left;
  direction_info down;
  direction_info right;
  direction_info stop;
};

}



#endif //__DNN_TRACKER_CPP_TARGET_TARGET_DIRECTION_H__
