#ifndef __DNN_TRACKER_CPP_TARGET_TARGET_DIRECTION_H__
#define __DNN_TRACKER_CPP_TARGET_TARGET_DIRECTION_H__

#include "dnn_tracker_cpp/region.h"

namespace dnn {
class target_direction {
public:

  DNNTRR_API target_direction();

  DNNTRR_API target_direction(bool _up,
                              bool _left,
                              bool _down,
                              bool _right,
                              bool _stop);

  DNNTRR_API target_direction(region::direction dir);

  DNNTRR_API bool valid_direction(region::direction dir) const;

public:
  bool up;
  bool left;
  bool down;
  bool right;
  bool stop;
};

}


namespace dnn {

DNNTRR_API target_direction
to_target_direction(const std::tstring& str);

DNNTRR_API target_direction
to_target_direction(bool up, bool down, bool left, bool right, bool stop);

}

#endif //__DNN_TRACKER_CPP_TARGET_TARGET_DIRECTION_H__
