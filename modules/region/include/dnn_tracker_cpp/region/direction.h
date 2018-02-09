#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_REGION_DIRECTION_H__
#define __DNN_TRACKER_CPP_REGION_REGION_DIRECTION_H__
#include "dnn_tracker_cpp/core.h"

namespace dnn {
namespace region {

class direction {
public:
  using state_t = int;
  enum class state : state_t {
    stop = 0x0010,
    up = 0x0100,
    down = 0x0200,
    left = 0x1000,
    right = 0x2000,
    ignore = 0x0000,
    none = 0x0000
  };

public:
  DNNTRR_API direction();
  DNNTRR_API direction(state_t _state);
  DNNTRR_API direction(state _state);
  DNNTRR_API direction(const direction& dir);
  DNNTRR_API direction(cv::Point first_pos, cv::Point current_pos);

  DNNTRR_API state_t operator()() const;
  DNNTRR_API void operator=(state_t v);
  DNNTRR_API state& operator =(const state& v);
  DNNTRR_API state& operator |=(const state& v);
  DNNTRR_API direction& operator |=(const direction& v);
  DNNTRR_API state& operator &=(const state& v);
  DNNTRR_API direction& operator &=(const direction& v);
  DNNTRR_API bool operator ==(const state& v);
  DNNTRR_API bool operator ==(const direction& v);

protected:
  DNNTRR_API state calc_direction(cv::Point first_pt, cv::Point currnt_pt);

private:
  state state_;

};

DNNTRR_API direction::state operator &(const direction& v1, const direction::state& v2);
DNNTRR_API direction::state operator |(const direction& v1, const direction::state& v2);
DNNTRR_API direction operator &(const direction& v1, const direction& v2);
DNNTRR_API direction operator |(const direction& v1, const direction& v2);

}
}

#endif //__DNN_TRACKER_CPP_REGION_REGION_DIRECTION_H__
