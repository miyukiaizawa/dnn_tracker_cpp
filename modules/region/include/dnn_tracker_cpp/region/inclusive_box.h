#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_INCLUSIVE_BOX_H__
#define __DNN_TRACKER_CPP_REGION_INCLUSIVE_BOX_H__
#include "dnn_tracker_cpp/region/track_box.h"

namespace dnn {
namespace region {

class inclusive_box {
public:
  DNNTRR_API inclusive_box();
  DNNTRR_API inclusive_box(track_box& _inner);
  DNNTRR_API inclusive_box(track_box& _inner, track_box& _outer);

  DNNTRR_API track_box& inner();
  DNNTRR_API track_box& outer();

  DNNTRR_API void set_as_outer(track_box& box);

  DNNTRR_API void reset_outer();

public: //property
  Declear_Properties(track_box, inclusive_box, _outer, Outer);
  Declear_Properties(track_box, inclusive_box, _inner, Inner);

  DNNTRR_API void set_properties();

private:
  track_box inner_;
  track_box outer_;
};

}
}


#endif //__DNN_TRACKER_CPP_REGION_INCLUSIVE_BOX_H__
