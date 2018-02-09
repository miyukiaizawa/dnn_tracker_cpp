#include "dnn_tracker_cpp/region/collision_generator.h"

namespace dnn {
namespace region {

collision
collision_generator::
generate(collision_preset& _preset) {
  switch (_preset) {
  case collision_preset::any:
    return any_collision();
  case collision_preset::contain:
    return contain_collision();
  case collision_preset::within_vertical:
    return within_vertical_collision();
  case collision_preset::within_horicontal:
    return within_horizontal_collision();
  case collision_preset::convex:
    return convex_collision();
  case collision_preset::concavity:
    return concavity_collision();
  }
  return any_collision();
}

}

namespace region {

collision_preset
to_collision_preset(const std::tstring& str) {
  if (str.find(_T("any")) != str.npos) {
    return collision_preset::any;
  }
  if (str.find(_T("concavity")) != str.npos) {
    return collision_preset::concavity;
  }
  if (str.find(_T("contain")) != str.npos) {
    return collision_preset::contain;
  }
  if (str.find(_T("convex")) != str.npos) {
    return collision_preset::convex;
  }
  if (str.find(_T("none")) != str.npos) {
    return collision_preset::none;
  }
  if (str.find(_T("within_horicontal")) != str.npos) {
    return collision_preset::within_horicontal;
  }
  if (str.find(_T("within_vertical")) != str.npos) {
    return collision_preset::within_vertical;
  }
  return collision_preset::none;
}

}
}