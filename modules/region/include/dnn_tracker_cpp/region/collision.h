#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_COLLISION_H__
#define __DNN_TRACKER_CPP_REGION_COLLISION_H__
#include "dnn_tracker_cpp/core.h"

namespace dnn {
namespace region {

class collision {
public:
  enum class state {
    greater,
    less,
    ignore,
    any,
    none
  };

public:
  DNNTRR_API collision();
  DNNTRR_API collision(state _left, state _top, state _right, state _bottom);

  DNNTRR_API bool detect(int sx1, int sy1, int ex1, int ey1, int sx2, int sy2, int ex2, int ey2);
  DNNTRR_API bool detect(cv::Rect r1, cv::Rect r2);
  DNNTRR_API bool detect(cv::Point sp1, cv::Point ep1, cv::Point sp2, cv::Point ep2);

private:
  bool greater(int v1, int v2);
  bool less(int v1, int v2);
  bool check_gather_or_less(state& state, int v1, int v2);

public:
  state left;
  state top;
  state right;
  state bottom;
};

}

namespace region {

DNNTRR_API std::tstring to_tstring(const collision::state& state);

DNNTRR_API collision::state to_collision(const std::tstring & state);

}
}

#endif //__DNN_TRACKER_CPP_REGION_COLLISION_H__
