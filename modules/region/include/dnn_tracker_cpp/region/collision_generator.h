#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_COLLISION_GENERATOR_H__
#define __DNN_TRACKER_CPP_REGION_COLLISION_GENERATOR_H__

#include "dnn_tracker_cpp/region/collision.h"

namespace dnn {
namespace region {

enum class collision_preset {
  any,
  contain,
  within_vertical,
  within_horizontal,
  convex,
  convex_or_within_horizontal,
  concavity,
  none
};

class collision_generator {
public:
  DNNTRR_API static collision generate(collision_preset& _preset);
};

//any
DNNTRR_API collision any_collision();

//□:should be set to parent object (car)
DNNTRR_API collision contain_collision();

//=
DNNTRR_API collision within_vertical_collision();

//||
DNNTRR_API collision within_horizontal_collision();

//凸:should be set to parent object (bicycle) or (motorbike)
DNNTRR_API collision convex_collision();

//for bycycle
DNNTRR_API collision convex_or_within_horizontal_collision();

//凹
DNNTRR_API collision concavity_collision();

}

namespace region {

DNNTRR_API region::collision_preset
to_collision_preset(const std::tstring& str);

}
}

#endif //__DNN_TRACKER_CPP_REGION_COLLISION_GENERATOR_H__
