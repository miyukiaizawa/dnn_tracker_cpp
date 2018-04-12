#include "dnn_tracker_cpp/target/target_direction.h"

namespace dnn {

target_direction::
target_direction() :
  up(),
  left(),
  right(),
  down(),
  stop() {}

target_direction::
target_direction(const direction_info& _up,
                 const direction_info& _left,
                 const direction_info& _down,
                 const direction_info& _right,
                 const direction_info& _stop) :
  up(_up),
  left(_left),
  right(_right),
  down(_down),
  stop(_stop) {}

bool
target_direction::
valid_direction(region::direction dir) const {
  bool dst = false;

  using state = region::direction::state;

  auto vstate = dir & state::vand;
  auto hstate = dir & state::hand;

  dst |= (up.is_valid) && (vstate == state::up);

  dst |= (down.is_valid) && (vstate == state::down);

  dst |= (left.is_valid) && (hstate == state::left);

  dst |= (right.is_valid) && (hstate == state::right);

  dst |= (stop.is_valid) && ((hstate == state::hstop) && (vstate == state::vstop));

  return dst;
}

}

