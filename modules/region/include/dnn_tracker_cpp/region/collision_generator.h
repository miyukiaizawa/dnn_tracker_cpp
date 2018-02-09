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
  within_horicontal,
  convex,
  concavity,
  none
};

class collision_generator {
public:
  DNNTRR_API static collision generate(collision_preset& _preset);
};

//any
DNNTRR_API collision any_collision();

//Å†:should be set to parent object (car)
DNNTRR_API collision contain_collision();

//=
DNNTRR_API collision within_vertical_collision();

//||
DNNTRR_API collision within_horizontal_collision();

//ì :should be set to parent object (bicycle) or (motorbike)
DNNTRR_API collision convex_collision();

//âö
DNNTRR_API collision concavity_collision();

}

namespace region {

DNNTRR_API region::collision_preset
to_collision_preset(const std::tstring& str);

}
}

#endif //__DNN_TRACKER_CPP_REGION_COLLISION_GENERATOR_H__
