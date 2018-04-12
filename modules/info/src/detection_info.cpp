#include "dnn_tracker_cpp/info/detection_info.h"

namespace dnn {

detection_info::
detection_info() :
  last_update_tp(),
  boxes(),
  detected(false) {}

detection_info::
detection_info(dependent_object_ptrs _boxes,
               std::chrono::time_point<std::chrono::system_clock> time,
               bool _detected) :
  last_update_tp(time),
  boxes(_boxes),
  detected(_detected) {}

}
